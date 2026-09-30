[![pt-br](https://img.shields.io/badge/lang-pt--br-green)](docs/README_pt-br.md)

# knight_game

Simple coin collecting game made using SDL3.

## Dependencies
* SDL3
* SDL3_image
* SDL3_ttf
* SDL3_mixer

Fetched automatically from root `CMakeLists.txt`

## Building

### Requirements
- CMake 3.X+
- GCC/Clang
- Git

### PC build
```sh
$ cmake --preset pc
$ cmake --build build
```
The output will be in build/bin/

### Web (Emscripten)
#### 1. Install the Emscripten SDK 
```sh
$ git clone https://github.com/emscripten-core/emsdk
$ cd emsdk
$ ./emsdk install latest
$ ./emsdk activate latest
```

#### 2. Activate it:
```sh
$ source ./emsdk_env.sh
```

Windows:
```
emsdk_env.bat
```

#### 3. Build:
```sh
$ cmake --preset web
$ cmake --build build-web
```
The output will be in build-web/bin/

#### 4. Serve the output folder
Example:
```sh
$ python -m http.server 8080 -d build-web/bin
```


## Demo
https://github.com/user-attachments/assets/cae325a6-eff9-46fd-9810-a25620cece8b

## Playable web demo
https://5tack-s.github.io/knight_game/
