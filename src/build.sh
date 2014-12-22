#!/bin/bash

echo "Project source code for Brain Edge Detection."
echo "Building entire pipeline for Ganita Brain ..."

cd PREP/
sh ./build.sh
cd ../
cd FEAT/
sh ./build.sh
cd ../
cd GRAPH/
sh ./build.sh
cd ../
echo "Finished Ganita Brain build."
