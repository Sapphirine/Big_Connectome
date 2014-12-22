#!/bin/bash

echo "Building PREP ..."
echo "Building C programs ..."
cd c/ 
sh ./build.sh
cd ../
echo "Building C++ programs ..."
cd cpp/
sh ./build.sh
cd ../
echo "Building jar file ..."
cd Java/
sh ./build.sh
cd ../
echo "Finished build process on PREP."
