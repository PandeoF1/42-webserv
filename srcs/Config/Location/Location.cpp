/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:52:24 by nard              #+#    #+#             */
/*   Updated: 2022/06/10 15:02:06 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

int Location::_verbose = 0;

Location::Location(void) : _name("undefined")
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
	loc.setName(Config::getDataBeforeLine(content, pos));
	pos += loc.getName().length() - 1;
	std::string tmp = Config::getBracket(content, pos);
	std::cout << tmp << std::endl;
	pos = 1;
	while (!Config::isEndOfBracket(tmp, pos))
	{
		/* Skip all useless char */
		while (pos < tmp.length() && (tmp[pos] == '\n' || tmp[pos] == ' ' || tmp[pos] == '	'))
			pos++;
		if (Config::isSameWord(tmp, pos, "allow_methods"))
		{
			std::cout << "Location allow_methods part" << std::endl;
			pos += std::string("allow_methods").length() + 1;
			loc.setAllow_methods(Config::getDataBeforeLine(tmp, pos));
			pos += loc.getAllow_methods().length();
			std::cout << tmp[pos] << std::endl;
		}
		else
			throw Config::SyntaxInvalidAt(Config::getLineOfPos(content, global_l + pos));
	}
	
	return (loc);
}

void Location::setName(std::string name)
{
	this->_name = name;
}

void Location::setAllow_methods(std::string name)
{
	this->_allow_methods = name;
}

std::string Location::getName(void)
{
	return (this->_name);
}

std::string Location::getAllow_methods(void)
{
	return (this->_allow_methods);
}
