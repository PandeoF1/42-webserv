#include "Location.hpp"

int Location::_verbose = 0;

Location::Location(void)
{
	if (_verbose)
		std::cout<< "Location constructor called" << std::endl;
}

Location::~Location(void){
	if (_verbose)
		std::cout<< "Location destructor called" << std::endl;
}

Location	Location::extractLocation(std::string content, size_t pos)
{
	Location	loc;

	pos += std::string("location ").length();
	loc.setLocation("name", Config::getDataBeforeLine(content, pos));
	pos += Config::getDataBeforeLine(content, pos).length() - 1;
	std::string tmp = Config::getBracket(content, pos);
	size_t		global_l = pos;
	pos = 1;
	while (!Config::isEndOfBracket(tmp, pos))
	{
		/* Skip all useless char */
		while (pos < tmp.length() && (tmp[pos] == '\n' || tmp[pos] == ' ' || tmp[pos] == '	'))
			pos++;
		if (Location::isValidParameter(tmp, pos))
		{
			if (Config::removeWhiteSpace(Config::getDataBeforeLine(tmp, pos + Config::getWord(tmp, pos).length())).length() > 0)
			{
				loc.setLocation(Config::getWord(tmp, pos), Config::removeWhiteSpace(Config::getDataBeforeLine(tmp, pos + Config::getWord(tmp, pos).length())));
				loc.isValidValue(Config::getWord(tmp, pos), Config::removeWhiteSpace(Config::getDataBeforeLine(tmp, pos + Config::getWord(tmp, pos).length())));
			}
			else
				throw Config::SyntaxInvalidAt(Config::getLineOfPos(content, global_l + pos));
			pos += Config::getWord(tmp, pos).length() + Config::getDataBeforeLine(tmp, pos + Config::getWord(tmp, pos).length()).length();
		}
		else
			throw Config::SyntaxInvalidAt(Config::getLineOfPos(content, global_l + pos));
	}
	
	return (loc);
}

int	Location::isValidValue(std::string param, std::string value)
{
	if (param == Location_Valid_Param[Location_Methods])
		Config::isValidMethods(value);
	else if (param == Location_Valid_Param[Location_Root] && Config::getNumberOfValue(value) != 1)
		throw Config::SyntaxInvalidValue(Location_Valid_Param[Location_Root], value);
	else if (param == Location_Valid_Param[Location_Cgi] && Config::getNumberOfValue(value) != 1)
		throw Config::SyntaxInvalidValue(Location_Valid_Param[Location_Cgi], value);
	else if (param == Location_Valid_Param[Location_Buffer])
	{
		if (atoi(value.c_str()) < Buffer_Min || atoi(value.c_str()) > Buffer_Max)
			throw Config::SyntaxInvalidValue(Location_Valid_Param[Location_Buffer], value);
		for (size_t x = 0; x < value.length(); x++)
			if (!isdigit(value[x]))
				throw Config::SyntaxInvalidValue(Location_Valid_Param[Location_Buffer], value);
	}
	else if (param == Location_Valid_Param[Location_autoindex])
	{
		if (value == "on" || value == "off")
			return (0);
		else
			throw Config::SyntaxInvalidValue(Location_Valid_Param[Location_autoindex], value);
	}
	else if (param == Location_Valid_Param[Location_Return])
	{
		size_t		pos = 0;
		std::string	code, path;
		while (pos < value.length() && (value[pos] == ' ' || value[pos] == '	'))
			pos++;
		while (pos < value.length() && isdigit(value[pos]))
			code += value[pos], pos++;
		if (pos == value.length() || (value[pos] != ' ' && value[pos] != '	'))
			throw Config::SyntaxInvalidValue(Location_Valid_Param[Location_Return], value);
		while (pos < value.length() && (value[pos] == ' ' || value[pos] == '	'))
			pos++;
		while (pos < value.length())
			path += value[pos], pos++;
		this->setLocation("return_code", code);
		this->setLocation("return_path", path);
	}
	else
		return (0);
	return (1);
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

	while (pos > 0 && !isalnum(content[pos]) && content[pos] != '/' && content[pos] != '.')
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