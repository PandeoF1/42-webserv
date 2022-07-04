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

std::vector<std::string>	Utils::split_with_space(std::string line)
{
	std::vector<std::string>	words;

	if (line.size() == 0)
		return (words);
	int k = 0;
	int j = -1;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			//to prevent segfault from starting at words[1] instead of words[0]
			if (i != 0)
				k++;
			while (line[i] == ' ' || line[i] == '\t')
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

std::string	Utils::read_fd(int fd)
{
	char	buf[2048];
	char	*value;
	char	*tmp;
	int		size = 0;
	int		len = 0;

	value = (char *)malloc(sizeof(char));
	if (!value)
		return (NULL);
	len = read(fd, buf, 2048);
	while (len > 0)
	{
		tmp = (char *)malloc((size + len + 1) * sizeof(char));
		if (!tmp)
			break ;
		tmp = strncpy(tmp, value, size);
		free(value);
		strncpy(tmp + size, buf, len);
		value = tmp;
		size += len;
		value[size] = '\0';
		len = read(fd, buf, 2048);
	}
	if (len)
		free(value);
	std::string v = value;
	free(value);
	return (v);
}

std::map<std::string, std::string>	Utils::envToMap(char **env)
{
	std::map<std::string, std::string>	map;
	char								*key;
	char								*value;

	while (*env)
	{
		key = *env;
		value = *env;
		while (value[0] != '=' && value[0] != '\0')
			value++;
		if (value[0] == '=')
		{
			value[0] = '\0';
			value++;
			map[key] = value;
		}
		env++;
	}
	return (map);
}

char	**Utils::mapToEnv(std::map<std::string, std::string> map)
{
	//char	**env;
	//int		i;
//
	//env = (char **)malloc(sizeof(char *) * (map.size() + 1));
	//i = 0;
	//while (map.find(i) != map.end())
	//{
	//	env[i] = (char *)malloc(sizeof(char) * (map[i].size() + 1));
	//	strcpy(env[i], map[i].c_str());
	//	i++;
	//}
	//env[i] = NULL;
	//return (env);
}