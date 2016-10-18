/*
 * number.h
 *
 *  Created on: 15 de oct. de 2016
 *      Author: kmoriell
 */

#ifndef NUMBER_H_
#define NUMBER_H_

#include "lobby.h"
#include <iostream>

class Number : public Lobby {
 private:
  float number;

 public:
  Number();
  Lobby* print(const std::vector<Lobby*>& args);
  Lobby* mutableAsignation(const std::vector<Lobby*>& args);
  Lobby* operator=(const std::vector<Lobby*>& args);
  Lobby* operator*(const std::vector<Lobby*>& args);
  Lobby* operator+(const std::vector<Lobby*>& args);
  Lobby* operator-(const std::vector<Lobby*>& args);
  Lobby* operator/(const std::vector<Lobby*>& args);

  //Lobby* operator==(const std::vector<Lobby*>& args);
  //Lobby* operator!=(const std::vector<Lobby*>& args);
};



#endif /* NUMBER_H_ */
