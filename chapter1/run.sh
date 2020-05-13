#!/bin/bash

RUN_PROG=$1
docker container run --rm -v "$(pwd)":/Source trhoangtuan96/cpp9-build:latest /bin/bash -c "cd ./build && ./$RUN_PROG"
