/* Starter template for handling of EM image slices. 
   Incomplete at this point.                         */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include "GanitaCore.hpp"

using namespace std;

class GanitaImage
{
private:
  long width;
  long height;
  long n_chan;
  int *data;
  int **gi;
public:
  GanitaImage();
  //int readPGM(char *myfilestr);
  int allocateIm(long ww, long hh, int nc);
  int allocateGI(long ww, long hh);
  int assign(long xx, long yy, int val);
  long returnWidth();
  long returnHeight();
  long w();
  long h();
  int value(long ww, long hh);
  int dumpPgm(void);
  long binarizeGI(double thresh);
};

GanitaImage::GanitaImage()
{
  // grayscale is default
  n_chan = 1;
}

// int GanitaImage::readPGM(char *myfilestr)
// {
//   string line;
//   ifstream myfile(myfilestr);
//   int ntokens, token[256];
//   int ii;
   
//   if (!myfile.is_open()){
//     cout<<"Unable to open input file."<<endl;
//     return(-1);
//   }
//   // read header line
//   getline (myfile,line);
//   //cout << line << endl;
//   while ( getline (myfile,line) )
//     {
//       //cout << line << endl;
//       std::istringstream is(line);
//       ii=0;
//       while(std::getline(is, token[ii], '\t')) {
// 	//std::cout << token[ii] << '\n';
// 	ii++;
// 	if(ii >= 10) break;
//       }
//       ntokens = ii;
//     }

//   return(1);
// }

int GanitaImage::allocateIm(long ww, long hh, int nc)
{
  data = (int *) malloc(sizeof(char)*ww*hh*nc);
  if(data == NULL){
    cout<<"Unable to allocate image slice."<<endl;
    return(-1);
  }
  return(1);
}

int GanitaImage::allocateGI(long ww, long hh)
{
  width = ww;
  height = hh;
  n_chan = 1;
  gi = allocGI(ww,hh);
  
  if(gi == NULL){
    return(-1);
  }
  
  return(1);
}

int GanitaImage::assign(long xx, long yy, int val)
{
  gi[xx % width][yy % height] = val;

  return(val);
}

long GanitaImage::returnWidth()
{
  return(width);
}

long GanitaImage::returnHeight()
{
  return(height);
}

long GanitaImage::w()
{
  return(width);
}

long GanitaImage::h()
{
  return(height);
}

int GanitaImage::value(long xx, long yy)
{
  return(gi[xx % width][yy % height]);
}

int GanitaImage::dumpPgm(void)
{
  int ii, jj;
  long tmp = 0;

  fprintf(stdout, "P2\n%ld %ld\n255\n", width, height);
  for(ii=0; ii<height; ii++){
      for(jj=0; jj<width; jj++){
	cout << value(jj,ii) << " ";
	tmp++;
	if(tmp % 16 == 15){
	  cout<<endl;
	}
      }
  }
  return(1);
}

long GanitaImage::binarizeGI(double thresh)
{
  int ii, jj;
  long cnt = 0;

  for(ii=0; ii<height; ii++){
      for(jj=0; jj<width; jj++){
	if(value(jj,ii) >= thresh){
	  assign(jj,ii,255);
	  cnt++;
	}
	else assign(jj,ii,0);
      }
  }

  return(cnt);
}

