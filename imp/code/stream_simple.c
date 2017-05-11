#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  const char *method, *mode;
  int i;
  size_t bytes;
  FILE* f;
  char filename[1024];
  char* buf = NULL;
  size_t len;
  char* data;
  if( argc != 4 ) {
    printf("Usage: %s <stream|posix>"
           "<read|write> <number of bytes>\n",argv[0]);
    return 0;
  }
  method = argv[1];
  mode = argv[2];
  bytes = atoi(argv[3]);

  data = (char*) malloc(bytes*sizeof(char));
  for(i=0;i<bytes;i++) data[i] = 1;

  /**** open stream ****/
  if( !strcmp(method,"stream") && !strcmp(mode,"write") ) {
    f = open_memstream(&buf, &len);
  } if( !strcmp(method,"stream") && !strcmp(mode,"writeprealloc") ) {
    buf = malloc(bytes*sizeof(char));
    f = fmemopen(buf, bytes, "w");
  } else if( !strcmp(method,"stream") && !strcmp(mode,"read") ) {
    f = fmemopen(buf, bytes, "r");
  } else if( !strcmp(method,"stream") && !strcmp(mode,"readprealloc") ) {
    buf = malloc(bytes*sizeof(char));
    f = fmemopen(buf, bytes, "r");
  /**** open posix ****/
  } else if( !strcmp(method,"posix") && !strcmp(mode,"write") ) {
    f = fopen("/tmp/foo.txt", "w");
  } else if( !strcmp(method,"posix") && !strcmp(mode,"read") ) {
    sprintf(filename,"/tmp/%lu.dat",bytes);
    f = fopen(filename, "r");
  }

  /**** read|write ****/
  if( !strcmp(mode,"write") || !strcmp(mode,"writeprealloc") ) {
    fwrite(data,sizeof(char),bytes,f);
  } else if( !strcmp(mode,"read") || !strcmp(mode,"readprealloc") ) {
    fread(data,sizeof(char),bytes,f);
  }
  fclose(f);

  if( !strcmp(method,"stream") &&
      ( !strcmp(mode,"write") || 
        !strcmp(mode,"writeprealloc") || 
        !strcmp(mode,"readprealloc") ) ) {
    free(buf);
  }
  free(data);
  return 0;
}
