#include "myshell.h"

vector<string> find_path(string & path) {  //parse the PATH
                                           //@return: a vector containing all the paths in $PATH
  vector<string> full_path;

  size_t prevpos = 0;
  size_t pos = 0;
  pos = path.find(':', prevpos);
  while (pos != string::npos) {
    string subpath = path.substr(prevpos, pos - prevpos + 1);
    subpath[pos - prevpos] = '\0';
    full_path.push_back(subpath);
    prevpos = pos + 1;
    pos = path.find(':', prevpos);
  }
  string subpath = path.substr(prevpos);
  full_path.push_back(subpath);
  return full_path;
}

int main() {
  // map<string, string> env;   //store environment variables
  map<string, string> vars;  //store keys and values of variables

  while (true) {
    string command_name;
    char buf[100];
    setenv("ECE551PATH", getenv("PATH"), true);
    //show the current directory
    string current_dir_name = getcwd(buf, sizeof(buf));
    cout << "myShell:" << current_dir_name << "$";
    pid_t cpid, w;
    int wstatus;
    shell myshell;
    int argc = 0;
    //read one line of input (from stdin), which is the name of a command
    getline(std::cin, command_name);

    if (command_name == "exit") {  //If the user types the command "exit," the shell exit.
      break;
    }

    vector<string> cmd_argv = myshell.escape_cmd(command_name);  //parse the command line

    //skip empty string in command line
    vector<string> cmd_argv_s;
    for (vector<string>::iterator i = cmd_argv.begin(); i != cmd_argv.end(); i++) {
      if ((*i).length() != 0 && (*i) != "") {  //check for empty string
        string temp = *i;
        cmd_argv_s.push_back(temp);
      }
    }

    //count for argc
    for (vector<string>::iterator i = cmd_argv_s.begin(); i != cmd_argv_s.end(); ++i) {
      if (*i != "") {
        argc++;
      }
    }

    if (cmd_argv_s.size() < 1) {
      exit(EXIT_SUCCESS);
    }

    //if contains $variable name, replace it with variable's value
    for (vector<string>::iterator i = cmd_argv_s.begin(); i != cmd_argv_s.end(); i++) {
      string temp_command = *i;
      size_t pos = temp_command.find("$");
      if (pos != string::npos) {                       //check for $
        *i = myshell.replace_var(temp_command, vars);  //replace it with value
      }
    }

    if (cmd_argv_s[0] == "cd") {  //add cd command
      myshell.change_directory(cmd_argv_s, argc);
      continue;
    }

    //create a variable called ECE551PATH in var map
    vars = myshell.add_ece551path(vars);

    if (cmd_argv_s[0] == "set") {  //set var
      vars = myshell.set_var(cmd_argv_s, argc, vars);
      continue;
    }
    if (cmd_argv_s[0] == "export") {  //export var
      myshell.export_var(cmd_argv_s, argc, vars);
      continue;
    }

    if (cmd_argv_s[0] == "inc") {  //inc var
      vars = myshell.inc_var(cmd_argv_s, argc, vars);
      continue;
    }

    cpid = fork();
    if (cpid < 0) {
      perror("fork");
      exit(EXIT_FAILURE);
    }

    else if (cpid == 0) { /* Code executed by child */
      string key = "ECE551PATH";
      string PATH = vars.find(key)->second;  //get the ECE551PATH

      vector<string> path_book =
          find_path(getenv("ECE551PATH"));  //searches the environment for command

      string executable = myshell.find_executable(cmd_argv_s[0], path_book);

      if (executable == "") {  //if command not executable,exit
        exit(EXIT_SUCCESS);
      }

      //construct newargv for execve

      cmd_argv_s[0] = executable;
      char ** newargv;
      newargv = new char *[cmd_argv_s.size() + 1];

      for (size_t i = 0; i < cmd_argv_s.size(); i++) {
        newargv[i] = new char[cmd_argv_s[i].size() + 1];
        strcpy(newargv[i], cmd_argv_s[i].c_str());
      }
      newargv[cmd_argv_s.size()] = NULL;
      /*
      //construct newenvir for execve
      //first get value from env map
      vector<string> value;
      map<string, string>::iterator iter;
      iter = env.begin();
      while (iter != env.end()) {
        string v = iter->second;
        value.push_back(v);
        iter++;
      }
      //second convert vector<string> to char**
      char ** newenvir = new char *[value.size() + 1];
      for (size_t i = 0; i < value.size(); i++) {
        newenvir[i] = new char[value[i].size() + 1];
        strcpy(newenvir[i], value[i].c_str());
      }
      newenvir[env.size()] = NULL;
      */

      //execve
      int ret = execve(newargv[0], newargv, environ);

      //free memory
      for (size_t i = 0; i < cmd_argv_s.size() + 2; i++) {
        delete[] newargv[i];
      }
      delete[] newargv;
      //      for (size_t i = 0; i < value.size() + 2; i++) {
      // delete[] newenvir[i];
      // }
      // delete[] newenvir;

      if (ret == -1) {
        perror("execve error");
      }

      perror("execve"); /* execve() returns only on error */

      exit(EXIT_FAILURE);
    }

    else { /* Code executed by parent */
      do {
        w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
        if (w == -1) {
          perror("waitpid");
          exit(EXIT_FAILURE);
        }

        if (WIFEXITED(wstatus)) {
          printf("Program exited with status %d\n", WEXITSTATUS(wstatus));
        }
        else if (WIFSIGNALED(wstatus)) {
          printf("Program was killed by signal %d\n", WTERMSIG(wstatus));
        }
      } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    }

    //loop until EOF is encountered reading from stdin
    if (std::cin.eof())
      break;
  }

  // env.clear();
  vars.clear();

  exit(0);
}
