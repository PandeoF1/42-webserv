/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:21:18 by nard              #+#    #+#             */
/*   Updated: 2022/06/10 15:45:16 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

/*
TODO:
	extractConfig :
		ex (root /test), gerer x espace et pas que un (+1 dans le += pos), pareil pour locaation dcp

*/

int Config::_verbose = 0;

Config::Config(void) : _serverName("undefined"), _root("undefined"), _index("undefined"), _allow_methods("undefined"), _listen_ip("undefined"), _listen_port(0)
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
	std::map<int, Config> dump;
	File			file;
	std::string		content;
	size_t			pos = 0;
	

	content = file.getFile(path);
	/* Go ahead to find the bracket and check it */
	while (pos < content.length() && (content[pos] == '\n' || content[pos] == ' ' || content[pos] == '	'))
		pos++;
	/* If its end of file, this is invalid */
	if (Config::isEndOfFile(content, pos))
		throw SyntaxInvalidAt(Config::getLineOfPos(content, pos));

	pos = Config::isValidServer(content, pos);
	
	std::string tmp = Config::getBracket(content, pos);
	std::cout << tmp << std::endl << "------------------- Extract : -------------------" << std::endl;
	dump[0] = Config::extractConfig(tmp);
	if (Config::isEndOfFile(content, pos))
		throw SyntaxInvalidAt(Config::getLineOfPos(content, pos));
	exit(0);
	return (dump);
}

std::string	Config::operator[](std::string index) const
{
	if (index == "test")
		return (std::string("hey"));
	return (std::string(";)"));
}

Config		Config::extractConfig(std::string content)
{
	Config	config;
	size_t	pos = 0;

	std::cout << config["test"] << " " << config["gfgd"] << std::endl;
	if (content[pos] == '{')
		pos++;
	/* While server bracket is not cleared */
	while (!Config::isEndOfBracket(content, pos))
	{
		/* Skip all useless char */
		while (pos < content.length() && (content[pos] == '\n' || content[pos] == ' ' || content[pos] == '	'))
			pos++;
		
		config._data["test"] = "hey";
		if (Config::isSameWord(content, pos, "location"))
		{
			std::cout << "location part" << std::endl;
			//pos += std::string("location").length() + 1;
			//config.setAllow_methods(Config::getDataBeforeLine(content, pos));
			pos += getDataBeforeLine(content, pos).length() - 1;
			pos += Config::getBracket(content, pos).length();
		}
		else
		{
			//std::cout << "test : " << Config::getWord(content, pos) << std::endl;
			std::cout << "New type : " << Config::getWord(content, pos) << std::endl;
			
			config._data[Config::getWord(content, pos)] = Config::getDataBeforeLine(content, pos + Config::getWord(content, pos).length() + 1 // replace 1 by the number of space / tab);
			pos += Config::getWord(content, pos).length() + config._data[Config::getWord(content, pos)].length() + 1;
		}
		// else
		// 	throw Config::SyntaxInvalidAt(Config::getLineOfPos(content, pos));
		std::cout << content[pos - 1] << " | " << pos << " | " << Config::getLineOfPos(content, pos) << std::endl;
		//exit(0);
	}
	std::cout << config._data["listen"] << std::endl;
	(void)content;
	return (config);
}

std::string Config::getWord(std::string content, size_t pos)
{
	std::string tmp;

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
	if (pos_word == word.length() && pos + 1 < content.length() && (content[pos] == ' ' || content[pos] == '	'))
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
	if (content.find("server") != pos)
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
	while (content.length() > (size_t)(pos + x) && content.at(pos + x) != '\0')
	{
		if (content.at(pos + x) == '	' || content.at(pos + x) == '\n' || content.at(pos + x) == '\r' || content.at(pos + x) == ' ')
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

std::string Config::getServerName(void) const
{
	return (this->_serverName);
}

std::string	Config::getIndex(void) const
{
	return (this->_index);
}

std::string	Config::getRoot(void) const
{
	return (this->_root);
}

std::string	Config::getAllow_methods(void) const
{
	return (this->_allow_methods);
}

std::string	Config::getListen_ip(void) const
{
	return (this->_listen_ip);
}

int			Config::getListen_port(void) const
{
	return (this->_listen_port);
}

std::map<int, Location>	Config::getLocation(void) const
{
	return (this->_location);
}

void	Config::setServerName(std::string data)
{
	this->_serverName = data;
}

void	Config::setIndex(std::string data)
{
	this->_index = data;
}

void	Config::setRoot(std::string data)
{
	this->_root = data;
}

void	Config::setAllow_methods(std::string data)
{
	this->_allow_methods = data;
}

void	Config::setListen_ip(std::string data)
{
	this->_listen_ip = data;
}

void	Config::setListen_port(int data)
{
	this->_listen_port = data;
}
