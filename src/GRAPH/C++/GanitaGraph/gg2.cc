// g++ -std=c++11 -O3 gg2.cc -o gg2 -lm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <math.h>

#include "GanitaGraph.cpp"

int main(int argc, char *argv[])
{
  int total = 0;
  int ii;
  GanitaGraph gg;

  if(argc < 3){
    cout<<"Usage: node-file edge-file"<<endl;;
    exit(1);
  }

  //gg.ggInit(argv[1],argv[2],argv[3]);

  gg.readWeightedEdges(argv[1],argv[2]);
  cout<<"Reached end"<<endl;

  //gg.dumpIndices();
  //gg.computeEdges();
  //gg.dumpEdges();
  //gg.dumpRels();

  //gg.setMinTrace(5);
  //gg.recommenderBasic(3,1);

  return(1);
}

