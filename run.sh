#!/bin/sh

cmake -B build
cmake --build build
./bin/game-engine
