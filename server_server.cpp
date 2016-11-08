#include "server_server.h"

std::string Server::loadWorkspace(std::string name) {
  m.lock();
  auto it = workspaces.find(name);
  if (it == workspaces.end()) {
    m.unlock();
    throw std::runtime_error("No existe el workspace");
  }

  if (it->second > 0) {
	  m.unlock();
	  std::string error = "El workspace ";
	  error += name + " esta en uso.";
	  throw std::runtime_error(error);
  }

  it->second = it->second + 1;
  m.unlock();

  std::ifstream file(name);
  if (!file.is_open()) {
	  std::string error = "No se puede abrir el workspace ";
	  error += name+ ".";
	  throw std::runtime_error(error);
  }

  std::string x, strFile;

  	while (file >> x)
  		strFile += x + " ";

  	return strFile;
}

std::vector<std::string> Server::availableWorkspace() {
  std::vector<std::string> _workspaces;
  m.lock();
  for (auto it = workspaces.begin(); it != workspaces.end(); ++it) {
    _workspaces.push_back(it->first);
  }
  m.unlock();
  return _workspaces;
}

void Server::newWorkspace(std::string name) {
  m.lock();
  auto it = workspaces.find(name);

  if (it != workspaces.end()) {
    m.unlock();
    throw std::runtime_error("No existe el workspace");
  }

  workspaces.insert(std::make_pair(name, 0));
  m.unlock();
}

void Server::closeWorkspace(std::string name) {
  m.lock();
  auto it = workspaces.find(name);
  if (it == workspaces.end()) {
    m.unlock();
    throw std::runtime_error("No existe el workspace");
  }

  it->second = it->second - 1;
  m.unlock();
}

bool Server::checkExistence(std::string name){

}

void Server::deleteWorkspace(std::string name) {
  m.lock();
  auto it = workspaces.find(name);
  if (it == workspaces.end()) {
    m.unlock();
    throw std::runtime_error("No existe el workspace");
  }

  workspaces.erase(name);
  m.unlock();
}
