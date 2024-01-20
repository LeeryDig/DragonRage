# DragonRage
Melhor Engine em produção

## Opcional para MacOS
- homebrew Para facilitar instalações importante

## Gerar uma build MacOS
Se tiver usando o vscode:
- Na aba de "Terminal" selecione: "Configure Default Build Task"
- Selecione a opção de Build "C/C++: clang++"
- Dentro do "tasks.json" na seção "args:[]":
```json
[
"-std=c++17",
"-fdiagnostics-color=always",
"-Wall",
"-g",
"-I${workspaceFolder}/dependencies/include",
"-L${workspaceFolder}/dependencies/library",
"${workspaceFolder}/dependencies/library/libglfw.3.dylib",
"${workspaceFolder}/src/*.cpp",
"${workspaceFolder}/glad.c",
"-o",
"${workspaceFolder}/DragonRage",
"-framework",
"OpenGL",
"-framework",
"Cocoa",
"-framework",
"IOKit",
"-framework",
"CoreVideo",
"-framework",
"CoreFoundation",
"-Wno-deprecated"
]
```
- Depois tente fazer uma build com o comando cmd + shift + B
- Para rodar abra um terminal e coloque o comando $./DragonRage