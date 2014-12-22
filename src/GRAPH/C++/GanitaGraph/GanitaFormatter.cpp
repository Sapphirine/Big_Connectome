// g++ -O3 neo4jFormatter.c -o neo4jFormatter -lm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

class Neo4jFormatter
{
private:
  long total;
  vector<string> nodes1;
  vector<string> nodes2;
  string node_csv;
  string rel_csv;
public:
  Neo4jFormatter();
  int readCSV(ifstream myfile);
  long readCSV(char *myfilestr);
  long readCSV(char *myfilestr,char *myfilestr2,char *myfilestr3);
};

Neo4jFormatter::Neo4jFormatter()
{
  total = 0;
  node_csv.assign("nodes.csv");
  rel_csv.assign("rels.csv");
}

int Neo4jFormatter::readCSV(ifstream myfile)
{
  string line;

  if (myfile.is_open())
    {
      while ( getline (myfile,line) )
	{
	  cout << line << '\n';
	}
      myfile.close();
      return 1;
    }
  else cout << "Unable to open file"; 
  return -1;
}

long Neo4jFormatter::readCSV(char *myfilestr)
{
  string line, token[10];
  ifstream myfile(myfilestr);
  vector<string> myvec1;
  vector<long> myrow1;
  vector<string> myvec2;
  vector<long> myrow2;
  long from, to;
  vector<long> counts1;
  vector<long> counts2;
  string tmp1, tmp2;
  long row;
  int ii;
  ofstream myout1(node_csv.c_str());
  ofstream myout2(rel_csv.c_str());

  if((!myout1.is_open()) || (!myout2.is_open())){
    cout<<"Could not open output files!"<<endl;
    return(-1);
  }

  myout1 << "Node" << "\t" << "Id" << "\t" << "Type:string" << endl;
  myout2 << "start" << "\t" << "end" << "\t" << "type" << endl;

  row = 0;
  if (myfile.is_open())
    {
      // read header line
      getline (myfile,line);
      //cout << line << endl;
      while ( getline (myfile,line) )
	{
	  //cout << line << endl;
	  std::istringstream is(line);
	  ii=0;
	  while(std::getline(is, token[ii], '\t')) {
	    //std::cout << token[ii] << '\n';
	    ii++;
	    if(ii >= 10) break;
	  }
	  //cout << "Tokens " << ii << endl;
	  if(ii > 1){
	    for(ii=0; ii<myvec1.size(); ii++){
	      //cout << "Existing vector: " << ii << " " << myvec[ii] << endl;
	      //cout << "Existing token: " << ii << " " << token[0] << endl;
	      if(myvec1[ii].compare(token[0]) == 0){
		counts1[ii]++;
		from = myrow1[ii];
		break;
	      }
	    }
	    //cout << "here" << endl;
	    if(myvec1.size() == 0){
	      myvec1.push_back(token[0]);
	      myrow1.push_back(0);
	      counts1.push_back(1);
	      from = row;
	      myout1 << row << "\t" << token[0] << "\t" << "user" << endl;
	      row++;
	    }
	    //cout << "here 2" << endl;
	    if(ii == myvec1.size()){
	      cout << "Add new element: "<<token[0]<< '\n';
	      myvec1.push_back(token[0]);
	      myrow1.push_back(row);
	      from = row;
	      counts1.push_back(1);
	      myout1 << row << "\t" << token[0] << "\t" << "user" << endl;
	      row++;
	      //cout << "New size: "<<counts.size()<< '\n';
	    }
	    //cout << "here 3" << endl;
	  }
	  for(ii=0; ii<myvec2.size(); ii++){
	    //cout << "Existing vector: " << ii << " " << myvec[ii] << endl;
	    //cout << "Existing token: " << ii << " " << token[1] << endl;
	    if(myvec2[ii].compare(token[1]) == 0){
	      counts2[ii]++;
	      to = myrow2[ii];
	      break;
	    }
	  }
	  //cout << "here" << endl;
	  if(myvec2.size() == 0){
	    myvec2.push_back(token[1]);
	    myrow2.push_back(0);
	    counts2.push_back(1);
	    to = row;
	    myout1 << row << "\t" << token[1] << "\t" << "movie" << endl;
	    row++;
	  }
	  //cout << "here 2" << endl;
	  if(ii == myvec2.size()){
	    cout << "Add new element: "<<token[1]<< '\n';
	    myvec2.push_back(token[1]);
	    myrow2.push_back(row);
	    to = row;
	    counts2.push_back(1);
	    myout1 << row << "\t" << token[1] << "\t" << "movie" << endl;
	    row++;
	    //cout << "New size: "<<counts.size()<< '\n';
	  }
	  cout << from+1 << " --> " << to+1 << endl;
	  myout2 << from+1 << "\t" << to+1 << "\t" << "LIKES" << endl;
	}
      //cout<<"Size of vector: "<<counts.size()<<endl;
      //cl_sizes = counts;
      myfile.close();
      myout1.close();
      myout2.close();
      return row;
    }
  else cout << "Unable to open file" << endl; 
  return -1;
}

long Neo4jFormatter::readCSV(char *myfilestr,char *myfilestr2,char *myfilestr3)
{
  string line, token[10];
  ifstream myfile(myfilestr);
  vector<string> myvec1;
  vector<long> myrow1;
  vector<string> myvec2;
  vector<long> myrow2;
  long from, to;
  vector<long> counts1;
  vector<long> counts2;
  string tmp1, tmp2;
  long row;
  int ii, ntokens;
  ofstream myout1(myfilestr2);
  ofstream myout2(myfilestr3);

  if((!myout1.is_open()) || (!myout2.is_open())){
    cout<<"Could not open output files!"<<endl;
    return(-1);
  }

  row = 0;
  if (myfile.is_open())
    {
      // read header line
      //getline (myfile,line);
      //cout << line << endl;
      while ( getline (myfile,line) )
	{
	  //cout << line << endl;
	  std::istringstream is(line);
	  ii=0;
	  while(std::getline(is, token[ii], '\t')) {
	    //std::cout << token[ii] << '\n';
	    ii++;
	    if(ii >= 10) break;
	  }
	  ntokens = ii;
	  //cout << "Tokens " << ii << endl;
	  if(ntokens > 1){
	    for(ii=0; ii<myvec1.size(); ii++){
	      //cout << "Existing vector: " << ii << " " << myvec[ii] << endl;
	      //cout << "Existing token: " << ii << " " << token[0] << endl;
	      if(myvec1[ii].compare(token[0]) == 0){
		counts1[ii]++;
		from = myrow1[ii];
		break;
	      }
	    }
	    //cout << "here" << endl;
	    if(myvec1.size() == 0){
	      myvec1.push_back(token[0]);
	      myrow1.push_back(0);
	      counts1.push_back(1);
	      from = row;
	      myout1 << "Node" << "\t" << "Id" << "\t" << "Type:string" << endl;
	      if(ntokens > 2){
		myout2 << "start" << "\t" << "end" << "\t" << "type" << "\t" << "tomatoes:byte" << endl;
	      }
	      else {
		myout2 << "start" << "\t" << "end" << "\t" << "type" << endl;
	      }
	      myout1 << row << "\t" << token[0] << "\t" << "user" << endl;
	      row++;
	    }
	    //cout << "here 2" << endl;
	    if(ii == myvec1.size()){
	      cout << "Add new element: "<<token[0]<< '\n';
	      myvec1.push_back(token[0]);
	      myrow1.push_back(row);
	      from = row;
	      counts1.push_back(1);
	      myout1 << row << "\t" << token[0] << "\t" << "user" << endl;
	      row++;
	      //cout << "New size: "<<counts.size()<< '\n';
	    }
	    //cout << "here 3" << endl;
	  }
	  for(ii=0; ii<myvec2.size(); ii++){
	    //cout << "Existing vector: " << ii << " " << myvec[ii] << endl;
	    //cout << "Existing token: " << ii << " " << token[1] << endl;
	    if(myvec2[ii].compare(token[1]) == 0){
	      counts2[ii]++;
	      to = myrow2[ii];
	      break;
	    }
	  }
	  //cout << "here" << endl;
	  if(myvec2.size() == 0){
	    myvec2.push_back(token[1]);
	    myrow2.push_back(0);
	    counts2.push_back(1);
	    to = row;
	    myout1 << row << "\t" << token[1] << "\t" << "movie" << endl;
	    row++;
	  }
	  //cout << "here 2" << endl;
	  if(ii == myvec2.size()){
	    cout << "Add new element: "<<token[1]<< '\n';
	    myvec2.push_back(token[1]);
	    myrow2.push_back(row);
	    to = row;
	    counts2.push_back(1);
	    myout1 << row << "\t" << token[1] << "\t" << "movie" << endl;
	    row++;
	    //cout << "New size: "<<counts.size()<< '\n';
	  }
	  cout << from+1 << " --> " << to+1 << endl;
	  if(ntokens > 2){
	    myout2 << from+1 << "\t" << to+1 << "\t" << "LIKES" << "\t" << token[2] << endl;
	  }
	  else {
	    myout2 << from+1 << "\t" << to+1 << "\t" << "LIKES" << endl;
	  }
	}
      //cout<<"Size of vector: "<<counts.size()<<endl;
      //cl_sizes = counts;
      myfile.close();
      myout1.close();
      myout2.close();
      return row;
    }
  else cout << "Unable to open file" << endl; 
  return -1;
}

