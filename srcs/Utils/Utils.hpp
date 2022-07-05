#pragma once

#include "../../includes/webserv.hpp"

class Utils 
{

	public:
		static int                              string_to_int(std::string string);
		static std::string                      int_to_string(int integer);
		static std::vector<std::string>         split_with_comma(std::string line);
		static std::vector<std::string>         split_with_space(std::string line);
		static std::string						read_fd(int fd);
		static char								**mapToEnv(std::map<int, std::string> map);
		static std::map<int, std::string>       envToMap(char **env);
		static std::string                 	    lastPath(std::string path);
		static int								isSameExt(std::string path, std::string ext);
};