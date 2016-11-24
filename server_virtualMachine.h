#ifndef SERVER_VIRTUALMACHINE_H_
#define SERVER_VIRTUALMACHINE_H_

#include <stack>
#include "server_object.h"

class VirtualMachine {
private:
	Object* lobby = nullptr;
public:
	Object *createNil();
	Object *createString(std::string &strString);
	Object *createNumber(float number);
	Object *createBoolean(bool value);
	Object* createEmptyObject();
	void destroyObjects(uint32_t count);

	void setLobby(Object* lobby);
};

#endif /* SERVER_VIRTUALMACHINE_H_ */
