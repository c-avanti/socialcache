#include "Server.h"
#include <vector>
#include "Cache.h"

using namespace std;

Server::Server(const char* port)
{
	_server_socket = ServerSocket(port);
	_server_socket.registerHandler(acceptHandler);
}

void Server::start()
{
	_server_socket.runServer();
}

static void* Server::acceptHandler(void* args)
{
	Socket client_fd = *(Socket*)args;
	HttpString input;
	client_fd.read(input);
	HttpString type = input.type();
	if (type == "POST")
	{
		HttpString data = input.data();
		vector<HttpString> key_values;
		data.split(key_values, '&');
		for(vector<HttpString>::iterator iter = key_values.begin(); iter != key_values.end(); ++iter)
		{
			vector<HttpString> key_value;
			iter->split(key_value, '=');
			Cache::getInstance()->put(key_value[0], key_value[1]);
			client_fd.send("");
			client_fd.close();
		}
	}
	else if (type == "GET")
	{
		HttpString key = input.key();
		HttpString value = Cache::getInstance()->get(key);
		client_fd.send(value);
		client_fd.close();
	}
	return NULL;
}
