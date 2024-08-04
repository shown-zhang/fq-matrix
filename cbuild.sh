#!/bin/bash
rm -rf build && rm -rf lib && mkdir build && cd build && cmake .. && make
cd ..
