/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:52:24 by nard              #+#    #+#             */
/*   Updated: 2022/06/11 22:40:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

int Location::_verbose = 0;

Location::Location(void)
{
	if (_verbose)
		std::cout << "Location constructor called" << std::endl;
}

Location::~Location(void){
	if (_verbose)
		std::cout << "Location destructor called" << std::endl;
}

Location	Location::extractLocation(std::string content, size_t pos)
{
	Location	loc;
	size_t		global_l = pos;

	pos += std::string("location ").length();
	loc.setLocation("name", Config::getDataBeforeLine(content, pos));
	pos += Config::getDataBeforeLine(content, pos).length() - 1;
	std::string tmp = Config::getBracket(content, pos);
	pos = 1;
	while (!Config::isEndOfBracket(tmp, pos))
	{
		/* Skip all useless char */
		while (pos < tmp.length() && (tmp[pos] == '\n' || tmp[pos] == ' ' || tmp[pos] == '	'))
			pos++;
		if (Location::isValidParameter(tmp, pos))
		{
			if (Config::removeWhiteSpace(Config::getDataBeforeLine(tmp, pos + Config::getWord(tmp, pos).length())).length() > 0)
				loc.setLocation(Config::getWord(tmp, pos), Config::removeWhiteSpace(Config::getDataBeforeLine(tmp, pos + Config::getWord(tmp, pos).length())));
			else
				loc.setLocation(Config::getWord(tmp, pos), "undefined");
			pos += Config::getWord(tmp, pos).length() + Config::getDataBeforeLine(tmp, pos + Config::getWord(tmp, pos).length()).length();
		}
		else
			throw Config::SyntaxInvalidAt(Config::getLineOfPos(content, global_l + pos));
	}
	
	return (loc);
}

int	Location::isValidParameter(std::string content, size_t pos)
{
	for (int i = 0; i < Location_Valid_Param_Length; i++)
		if (Config::isSameWord(content, pos, Location_Valid_Param[i]))
			return (1);
	return (0);
}

void		Location::setLocation(std::string index, std::string value)
{
	this->_data[index] = value;
}

std::string	Location::removeBracket(std::string content)
{
	size_t	pos = content.length() - 1;

	while (!isalnum(content[pos]) && pos > 0)
		pos--;
	return (content.substr(0, pos + 1));
}

std::string	Location::operator[](std::string index) const
{
	return (this->getData()[index]);
}

std::map<std::string, std::string>	Location::getData(void) const
{
	return (this->_data);
}