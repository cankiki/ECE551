#ifndef __FILE_HASHER_H__
#define __FILE_HASHER_H__

#include <fstream>
#include <iostream>
#include <string>
#include <tr1/functional>
#include <unordered_map>

int hashfile(const std::string & filename) {
  std::ifstream f(filename);
  std::stringstream ss;
  ss << f.rdbuf();
  std::tr1::hash<std::string> hash_function;
  return hash_function(ss.str());
}

class file_hasher
{
 private:
  std::unordered_map<int, std::string> dict;

 public:
  file_hasher() {
    dict.clear();
    std::cout << "#!/bin/bash" << std::endl;
  }
  int check_dup(std::string & path) {
    int hash = hashfile(path);
    auto dup = dict.find(hash);
    if (dup == dict.end()) {
      dict.insert({hash, path});
      return 0;
    }
    else if (dup->second != path) {
      std::cout << "#Removing " << path;
      std::cout << " (duplicate of " << dup->second;
      std::cout << ").\n\n";
      std::cout << "rm " << path << "\n\n";
    }
    return 1;
  }
};

#endif
