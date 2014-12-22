// g++ -std=c++11 -O3 ganitaGraph.cc -o ganitaGraph -lm
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

  if(argc < 4){
    cout<<"Usage: input-file node-file edge-file"<<endl;;
    exit(1);
  }
  gg.ggInit(argv[1],argv[2],argv[3]);
  cout<<"Reached end"<<endl;

  //gg.dumpIndices();
  gg.computeEdges();
  //gg.dumpEdges();
  //gg.dumpRels();

  //gg.setMinTrace(5);
  //gg.recommenderBasic(3,1);

  cout<<"Compute common nodes: "<<endl;
  gg.nodeDotProd(0);

  cout<<"Number of recommendations: "<<endl;
  total = gg.returnNumNodes();
  //for(ii=0; ii<total; ii++){
    gg.nodeDotProd2(1,10);
    //}

  return(1);
}

