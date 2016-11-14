
#ifndef SERVER_VIRTUALMACHINE_H_
#define SERVER_VIRTUALMACHINE_H_

#include <stack>
#include "server_object.h"

const std::string OP_SUMA = "+";
const std::string OP_RESTA = "-";
const std::string OP_MULTIPLICACION = "*";
const std::string OP_DIVISION = "/";
const std::string OP_DISTINTO = "!=";
const std::string OP_IGUAL = "==";
const std::string METHOD_PRINT = "print";

class VirtualMachine {
 private:
  std::stack<Object*> objects;
 public:
  ~VirtualMachine();

  Object *createNil();
  Object *createString(std::string &strString);
  Object *createNumber(float number);
  Object *createBoolean(bool value);
  Object* createEmptyObject();
  void destroyObjects(uint32_t count);

};

#endif /* SERVER_VIRTUALMACHINE_H_ */
