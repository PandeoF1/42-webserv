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
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include "includes/webserv.hpp"
	 
#define TRUE 1
#define FALSE 0
#define MAX_CLIENTS 50000
#define BUFLEN 65536

static	int	status = 1;

void	sig_int(int sig)
{
	(void)sig;
	if (write(2, "\b\b", 2) == -1)
		std::cerr << RED << "Write error." << RST << std::endl;
	std::cout << "Shutdown in progress..." << std::endl;
	status = 0;
}

void Server::start_servers(std::map<int, Config> configs, char **envp)
{  
	signal(SIGINT, sig_int);
	Server servers[configs.size()];
	for (int i = 0; i < configs.size(); i++)
	{
		servers[i] = Server();
		servers[i].set_envp(envp);
		servers[i].set_config(&configs[i]);
		servers[i].set_port(Utils::string_to_int(configs[i]["port"]));
	}

	int new_socket, client_socket[MAX_CLIENTS], max_clients = MAX_CLIENTS, activity, i, valread , sd, max_sd;

	//initialise all client_socket[] to 0 so not checked
	for (i = 0; i < max_clients; i++)
		client_socket[i] = 0;  

	std::vector<char> buffer(BUFLEN);
	std::string test[MAX_CLIENTS];
	size_t y;
	fd_set readfds;
	
	while(status)
	{
		//clear the socket set 
		FD_ZERO(&readfds);  
		
		max_sd = 0;
		//add master socket to set
		for (int i = 0; i < configs.size(); i++)
		{
			FD_SET(servers[i].get_master_socket() , &readfds);
			if (servers[i].get_master_socket() > max_sd)
				max_sd = servers[i].get_master_socket();
		}
		//add child sockets to set 
		for ( i = 0 ; i < max_clients ; i++)  
		{  
			//socket descriptor 
			sd = client_socket[i];  
					
			//if valid socket descriptor then add to read list 
			if(sd > 0) 
				FD_SET( sd , &readfds);  
					
			//highest file descriptor number, need it for the select function 
			if(sd > max_sd)  
				max_sd = sd;  
		}  
		
		//wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
		if (status == 0)
			break;
		if ((activity < 0) && (errno!=EINTR))  
		{  
			std::cout << "select error" << std::endl;;  
		}  
			 
		//If something happened on the master socket , then its an incoming connection
		for (int i = 0; i < configs.size(); i++)
		{
			if (FD_ISSET(servers[i].get_master_socket(), &readfds))
			{
				struct sockaddr_in address = servers[i].get_address();
				int addrlen = sizeof(address);
				if ((new_socket = accept(servers[i].get_master_socket(),
						(struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
				{  
					std::cerr << "accept" << std::endl;  
					exit(EXIT_FAILURE);
				}				
				//add new socket to array of sockets 
				for (int j = 0; j < max_clients; j++)  
				{  
					//if position is empty 
					if( client_socket[j] == 0 )  
					{  
						client_socket[j] = new_socket;
						servers[i].add_client(new_socket); 
						break;  
					}  
				}
			}
		}      
		//else its some IO operation on some other socket
		for (int k = 0; k < max_clients; k++)  
		{  
			sd = client_socket[k];
			memset(buffer.data(), 0, BUFLEN);
			if (FD_ISSET( sd , &readfds))  
			{  
				//Check if it was for closing , and also read the incoming message)
				if ((valread = recv( sd , buffer.data(), BUFLEN, 0)) == 0)
				{
					//Somebody disconnected , get his details and print  
					//std::cout << "Host disconnected , fd " << client_socket[k] << std::endl;                       
					//Close the socket and mark as 0 in list for reuse 
					client_socket[k] = 0;
					for (int l = 0; l < configs.size(); l++)
						if (servers[l].find_client(sd))
							servers[l].remove_client(sd);
					close( sd );
					test[k] = "";
					break ;
				}
				else if (valread < 0)
				{
					//std::cerr << "Error: couldn't handle request." << std::endl;
					client_socket[k] = 0;
					for (int l = 0; l < configs.size(); l++)
						if (servers[l].find_client(sd))
							servers[l].remove_client(sd);
					test[k] = "";
					close( sd );
					break ;
				}              
				else 
				{
					//set the string terminating NULL byte on the end of the data read 
					buffer[valread] = '\0';
					if (test[k].size() > 0)
						test[k] += buffer.data();
					else
						test[k] = buffer.data();
					if ((y = test[k].find("\r\n\r\n")) == std::string::npos)
						break ;
					// if (test[k].find("\r\n\r\n", y + 4) == std::string::npos && ((test[k].find("PUT")) == 0 || (test[k].find("POST")) == 0))
					// 	break ;
					if (strlen(buffer.data()) == BUFLEN)
						break;
					for (int l = 0; l < configs.size(); l++)
					{
						if (servers[l].find_client(sd))
						{
							Request request(test[k], servers[l]);
							Response response(request, servers[l]);
							send(sd, response.get_response().c_str(), response.get_response().size(), MSG_NOSIGNAL);
							test[k] = "";
							if (!request.get_headers()["connection"].empty())
							{
								if (Utils::split_with_comma(request.get_headers()["connection"])[0] == "close")
								{
									client_socket[k] = 0;
									for (int l = 0; l < configs.size(); l++)
										if (servers[l].find_client(sd))
											servers[l].remove_client(sd);
									test[k] = "";
									close( sd );
								}
							}
							break;
						}
					}
				}
			}  
		}  
	}  
}