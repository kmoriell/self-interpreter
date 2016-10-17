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

class String : public Lobby {
 private:
  std::string _internalString;

 public:
  String(std::string _string);
  ~String();

  Lobby* print();
};



#endif /* STRING_H_ */
