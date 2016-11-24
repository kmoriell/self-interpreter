#include <iostream>
#include <fstream>
#include "client_proxyServer.h"
#include <unistd.h>

#define CLIENT_PARAMS 4
#define RET_OK 0
#define RET_NOK 1


#define SOLOGUI

#ifdef SOLOGUI
#include "client_mainWindow.h"
#endif


int main(int argc, char **argv) {
  if (argc != 4) {
    std::cout << "Argumentos: >>> .\\client <serverIP> <puerto> <archivo>."
        << std::endl;
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
  Socket socket(server, port);
  ProxyServer proxyServer(socket, morph);

  //Aca se abrio un hilo nuevo que es del proxy
  proxyServer.start();
  std::cout << "Se abre un hilo para el proxyServer." << std::endl;
  std::cout << "Seteamos el flag." << std::endl;
  #ifdef SOLOGUI
  std::string message = LOBBY + PUNTO;
  proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, message);
  auto app = Gtk::Application::create();
  MainWindow window(morph, proxyServer);
  app->run(*window.getWindow());
  #else
  std::string message = script;
  std::cout << "script: " << script << std::endl;
  proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, message);
  sleep(2);

  /*std::string message;
  message = LOBBY + PUNTO;
  proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, message);
  sleep(2);
  std::string message = script;
  message = "lobby _AddSlots: (|punto = (|x<-3.|).|)..";
  proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, message);
  message = "punto = (|x<-3.|).";
  proxyServer.sendCmdMessage(ADD_SLOT, message);
  sleep(2);
  message = "lobby punto.";
  proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, message);
  sleep(2);
  message = "x";
  proxyServer.sendCmdMessage(REMOVE_SLOT, message);
  sleep(2);
  message = "x";
  proxyServer.sendCmdMessage(GET_SLOT_OBJ, message);
  sleep(2);*/

  /*message = "juanjo";
  proxyServer.sendCmdMessage(SET_OBJ_NAME, message);
  sleep(2);
  message = "code..";
  proxyServer.sendCmdMessage(SET_CODESEGMENT, message);
  sleep(2);*/
  morph.mostrar();
  char __char;
    std::cin >> __char;
    #endif

  proxyServer.interrupt();
  proxyServer.join();
  std::cout << "JOIN." << std::endl;
  std::cout << "SALIMOS." << std::endl;
  return 0;
}
