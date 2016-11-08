#include <map>
#include <mutex>
#include <string>
#include <stdexcept>
#include <fstream>
#include "common_object.h"

class Server {
private:
  std::mutex m;
  std::map<std::string, uint32_t> workspaces;
  bool checkExistence(std::string name);
public:
  void loadWorkspace(std::string name);
  std::vector<std::string> availableWorkspace();
  void newWorkspace(std::string name);
  void closeWorkspace(std::string name);
  void deleteWorkspace(std::string name);
};
