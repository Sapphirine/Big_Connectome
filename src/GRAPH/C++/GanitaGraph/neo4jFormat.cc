// g++ -O3 neo4jFormat.cc -o neo4jFormat -lm
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <math.h>

#include "Neo4jFormatter.cpp"

int main(int argc, char *argv[])
{
  int total = 0;
  int ii;
  Neo4jFormatter *myNeo4j = new Neo4jFormatter;

  if(argc < 2){
    cout<<"Usage: input-file"<<endl;;
    exit(1);
  }
  if(argc > 3){
    myNeo4j->readCSV(argv[1],argv[2],argv[3]);
  }
  else{
    myNeo4j->readCSV(argv[1]);
  }

  exit(1);
}

