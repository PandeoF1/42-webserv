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
	int i = 0;

	// Parcours toutes les lignes pour parser la request
	while (std::getline(requestString, line) && _return_code != 400)
	{
		if (i == 0)
			set_method(line);
		i++;
	}
}

std::string    checkMethod(std::string line)
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
		std::cerr << "Method not found or not at good place" << std::endl;
		_return_code = 400;
		return ;
	}
	if (line.find_first_of(' ') == std::string::npos)
	{
		std::cerr << "No space after method" << std::endl;
		_return_code = 400;
		return ;
	}
	//MANQUE Verif l'espace apres la methode
	int find_first_space = line.find_first_of(' ');
	
	for (int i = find_first_space; line[i] != '/'; i++)
	{
		if (line[i] != ' ')
		{		
			std::cerr << "Not only space after method" << std::endl;
			_return_code = 400;
			return ;
		}
	}
	_method = line.substr(0, find_first_space);
}

void	Request::check_http_version(std::string line) {
	int i = line.find("HTTP/1.1");
	if (i == std::string::npos)
	{
		std::cerr << "HTTP version not found" << std::endl;
		_return_code = 400;
		return ;
	}
	if (line.find(" ", i - 1) != i - 1)
	{
		std::cerr << "No space before HTTP version" << std::endl;
		_return_code = 400;
		return ;
	}
	i = line.find("HTTP/1.1");
	if (line.find_first_not_of("\n\r ", i + 8) != std::string::npos)
	{
		std::cerr << "Invalid char after HTTP version" << std::endl;
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