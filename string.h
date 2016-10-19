/*
 * string.h
 *
 *  Created on: 15 de oct. de 2016
 *      Author: kmoriell
 */

#ifndef STRING_H_
#define STRING_H_

#include <string>
#include <iostream>
#include "object.h"

class String : public Object {
 private:
  std::string _internalString;

 public:
  String();
  String(std::string _string);
  ~String();

  Object* print(const std::vector<Object*>& args);
  Object* operator=(const std::vector<Object*>& args);
  Object* mutableAsignation(const std::vector<Object*>& args);
};



#endif /* STRING_H_ */
