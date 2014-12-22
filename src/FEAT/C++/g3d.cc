// g++ -std=c++11 -O3 g3d.cc -o g3d -lm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <math.h>

#include "Ganita3D.cpp"

int main(int argc, char *argv[])
{
  int total = 0;
  int ii;
  Ganita3D g3d;
  GanitaImage *sobelG = new GanitaImage();

  if(argc < 3){
    cout<<"Usage: h5dump-file output-basename"<<endl;;
    exit(1);
  }

  g3d.readH5Dump(argv[1], argv[2]);
  g3d.dumpDepth();
  //g3d.dumpPgm(80);
  sobelG = g3d.sobel3D(80,1);
  g3d.dumpStats(2);
  sobelG->binarizeGI(g3d.returnStat(0) + threshg1*g3d.returnStat(1));
  sobelG->dumpPgm();
  //cout<<"Reached end"<<endl;

  return(1);
}

