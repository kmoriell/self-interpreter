#ifndef MODESELECTOR_H_
#define MODESELECTOR_H_

#include "server_accepter.h"
#include "server_accepter.h"
#include "common_define.h"

class ModeSelector {
public:
	ModeSelector(int port);

	ModeSelector(std::string filename);

	ModeSelector(const ModeSelector&) = delete;

	ModeSelector(ModeSelector&&) = delete;

	ModeSelector& operator=(const ModeSelector&) = delete;

	ModeSelector& operator=(ModeSelector&&) = delete;
	virtual ~ModeSelector();

private:
	void exitRoutine(Accepter* connectionsAccepter);
};

#endif /* MODESELECTOR_H_ */
