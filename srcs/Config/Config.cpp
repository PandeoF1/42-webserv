/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:21:18 by nard              #+#    #+#             */
/*   Updated: 2022/06/11 22:41:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

/*
TODO:
	Add ip to config["ip"]
	Allowmethods to check
*/

int Config::_verbose = 0;

Config::Config(void)
{
	if (_verbose)
		std::cout << "Config constructor called" << std::endl;
}

Config::~Config(void)
{
	if (_verbose)
		std::cout << "Config destructor called" << std::endl;
}

std::map<int, Config> Config::createConfig(std::string path)
{
	std::map<int, Config>	dump;
	File					file;
	std::string				content;
	size_t					pos = 0;
	

	content = file.getFile(path);
	while (!Config::isEndOfFile(content, pos))
	{
		/* Go ahead to find the bracket and check it */
		while (pos < content.length() && (content[pos] == '\n' || content[pos] == ' ' || content[pos] == '	'))
			pos++;
		pos = Config::isValidServer(content, pos);
		
		std::string tmp = Config::getBracket(content, pos);
		std::cout << "------------------- Extract : -------------------" << tmp << std::endl;
		dump[dump.size()] = Config::extractConfig(tmp);
		std::cout << "------------------- End of extract : -------------------" << std::endl;
		pos += tmp.length();
	}
	return (dump);
}

std::string	Config::operator[](std::string index) const
{
	return (this->getData()[index]);
}

std::map<std::string, std::string>	Config::getData(void) const
{
	return (this->_data);
}

Config		Config::extractConfig(std::string content)
{
	Config	config;
	size_t	pos = 0;

	if (content[pos] == '{')
		pos++;
	/* While server bracket is not cleared */
	while (!Config::isEndOfBracket(content, pos))
	{
		/* Skip all useless char */
		while (pos < content.length() && (content[pos] == '\n' || content[pos] == ' ' || content[pos] == '	'))
			pos++;
		/* If location part == special case of new bracket */
		if (Config::isSameWord(content, pos, Location_Name))
		{
			Location tmp = Location::extractLocation(content, pos);
			config.setLocation(Location::removeBracket(tmp["name"]), tmp);
			pos += getDataBeforeLine(content, pos).length() - 1;
			pos += Config::getBracket(content, pos).length();
		}
		/* Else, check if it's a valid parameter */
		else if (Config::isValidParameter(content, pos))
		{
			config.setData(Config::getWord(content, pos), Config::removeWhiteSpace(Config::getDataBeforeLine(content, pos + Config::getWord(content, pos).length())));
			Config::isValidValue(Config::getWord(content, pos), Config::removeWhiteSpace(Config::getDataBeforeLine(content, pos + Config::getWord(content, pos).length())));
			pos += Config::getWord(content, pos).length() + Config::getDataBeforeLine(content, pos + Config::getWord(content, pos).length()).length();
		}
		else
			throw Config::SyntaxInvalidAt(Config::getLineOfPos(content, pos));
	}
	return (config);
}

int	Config::isValidValue(std::string param, std::string value)
{
	if (param == Server_Valid_Param[Server_IP])
	{
		size_t pos = 0;
		std::cout << std::endl << "Param : " << param << " | Value : " << value << std::endl << std::endl;
		if (value.find(":") == std::string::npos)
			throw Config::SyntaxInvalidValue(param, value);
		else
		{
			pos = value.find(":");
			std::string ip = value.substr(0, pos);
			std::string port = value.substr(pos + 1);
			std::cout << "IP : `" << ip << "` | Port : `" << port << '`' << std::endl << std::endl;
			if (ip.length() > 15 || port.length() > 5)
				throw Config::SyntaxInvalidValue(param, value);
			pos = 0;
			int	dot = 0;
			while (pos < ip.length())
			{
				if (((ip[pos] < '0' || ip[pos] > '9') && ip[pos] != '.') || (ip[pos] == '.' && dot++ > 3) || (ip[pos] == '.' && pos == 0) || (ip[pos] == '.' && pos == ip.length() - 1) || (pos < ip.length() && ip[pos] == '.' && ip[pos + 1] == '.'))
					throw Config::SyntaxInvalidValue(param, value);
				pos++;
			}
			if (dot != 3)
				throw Config::SyntaxInvalidValue(param, value);
			Config::isValidIp(ip);
		}
	}
	else
		return (1);
	//exit(0);
	return (1);
}

int			Config::isValidIp(std::string ip)
{
	size_t pos = ip.find(".");
	std::string a = ip.substr(0, ip.find("."));
	std::string b = ip.substr(pos + 1, ip.find(".", pos + 1) - pos - 1);
	pos = ip.find(".", pos + 1);
	std::string c = ip.substr(pos + 1, ip.find(".", pos + 1) - pos - 1);
	pos = ip.find(".", pos + 1);
	std::string d = ip.substr(pos + 1, ip.find(".", pos + 1) - pos - 1);
	std::cout << a << " " << b << " " << c << " " << d << " " << std::endl;
	// if (a.length() > 3 || b.length() > 3 || c.length() > 3 || d.length() > 3) add it if you want to parse 00005
	// 	throw Config::SyntaxInvalidValue("IP", ip);
	// to do : add ip to config["ip"]
	if (atoi(a.c_str()) > 255 || atoi(b.c_str()) > 255 || atoi(c.c_str()) > 255 || atoi(d.c_str()) > 255)
		throw Config::SyntaxInvalidValue("IP", ip);
	return (0);
}

std::map<int, Location>	Config::getLocation(void) const
{
	return (this->_location);
}

std::map<std::string, Location>	Config::getLocation_str(void) const
{
	return (this->_location_str);
}
void					Config::setLocation(std::string index, Location value)
{
	this->_location_str[index] = value;
	this->_location[this->_location.size()] = value;
	
}

std::string		Config::removeWhiteSpace(std::string content)
{
	size_t		pos = 0;

	while (pos < content.length() && (content[pos] == ' ' || content[pos] == '	'))
		pos++;
	return (content.substr(pos));
}

int			Config::isValidParameter(std::string content, size_t pos)
{
	for (int i = 0; i < Server_Valid_Param_Length; i++)
		if (Config::isSameWord(content, pos, Server_Valid_Param[i]))
			return (1);
	return (0);
}

std::string Config::getWord(std::string content, size_t pos)
{
	std::string tmp;

	/* Copy all char while it is not a space, new line or a tab */
	while (pos < content.length() && ((content[pos] != '\n' && content[pos] != ' ' && content[pos] != '	')))
		tmp += content[pos++];
	return (tmp);
}

std::string	Config::getDataBeforeLine(std::string content, size_t pos)
{
	size_t		x = pos;
	std::string	tmp;

	while (x < content.length() && content[x] != '\n')
		x++;
	return (content.substr(pos, x - pos));
}

int			Config::isSameWord(std::string content, size_t pos, std::string word)
{
	size_t	pos_word = 0;

	while (pos < content.length() && pos_word < word.length() && content[pos] == word[pos_word])
		pos_word++, pos++;
	if (pos_word == word.length() && pos + 1 < content.length() && (content[pos] == ' ' || content[pos] == '	' || content[pos] == '\n'))
		return (1);
	return (0);
}

std::string Config::getBracket(std::string content, size_t pos)
{
	size_t	tmp = pos;
	int		count = 1;

	if (content[tmp] != '{')
		throw Config::SyntaxInvalidAt(Config::getLineOfPos(content, pos));
	tmp++;
	while (tmp < content.length() && count != 0)
	{
		if (content[tmp] == '{')
			count++;
		else if (content[tmp] == '}')
			count--;
		tmp++;
	}
	if (count != 0)
		throw Config::SyntaxInvalidAt(Config::getLineOfPos(content, tmp));
	return (content.substr(pos, tmp - pos));
}

int	Config::isValidServer(std::string content, size_t pos)
{
	if (content.find("server", pos) != pos)
		throw Config::SyntaxInvalidAt(Config::getLineOfPos(content, pos));
	pos += std::string("server").length();
	while (pos < content.length() && (content[pos] == ' ' || content[pos] == '	'))
		pos++;
	if (content[pos] == '{')
		return (pos);
	throw Config::SyntaxInvalidAt(Config::getLineOfPos(content, pos));
}

int	Config::isEndOfFile(std::string content, size_t pos)
{
	size_t	x;

	x = 0;
	while (content.length() > (pos + x) && content.at(pos + x) != '\0')
	{
		if (content.at(pos + x) != '	' && content.at(pos + x) != '\n' && content.at(pos + x) != '\r' && content.at(pos + x) != ' ')
			return (0);
		x++;
	}
	return (1);
}

int	Config::isEndOfBracket(std::string content, size_t pos)
{
	size_t	x;

	x = 0;
	while (content.length() > (pos + x))
	{
		if (content.at(pos + x) != '	' && content.at(pos + x) != '\n' && content.at(pos + x) != '\r' && content.at(pos + x) != ' ')
		{
			if (content.at(pos + x) == '}' && (pos + x) == content.length() - 1)
				return (1);
			return (0);
		}
		x++;
	}
	return (1);
}

int	Config::getLineOfPos(std::string content, size_t pos)
{
	size_t	x;
	size_t	nb_line;

	nb_line = 1;
	x = 0;
	while (x < content.length() && x != pos)
	{
		if (content.at(x) == '\n')
			nb_line++;
		x++;
	}
	return (nb_line);
}

int	Config::findEndBracket(std::string content, size_t pos)
{
	size_t	x;
	size_t	tmp;

	tmp = pos;
	x = 0;
	while (content.at(tmp) != '{')
		tmp++;
	if (content.at(tmp++) == '{')
		x++;
	while (tmp <= content.length() && x != 0)
	{
		if (content.at(tmp) == '}')
			x--;
		else if (content.at(tmp) == '{')
			x++;
		tmp++;
	}
	if (tmp != pos)
		return (tmp + 1);
	return (pos);
}

void		Config::setData(std::string index, std::string value)
{
	this->_data[index] = value;
}