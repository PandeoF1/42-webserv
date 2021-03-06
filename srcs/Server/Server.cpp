#include "Server.hpp"

Server::Server(){}

Server::~Server(){}

void Server::set_port(int port_entry)
{
	this->_port = port_entry;
	ft_create_serv();
}

void	Server::set_config(Config *config)
{
	this->_config = config;
}

void	Server::set_envp(char **envp)
{
	this->_envp = envp;
}

char	**Server::get_envp(void) const
{
	return (this->_envp);
}

int Server::get_master_socket() const
{
	return (this->_master_socket);
}

struct sockaddr_in Server::get_address() const
{
	return (this->_address);
}

int Server::get_port() const
{
	return (this->_port);
}

void Server::add_client(int client_socket)
{
	this->_client_sockets.push_back(client_socket);
}

void Server::remove_client(int client_socket)
{
	for (unsigned int i = 0; i < this->_client_sockets.size(); i++)
	{
		if (this->_client_sockets[i] == client_socket)
		{
			this->_client_sockets.erase(this->_client_sockets.begin() + i);
			break;
		}
	}
}

bool Server::find_client(int client_socket)
{
	for (unsigned int i = 0; i < this->_client_sockets.size(); i++)
	{
		if (this->_client_sockets[i] == client_socket)
			return (true);
	}
	return (false);
}

void Server::ft_create_serv()
{
	int opt = 1;

	//create a master socket 
	if ((_master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cerr << "socket failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	//set master socket to allow multiple connections , 
	if (setsockopt(_master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
					sizeof(opt)) < 0)
	{
		std::cerr << "setsockopt error" << std::endl;
		exit(EXIT_FAILURE);
	}

	//type of socket created 
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = inet_addr(get_config()["ip"].c_str());
	_address.sin_port = htons(_port);

	//bind the socket to localhost port 8888 
	if (bind(_master_socket, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		std::cerr << "[Webserv] Bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Listener on port " << _port << std::endl;

	//try to specify maximum of 3 pending connections for the master socket 
	if (listen(_master_socket, 100) < 0)
	{
		std::cerr << "listen error" << std::endl;
		exit(EXIT_FAILURE);
	}
}

Config	Server::get_config() const
{
	return (*this->_config);
}