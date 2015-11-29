#include "socket/ServerSocket.h"

class Server
{
private:
	ServerSocket _server_socket;
public:
	Server(const char* port);
	void start();

	static void* acceptHandler(void*); //pthread_create needs a global function as its callback
};
