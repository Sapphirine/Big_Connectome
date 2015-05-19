#!/bin/bash

# download ganitagraph and ganitazero first
cd src/GRAPH/C++/
git clone http://cloud.ganita.org:8083/ganita/ganitagraph.git
git clone http://cloud.ganita.org:8083/ganita/ganitazero.git
cd ../../../

# start the build process
cd src/
sh ./build.sh
cd ../
mkdir -p bin/
cp src/PREP/c/h5dump2seq bin/
cp src/PREP/cpp/getKasthuri11 bin/
cp src/FEAT/C++/g3d bin/
cp src/GRAPH/C++/ganitagraph/build/ganitagraph1 bin/
cp src/GRAPH/C++/ganitagraph/build/ganitagraph2 bin/
cp src/GRAPH/C++/ganitagraph/build/gg3 bin/
cp src/GRAPH/C++/ganitazero/build/gzero bin/
cp src/PREP/Java/GanitaBasic.jar bin/
