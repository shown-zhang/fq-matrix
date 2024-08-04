#!/bin/bash
rm -rf testBuild && rm -rf bin && mkdir testBuild && cd testBuild && cmake .. -DTEST=ON && make
cd ..
