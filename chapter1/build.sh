#!/bin/bash

BUILD_PROG=$1
CC_FILE=$BUILD_PROG.cc
BUILD_DIR=./build/$BUILD_PROG
docker container run --rm -v "$(pwd)":/Source trhoangtuan96/cpp9-build:latest g++ -o $BUILD_DIR $CC_FILE
