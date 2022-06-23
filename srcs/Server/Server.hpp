/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:36:09 by asaffroy          #+#    #+#             */
/*   Updated: 2022/06/22 10:45:40 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../includes/webserv.hpp"

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