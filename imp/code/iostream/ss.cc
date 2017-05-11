#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

ostream* open_writer(const char* name, bool stream);
istream* open_reader(const char* name, ostream* os=NULL);
void write(ostream* fh, int* data, size_t len);
size_t read(istream* fh, int*& data);

ostream* open_writer(const char* name, bool stream) {
  if(stream) {
    (void) name;
    ostringstream* oss = new ostringstream;
    return oss;
  } else {
    ofstream* ofs = new ofstream;
    ofs->open(name,ofstream::binary);
    return ofs;
  }
}

istream* open_reader(const char* name, ostream* os) {
  if(os) {
    (void) name;
    ostringstream* oss = reinterpret_cast<ostringstream*>(os);
    istringstream* iss = new istringstream(oss->str());
    return iss;
  } else {
    ifstream* ifs = new ifstream;
    ifs->open(name,ifstream::binary);
    return ifs;
  }
}

void write(ostream* fh, int* data, size_t len) {
  const char* buf = reinterpret_cast<char*>(data);
  streamsize sz = static_cast<streamsize>(len*sizeof(int));
  fh->write(buf,sz);
}

size_t read(istream* fh, int*& data) {
  fh->seekg(0,fh->end);
  streamsize sz = fh->tellg();
  fh->seekg(0,fh->beg);
  cout<< "read size " << sz << "\n";
  size_t numints = static_cast<size_t>(sz)/sizeof(int);
  cout<< numints << "\n";
  data = new int[numints];
  char* buf = reinterpret_cast<char*>(data);
  fh->read(buf,sz);
  return numints;
}

int main() {
  const char* fname = "foo.txt";
  int outdata[3] = {0,3,13};
  for(int i=0;i<2;i++) {
    bool streaming = i;
    ostream* oh = open_writer(fname,streaming);
    write(oh,outdata,3);
    int* indata = NULL;
    istream* ih = open_reader(fname,oh);
    size_t len = read(ih,indata);
    delete oh;
    delete ih;
    for(size_t j=0; j<len; j++)
      cout << indata[j] << " ";
    cout << "\n";
    delete [] indata;
  }
}
