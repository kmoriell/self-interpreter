/*
 * number.h
 *
 *  Created on: 15 de oct. de 2016
 *      Author: kmoriell
 */

#ifndef NUMBER_H_
#define NUMBER_H_

#include <iostream>
#include "object.h"

class Number : public Object {
 private:
  float number;

 public:
  Number();
  Number(float newNumber, bool _mutable);
  Number(const Number& _number);
  Object* print(const std::vector<Object*>& args);
  Object* mutableAsignation(const std::vector<Object*>& args);
  Object* operator=(const std::vector<Object*>& args);
  Object* operator*(const std::vector<Object*>& args);
  Object* operator+(const std::vector<Object*>& args);
  Object* operator-(const std::vector<Object*>& args);
  Object* operator/(const std::vector<Object*>& args);

  //Lobby* operator==(const std::vector<Lobby*>& args);
  //Lobby* operator!=(const std::vector<Lobby*>& args);
};



#endif /* NUMBER_H_ */
