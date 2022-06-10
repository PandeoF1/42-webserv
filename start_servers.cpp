#include <stdio.h> 
#include <iostream> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include "includes/webserv.hpp"
     
#define TRUE   1 
#define FALSE  0 
#define PORT 80
#define PORT2 8765
#define NB_PORTS 2
#define MAX_CLIENTS 20
#define BUFLEN 65536

void start_servers(void)
{  
	int ports_tab[NB_PORTS] = {PORT, PORT2};
	Server *servers[NB_PORTS];
	for (int i = 0; i < NB_PORTS; i++)
	{
		servers[i] = new Server();
		servers[i]->set_port(ports_tab[i]);
	}

    int new_socket , client_socket[MAX_CLIENTS] ,
          max_clients = MAX_CLIENTS , activity, i , valread , sd;
    int max_sd;
	//initialise all client_socket[] to 0 so not checked
	for (i = 0; i < max_clients; i++)
	{
		client_socket[i] = 0;  
	}

    puts("Waiting for connections ..."); 
	//a message 
	char 	buffer[BUFLEN];

	fd_set readfds;

    while(TRUE)  
    {  
        //clear the socket set 
        FD_ZERO(&readfds);  
     
		max_sd = 0;
        //add master socket to set
		for (int i = 0; i < NB_PORTS; i++)
		{
			FD_SET(servers[i]->get_master_socket() , &readfds);
			if (servers[i]->get_master_socket() > max_sd)
				max_sd = servers[i]->get_master_socket();
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
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
		// puts("selection artisanale");
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
             
        //If something happened on the master socket , 
        //then its an incoming connection
		for (int i = 0; i < NB_PORTS; i++)
		{
			if (FD_ISSET(servers[i]->get_master_socket(), &readfds))
			{
				struct sockaddr_in address = servers[i]->get_address();
				int addrlen = sizeof(address);
				if ((new_socket = accept(servers[i]->get_master_socket(),
						(struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
				{  
					perror("accept");  
					exit(EXIT_FAILURE);  
				}  
				
				//inform user of socket number - used in send and receive commands
				if (!client_socket[max_clients - 1])
				{
					printf("New connection on Port : %d, socket fd is %d , ip is : %s , port : %d\n" , servers[i]->get_port(),  new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
			
				//send new connection greeting message 
					// if( send(new_socket, message, strlen(message), 0) != strlen(message) )  
					// {  
					// 	perror("send");  
					// }
					// puts("Welcome message sent successfully");
				}
					
				//add new socket to array of sockets 
				for (int j = 0; j < max_clients; j++)  
				{  
					//if position is empty 
					if( client_socket[j] == 0 )  
					{  
						client_socket[j] = new_socket;
						servers[i]->add_client(new_socket); 
						printf("Adding to list of sockets, on master_socket %d\n" , i);  
							
						break;  
					}  
				}  
			}
		}      
        //else its some IO operation on some other socket
        for (int k = 0; k < max_clients; k++)  
        {  
            sd = client_socket[k];
            if (FD_ISSET( sd , &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message
                if ((valread = recv( sd , buffer, BUFLEN, 0)) == 0)  
                {  
                    //Somebody disconnected , get his details and print  
                    printf("Host disconnected , fd %d\n" , client_socket[k]);                       
                    //Close the socket and mark as 0 in list for reuse 
                    client_socket[k] = 0;
					for (int l = 0; l < NB_PORTS; l++)
					{
						if (servers[l]->find_client(sd))
						{
							servers[l]->remove_client(sd);
						}
					}
                    close( sd );
                }
				else if (valread < 0)
				{
					std::cerr << "Error: couldn't handle request." << std::endl;
					client_socket[k] = 0;
					for (int l = 0; l < NB_PORTS; l++)
					{
						if (servers[l]->find_client(sd))
						{
							servers[l]->remove_client(sd);
						}
					}
                    close( sd );
				}              
                else 
                {  
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    buffer[valread] = '\0';  
                    // std::string response = "HTTP/1.1 200 OK\r\ncontent-type: text/html\r\ncontent-length: 12\r\n\r\n<h1>Oui</h1>\r\n";
					// send(sd , response.c_str() , response.size() , 0 );
					// printf("%s\n", buffer);
					for (int l = 0; l < NB_PORTS; l++)
					{
						if (servers[l]->find_client(sd))
						{
							Request request(buffer, *servers[l]);
							
							std::string response;
							switch (request.get_code())
							{
								case 200:
							 		response = "HTTP/1.1 200 OK\r\ncontent-type: text/html\r\ncontent-length: 15\r\n\r\n<h1>200 OK</h1>\r\n";
									send(sd , response.c_str() , response.size() , 0 );
									break;
								case 400:
									response = "HTTP/1.1 400 Bad Request\r\ncontent-type: text/html\r\ncontent-length: 24\r\n\r\n<h1>400 Bad Request</h1>\r\n";
									send(sd , response.c_str() , response.size() , 0 );
									break;
							}
						}
					}
				}  
            }  
        }  
    }  
}