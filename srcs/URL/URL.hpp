#pragma once
#include "../../includes/webserv.hpp"
class URL {

public:
    URL(void);
    ~URL(void);

    static std::string  encode(std::string);
    static std::string  decode(std::string);
};