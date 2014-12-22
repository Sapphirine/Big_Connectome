// C++ class for processing HDF5 dump files. 
// This is a class for running 3D algorithms 
// on EM voxels. 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include "GanitaImage.cpp"
#include "GanitaFilters.hpp"

using namespace std;

class Ganita3D
{
private:
  long width;
  long height;
  long depth;
  long n_chan;
  vector<std::shared_ptr<GanitaImage>> voxel;
  int startX, startY, startZ;
  double stat[NUM_STATS];
public:
  Ganita3D();
  int hdf5ToPgm(char *, char *);
  int readH5Dump(char *, char *);
  int dumpDepth();
  int dumpPgm(int slice);
  int dumpFirstPgm();
  double sobel3D(long xx, long yy, long zz);
  double sobel3D(long xx, long yy, long zz, long skip);
  GanitaImage *sobel3D(long zz);
  GanitaImage *sobel3D(long zz, int scale);
  int dumpStats(int nstats);
  int returnStat(int stat_i);
};

Ganita3D::Ganita3D()
{
  startX = 0;
  startY = 0;
  startZ = 0;
}

// Convert HDF5 dump file to PGM files. 
int Ganita3D::readH5Dump(char *inputfile, char *outputfile)
{
  FILE *infile, *outfile;
  char line1[1000], line2[1000];
  char fn[1000];
  char *ptr;
  char *saveptr1;
  int xx1,yy1,zz1;
  int xx2,yy2,zz2;
  char delim[2] = {":"};
  char delim2[2] = {","};
  int count = 0;
  long pc = 0; // pixel count
  int grey, ii, dif;
  char tmp[1000];
  int xblk_size, yblk_size, zblk_size;
  int xs1, ys1, zs1;
  int xs2, ys2, zs2;
  GanitaImage *gi = new GanitaImage();

  infile = fopen(inputfile,"rb");
  if(infile == NULL){
    fprintf(stderr, "Unable to read %s.\n", inputfile);
    return(-1);
  } 

  sprintf(fn,"%s_%08d.pgm",outputfile, count);
  outfile = fopen(fn,"w");
  if(outfile == NULL){
    fprintf(stderr, "Unable to open %s.\n", outputfile);
    exit(1);
  }

  if(fgets ( line2, sizeof line2, infile ) == NULL){
    fprintf(stdout, "Could not read file %s.\n", inputfile);
    return(-1);
  }
  else{
    ptr = fgets ( line2, sizeof line2, infile );
    ptr = fgets ( line2, sizeof line2, infile );
    ptr = fgets ( line2, sizeof line2, infile );
    ptr = fgets ( line2, sizeof line2, infile );
    sscanf(line2,"\tDATASPACE  SIMPLE { ( %d, %d, %d ) / ( %d, %d, %d ) }", &xs1, &ys1, &zs1, &xs2, &ys2, &zs2);
    //fprintf(stdout, "Line=%s", line2);
    fprintf(stdout, "(%d,%d,%d) / (%d,%d,%d)\n", xs1,ys1,zs1,xs2,ys2,zs2);
    xblk_size = zs1;
    yblk_size = ys1;
  }
  ptr = fgets ( line2, sizeof line2, infile );
  ptr = fgets ( line2, sizeof line2, infile );
  fprintf(outfile, "P2\n%d %d\n255\n", xblk_size, yblk_size);
  gi->allocateGI(xblk_size, yblk_size);
  width = xblk_size; height = yblk_size;
  while ( fgets ( line1, sizeof line1, infile ) != NULL ){
    sscanf(line2, "\t(%d,%d,%d):", &zz2, &yy2, &xx2);
    ptr = strtok_r(&line2[0],delim,&saveptr1);
    sscanf(line1, "\t(%d,%d,%d):", &zz1, &yy1, &xx1);
    if(yy1 == yy2){
      dif = xx1 - xx2;
      //fprintf(stdout, "xx1=%d,xx2=%d,dif=%d ", xx1,xx2,dif);
      for(ii=0; ii<dif; ii++){
	ptr = strtok_r(saveptr1,delim2,&saveptr1);
	sscanf(saveptr1,"%d,", &grey);
	fprintf(outfile, "%3d ", grey);
	gi->assign(pc % xblk_size, pc / xblk_size, grey);
	pc++;
      }
    }
    else{
      dif = xblk_size - xx2;
      //fprintf(stdout, "xx1=%d,xx2=%d,dif=%d ", xx2,xblk_size,dif);
      for(ii=0; ii<dif; ii++){
	ptr = strtok_r(saveptr1,delim2,&saveptr1);
	sscanf(saveptr1,"%d,", &grey);
	fprintf(outfile, "%3d ", grey);
	gi->assign(pc % xblk_size, pc / xblk_size, grey);
	pc++;
      }
      if(zz1 != zz2){
	// start a new image slice
	fclose(outfile);
	count++;
	// Push Ganita Image onto voxel.
	// Reset pixel count pc=0.
	voxel.push_back(std::make_shared<GanitaImage>(*gi));
	pc = 0;
	delete gi;
	GanitaImage *gi = new GanitaImage();
	gi->allocateGI(xblk_size, yblk_size);
	//if(argc > 4){
	//sprintf(fn,"%s_%08d_%08d_%08d.pgm",inputfile, startX, startY, count + startZ);
	//}
	//else sprintf(fn,"%s_%08d.pgm",inputfile, count);
	sprintf(fn,"%s_%08d.pgm",outputfile, count);
	outfile = fopen(fn,"w");
	if(outfile == NULL){
	  fprintf(stderr, "Unable to open %s.\n", fn);
	  return(-1);
	}
	fprintf(outfile, "P2\n%d %d\n255", xblk_size, yblk_size);
      }
      fprintf(outfile, "\n");
    }
    xx2 = xx1; yy2 = yy1; zz2 = zz1;
    strcpy(line2,line1);
    ptr = strtok_r(&line1[0],delim,&saveptr1);
    //fprintf(stdout, "%s", saveptr1);
  }

  // finish last image slice
  ptr = strtok_r(&line2[0],delim,&saveptr1);
  dif = xblk_size - xx2;
  for(ii=0; ii<dif; ii++){
    ptr = strtok_r(saveptr1,delim2,&saveptr1);
    sscanf(saveptr1,"%d,", &grey);
    fprintf(outfile, "%3d ", grey);
    gi->assign(pc % xblk_size, pc / xblk_size, grey);
    pc++;
  }

  voxel.push_back(std::make_shared<GanitaImage>(*gi));
  depth = voxel.size();
  delete gi;
  return(count);
}

// Read in pixel values from hdf5 dump file. 
// This is a 3D voxel. 
int Ganita3D::hdf5ToPgm(char *inputfile, char *outputfile)
{
  FILE *infile, *outfile;
  char line1[1000], line2[1000];
  char fn[1000];
  char *ptr;
  char *saveptr1;
  int xx1,yy1,zz1;
  int xx2,yy2,zz2;
  char delim[2] = {":"};
  char delim2[2] = {","};
  int count = 0;
  int grey, ii, dif;
  char tmp[1000];
  int xblk_size, yblk_size, zblk_size;
  int xs1, ys1, zs1;
  int xs2, ys2, zs2;

  infile = fopen(inputfile,"rb");
  if(infile == NULL){
    fprintf(stderr, "Unable to read %s.\n", inputfile);
    return(-1);
  } 

  sprintf(fn,"%s_%08d.pgm",outputfile, count);
  outfile = fopen(fn,"w");
  if(outfile == NULL){
    fprintf(stderr, "Unable to open %s.\n", outputfile);
    exit(1);
  }

  if(fgets ( line2, sizeof line2, infile ) == NULL){
    fprintf(stdout, "Could not read file %s.\n", inputfile);
    return(-1);
  }
  else{
    ptr = fgets ( line2, sizeof line2, infile );
    ptr = fgets ( line2, sizeof line2, infile );
    ptr = fgets ( line2, sizeof line2, infile );
    ptr = fgets ( line2, sizeof line2, infile );
    sscanf(line2,"\tDATASPACE  SIMPLE { ( %d, %d, %d ) / ( %d, %d, %d ) }", &xs1, &ys1, &zs1, &xs2, &ys2, &zs2);
    //fprintf(stdout, "Line=%s", line2);
    fprintf(stdout, "(%d,%d,%d) / (%d,%d,%d)\n", xs1,ys1,zs1,xs2,ys2,zs2);
    xblk_size = zs1;
    yblk_size = ys1;
  }
  ptr = fgets ( line2, sizeof line2, infile );
  ptr = fgets ( line2, sizeof line2, infile );
  fprintf(outfile, "P2\n%d %d\n255\n", xblk_size, yblk_size);
  while ( fgets ( line1, sizeof line1, infile ) != NULL ){
    sscanf(line2, "\t(%d,%d,%d):", &zz2, &yy2, &xx2);
    ptr = strtok_r(&line2[0],delim,&saveptr1);
    sscanf(line1, "\t(%d,%d,%d):", &zz1, &yy1, &xx1);
    if(yy1 == yy2){
      dif = xx1 - xx2;
      //fprintf(stdout, "xx1=%d,xx2=%d,dif=%d ", xx1,xx2,dif);
      for(ii=0; ii<dif; ii++){
	ptr = strtok_r(saveptr1,delim2,&saveptr1);
	sscanf(saveptr1,"%d,", &grey);
	fprintf(outfile, "%3d ", grey);
      }
    }
    else{
      dif = xblk_size - xx2;
      //fprintf(stdout, "xx1=%d,xx2=%d,dif=%d ", xx2,xblk_size,dif);
      for(ii=0; ii<dif; ii++){
	ptr = strtok_r(saveptr1,delim2,&saveptr1);
	sscanf(saveptr1,"%d,", &grey);
	fprintf(outfile, "%3d ", grey);
      }
      if(zz1 != zz2){
	fclose(outfile);
	count++;
	//if(argc > 4){
	//sprintf(fn,"%s_%08d_%08d_%08d.pgm",inputfile, startX, startY, count + startZ);
	//}
	//else sprintf(fn,"%s_%08d.pgm",inputfile, count);
	sprintf(fn,"%s_%08d.pgm",outputfile, count);
	outfile = fopen(fn,"w");
	if(outfile == NULL){
	  fprintf(stderr, "Unable to open %s.\n", fn);
	  return(-1);
	}
	fprintf(outfile, "P2\n%d %d\n255", xblk_size, yblk_size);
      }
      fprintf(outfile, "\n");
    }
    xx2 = xx1; yy2 = yy1; zz2 = zz1;
    strcpy(line2,line1);
    ptr = strtok_r(&line1[0],delim,&saveptr1);
    //fprintf(stdout, "%s", saveptr1);
  }

  // finish last image slice
  ptr = strtok_r(&line2[0],delim,&saveptr1);
  dif = xblk_size - xx2;
  for(ii=0; ii<dif; ii++){
    ptr = strtok_r(saveptr1,delim2,&saveptr1);
    sscanf(saveptr1,"%d,", &grey);
    fprintf(outfile, "%3d ", grey);
  }

  return(1);
}

int Ganita3D::dumpDepth()
{
  cout<<"# images: "<<voxel.size()<<"."<<endl;

  return(voxel.size());
}

int Ganita3D::dumpPgm(int slice)
{
  int ii, jj;
  long tmp = 0;

  fprintf(stdout, "P2\n%ld %ld\n255\n", voxel[slice % voxel.size()]->w(),voxel[slice % voxel.size()]->h());
  for(ii=0; ii<voxel[slice % voxel.size()]->h(); ii++){
      for(jj=0; jj<voxel[slice % voxel.size()]->w(); jj++){
	cout << voxel[slice % voxel.size()]->value(jj,ii) << " ";
	tmp++;
	if(tmp % 16 == 15){
	  cout<<endl;
	}
      }
  }
  return(1);
}

int Ganita3D::dumpFirstPgm()
{
  int ii, jj;
  long tmp = 0;

  fprintf(stdout, "P2\n%ld %ld\n255\n", voxel[0]->w(),voxel[0]->h());
  for(ii=0; ii<voxel[0]->h(); ii++){
      for(jj=0; jj<voxel[0]->w(); jj++){
	cout << voxel[0]->value(jj,ii) << " ";
	tmp++;
	if(tmp % 16 == 15){
	  cout<<endl;
	}
      }
  }
  return(1);
}

double Ganita3D::sobel3D(long xx, long yy, long zz)
{
  int ptx[3];
  int pty[3];
  int ptz[3];
  int gx, gy, gz;
  int ii, jj, kk;
  double mag;

  gx = 0; 
  gy = 0;
  gz = 0;

  if(xx <= 0){
    ptx[0] = 0; ptx[1] = 0; ptx[2] = 1;
  }
  else if(xx >= width-1){
    ptx[0] = width-2; ptx[1] = width-1; ptx[2] = width-1;
  }
  else{
    ptx[0] = xx-1; ptx[1] = xx; ptx[2] = xx+1;
  }

  if(yy <= 0){
    pty[0] = 0; pty[1] = 0; pty[2] = 1;
  }
  else if(yy >= height-1){
    pty[0] = height-2; pty[1] = height-1; pty[2] = height-1;
  }
  else{
    pty[0] = yy-1; pty[1] = yy; pty[2] = yy+1;
  }

  if(zz <= 0){
    ptz[0] = 0; ptz[1] = 0; ptz[2] = 1;
  }
  else if(zz >= depth-1){
    ptz[0] = depth-2; ptz[1] = depth-1; ptz[2] = depth-1;
  }
  else{
    ptz[0] = zz-1; ptz[1] = zz; ptz[2] = zz+1;
  }

  for(ii=0; ii<3; ii++){
    for(jj=0; jj<3; jj++){
      for(kk=0; kk<3; kk++){
	gx += sobelg3d[ii][jj][kk] * voxel[ptz[ii]]->value(ptx[kk],pty[jj]);
	gy += sobelg3d[ii][jj][kk] * voxel[ptz[ii]]->value(ptx[jj],pty[kk]);
	gz += sobelg3d[ii][jj][kk] * voxel[ptz[kk]]->value(ptx[ii],pty[jj]);
      }
    }
  }

  gz = gz / 10;
  mag = pow(pow(abs(gx),pdim) + pow(abs(gy),pdim) + pow(abs(gz),pdim), 1/pdim);

  return(mag);
}

double Ganita3D::sobel3D(long xx, long yy, long zz, long skip)
{
  int ptx[3];
  int pty[3];
  int ptz[3];
  int gx, gy, gz;
  int ii, jj, kk;
  double mag;
  long skipz = 1;

  gx = 0; 
  gy = 0;
  gz = 0;

  if(xx <= 0){
    ptx[0] = 0; ptx[1] = 0; ptx[2] = skip;
  }
  else if(xx >= width-skip){
    ptx[0] = width-2*skip; ptx[1] = width-skip; ptx[2] = width-skip;
  }
  else{
    ptx[0] = xx-skip; ptx[1] = xx; ptx[2] = xx+skip;
  }

  if(yy <= 0){
    pty[0] = 0; pty[1] = 0; pty[2] = skip;
  }
  else if(yy >= height-skip){
    pty[0] = height-2*skip; pty[1] = height-skip; pty[2] = height-skip;
  }
  else{
    pty[0] = yy-skip; pty[1] = yy; pty[2] = yy+skip;
  }

  if(zz <= 0){
    ptz[0] = 0; ptz[1] = 0; ptz[2] = skipz;
  }
  else if(zz >= depth-skipz){
    ptz[0] = depth-2*skipz; ptz[1] = depth-skipz; ptz[2] = depth-skipz;
  }
  else{
    ptz[0] = zz-skipz; ptz[1] = zz; ptz[2] = zz+skipz;
  }

  for(ii=0; ii<3; ii++){
    for(jj=0; jj<3; jj++){
      for(kk=0; kk<3; kk++){
	gx += sobelg3d[ii][jj][kk] * voxel[ptz[ii]]->value(ptx[kk],pty[jj]);
	gy += sobelg3d[ii][jj][kk] * voxel[ptz[ii]]->value(ptx[jj],pty[kk]);
	gz += sobelg3d[ii][jj][kk] * voxel[ptz[kk]]->value(ptx[ii],pty[jj]);
      }
    }
  }

  gz = gz / 10;
  mag = pow(pow(abs(gx),pdim) + pow(abs(gy),pdim) + pow(abs(gz),pdim), 1/pdim);

  return(mag);
}

GanitaImage *Ganita3D::sobel3D(long zz)
{
  int ii, jj;
  GanitaImage *sobelGI = new GanitaImage();
  int mag;
  int max = 0;
  int min = 255;
  int val;

  //cout<<"Allocate image: "<<

  sobelGI->allocateGI(width,height);
  
  //<<endl;

  for(ii=0; ii<width; ii++){
    for(jj=0; jj<height; jj++){
      mag = (int) round(sobel3D(ii,jj,zz));
      //cout<<ii<<","<<jj<<": "<<mag<<endl;
      if(mag > max) max = mag;
      if(mag < min) min = mag;
      //cout<<"Assign ..."<<endl;
      sobelGI->assign(ii,jj,mag);
      //cout<<"Finished assign."<<endl;
      //fflush(stdout);
    }
  }

  if(max == min){
    // nothing to normalize
    return(sobelGI);
  }

  cout<<"Completed 3D Sobel operator."<<endl;
  cout<<"Max/min magnitudes: "<<max<<"/"<<min<<endl;

  // normalize the image slice between 0 and 255
  for(ii=0; ii<width; ii++){
    for(jj=0; jj<height; jj++){
      val = 255 * (sobelGI->value(ii,jj) - min) / (max - min);
      sobelGI->assign(ii,jj,val);
    }
  }

  return(sobelGI);
}

GanitaImage *Ganita3D::sobel3D(long zz, int scale)
{
  int ii, jj;
  GanitaImage *sobelGI = new GanitaImage();
  int mag;
  int max = 0;
  int min = 255;
  int val;
  int ww, hh;
  double sum = 0;
  double sum2 = 0;

  //cout<<"Allocate image: "<<

  ww = width/scale;
  hh = height/scale;

  sobelGI->allocateGI(ww,hh);
  
  //<<endl;

  for(ii=0; ii<ww; ii++){
    for(jj=0; jj<hh; jj++){
      mag = (int) round(sobel3D(scale*ii,scale*jj,zz,scale));
      //cout<<ii<<","<<jj<<": "<<mag<<endl;
      if(mag > max) max = mag;
      if(mag < min) min = mag;
      //cout<<"Assign ..."<<endl;
      sobelGI->assign(ii,jj,mag);
      //cout<<"Finished assign."<<endl;
      //fflush(stdout);
    }
  }

  if(max == min){
    // nothing to normalize
    return(sobelGI);
  }

  cout<<"Completed 3D Sobel operator."<<endl;
  cout<<"Max/min magnitudes: "<<max<<"/"<<min<<endl;

  // normalize the image slice between 0 and 255
  for(ii=0; ii<ww; ii++){
    for(jj=0; jj<hh; jj++){
      val = 255 * (sobelGI->value(ii,jj) - min) / (max - min);
      // compute the mean while looping through values
      sum += val;
      // compute the standard deviation while looping
      sum2 += val * val;
      sobelGI->assign(ii,jj,val);
    }
  }
  
  stat[0] = sum / (ww * hh);
  stat[1] = sqrt((sum2 - sum * stat[0]) / (ww * hh));

  return(sobelGI);
}

int Ganita3D::dumpStats(int nstats)
{
  int ii;
  if(nstats >= NUM_STATS) nstats = NUM_STATS;
  cout<<"Stats";
  for(ii=0; ii<nstats; ii++){
    cout<<" : "<<stat[ii];
  }
  cout<<endl;

  return(nstats);
}

int Ganita3D::returnStat(int stat_i)
{
  return(stat[stat_i % NUM_STATS]);
}

