#pragma once
#include "../Server/Server.hpp"
#include <map>
#include <iostream>
#include <sstream>

class Request
{
	private:
		std::string                         _method;
		std::map<std::string, std::string>  _headers;
		Server                              &_server;
		std::string							_target_path;
		std::string                         _default_request;
		int                                 _return_code;

		void    parse();
		void    set_method(std::string line);
		void    set_target_path(std::string line);
		void    check_http_version(std::string line);
		void    check_first_line_words(std::string line);

	public:
		Request(char *request, Server &server);
		~Request(void);

		std::string    get_method() const;
		int            get_code() const;
};