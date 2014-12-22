// Core graph data structures 

long **ggAlloc(long tv, long *index){
  long i;
  long **gg_edges;
  gg_edges = (long **) calloc(tv, sizeof(long*));

  // Then allocate each column
  for(i = 0; i < index[i]; i++) {
    /* the height */
    gg_edges[i] = (long *) calloc(index[i], sizeof(long));
  }

  return(gg_edges);
}

long ggDeAlloc(long tv, long **gg_edges){
  long i;
  for(i = 0; i < tv; i++) {
    free(gg_edges[i]);
  }
  return(i);
}

