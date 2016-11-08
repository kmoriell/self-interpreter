
#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <map>
#include <mutex>
#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
#include "common_object.h"
#include "common_thread.h"

class Server {
private:
  std::mutex m;
  std::map<std::string, uint32_t> workspaces;
  bool checkExistence(std::string name);

  std::vector<Thread*> threads;

public:
  std::string loadWorkspace(std::string name);
  std::vector<std::string> availableWorkspace();
  void newWorkspace(std::string name);
  void closeWorkspace(std::string name);
  void deleteWorkspace(std::string name);
};

#endif /* SERVER_SERVER_H_ */
