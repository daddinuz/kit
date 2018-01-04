#!/usr/bin/env bash

set -e

mkdir build
cd build
cmake ..
make
make test
