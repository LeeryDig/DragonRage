#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_s.h>
#include <camera.h>

// #include <src/playerInput/playerInput.cpp>

#include <iostream>
#include <filesystem>
#include <string>

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void calculateFps(GLFWwindow *window);

const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 700;

const string pathToImage = "resource/images/";
string title = "DragonRage";

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

int fps = 0;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    Shader ourShader("resource/texture.vs", "resource/texture.fs");

    float vertices[] = {
        // -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //Front face
        // 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        // 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        // 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        // -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        // -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        // -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, //Back face
        // 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        // 0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        // 0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        // -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        // -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        // -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, //Right face
        // -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        // -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        // -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        // -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        // -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        // 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, //Left face
        // 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        // 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        // 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        // 0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        // 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        // -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //Bottom face
        // 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        // 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        // 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        // -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        // -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // Top face
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, 0.0f),
        glm::vec3(-1.0f, -1.0f, 0.0f),
        // glm::vec3(-3.8f, -2.0f, -12.3f),
        // glm::vec3(2.4f, -0.4f, -3.5f),
        // glm::vec3(-1.7f, 3.0f, -7.5f),
        // glm::vec3(1.3f, -2.0f, -2.5f),
        // glm::vec3(1.5f, 2.0f, -2.5f),
        // glm::vec3(1.5f, 0.2f, -1.5f),
        // glm::vec3(-1.3f, 1.0f, -1.5f)
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    string image = pathToImage + "container.jpg";
    unsigned char *data = stbi_load(image.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    image = pathToImage + "container.png";
    data = stbi_load(image.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    while (!glfwWindowShouldClose(window))
    {
        calculateFps(window);
        processInput(window);

        render();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 3; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void calculateFps(GLFWwindow *window)
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    fps++;
    if (deltaTime >= 1.0 / 30.0)
    {
        std::string FPS = std::to_string((1.0 / deltaTime) * fps);
        std::string ms = std::to_string((deltaTime / fps) * 1000);
        std::string newTitle = title + " FPS:" + FPS + " ms:" + ms;
        glfwSetWindowTitle(window, newTitle.c_str());
        lastFrame = currentFrame;
        fps = 0;
    }
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}