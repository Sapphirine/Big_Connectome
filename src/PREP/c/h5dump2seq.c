// gcc -O3 h5dump2seq.c -o h5dump2seq
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFSIZE
#define BUFSIZE
#endif

int main(int argc, char *argv[])
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
  int startX, startY, startZ;

  if(argc < 2){
    fprintf(stdout, "Usage: input-file [start-x start-y start-z]\n");
    exit(1);
  }

  infile = fopen(argv[1],"rb");
  if(infile == NULL){
    fprintf(stderr, "Unable to read %s.\n", argv[1]);
    exit(1);
  } 

  if(argc > 4){
    sscanf(argv[2],"%d",&startX);
    sscanf(argv[3],"%d",&startY);
    sscanf(argv[4],"%d",&startZ);
  }

  //sscanf(argv[2],"%d", &xblk_size);

  if(argc > 4){
    sprintf(fn,"%s_%08d_%08d_%08d.pgm",argv[1], startX, startY, startZ);
  }
  else sprintf(fn,"%s_%08d.pgm",argv[1], count);

  outfile = fopen(fn,"w");
  if(outfile == NULL){
    fprintf(stderr, "Unable to open %s.\n", fn);
    exit(1);
  }

  if(fgets ( line2, sizeof line2, infile ) == NULL){
    fprintf(stdout, "Could not read file %s.\n", argv[1]);
    exit(1);
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
	if(argc > 4){
	  sprintf(fn,"%s_%08d_%08d_%08d.pgm",argv[1], startX, startY, count + startZ);
	}
	else sprintf(fn,"%s_%08d.pgm",argv[1], count);
	outfile = fopen(fn,"w");
	if(outfile == NULL){
	  fprintf(stderr, "Unable to open %s.\n", fn);
	  exit(1);
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
  fclose(outfile);

  exit(1);
}

