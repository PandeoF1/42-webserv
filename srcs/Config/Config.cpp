/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nard <nard@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:21:18 by nard              #+#    #+#             */
/*   Updated: 2022/06/08 00:28:42 by nard             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

int Config::_verbose = 0;

Config::~Config(void)
{
	if (_verbose)
		std::cout << "Config destructor called" << std::endl;
}

Config *Config::createConfig(std::string path)
{
	File file;
	std::string content;
	std::string	tmp;
	int			pos;
	

	content = file.getFile(path);
	/* Reset var to find all server brackets */
	tmp = "";
	pos = 0;
	while ((pos = content.find("server", pos)) != (int)std::string::npos)
	{
		/* Verif if synthax is ok */
		if (pos + std::string("server").length() <= content.length() && content.at(pos + std::string("server").length()) == ' ')
		{
			/* Put in "TMP" the server bracket */
			tmp = content.substr(pos, Config::findEndBracket(content, pos));
			pos = Config::findEndBracket(content, pos);
			/* Create a new Config object */
			std::cout << tmp << std::endl;
		}
		else
			throw SyntaxInvalidAt(Config::getLineOfPos(content, pos));
	}
	std::cout << Config::getLineOfPos(content, pos) << std::endl;
	if (Config::isEndOfFile(content, pos))
		throw SyntaxInvalidAt(Config::getLineOfPos(content, pos));
	//std::cout << content << std::endl;
	return (NULL);
}

int	Config::isEndOfFile(std::string content, int pos)
{
	int	x;

	x = 0;
	while (content.length() > (size_t)(pos + x) && content.at(pos + x) != '\0')
	{
		if (content.at(pos + x) == '	' || content.at(pos + x) == '\n' || content.at(pos + x) == '\r' || content.at(pos + x) == ' ')
			return (0);
		x++;
	}
	return (1);
}

int	Config::getLineOfPos(std::string content, int pos)
{
	size_t	x;
	int		nb_line;

	nb_line = 0;
	x = 0;
	while (x < content.length() && x != (size_t)pos)
	{
		if (content.at(x) == '\n')
			nb_line++;
		x++;
	}
	return (nb_line);
}

int	Config::findEndBracket(std::string content, int pos)
{
	int	x;
	int	tmp;

	tmp = pos;
	x = 0;
	while (content.at(tmp) != '{')
		tmp++;
	if (content.at(tmp++) == '{')
		x++;
	while (tmp <= (int)content.length() && x != 0)
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

