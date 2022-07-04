#include "URL.hpp"

URL::URL() {
}

URL::~URL() {

}

std::string URL::decode(std::string url) 
{
	int n;
	for (int i = 0; i < url_encoding_length; i++)
	{
		while ((n = url.find(url_encoding_utf8[i])) != std::string::npos)
		{
			url.erase(n, url_encoding_utf8[i].size());
			url.insert(n, url_encoding_characters[i]);
		}
	}
	return (url);
}

std::string URL::encode(std::string url) 
{
	int n;
	for (int i = 0; i < url_encoding_length; i++)
	{
		while ((n = url.find(url_encoding_characters[i])) != std::string::npos)
		{
			url.erase(n, url_encoding_characters[i].size());
			url.insert(n, url_encoding_utf8[i]);
		}
	}
	return (url);
}