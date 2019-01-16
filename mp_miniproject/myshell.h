#include <bits/stdc++.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
class shell
{
 private:
  string cmd;
  vector<string> cmd_argv;
  string executable;
  string ECE551PATH;

 public:
  shell() : cmd(), cmd_argv(), executable(), ECE551PATH(getenv("PATH")) {}

  string get_ECE551PATH() { return ECE551PATH; }

  map<string, string> add_ece551path(map<string, string> vars) {
    string key = "ECE551PATH";
    string value = ECE551PATH;
    vars.insert(pair<string, string>(key, value));
    return vars;
  }

  vector<string> escape_cmd(string cmd) {  //to parse the command
    vector<string> argv;
    size_t prevpos = 0;
    size_t pos = 0;

    // Ignore all predecessing spaces
    while (pos < cmd.size() && cmd[pos] == ' ') {
      pos++;
    }

    // If all spaces, return an empty vector argv
    if (pos == cmd.size()) {
      return argv;
    }

    // Find next space char
    string subarg = "";
    prevpos = pos;
    pos = cmd.find(' ', prevpos);
    while (pos != string::npos) {
      // if the space is escaped, put what is before the space and the space itself to temp string
      if (cmd[pos - 1] == '\\') {
        subarg += cmd.substr(prevpos, pos - prevpos - 1) + " ";
      }
      else {
        // else, put the argument into argv vector
        subarg += cmd.substr(prevpos, pos - prevpos);
        argv.push_back(subarg);
        subarg = "";
      }
      prevpos = pos + 1;
      pos = cmd.find(' ', prevpos);
    }
    // Finally, put the last argument into argv
    subarg += cmd.substr(prevpos);
    argv.push_back(subarg);

    return argv;
  }

  string find_executable(
      string cmd,
      const vector<string> & path_book) {  //find if the command in path is executable
    struct stat sb;
    if (cmd.find('/') == string::npos) {
      // a command name that does not have a forward slash (/)
      for (size_t i = 0; i < path_book.size(); i++) {
        char * path = new char[path_book[i].size() + cmd.size() + 10];
        path = strcpy(path, path_book[i].c_str());
        strcpy(&path[path_book[i].size() - 1], "/");
        strcpy(&path[path_book[i].size()], cmd.c_str());
        path[path_book[i].size() + cmd.size()] = '\0';

        if (lstat(path, &sb) == 0 && sb.st_mode & S_IXUSR) {
          return path;
        }
      }
      cerr << "Command " << cmd << " not found " << endl;  //not found in PATH
    }
    else {
      //path name does contain a / in it
      string path = cmd;
      return path;

      //if (stat(path.c_str(), &sb) == 0 && sb.st_mode & S_IXUSR) {
      //  return path;
    }
    return "";
  }

  void change_directory(const vector<string> & cmd_argv,
                        int argc) {  //cd command to change directory
    if (argc == 1) {                 //only cd
      chdir("/");
    }
    else if (argc == 2) {
      int rc = chdir(cmd_argv[1].c_str());
      if (rc == 0) {
        return;
      }
      else {
        cerr << "cd: " << cmd_argv[1] << " : No such file or directory" << endl;
        return;
      }
    }
    else {
      cerr << "invalid cd" << endl;
    }
  }

  bool varname_is_legal(string var_name) {  //check if variable name is legal
    for (size_t i = 0; i < var_name.size(); i++) {
      char let = var_name[i];
      if (let < 48 || (let > 57 && let < 65) || (let > 90 && let != 95 && let < 97) || let > 122) {
        return false;
      }
    }
    return true;
  }

  //set variable
  map<std::string, std::string> set_var(const vector<string> & argv,
                                        int argc,
                                        map<std::string, std::string> vars) {
    if (argc == 3) {
      //check var name
      string var_name = argv[1];
      if (varname_is_legal(var_name) == false) {
        cerr << "variable can only contains letters, underscores or numbers" << endl;
      }
      string key = argv[1];
      string value = argv[2];
      map<string, string>::iterator it = vars.find(key);
      if (it != vars.end()) {            //find the key in previous map
        vars.find(key)->second = value;  //replace the value
      }
      else {
        vars.insert(pair<string, string>(key, value));  //not find, insert key and value into map
      }
    }
    else {
      cerr << "invalid set" << endl;
    }
    return vars;
  }

  //export variable
  void export_var(const vector<string> & argv, int argc, map<string, string> vars) {
    string key = argv[1];
    string value = vars.find(key)->second;
    if (argc != 2) {
      cerr << "invalid export" << endl;
    }

    map<string, string>::iterator it_v = vars.find(key);  //find if var is in vars
    if (it_v != vars.end()) {
      setenv(key.c_str(), value.c_str(), true);
      /*
      map<string, string>::iterator it_e = env.find(key);  //find if var is in env
      if (it_e != env.end()) {  //if find, replace the value in the environment
        env.find(key)->second = value;
      }
      else {  //not find in env,insert pair into env

        env.insert(pair<string, string>(key, value));
      }
    }

    else {  //not find in vars, no such variables
      cerr << "no such variable" << endl;
      exit(EXIT_FAILURE);
    }
    return env;

      */
    }
  }
  bool isnum(string s)  // check if the string is a base 10 number
  {
    stringstream sin(s);
    double t;
    char p;
    if (!(sin >> t)) {
      return false;
    }
    if (sin >> p) {
      return false;
    }
    else
      return true;
  }

  //add inc command
  map<string, string> inc_var(const vector<string> & argv, int argc, map<string, string> vars) {
    if (argc != 2) {
      cerr << "invalid inc" << endl;
    }
    string key = argv[1];
    string value;
    map<string, string>::iterator it_v = vars.find(key);  //find if var is in vars
    if (it_v != vars.end()) {
      value = vars.find(key)->second;
      //check if var represents a number in base10
      if (isnum(value)) {
        string s;
        stringstream ss;
        int num;
        //convert string to number
        ss << value;
        ss >> num;
        num++;
        //convert number to string
        stringstream s2;
        s2 << num;
        s = s2.str();
        vars.find(key)->second = s;  //replace new value in vars map
      }
      else {  //not numnber
        vars.find(key)->second = "1";
      }
    }
    else {
      if (varname_is_legal(key) == false) {  //check if var name is legal
        cerr << "variable can only contains letters, underscores or numbers" << endl;
      }
      vars.insert(pair<string, string>(key, "1"));  //legal var name, insert into vars map
    }
    return vars;
  }

  string replace_helper(string sub_var, map<string, string> vars) {
    //replace the variable name in the vars map with value
    string new_sub_var;
    size_t i;
    if (sub_var == "$") {
      return sub_var;
    }

    for (i = 1; i < sub_var.size(); i++) {  //check from pos 1 cause pos 0 is $
      char let = sub_var[i];
      if (let < 48 || (let > 57 && let < 65) || (let > 90 && let != 95 && let < 97) || let > 122) {
        break;
      }
    }
    string key = sub_var.substr(1, i - 1);  //variable name of string

    string value;
    string rest = sub_var.substr(i);  //rest of the string
    //find if the variable name key is in the vars map
    map<string, string>::iterator it_v = vars.find(key);
    if (it_v != vars.end()) {  //if find, replace with value
      value = vars.find(key)->second;
      new_sub_var = value + rest;
    }
    else {  //if not find, do not change

      new_sub_var = sub_var;
    }
    return new_sub_var;
  }

  string replace_var(string command, map<string, string> vars) {
    //convert the legal var name after it
    vector<string> temp_name;
    string new_command;
    string sub_var;
    size_t pos1 = 0;
    size_t pos2 = 0;
    pos1 = command.find("$");
    while (pos1 != string::npos) {
      pos2 = command.find("$", pos1 + 1);
      sub_var = command.substr(pos1, pos2 - pos1);

      string new_sub_var = replace_helper(sub_var, vars);  //replace legal sub varname in var
      temp_name.push_back(new_sub_var);                    //store in the vector string
      pos1 = pos2;
    }
    //convert the string in vector string into the string command
    for (vector<string>::iterator i = temp_name.begin(); i != temp_name.end(); i+\
+) {
      new_command += *i;
    }

    return new_command;
  }
};
