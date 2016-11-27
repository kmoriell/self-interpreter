#ifndef SERVER_VIRTUALMACHINE_H_
#define SERVER_VIRTUALMACHINE_H_

#include <stack>
#include "server_object.h"

class VirtualMachine {
private:
	Object* lobby = nullptr;

public:
	VirtualMachine(const VirtualMachine&) = delete;
	VirtualMachine(VirtualMachine&&) = delete;
	VirtualMachine& operator=(const VirtualMachine&) = delete;
	VirtualMachine& operator=(VirtualMachine&&) = delete;
	VirtualMachine() {}
	Object *createNil();
	Object *createString(std::string &strString);
	Object *createNumber(float number);
	Object *createBoolean(bool value);
	Object* createEmptyObject();

	Object* findObjectById(uint32_t id);
	void destroyObjects(uint32_t count);

	void setLobby(Object* lobby);
};

#endif /* SERVER_VIRTUALMACHINE_H_ */
