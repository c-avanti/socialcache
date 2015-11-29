#include <sstream>
#include "utils/HttpString.h"

void HttpString::split(vector<HttpString>& tokens, char delimiter)
{
	int start = 0;
	int end = find(delimiter);
	while(end != HttpString::npos)
	{
		end++;
		HttpString token = substr(start, end);
		tokens.push_back(token);
		start = end;
		end = find(delimiter);
	}
	HttpString token = substr(start, end);
	tokens.push_back(token);
}

HttpString HttpString::type()
{
	HttpString first_line;
	istringstream is(*this);
	getline(is, first_line);
	vector<HttpString> tokens;
	first_line.split(tokens, '=');
	return tokens[0];
}

HttpString HttpString::data()
{
	int start = find("\n\n");
	start += 2;
	int end = find("\n", start);
	int len = end - start;
	HttpString data = substr(start, len);
	return data;
}

HttpString HttpString::key()
{
	HttpString first_line;
	istringstream is(*this);
	getline(is, first_line);
	vector<HttpString> tokens;
	first_line.split(tokens, '=');
	return tokens[1];
}
