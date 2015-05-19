#!/bin/bash

echo "Building graph and zero engines ..."

cd C++/ganitagraph
mkdir build
cd build
cmake ../config
make
sudo make install
cd ../../../

cd C++/ganitazero
mkdir build
cd build
cmake ../config
make
sudo make install

cd ../../../
echo "Finished build of GRAPH."
