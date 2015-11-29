#include <string>
#include <vector>

using namespace std;

class HttpString : public string
{
public:
	HttpString(): string() {}
	HttpString(const char* rhs): string(rhs){}

	void split(vector<HttpString>& tokens, char delimiter);
	HttpString type();
	HttpString data();
	HttpString key();
};
