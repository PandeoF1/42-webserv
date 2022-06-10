#include "../../includes/webserv.hpp"

Request::Request(char *request, Server &server) :  
	_server(server),
	_return_code(200)
{
	(void)_server;
	std::string new_request = request;
	_default_request = new_request;
	std::cout << "New request from port: " << server.get_port() << std::endl;
	std::cout << _default_request << std::endl;
	parse();
}

Request::~Request(void) {

}

void    Request::parse()
{
	std::istringstream  requestString(_default_request);
	std::string         line;
	std::string         parsed_line;
	int i = 0;

	// Parcours toutes les lignes pour parser la request
	while (std::getline(requestString, line) && _return_code != 400)
	{
		if (i == 0)
		{
			check_first_line_words(line);
			if (_return_code != 400)
				check_http_version(line);
			if (_return_code != 400)
				set_method(line);
			if (_return_code != 400)
				set_target_path(line);
		}
		if (i > 0)
		{
			for (size_t j = 0; j != line.size() && line[j] != ':'; j++)
				line[j] = ::tolower(line[j]);
			parsed_line = parse_line(line);
			if (parsed_line != "")
			{
				_headers[parsed_line] = line.substr(line.find_first_of(':') + 1, line.size() - line.find_first_of(':'));
				std::cout << "look }" << _headers[parsed_line] << std::endl;
			}
		}
		i++;
	}
}

std::string    Request::checkMethod(std::string line)
{
	std::vector<std::string>    methods;

	methods.push_back("GET ");
	methods.push_back("POST ");
	methods.push_back("DELETE ");
		
	for (std::vector<std::string>::iterator it = methods.begin() ; it != methods.end(); ++it)
	{
		if (line.find(*it) == 0)
			return (*it);
	}
	return ("");
}


void    Request::set_method(std::string line)
{
	std::string method;

	//Surement a changer avec un check dans un vector pour toutes les methodes possible
	if ((method = checkMethod(line)) == "")
	{
		std::cerr << RED << "Method not found or not at good place" << RST << std::endl;
		_return_code = 400;
		return ;
	}
	if (line.find_first_of(' ') == std::string::npos)
	{
		std::cerr << RED << "No space after method" << RST << std::endl;
		_return_code = 400;
		return ;
	}
	//MANQUE Verif l'espace apres la methode
	int find_first_space = line.find_first_of(' ');
	
	for (int i = find_first_space; line[i] != '/'; i++)
	{
		if (line[i] != ' ')
		{		
			std::cerr << RED << "Not only space after method" << RST << std::endl;
			_return_code = 400;
			return ;
		}
	}
	_method = line.substr(0, find_first_space);
}

void    Request::set_target_path(std::string line)
{
	std::size_t i, j;

	for (i = line.find_first_of(' '); line[i] && line[i] == ' '; i++);
	if (i != std::string::npos && line[i] && line[i] != '/')
	{
		std::cerr << RED << "Target path not start by '/'" << RST << std::endl;
		_return_code = 400;
		return ;
	}

	for (j = 0; line[i + j] && line[i + j] != ' '; j++);
	_target_path = line.substr(i, j); 
}

std::string	Request::parse_line(std::string line)
{
	std::vector<std::string>    header_lines;

	header_lines.push_back("host:");
	header_lines.push_back("cache-control:");
	header_lines.push_back("sec-ch-ua:");
	header_lines.push_back("sec-ch-mobile:");
	header_lines.push_back("sec-ch-ua-platform:");
	header_lines.push_back("upgrade-insecure-requests:");
	header_lines.push_back("user-agent:");
	header_lines.push_back("sec-fetch-site:");
	header_lines.push_back("sec-fetch-mode:");
	header_lines.push_back("sec-fetch-user:");
	header_lines.push_back("sec-fetch-dest:");
	header_lines.push_back("accept-encoding:");
	header_lines.push_back("accept-language:");
	header_lines.push_back("connection:");
	header_lines.push_back("accept:");
	header_lines.push_back("referer:");
	header_lines.push_back("connection:");

	for (std::vector<std::string>::iterator it = header_lines.begin() ; it != header_lines.end(); ++it)
	{
		if (line.find(*it) == 0)
			return (*it);
	}
	return ("");
}

void    Request::check_first_line_words(std::string line)
{
	std::string delimiter = " ";
	std::vector<std::string>	words;
	size_t 			pos;
	int 			u = 0;

	while ((pos = line.find(delimiter)) != std::string::npos) {
		words.push_back(line.substr(0, pos));
		line.erase(0, pos + delimiter.length());
		if (line[0] == ' ')
		{
			for (u = 0; line[u] == ' '; u++);
			line.erase(0, u);
		}
		if (line.find(delimiter) == std::string::npos)
			words.push_back(line.substr(0, line.size()));
	}

	if (words.size() != 3 && words.size() != 4)
	{
		std::cerr << RED << "First line not contains 3 or 4 words" << RST << std::endl;
		_return_code = 400;
		return ;
	}
}

void	Request::check_http_version(std::string line) {
	unsigned long i = line.find("HTTP/1.1");
	if (line.find("HTTP/1.1") == std::string::npos)
	{
		std::cerr << RED << "HTTP version not found" << RST << std::endl;
		_return_code = 400;
		return ;
	}
	if (line.find(" ", i - 1) != i - 1)
	{
		std::cerr << RED << "No space before HTTP version" << RST << std::endl;
		_return_code = 400;
		return ;
	}
	i = line.find("HTTP/1.1");
	if (line.find_first_not_of("\n\r ", i + 8) != std::string::npos)
	{
		std::cerr << RED << "Invalid char after HTTP version" << RST << std::endl;
		_return_code = 400;
		return ;
	}
}

std::string Request::get_method() const {
	return (_method);
}

int Request::get_code() const {
	return (_return_code);
}