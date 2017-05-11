#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rdtsc.h"

#define TIME(cmd) {\
    chefio_time(&t0);\
    cmd \
    chefio_time(&t1);\
    elapsed = chefio_time_diff(&t0,&t1,cpus);\
}

int main(int argc, char** argv) {
  const char *method, *mode;
  int i;
  size_t bytes;
  FILE* f;
  char filename[1024];
  char* buf = NULL;
  size_t len;
  chefioTime t0,t1;
  size_t cpus, elapsed, totaltime;
  char* data;
  if( argc < 4 || argc > 5) {
    printf("Usage: %s <stream|posix> <read|write> <number of bytes> [cpus]\n",argv[0]);
    return 0;
  }
  method = argv[1];
  mode = argv[2];
  bytes = atoi(argv[3]);
  if( argc == 5 )
    cpus = atoi(argv[4]);
  else 
    cpus = chefio_getCyclesPerMicroSec();

  data = (char*) malloc(bytes*sizeof(char));
  for(i=0;i<bytes;i++) data[i] = 1;

  totaltime = 0;
  /* stream */
  if( !strcmp(method,"stream") && !strcmp(mode,"write") ) {
    TIME(f = open_memstream(&buf, &len);)
  } if( !strcmp(method,"stream") && !strcmp(mode,"writeprealloc") ) {
    TIME(buf = malloc(bytes*sizeof(char));)
    totaltime += elapsed;
    TIME(f = fmemopen(buf, bytes, "w");)
  } else if( !strcmp(method,"stream") && !strcmp(mode,"read") ) {
    TIME(f = fmemopen(buf, bytes, "r");)
  } else if( !strcmp(method,"stream") && !strcmp(mode,"readprealloc") ) {
    TIME(buf = malloc(bytes*sizeof(char));)
    totaltime += elapsed;
    TIME(f = fmemopen(buf, bytes, "r");)
  /* posix */
  } else if( !strcmp(method,"posix") && !strcmp(mode,"write") ) {
    TIME(f = fopen("/tmp/foo.txt", "w");)
  } else if( !strcmp(method,"posix") && !strcmp(mode,"read") ) {
    sprintf(filename,"/tmp/%lu.dat",bytes);
    TIME(f = fopen(filename, "r");)
  }
  printf("opened %s in %s mode in %lu microseconds\n",method,mode,elapsed);
  totaltime += elapsed;

  if( !strcmp(mode,"write") || !strcmp(mode,"writeprealloc") ) {
    TIME(fwrite(data,sizeof(char),bytes,f);)
  } else if( !strcmp(mode,"read") || !strcmp(mode,"readprealloc") ) {
    TIME(fread(data,sizeof(char),bytes,f);)
  }
  totaltime += elapsed;
  /* B/us * 10^6us/s * MB/10^6B = MB/s */
  printf("%s %lu bytes in %lu microseconds perceived bandwidth %lu MB/s\n",
    mode,bytes,elapsed,bytes/elapsed);

  TIME(fclose(f);)
  totaltime += elapsed;
  printf("closed %s in %s mode %lu microseconds\n",method,mode,elapsed);

  printf("%s %lu bytes in %lu microseconds effective bandwidth %lu MB/s\n",
    mode,bytes,totaltime,bytes/totaltime);

  if( !strcmp(method,"stream") &&
      ( !strcmp(mode,"write") || 
        !strcmp(mode,"writeprealloc") || 
        !strcmp(mode,"readprealloc") ) ) {
    free(buf);
  }
  free(data);
  return 0;
}
