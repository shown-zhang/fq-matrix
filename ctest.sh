#!/bin/bash
echo "Running unit tests: FQ_MATRIX_CTEST..."

bash cbuild.sh

printf "\n\n"
echo "Building unit tests: "
mkdir testBuild && cd testBuild && cmake .. -DTEST=ON && make
cd ..

printf "\n\n"
echo "Running unit tests: "
./bin/FQ_MATRIX_CTEST
