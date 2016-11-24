#ifndef MODESELECTOR_H_
#define MODESELECTOR_H_

#include "server_accepter.h"
#include "server_accepter.h"
#include "common_define.h"

class ModeSelector {
public:
	ModeSelector(int port);
	ModeSelector(std::string filename);
	virtual ~ModeSelector();

private:
	void exitRoutine(Accepter* connectionsAccepter);
};

#endif /* MODESELECTOR_H_ */
