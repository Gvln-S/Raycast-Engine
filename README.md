# Gio respira por el culo y cuando se sienta se ahoga
Ola este es motor de renderizado que hice estos dias para que lo usemos de base, librerias de OpenGL,
las otras que van a ver en codigo se pusieron solas pero no son obligatorias:
```c++
#include <ostream>
#include <stdlib.h>
```
compilar en windows con msys64:
```bash
mkdir build
cd build
cmake .. -G "minGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
mingw32-make
.\Raycast-Engine.exe
```

compilar en linux (debian like):
```bash
sudo apt install build-essential cmake

mkdir build
cd build
cmake ..
make
./Raycast-Engine
```

compilar en mac:
```bash
xcode-select --install
brew install cmake

mkdir build
cd build
cmake ..
make
./Raycast-Engine
```

ahí subo unas fotos para que vean como se ve antes de descargarlo:
![photo_one][img/github_one.png]
![photo_two][img/github_two.png]

