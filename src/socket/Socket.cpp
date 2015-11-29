#include "socket/Socket.h"
#include <sys/socket.h>
#include <sys/ioctl.h>

Socket::Socket():_fd(-1)
{
}

Socket::Socket(int fd):_fd(fd)
{
}

int Socket::getFd()
{
	return _fd;
}

void Socket::close()
{
	::close(_fd);
}

bool Socket::valid()
{
	return _fd > 0;
}

void Socket::read(HttpString& input)
{
	int len = 0;
	ioctl(_fd, FIONREAD, &len); //ioctl to find out the length of available data on socket
	if (len > 0) {
		char* buffer = new char[len + 1];
		len = ::read(_fd, buffer, len);
		buffer[len] = 0; //'\0'
		input = HttpString(buffer);
	}
}

void Socket::send(const HttpString& data)
{
	::send(_fd, data.c_str(), (unsigned long int)data.size(), 0);
}
