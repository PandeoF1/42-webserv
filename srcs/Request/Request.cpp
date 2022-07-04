#include "../../includes/webserv.hpp"

Request::Request(std::string request, Server &server) :  
	_server(server),
	_return_code(200)
{
	(void)_server;
	std::string new_request = request;
	_default_request = new_request;
	// std::cout<< _default_request << std::endl;
	parse();
}

Request::~Request(void) {
}

std::map<std::string, int>	Request::get_content_type_map() {
	return (_content_type_map);
}

void    Request::parse()
{
	std::istringstream  requestString(_default_request);
	std::string         line;
	std::string         parsed_line;
	int i = 0;

	while (std::getline(requestString, line) && _return_code != 400)
	{
		if (i == 0)
		{
			check_first_line_words(line);
			if (_return_code != 400)
				check_http_version(line);
			if (_return_code != 400)
				set_target_path(line);
			if (_return_code != 400)
				set_method(line);
		}
		if (i > 0)
		{
			for (size_t j = 0; j != line.size() && line[j] != ':'; j++)
				line[j] = ::tolower(line[j]);
			parsed_line = parse_line(line);
			if (parsed_line != "")
				_headers[parsed_line] = line.substr(line.find_first_of(':') + 1, line.size() - line.find_first_of(':'));
		}
		i++;
	}
	if (_headers["host"].size() > 0)
	{
		int after_space = _headers["host"].find_first_not_of(' ');
		if (_headers["host"][after_space] == '\r' || _headers["host"][after_space] == std::string::npos)
		{
			std::cout << RED << "Error: host not valid" << RST << std::endl;
			_return_code = 400;
		}
	} else if (_headers["host"].size() == 0)
	{
		std::cout << RED << "Error: host not valid" << RST << std::endl;
		_return_code = 400;
	}
	if (ACCEPT == 1)
	{
		if (!_headers["accept"].empty())
		{
			std::vector<std::string>	accept_vector = Utils::split_with_comma(_headers["accept"]);
			if (accept_vector.empty())
			{
				_content_type_map["*/*"] = 1;
				return ;
			}
			for (size_t i = 0; i != accept_vector.size(); i++)
			{
				if (accept_vector[i] == "*/*")
				{
					_content_type_map["*/*"] = 1;
					return ;
				}
			}
			for (i = 0; i != accept_vector.size(); i++)
			{
				if (!(accept_vector[i][0] && accept_vector[i][0] == 'q' && accept_vector[i][1] && accept_vector[i][1] == '='))
					_content_type_map[accept_vector[i]] = 1;
			}
		}
		else
			_content_type_map["*/*"] = 1;
	}
}

std::string    Request::checkMethod(std::string line)
{
	std::vector<std::string>    methods;
	Location location;

	try {
		location = Config::returnPath(_server.get_config(), URL::encode(get_target_path()));
	
		if (location["allow_methods"].empty())	//Allow methods from webserv.hpp if not found in location
		{
			for (int i = 0; i < Methods_List_Length; i++)
				methods.push_back(Methods_List[i] + " ");
		} else {
			std::vector<std::string>	allow_methods = Utils::split_with_space(location["allow_methods"]);

			for (size_t i = 0; i != allow_methods.size(); i++)
				methods.push_back(allow_methods[i] + " ");
		}
	}
	catch (const std::exception& e){
		for (int i = 0; i < Methods_List_Length; i++)
			methods.push_back(Methods_List[i] + " ");
	}

	for (int i = 0; line[i] != ' '; i++)
		if (std::islower(line[i]))
			return ("400");

	for (std::vector<std::string>::iterator it = methods.begin() ; it != methods.end(); ++it)
		if (line.find(*it) == 0)
			return (*it);

	for (int i = 0; line[i] != ' '; i++)
		if (std::isupper(line[i]))
			return ("405");
	return ("400");
}

void    Request::set_method(std::string line)
{
	std::string method;

	method = checkMethod(line);
	if (method == "405")
	{
		std::cerr << RED << "Method not allowed" << RST << std::endl;
		_return_code = 405;
		return ;
	}
	if (method == "400")
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

	int find_first_space = line.find_first_of(' ');
	_method = line.substr(0, find_first_space);
}

bool 	Request::check_target_path(std::string line)
{
	std::size_t 	i;
	bool			is_http_request = false;

	for (i = 0; line[i]; i++) line[i] = std::tolower(line[i]);

	for (i = line.find_first_of(' '); line[i] && line[i] == ' '; i++);
	if ((line[i] == 'h' && line[i + 1] == 't' && line[i + 2] == 't' && line[i + 3] == 'p' && line[i + 4] == ':' && line[i + 5] == '/' && line[i + 6] == '/'))
		is_http_request = true;
	if (i != std::string::npos && line[i] && (line[i] != '/' && is_http_request == false))
		return (false);

	if (is_http_request)
	{
		i = i + 7;
		bool has_double_point = false;
		if (!std::isalnum(line[i]))
			return (false);
		for (line[i]; line[i] && line[i] != '/' && line[i] != ' '; i++)
		{
			if (has_double_point && line[i] == ':')
				return (false);
			else if (line[i] == ':')
				has_double_point = true;
			if (line[i] != ':' && !std::isalnum(line[i]))
				return (false);
		}
	}
	return (true);
}

void    Request::set_target_path(std::string line)
{
	std::size_t i, j;

	if (!check_target_path(line))
	{
		std::cerr << RED << "Invalid target path" << RST << std::endl;
		_return_code = 400;
		return ;
	}

	for (i = line.find_first_of(' '); line[i] && line[i] == ' '; i++);
	for (j = 0; line[i + j] && line[i + j] != ' '; j++);
	_target_path = URL::decode(line.substr(i, j));
	if (_target_path.find("?") != std::string::npos)
	{
		i = _target_path.find("?");
		_target_path_queries = _target_path.substr(i + 1, i  - _target_path.size());
		_target_path = _target_path.substr(0, i);
	}
}

void    Request::set_target_path_force(std::string line)
{
	_target_path = line;
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

	for (std::vector<std::string>::iterator it = header_lines.begin() ; it != header_lines.end(); ++it)
	{
		if (line.find(*it) == 0)
			return ((*it).erase((*it).size() -1));
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

	if ((words.size() != 3 && words.size() != 4))
	{
		std::cerr << RED << "First line not contains 3 or 4 words" << RST << std::endl;
		_return_code = 400;
		return ;
	}

	if (words[2].find("HTTP/1.1") == std::string::npos)
	{
		std::cerr << RED << "First line has not HTTP/1.1 in third argument" << RST << std::endl;
		_return_code = 400;
		return ;
	}

	return ;
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

std::string Request::get_target_path() const {
	return (_target_path);
}

int Request::get_code() const {
	return (_return_code);
}

void	Request::set_code(int code) {
	_return_code = code;
}

std::map<std::string, std::string>	Request::get_headers() const {
	return (_headers);
}