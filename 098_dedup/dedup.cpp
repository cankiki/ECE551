#include <dirent.h>
#include <sys/stat.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>

#include "./file_hasher.h"

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::cerr << "No argument stated." << std::endl;
    return -1;
  }
  file_hasher hasher;
  std::queue<std::string> path_queue;
  // use a BFS iterate through path
  for (int i = 1; i < argc; ++i) {
    std::string s(argv[i]);
    path_queue.push(s);
  }

  while (!path_queue.empty()) {
    struct stat sb;
    DIR * dp;
    struct dirent * dirp;
    std::string curdir = path_queue.front();
    path_queue.pop();
    // std::cout << "checking " << curdir << std::endl;
    lstat(curdir.c_str(), &sb);
    if (S_ISDIR(sb.st_mode)) {
      // std::cout << curdir.c_str() << std::endl;
      dp = opendir(curdir.c_str());
      while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) {
          continue;
        }
        std::stringstream ss;
        ss << curdir << "/" << dirp->d_name;
        path_queue.push(ss.str());
      }
      closedir(dp);
    }
    else if (!S_ISLNK(sb.st_mode)) {
      if (hasher.check_dup(curdir)) {
        // print remove command
      }
    }
  }
  return 0;
}
