#pragma once
#include "../Request/Request.hpp"
#include "../File/File.hpp"
#include <map>
#include <iostream>
#include <sstream>

class Response
{
	private:
		Request			&_request;
		std::string		_extension;
		std::string		_content;
		std::string		_response;
		size_t			_content_length;

		void						create_response(void);
		void						set_extension(void);
		void						content_fill_from_file(void);
		void						fill_content_with_error_code(int code);
		std::string					get_content_type(void) const;
		std::string					get_text_code(void) const;
		std::string					get_extension(std::string file) const;
		void						autoindex(std::string directory, std::string indexFile);
		std::vector<std::string>	split_file_and_directory(std::string line);
	public:
		Response(Request &request);
		~Response(void);

		std::string		get_response(void) const;
};