// Core GanitaImage storage structure. 

int **allocGI(long ww, long hh){
  long i;
  int **gi;
  gi = (int **) calloc(ww, sizeof(long*));

  // Then allocate each column
  for(i = 0; i < ww; i++) {
    /* the height */
    gi[i] = (int *) calloc(hh, sizeof(long));
  }

  return(gi);
}

long ggDeAlloc(long ww, int **gi){
  long i;
  for(i = 0; i < ww; i++) {
    free(gi[i]);
  }
  return(i);
}

