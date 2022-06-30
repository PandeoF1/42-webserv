#include "Utils.hpp"

std::string Utils::int_to_string(int integer)
{
	std::stringstream ss;
	std::string return_string;

	ss << integer;
	return (ss.str());
}

int Utils::string_to_int(std::string str)
{
	std::stringstream ss;
	int return_int;

	ss << str;
	ss >> return_int;
	return (return_int);
}

std::vector<std::string>	Utils::split_with_comma(std::string line)
{
	std::vector<std::string>	words;

	if (line.size() == 0)
		return (words);
	int k = 0;
	int j = -1;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == ',' || line[i] == ';' || line[i] == '\r' || line[i] == '\n')
		{
			//to prevent segfault from starting at words[1] instead of words[0]
			if (i != 0)
				k++;
			while (line[i] == ' ' || line[i] == '\t' || line[i] == ',' || line[i] == ';' || line [i] == '\r' || line [i] == '\n')
				i++;
			i--;
		}
		else
		{
			//to create a new word in the vector
			if (j != k)
			{
				j = k;
				words.push_back("");
			}
			words[k].push_back(line[i]);
		}
	}
	return (words);
}