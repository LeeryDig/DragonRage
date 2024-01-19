// #include <GLFW/glfw3.h>
// #include <shader/camera.h>
// #include <iostream>
// using namespace std;

// class PlayerInput
// {
// public:
//     const int SCR_WIDTH;
//     const int SCR_HEIGHT;
//     bool firstMouse;

//     PlayerInput(int SCR_WIDTH, int SCR_HEIGHT, bool firstMouse)
//     {
//         SCR_WIDTH = SCR_WIDTH;
//         SCR_HEIGHT = SCR_HEIGHT;
//         firstMouse = firstMouse;
//     }

//     void processInput(GLFWwindow *window, float deltaTime, Camera camera);
//     void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//     void mouse_callback(GLFWwindow *window, double xposIn, double yposIn, Camera camera, float lastX, float lastY);
//     void scroll_callback(GLFWwindow *window, double xoffset, double yoffset, Camera camera);
// };

// void processInput(GLFWwindow *window, float deltaTime, Camera camera)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);

//     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//         camera.ProcessKeyboard(FORWARD, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//         camera.ProcessKeyboard(BACKWARD, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//         camera.ProcessKeyboard(LEFT, deltaTime);
//     if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//         camera.ProcessKeyboard(RIGHT, deltaTime);
// }

// void framebuffer_size_callback(GLFWwindow *window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }

// void mouse_callback(GLFWwindow *window, double xposIn, double yposIn, Camera camera, float lastX, float lastY)
// {
//     PlayerInput() input;
//     lastX = SCR_WIDTH / 2.0f;
//     lastY = SCR_HEIGHT / 2.0f;
//     float xpos = static_cast<float>(xposIn);
//     float ypos = static_cast<float>(yposIn);

//     if (input.firstMouse)
//     {
//         lastX = xpos;
//         lastY = ypos;
//         input.firstMouse = false;
//     }

//     float xoffset = xpos - lastX;
//     float yoffset = lastY - ypos;

//     lastX = xpos;
//     lastY = ypos;

//     camera.ProcessMouseMovement(xoffset, yoffset);
// }

// void scroll_callback(GLFWwindow *window, double xoffset, double yoffset, Camera camera)
// {
//     camera.ProcessMouseScroll(static_cast<float>(yoffset));
// }