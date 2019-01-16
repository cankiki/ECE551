#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream f(fname);
  int i;
  if (!f.is_open()) {
    std::cerr << "Failed to open file " << fname << " !\n";
    exit(EXIT_FAILURE);
  }
  uint64_t * counts = new uint64_t[257]();
  while ((i = f.get()) != EOF) {
    //  i = f.get();
    //   i = (i == -1) ? 256 : i;
    counts[i]++;
  }
  counts[256] = 1;
  f.close();

  return counts;

  //WRITE ME!
}
