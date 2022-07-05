#pragma once

#include "../../includes/webserv.hpp"
class Server;
class Request
{
	private:
		std::string                         _method;
		std::map<std::string, std::string>  _headers;
		std::map<std::string, int>		 	_accepted_type;
		Server                              &_server;
		std::string							_target_path;
		std::string							_target_path_queries;
		std::string                         _default_request;
		int                                 _return_code;
		std::string                         _ip;

		void    parse();
		void    set_method(std::string line);
		void    set_target_path(std::string line);
		void    check_http_version(std::string line);
		void    check_first_line_words(std::string line);
		bool    check_target_path(std::string line);
		std::string checkMethod(std::string line);
		std::string	parse_line(std::string line);

	public:
		Request(std::string request, Server &server);
		~Request(void);

		std::map<std::string, int>			get_accepted_type();
		std::map<std::string, int>			get_content_type_map();
		std::string							get_query_string() const;
		std::string							get_target_path() const;
		std::string							get_method() const;
		std::map<std::string, std::string>  get_headers() const;
		int									get_code() const;
		void								set_code(int code);
		void								setIp(char *ip);
		std::string							getIp(void) const;
		void								set_target_path_force(std::string line);
};