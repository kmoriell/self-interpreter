#include <iostream>
#include <fstream>
#include "client_proxyServer.h"
#include "client_morph.h"

int main(int argc, char **argv) {

  if (argc != 4) {
    std::cout << "Argumentos: server port archivo." << std::endl;
    return 1;
  }

  std::string server = argv[1];
  std::string _port = argv[2];
  uint32_t port = stoi(_port);
  std::ifstream filein(argv[3]);

  std::string script, x;

  while (filein >> x)
    script += x + " ";

  Morph morph;
  ProxyServer proxy(server, port, morph);
  proxy.sendCode(script);
  proxy.run();
  return 0;
}
