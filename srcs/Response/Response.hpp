#pragma once
#include "../Request/Request.hpp"
#include "../File/File.hpp"
#include <map>
#include <iostream>
#include <sstream>

class Response
{
	private:
		Server			&_server;
		Request			&_request;
		std::string		_extension;
		std::string		_content;
		std::string		_response;
		std::string		_redirection;
		size_t			_content_length;

		void						create_response(void);
		void						set_extension(void);
		void						set_redirection(std::string redir_path);
		void						content_fill_from_file(void);
		void						fill_content_with_error_code(int code);
		std::string					get_content_type(void) const;
		std::string					get_text_code(int code) const;
		std::string					get_extension(std::string file) const;
		void						autoindex(std::string directory, std::string indexFile);
		std::vector<std::string>	split_file_and_directory(std::string line) const;
		std::vector<std::string>	split_with_space(std::string line) const;
		std::string					get_index_file(std::string directory, std::string indexs_from_config) const;
		std::string					get_error_page(std::string paths_from_config) const;
		std::string					get_redirection(void) const;
		std::string					inLocationOrConfig(Location location, Config config, std::string what);

	public:
		Response(Request &request, Server &server);
		~Response(void);

		std::string		get_response(void) const;
};