#include <stdio.h>

#define LOG(...) fprintf(stderr, __VA_ARGS__)

class Socket
{
private:
	int _fd;

public:
	Socket();
	Socket(int fd);
	bool valid();
	int getFd();
	void close();

	void read(HttpString& input);
	void send(const HttpString& data);
};
