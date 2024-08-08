#!/bin/bash
echo "Cleaning up..."
rm -rf build && rm -rf lib
printf "\n\n"
echo "Building library: "
mkdir build && cd build && cmake .. && make
cd ..
printf "\n\n"
echo "Build successful!"
