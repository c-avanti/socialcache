#include "socket/Socket.h"

class ServerSocket
{
private:
	Socket _socket;
	void* (*_start_routine) (void*);

public:
	ServerSocket(const char* port);
	void registerHandler(void* (*start_routine) (void*));
	void runServer();
};
