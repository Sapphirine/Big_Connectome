#!/bin/bash

cd src/
sh ./build.sh
cd ../
mkdir -p bin/
cp src/PREP/c/h5dump2seq bin/
cp src/PREP/cpp/getKasthuri11 bin/
cp src/FEAT/C++/g3d bin/
cp src/GRAPH/C++/GanitaGraph/ganitaGraph bin/
cp src/GRAPH/C++/GanitaGraph/gg2 bin/
cp src/PREP/Java/GanitaBasic.jar bin/
