#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "socket/ServerSocket.h"

ServerSocket::ServerSocket(const char* port):_start_routine(NULL)
{
	addrinfo hints;
	addrinfo* res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;  // Not specifying which of IPv4 or v6 to be used
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // This system's IP

	int fd = -1;
	int result = getaddrinfo(NULL, port, &hints, &res);
	if (result != 0)
	{
		LOG("getaddrinfo: %s\n", gai_strerror(result));
	}
	else
	{
		for (; res != NULL && fd == -1; res = res->ai_addr)
		{
			fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		}
		if (fd == -1)
		{
			LOG("Error while creating socket");
		}
		else
		{
			result = bind(fd, res->ai_addr, res->ai_addrlen);
			if (result == -1)
			{
				LOG("Could not bind socket");
				close(fd);
			}
			else
			{
				_socket = Socket(fd);
			}
		}
	}
}

void ServerSocket::registerHandler(void* (*start_routine) (void*))
{
	_start_routine = start_routine;
}

void ServerSocket::runServer()
{
	int result = ::listen(_socket.getFd(), 10);
	if (result == -1)
	{
		LOG("Failed in listening...");
		return;
	}
	while (true)
	{
		sockaddr_storage client;
		socklen_t len;
		Socket client_fd = ::accept(_socket.getFd(), (sockaddr*)&client, &len);
		if (!client_fd.valid())
		{
			LOG("Error in accept");
			continue;
		}
		pthread_t tid;
		pthread_create(&tid, NULL, _start_routine, &client_fd);
		pthread_detach(tid);
	}
}

