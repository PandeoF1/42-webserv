#pragma once

#include "../../includes/webserv.hpp"

class Config;

class Server
{
	private :
		int					_port;
		int					_master_socket;
		char**				_envp;
		std::vector<int>	_client_sockets;
		struct sockaddr_in	_address;
		Config	*_config;
		void	ft_create_serv();
	public :
		Server();
		// Server(int port_entry);
		~Server();

		int					get_master_socket() const;
		int					get_port() const;
		Config				get_config() const;
		struct sockaddr_in	get_address() const;
		void 				set_port(int port_entry);
		void				set_envp(char **envp);
		void 				set_config(Config *config);
		char			**get_envp(void) const;
		void				add_client(int client_socket);
		void				remove_client(int client_socket);
		bool 				find_client(int client_socket);
		static void			start_servers(std::map<int, Config> configs, char **envp);
};