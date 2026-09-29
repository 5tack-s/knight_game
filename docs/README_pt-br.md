[![en](https://img.shields.io/badge/lang-en-green)](../README.md)

# knight_game

Jogo simples de coleta de moedas criado com SDL3.

## Dependências
* SDL3
* SDL3_image
* SDL3_ttf
* SDL3_mixer

Instaladas automaticamente a partir do arquivo `CMakeLists.txt` raiz.

## Compilação

### Requisitos
- CMake 3.X+
- GCC/Clang
- Git

### Compilação para PC
```sh
$ cmake --preset pc
$ cmake --build build
```
O resultado estará em `build/bin/`.

### Web (Emscripten)
#### 1. Instale o Emscripten SDK
```sh
$ git clone https://github.com/emscripten-core/emsdk
$ cd emsdk
$ ./emsdk install latest
$ ./emsdk activate latest
```

#### 2. Ative-o:
```sh
$ source ./emsdk_env.sh
```

Windows:
```
emsdk_env.bat
```

#### 3. Compile:
```sh
$ cmake --preset web
$ cmake --build build-web
```
O resultado estará em `build-web/bin/`.

#### 4. Sirva a pasta de saída
Exemplo:
```sh
$ python -m http.server 8080 -d build-web/bin
```


## Demonstração
https://github.com/user-attachments/assets/cae325a6-eff9-46fd-9810-a25620cece8b