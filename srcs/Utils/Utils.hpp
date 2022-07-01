#pragma once

#include "../../includes/webserv.hpp"

class Utils 
{

    public:
        static int string_to_int(std::string string);
        static std::string int_to_string(int integer);
		static std::vector<std::string>	split_with_comma(std::string line);
        static std::vector<std::string>	split_with_space(std::string line);

};

