// g++ -O3 ganitaGraph.cc -o ganitaGraph -lm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

class GanitaGraph
{
private:
  long total;
  vector<string> nodes1;
  vector<string> nodes2;
  vector<long> counts1;
  vector<long> counts2;
  vector<long> ti;
  vector<long> ti2;
  vector<long> si;
  string node_csv;
  string rel_csv;
  long *gg_rels;
  long *gg_edges;
  double *gg_edge_property;
  //long *gg_edges2;
  long tv, te;
  int compute_edge_flag;
  vector<long> trace[2];
  long kink;
public:
  GanitaGraph();
  int readCSV(ifstream myfile);
  long readCSV(char *myfilestr);
  long readCSV(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long readWeightedEdges(char *mynodefilestr, char *myedgefilestr);
  long getTotalCSV(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long ggInit(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long ggInitWeighted(char *myfilestr,char *myfilestr2,char *myfilestr3);
  long ggAllocRels(long te);
  long ggAllocWeights(long te);
  long ggDeAlloc(long tv);
  long createEdges(char *myfilestr);
  long createWeightedEdges(char *myfilestr);
  long dumpIndices();
  long computeEdges();
  long dumpEdges();
  long dumpRels();
  long setMinTrace(long len);
  long recommenderBasic(long ncom, long check_4_cycle);
  long checkCycle4(long ncom);
  long nodeDotProd(long nn1, long nn2);
  long nodeDotProd(long nn1);
  long nodeDotProd2(long nn1, long nn2, long tt);
  long nodeDotProd2(long nn1, long tt);
  long returnNumNodes();
};

GanitaGraph::GanitaGraph()
{
  total = 0;
  tv = 0; te = 0;
  compute_edge_flag = 0;
  node_csv.assign("nodes.csv");
  rel_csv.assign("rels.csv");
}

int GanitaGraph::readCSV(ifstream myfile)
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

long GanitaGraph::readCSV(char *myfilestr)
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

long GanitaGraph::readWeightedEdges(char *mynodefilestr, char *myedgefilestr)
{
  string line, token[10];
  long cur_token;
  ifstream mynodefile(mynodefilestr);
  ifstream myedgefile(myedgefilestr);
  long good;
  int ii, jj, ntokens;
  long tk1, tk2;
  char tk3[50];
  double tk4;
  long cur_node;

  tv = 0;
  if(mynodefile.is_open()){
    while ( getline (mynodefile,line) ){
      tv++;
    }
  }
  tv--;
  mynodefile.close();
  ti.resize(tv,0);
  si.resize(tv,0);

  good = 0; total = 0;
  if (myedgefile.is_open())
    {
      /*
       * Get the size of the file
       */
      //myedgefile.seekg(0,std::ios::end);
      //std::streampos length = myedgefile.tellg();
      //myedgefile.seekg(0,std::ios::beg);

      // read header line
      getline (myedgefile,line);
      //cout << line << endl;
      getline (myedgefile,line);
      sscanf(line.c_str(),"%ld %ld %s %lf", &tk1, &tk2, tk3, &tk4);
      //std::istringstream is(line);
      ii = 0; jj = 0;
      // while(std::getline(is, token[ii], ' ')) {
      // 	//std::cout << token[ii] << '\n';
      // 	ii++;
      // 	if(ii >= 10) break;
      // }
      ntokens = 3;
      //cout << "Tokens " << ii << endl;
      if(ntokens > 1){
	//cout<<"Read token: "<<tk1<<endl;
	//cout<<"Read token: "<<token[0]<<" "<<stol(token[0])<<endl;
	cur_token = tk1;
	jj++;
      }
      te = 1;
      while ( getline (myedgefile,line) )
	{
	  //cout << line << endl;
	  sscanf(line.c_str(),"%ld %ld %s %lf", &tk1, &tk2, tk3, &tk4);
	  //std::istringstream is(line);
	  ii=0;
	  // while(std::getline(is, token[ii], ' ')) {
	  //   //std::cout << token[ii] << '\n';
	  //   ii++;
	  //   if(ii >= 10) break;
	  // }
	  ntokens = 3;
	  //cout << "Tokens " << ii << endl;
	  if(ntokens > 1){
	    te++;
	    if(tk1 != cur_token){
	      ti[cur_token-1] = jj;
	      cur_token = tk1;
	      jj = 1;
	    }
	    else jj++;
	  }
	}
      ti[cur_token-1] = jj;
    }

  si[0] = 0;
  for(ii=1; ii<tv; ii++){
    si[ii] = si[ii-1] + ti[ii-1];
  }

  cout<<"Total edges: "<<si[tv-1]+ti[tv-1]<<endl;

  gg_edges = (long *) malloc(sizeof(long)*te);
  if(gg_edges == NULL){
    cout<<"Unable to allocated memory for edges."<<endl;
    return(-1);
  }
  
  gg_edge_property = (double *) malloc(sizeof(double)*te);
  if(gg_edges == NULL){
    cout<<"Unable to allocated memory for edges."<<endl;
    return(-1);
  }
  
  myedgefile.clear();
  myedgefile.seekg(0,std::ios::beg);
 
  // read header line
  getline (myedgefile,line);
  //cout << line << endl;
  for(ii=0; ii<tv; ii++){
    getline (myedgefile,line);
    sscanf(line.c_str(),"%ld %ld %s %lf", &tk1, &tk2, tk3, &tk4);
    //gg_edges[si[tk1]] = tk2;
    cur_node = tk1;
    total += ti[ii];
    //cout<<"Node: "<<tk1<<" Index: "<<ti[cur_node]<<endl;
    for(jj=1; jj<ti[cur_node-1]; jj++){
      getline (myedgefile,line);
      //cout<<line<<endl;
      sscanf(line.c_str(),"%ld %ld %s %lf", &tk1, &tk2, tk3, &tk4);
      //gg_edges[si[tk1]+jj] = tk2;
      //gg_edge_property[si[tk1]+jj] = tk4;
      //cout<<tk4<<" ";
      //total++;
      if(tk4 > 4.5) good++;
    }
  }

  myedgefile.close();

  cout<<"Read in graph - "<<tv<<" nodes - "<<te<<" edges."<<endl;
  cout<<"Found "<<good<<" edges with rating greater than 4.5."<<endl;
  cout<<"Found "<<total<<" edges."<<endl;
  return(te);
}

long GanitaGraph::readCSV(char *myfilestr,char *myfilestr2,char *myfilestr3)
{
  string line, token[10];
  ifstream myfile(myfilestr);
  vector<string> myvec1;
  vector<long> myrow1;
  vector<string> myvec2;
  vector<long> myrow2;
  long from, to;
  //vector<long> counts1;
  //vector<long> counts2;
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

long GanitaGraph::getTotalCSV(char *myfilestr,char *myfilestr2,char *myfilestr3)
{
  string line, token[10];
  ifstream myfile(myfilestr);
  vector<string> myvec1;
  vector<long> myrow1;
  vector<string> myvec2;
  vector<long> myrow2;
  long from, to;
  string tmp1, tmp2;
  long row;
  int ii, ntokens;
  ofstream myout1(myfilestr2);
  ofstream myout2(myfilestr3);

  if((!myout1.is_open()) || (!myout2.is_open())){
    cout<<"Could not open output files!"<<endl;
    return(-1);
  }

  row = 0; te = 0;
  if (!myfile.is_open()){
    cout<<"Unable to open input file."<<endl;
    return(-1);
  }
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
	    ti[from]++;
	    break;
	  }
	}
	//cout << "here" << endl;
	if(myvec1.size() == 0){
	  myvec1.push_back(token[0]);
	  myrow1.push_back(0);
	  counts1.push_back(1);
	  ti.push_back(1);
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
	  //cout << "Add new element: "<<token[0]<< '\n';
	  myvec1.push_back(token[0]);
	  myrow1.push_back(row);
	  from = row;
	  counts1.push_back(1);
	  ti.push_back(1);
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
	  ti[to]++;
	  break;
	}
      }
      //cout << "here" << endl;
      if(myvec2.size() == 0){
	myvec2.push_back(token[1]);
	myrow2.push_back(row);
	counts2.push_back(1);
	ti.push_back(1);
	to = row;
	myout1 << row << "\t" << token[1] << "\t" << "movie" << endl;
	row++;
      }
      //cout << "here 2" << endl;
      if(ii == myvec2.size()){
	//cout << "Add new element: "<<token[1]<< '\n';
	myvec2.push_back(token[1]);
	myrow2.push_back(row);
	to = row;
	counts2.push_back(1);
	ti.push_back(1);
	myout1 << row << "\t" << token[1] << "\t" << "movie" << endl;
	row++;
	//cout << "New size: "<<counts.size()<< '\n';
      }
      //cout << from+1 << " --> " << to+1 << endl;
      if(ntokens > 2){
	myout2 << from+1 << "\t" << to+1 << "\t" << "LIKES" << "\t" << token[2] << endl;
      }
      else {
	myout2 << from+1 << "\t" << to+1 << "\t" << "LIKES" << endl;
      }
      te++;
    }
  //cout<<"Size of vector: "<<counts.size()<<endl;
  //cl_sizes = counts;
  myfile.close();
  myout1.close();
  myout2.close();
  tv = counts1.size() + counts2.size();

  return (counts1.size() + counts2.size());
}

long GanitaGraph::createEdges(char *myfilestr)
{
  string line, token[10];
  ifstream myfile(myfilestr);
  vector<string> myvec1;
  vector<long> myrow1;
  vector<string> myvec2;
  vector<long> myrow2;
  long from, to;
  string tmp1, tmp2;
  long row;
  int ii, ntokens;
  //ofstream myout1(myfilestr2);
  //ofstream myout2(myfilestr3);
  long *cnt;
  long tt = 0;

  // if((!myout1.is_open()) || (!myout2.is_open())){
  //   cout<<"Could not open output files!"<<endl;
  //   return(-1);
  // }

  row = 0;
  if(!myfile.is_open()){
    cout<<"Could not open input file stream."<<endl;
    return(-1); 
  }
  cnt = (long *) malloc(sizeof(long) * (counts1.size() + counts2.size() + 2));
  //cnt2 = (long *) malloc(sizeof(long) * counts2.size());
  if(cnt == NULL){
    cout<< "Insufficient memory." << endl;
    return(-1);
  }
  memset(cnt,0, sizeof(long) * (counts1.size() + counts2.size() + 2));
  //memset(cnt2,0,counts2.size());
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
	    cnt[row]++;
	    from = myrow1[ii];
	    break;
	  }
	}
	//cout << "here" << endl;
	if(myvec1.size() == 0){
	  myvec1.push_back(token[0]);
	  myrow1.push_back(0);
	  //counts1.push_back(1);
	  cnt[0]++;
	  from = row;
	  //myout1 << "Node" << "\t" << "Id" << "\t" << "Type:string" << endl;
	  // if(ntokens > 2){
	  //   myout2 << "start" << "\t" << "end" << "\t" << "type" << "\t" << "tomatoes:byte" << endl;
	  // }
	  // else {
	  //   myout2 << "start" << "\t" << "end" << "\t" << "type" << endl;
	  // }
	  // myout1 << row << "\t" << token[0] << "\t" << "user" << endl;
	  row++;
	}
	//cout << "here 2" << endl;
	if(ii == myvec1.size()){
	  //cout << "Add new element: "<<token[0]<< '\n';
	  myvec1.push_back(token[0]);
	  myrow1.push_back(row);
	  from = row;
	  //counts1.push_back(1);
	  //myout1 << row << "\t" << token[0] << "\t" << "user" << endl;
	  row++;
	  cnt[row]++;
	  //cout << "New size: "<<counts.size()<< '\n';
	}
	//cout << "here 3" << endl;
      }
      for(ii=0; ii<myvec2.size(); ii++){
	//cout << "Existing vector: " << ii << " " << myvec[ii] << endl;
	//cout << "Existing token: " << ii << " " << token[1] << endl;
	if(myvec2[ii].compare(token[1]) == 0){
	  cnt[row]++;
	  to = myrow2[ii];
	  break;
	}
      }
      //cout << "here" << endl;
      if(myvec2.size() == 0){
	myvec2.push_back(token[1]);
	myrow2.push_back(1);
	//counts2.push_back(1);
	cnt[row]++;
	to = row;
	//myout1 << row << "\t" << token[1] << "\t" << "movie" << endl;
	row++;
      }
      //cout << "here 2" << endl;
      if(ii == myvec2.size()){
	//cout << "Add new element: "<<token[1]<< '\n';
	myvec2.push_back(token[1]);
	myrow2.push_back(row);
	to = row;
	//counts2.push_back(1);
	//myout1 << row << "\t" << token[1] << "\t" << "movie" << endl;
	row++;
	//cout << "New size: "<<counts.size()<< '\n';
	cnt[row]++;
      }
      //cout << from+1 << " --> " << to+1 << endl;
      // Add edge
      // if(ntokens > 2){
      // 	myout2 << from+1 << "\t" << to+1 << "\t" << "LIKES" << "\t" << token[2] << endl;
      // }
      // else {
      // 	myout2 << from+1 << "\t" << to+1 << "\t" << "LIKES" << endl;
      // }
      //gg_edges[from][cnt[from]] = to;
      //cout<<"here 1 "<< to << " " << cnt[to]<<endl;
      //gg_edges[to][cnt[to]] = from;
      //cout<<"here 2 "<<tt<<" "<<from<<"-->"<<to<<endl;
      gg_rels[2*tt] = from; gg_rels[2*tt+1]=to;
      if(to == 0){
	cout << "Row " << row << " From " << from << " Row2 " << myrow2[ii] << " " << token[1] << endl;
      }
      //cout<<"here 3"<<endl;
      fflush(stdout);
      //cout<<"here 4"<<endl;
      tt++;
    }
  cout<<"Number of edges: "<<tt<<endl;
  //cl_sizes = counts;
  if(myfile.is_open()){
    myfile.close();
  }
  //cout<<"Completed edge creation: "<<endl;
  //myout1.close();
  //myout2.close();
  cout<<"Completed edge creation: "<<endl;
  fflush(stdout);
  return row;
}

long GanitaGraph::createWeightedEdges(char *myfilestr)
{
  string line, token[10];
  ifstream myfile(myfilestr);
  vector<string> myvec1;
  vector<long> myrow1;
  vector<string> myvec2;
  vector<long> myrow2;
  long from, to;
  string tmp1, tmp2;
  long row;
  int ii, ntokens;
  //ofstream myout1(myfilestr2);
  //ofstream myout2(myfilestr3);
  long *cnt;
  long tt = 0;

  // if((!myout1.is_open()) || (!myout2.is_open())){
  //   cout<<"Could not open output files!"<<endl;
  //   return(-1);
  // }

  row = 0;
  if(!myfile.is_open()){
    cout<<"Could not open input file stream."<<endl;
    return(-1); 
  }
  cnt = (long *) malloc(sizeof(long) * (counts1.size() + counts2.size() + 2));
  //cnt2 = (long *) malloc(sizeof(long) * counts2.size());
  if(cnt == NULL){
    cout<< "Insufficient memory." << endl;
    return(-1);
  }
  memset(cnt,0, sizeof(long) * (counts1.size() + counts2.size() + 2));
  //memset(cnt2,0,counts2.size());
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
	    cnt[row]++;
	    from = myrow1[ii];
	    break;
	  }
	}
	//cout << "here" << endl;
	if(myvec1.size() == 0){
	  myvec1.push_back(token[0]);
	  myrow1.push_back(0);
	  //counts1.push_back(1);
	  cnt[0]++;
	  from = row;
	  //myout1 << "Node" << "\t" << "Id" << "\t" << "Type:string" << endl;
	  // if(ntokens > 2){
	  //   myout2 << "start" << "\t" << "end" << "\t" << "type" << "\t" << "tomatoes:byte" << endl;
	  // }
	  // else {
	  //   myout2 << "start" << "\t" << "end" << "\t" << "type" << endl;
	  // }
	  // myout1 << row << "\t" << token[0] << "\t" << "user" << endl;
	  row++;
	}
	//cout << "here 2" << endl;
	if(ii == myvec1.size()){
	  //cout << "Add new element: "<<token[0]<< '\n';
	  myvec1.push_back(token[0]);
	  myrow1.push_back(row);
	  from = row;
	  //counts1.push_back(1);
	  //myout1 << row << "\t" << token[0] << "\t" << "user" << endl;
	  row++;
	  cnt[row]++;
	  //cout << "New size: "<<counts.size()<< '\n';
	}
	//cout << "here 3" << endl;
      }
      for(ii=0; ii<myvec2.size(); ii++){
	//cout << "Existing vector: " << ii << " " << myvec[ii] << endl;
	//cout << "Existing token: " << ii << " " << token[1] << endl;
	if(myvec2[ii].compare(token[1]) == 0){
	  cnt[row]++;
	  to = myrow2[ii];
	  break;
	}
      }
      //cout << "here" << endl;
      if(myvec2.size() == 0){
	myvec2.push_back(token[1]);
	myrow2.push_back(1);
	//counts2.push_back(1);
	cnt[row]++;
	to = row;
	//myout1 << row << "\t" << token[1] << "\t" << "movie" << endl;
	row++;
      }
      //cout << "here 2" << endl;
      if(ii == myvec2.size()){
	//cout << "Add new element: "<<token[1]<< '\n';
	myvec2.push_back(token[1]);
	myrow2.push_back(row);
	to = row;
	//counts2.push_back(1);
	//myout1 << row << "\t" << token[1] << "\t" << "movie" << endl;
	row++;
	//cout << "New size: "<<counts.size()<< '\n';
	cnt[row]++;
      }
      //cout << from+1 << " --> " << to+1 << endl;
      // Add edge
      // if(ntokens > 2){
      // 	myout2 << from+1 << "\t" << to+1 << "\t" << "LIKES" << "\t" << token[2] << endl;
      // }
      // else {
      // 	myout2 << from+1 << "\t" << to+1 << "\t" << "LIKES" << endl;
      // }
      //gg_edges[from][cnt[from]] = to;
      //cout<<"here 1 "<< to << " " << cnt[to]<<endl;
      //gg_edges[to][cnt[to]] = from;
      //cout<<"here 2 "<<tt<<" "<<from<<"-->"<<to<<endl;
      gg_rels[2*tt] = from; gg_rels[2*tt+1]=to;
      // add weights 
      if(ntokens > 2){
	gg_edge_property[tt] = std::stod(token[2]);
      }
      else gg_edge_property[tt] = 0;

      if(to == 0){
	cout << "Row " << row << " From " << from << " Row2 " << myrow2[ii] << " " << token[1] << endl;
      }
      //cout<<"here 3"<<endl;
      fflush(stdout);
      //cout<<"here 4"<<endl;
      tt++;
    }
  cout<<"Number of edges: "<<tt<<endl;
  //cl_sizes = counts;
  if(myfile.is_open()){
    myfile.close();
  }
  //cout<<"Completed edge creation: "<<endl;
  //myout1.close();
  //myout2.close();
  cout<<"Completed edge creation: "<<endl;
  fflush(stdout);
  return row;
}

long GanitaGraph::ggInit(char *myfilestr,char *myfilestr2,char *myfilestr3)
{
  getTotalCSV(myfilestr,myfilestr2,myfilestr3);
  ggAllocRels(te);
  return(createEdges(myfilestr));
}

long GanitaGraph::ggInitWeighted(char *myfilestr,char *myfilestr2,char *myfilestr3)
{
  getTotalCSV(myfilestr,myfilestr2,myfilestr3);
  ggAllocRels(te);
  ggAllocWeights(te);
  return(createWeightedEdges(myfilestr));
}

long GanitaGraph::ggAllocRels(long tt)
{
  //gg_edges = (long **) calloc(tv, sizeof(long*));
  gg_rels = (long *) malloc(2 * (tt + 100) * sizeof(long));
  if(gg_rels == NULL){
    cout << "out of memory" << endl;
    return(-1);
  }

  cout<<"Allocated edges "<<tt<<endl;
  cout<<"Node sizes "<<counts1.size()<<" "<<counts2.size()<<endl;

  return(1);
}

long GanitaGraph::ggAllocWeights(long tt)
{
  gg_edge_property = (double *) malloc((tt + 100) * sizeof(long));
  if(gg_edge_property == NULL){
    cout << "out of memory" << endl;
    return(-1);
  }

  return(1);
}

long GanitaGraph::ggDeAlloc(long tv)
{
  //long i;
  //for(i = 0; i < tv; i++) {
    free(gg_edges);
    //}
  return(1);
}

long GanitaGraph::dumpIndices()
{
  long ii;

  for(ii=0; ii<ti.size(); ii++){
    cout<<"Vertex: "<<ii<<" Index: "<<ti[ii]<<"; ";
  }
  cout<<"Total # of vertices: "<<tv<<endl;

  return(ii);
}

long GanitaGraph::computeEdges()
{
  if((tv <= 0) || (te <= 0)){
    return(-1);
  }
  gg_edges = (long *) malloc(sizeof(long)*2*te);
  if(gg_edges == NULL){
    cout<<"Unable to allocate edges."<<endl;
    return(-1);
  }
  //compute partial sums of ti array
  long ii, jj, kk;
  long mm, sum;
  //vector<long> tmp_i;
  long from, to;
  sum = 0;
  for(ii=0; ii<tv; ii++){
    si.push_back(sum);
    sum += ti[ii];
    // tmp_i.push_back(0);
  }
  si.push_back(sum);
  cout << "Sum " << sum << " = " << 2*te << endl;
  for(ii=0; ii<2*te; ii++){
    gg_edges[ii] = -1;
  }
  for(ii=0; ii<te; ii++){
    for(mm=0; mm<2; mm++){
      from = gg_rels[2*ii + mm];
      to = gg_rels[2*ii + 1 - mm];
      jj = 0;
      while(gg_edges[si[from]+jj] < to){
	if((jj == (ti[from]-1)) || (gg_edges[si[from]+jj] == -1)){
	  if(from == 0){
	    //cout << "Assign " << from << "-->" << to << " | ";
	  }
	  break;
	}
	jj++;
      }
      if(jj < ti[from]){
	// insert the new to node. 
	for(kk=ti[from]-1; kk>jj; kk--){
	  gg_edges[si[from]+kk] = gg_edges[si[from]+kk-1];
	}
	gg_edges[si[from]+jj] = to;
	//if(from == 0){
	//cout << "Assign final " << from << "-->" << jj << "-->" << gg_edges[si[from]+jj] << " | ";
	  //}
      }
    }
  }
  
  compute_edge_flag = 1;
  return(1);
}

long GanitaGraph::dumpEdges()
{
  long ii, jj;

  if((gg_edges == NULL) || (compute_edge_flag < 1)){
    cout << "Need to compute edges first." << endl;
    return(-1);
  }
  for(ii=0; ii<tv; ii++){
    cout << "From vertex: " << ii << endl;
    cout << "  To vertex: ";
    for(jj=0; jj<ti[ii]; jj++){
      cout << gg_edges[si[ii]+jj] << " ";
    }
    cout << endl;
  }
  
  return(1);
}

long GanitaGraph::dumpRels()
{
  long ii;

  for(ii=0; ii<te; ii++){
    cout << "(" << gg_rels[2*ii] << "-->" << gg_rels[2*ii+1] << ") " << endl;
  }
  
  return(1);
}

// Initially we will assume undirected graph and no node is a leaf. 
long GanitaGraph::setMinTrace(long len)
{
  long pos, ii;
  long my_i = 0;

  //while(ti[ii] <= 0){
  //ii++;
  //}
  
  trace[0].clear();
  trace[0].push_back(gg_edges[si[0]]);
  for(ii=0; ii<len-1; ii++){
    trace[0].push_back(gg_edges[si[trace[0][ii]]]);
  }

  cout<<"Minimum path: ";
  for(ii=0; ii<len; ii++){
    cout<<trace[0][ii]<<" ";
  }
  cout<<endl;

  return(1);
}

long GanitaGraph::recommenderBasic(long ncom, long check_4_cycle)
{
  long level, path_count;
  long ii;
  int keep_going = 1;
  long four_cycle_cnt = 0;

  trace[0].clear();
  level = 0; path_count = 0;
  trace[0].push_back(0);
  trace[1].push_back(0);
  cout<<"Start: "<<trace[0][0];
  for(ii=0; ii<ncom; ii++){
    trace[0].push_back(gg_edges[si[trace[0][ii]]]);
    trace[1].push_back(0);
    cout<<" "<<gg_edges[si[trace[0][ii]]];
  }
  cout<<endl;

  while(keep_going){
    level = ncom;
    //cout<<"Node index: "<<ti[trace[0][level-1]]<<endl;
    while(ti[trace[0][level-1]] == trace[1][level]){
      trace[1][level] = 0;
      level--;
      if(level == 0){
	// increment root node
	break;
      }
    }
    
    if(level == 0){
      // increment root node
      trace[0][0]++;
      trace[1][0] = 0;
      cout<<"New root node: "<<trace[0][0]<<" Number of paths: "<<path_count<<endl;
      if(trace[0][0] >= tv){
	// completed search
	cout<<"Total paths: "<<path_count<<endl;
	return(1);
      }
      trace[0][level+1] = gg_edges[si[trace[0][level]]];
      trace[1][level+1] = 0;
    }
    else {
      trace[1][level]++;
      trace[0][level] = gg_edges[si[trace[0][level-1]] + trace[1][level]];
      //cout<<"New node: "<<trace[0][level]<<" at level "<<level<<endl;
    }
    //retrace path
    for(ii=level+1; ii<=ncom; ii++){
      trace[0][ii] = gg_edges[si[trace[0][ii-1]]];
      trace[1][ii] = 0;
    }
    // perform analysis on path
    if(check_4_cycle){
      if(checkCycle4(ncom) > 0){
	four_cycle_cnt++;
	if(four_cycle_cnt % 100000 == 0) cout<<"Total 4 cycles: "<<four_cycle_cnt<<endl;
      }
    }
    path_count++;
    //cout<<"New node: "<<trace[0][level+1]<<" Number of paths: "<<path_count<<endl;
  }
}

long GanitaGraph::checkCycle4(long ncom)
{
  long jj, kk;

  if(ncom >= 3){
    if((trace[0][0] != trace[0][2]) && (trace[0][1] != trace[0][3])){
      // check to see if trace[0][0] is connected to trace[0][3]
      if( ti[trace[0][0]] <= ti[trace[0][3]] ){
	jj = 0;
	while(gg_edges[si[trace[0][0]]+jj] != trace[0][3]){
	  jj++;
	  if(jj >= ti[trace[0][0]]) break;
	}
	if(jj < ti[trace[0][0]]){
	  //cout<<"Found 4 cycle:";
	  //for(kk=0; kk<=ncom; kk++){
	  //cout<<" "<<trace[0][kk];
	  //}
	  //cout<<endl;
	  return(1);
	}
      }
      else {
	jj = 0;
	while(gg_edges[si[trace[0][3]]+jj] != trace[0][0]){
	  jj++;
	  if(jj >= ti[trace[0][3]]) break;
	}
	if(jj < ti[trace[0][3]]){
	  //cout<<"Found 4 cycle: ";
	  //for(kk=0; kk<=ncom; kk++){
	  //cout<<" "<<trace[0][kk]; 
	  //}
	  //cout<<endl;
	  return(1);
	}
      }
    }
  }

  return(0);
}

long GanitaGraph::nodeDotProd(long nn1, long nn2)
{
  long dd;
  long ii, jj;

  ii = 0; jj = 0;
  dd = 0;
  while(jj < ti[nn2]){
    while(gg_edges[si[nn1]+ii] < gg_edges[si[nn2]+jj]){
      ii++;
      if(ii >= ti[nn1]) break;
    }
    if(gg_edges[si[nn1]+ii] == gg_edges[si[nn2]+jj]){
      dd++;
    }
    jj++;
    if(jj >= ti[nn2]) break;
  }

  return(dd);
}

long GanitaGraph::nodeDotProd2(long nn1, long nn2, long tt)
{
  long dd;
  long ii, jj;

  ii = 0; jj = 0;
  dd = 0;
  while(jj < ti[nn2]){
    while(gg_edges[si[nn1]+ii] < gg_edges[si[nn2]+jj]){
      ii++;
      if(ii >= ti[nn1]) break;
    }
    if(gg_edges[si[nn1]+ii] == gg_edges[si[nn2]+jj]){
      dd++;
    }
    jj++;
    if(jj >= ti[nn2]) break;
  }

  if(dd >= tt){
    return(ti[nn2] - dd);
  }
  else return (-1);

}

long GanitaGraph::nodeDotProd(long nn1)
{
  long nn2, dd;

  for(nn2=0; nn2<tv; nn2++){
    dd = nodeDotProd(nn1, nn2);
    if(dd > 2){
      cout<<"Nodes: ("<<nn1<<","<<nn2<<") Dot product: "<<dd<<endl;
    }
  }

  return(1);
}

long GanitaGraph::nodeDotProd2(long nn1, long tt)
{
  long nn2, uu;

  for(nn2=0; nn2<tv; nn2++){
    uu = nodeDotProd2(nn1, nn2, tt);
    if(uu > 0){
      cout<<"Nodes: ("<<nn1<<","<<nn2<<") Recommended nodes: "<<uu<<endl;
    }
  }

  return(1);
}

long GanitaGraph::returnNumNodes()
{
  return(tv);
}

