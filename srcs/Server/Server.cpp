/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:26:39 by asaffroy          #+#    #+#             */
/*   Updated: 2022/06/23 11:53:30 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	//set master socket to allow multiple connections , 
	//this is just a good habit, it will work without this 
	if (setsockopt(_master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
					sizeof(opt)) < 0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	//type of socket created 
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = inet_addr(get_config()["ip"].c_str());
	_address.sin_port = htons(_port);

	//bind the socket to localhost port 8888 
	if (bind(_master_socket, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	printf("Listener on port %d \n", _port);

	//try to specify maximum of 3 pending connections for the master socket 
	if (listen(_master_socket, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
}

Config	Server::get_config() const
{
	return (*this->_config);
}