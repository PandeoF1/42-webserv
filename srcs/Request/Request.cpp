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

void    Request::set_method(std::string line)
{
    //Surement a changer avec un check dans un vector pour toutes les methodes possible
    if ((line.find("GET") == std::string::npos) != 0 &&
        (line.find("POST") == std::string::npos) != 0 && 
        (line.find("DELETE") == std::string::npos) != 0) 
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
    _method = line.substr(0, line.find_first_of(' '));
}

// void    Request::check_http_version(std::string line) {
//     int i = line.find_last_of(' ');
// }

std::string Request::get_method() const {
    return (_method);
}

int Request::get_code() const {
    return (_return_code);
}