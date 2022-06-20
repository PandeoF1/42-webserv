/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:36:09 by asaffroy          #+#    #+#             */
/*   Updated: 2022/06/20 10:09:07 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <iostream>
#include <string.h> 
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <vector>
#include <map>

class Server
{
	private :
		int _port;
		int _master_socket;
		std::vector<int> _client_sockets;
		struct sockaddr_in _address;
		void	ft_create_serv();
	public :
		Server();
		// Server(int port_entry);
		~Server();

		int					get_master_socket() const;
		int					get_port() const;
		struct sockaddr_in	get_address() const;
		void 				set_port(int port_entry);
		void				add_client(int client_socket);
		void				remove_client(int client_socket);
		bool 				find_client(int client_socket);
};