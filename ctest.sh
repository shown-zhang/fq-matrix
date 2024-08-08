#!/bin/bash
echo "Running unit tests: FQ_MATRIX_CTEST..."
echo "Cleaning up..."
rm -rf testBuild
rm -rf bin
rm -rf build
rm -rf lib

printf "\n\n"
echo "Building library: "
mkdir build && cd build && cmake .. && make
cd ..

printf "\n\n"
echo "Building unit tests: "
mkdir testBuild && cd testBuild && cmake .. -DTEST=ON && make
cd ..

printf "\n\n"
echo "Running unit tests: "
./bin/FQ_MATRIX_CTEST
