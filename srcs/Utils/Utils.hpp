#pragma once

#include "../../includes/webserv.hpp"

class Utils 
{

	public:
		static int									string_to_int(std::string string);
		static std::string							int_to_string(int integer);
		static std::string							read_fd(int fd);
		static char									**mapToEnv(std::map<std::string, std::string> map);
		static std::map<std::string, std::string>	envToMap(char **env);

};

