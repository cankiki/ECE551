#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
bool myfunction(string i, string j) {
  return (i < j);
}

struct myclass {
  bool operator()(string i, string j) { return (i < j); }
} myobject;

void get(istream & st) {
  std::vector<std::string> ss;
  std::string temp;
  while (getline(st, temp)) {
    ss.push_back(temp);
  }
  if (ss.size() > 1) {
    std::sort(ss.begin(), ss.begin() + ss.size() / 2);

    std::sort(ss.begin() + ss.size() / 2, ss.end(), myfunction);

    std::sort(ss.begin(), ss.end(), myobject);
  }
  for (std::vector<std::string>::iterator j = ss.begin(); j != ss.end(); ++j) {
    std::cout << *j;
    std::cout << "\n";
  }
}

int main(int argc, char ** argv) {
  int i = 1;
  if (argc == 1) {
    get(std::cin);
  }

  while (i < argc) {
    std::ifstream file(argv[i]);
    if (file) {
      get(file);
    }
    else {
      std::cerr << "wrong";
      return EXIT_FAILURE;
    }
    i++;
  }

  return EXIT_SUCCESS;
}
