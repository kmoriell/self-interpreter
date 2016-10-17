/*
 * number.h
 *
 *  Created on: 15 de oct. de 2016
 *      Author: kmoriell
 */

#ifndef NUMBER_H_
#define NUMBER_H_

#include "lobby.h"

class Number : public Lobby {
 private:
  float number;

 public:
  Number(float number);

  Number operator+(const Number& otherNumber);
  Number operator-(const Number& otherNumber);
  Number operator*(const Number& otherNumber);
  Number operator/(const Number& otherNumber);
};



#endif /* NUMBER_H_ */
