#!/bin/bash
cmake . -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=/home/mihai/Development/cube-engine/Lib/SDL2-2.0.22/


#TO BUILD SDL2
#cmake -S . -B build/debug -G Ninja -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Debug
#cmake --build build/debug --target install


#cmake -S . -B build/release -G Ninja -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Release
#cmake --build build/release--target install


#cmake -S . -B build/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=<path to install>
#cmake --build build/debug


