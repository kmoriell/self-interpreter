/*
 * string.h
 *
 *  Created on: 15 de oct. de 2016
 *      Author: kmoriell
 */

#ifndef STRING_H_
#define STRING_H_

#include "lobby.h"
#include <string>
#include <iostream>

class String : public Lobby {
 private:
  std::string _internalString;

 public:
  String();
  String(std::string _string);
  ~String();

  Lobby* print(const std::vector<Lobby*>& args);
  Lobby* operator=(const std::vector<Lobby*>& args);
  Lobby* mutableAsignation(const std::vector<Lobby*>& args);
};



#endif /* STRING_H_ */
