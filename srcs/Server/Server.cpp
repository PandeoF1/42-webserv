/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:03:28 by jbosquet          #+#    #+#             */
/*   Updated: 2022/06/07 12:25:31 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void) : opt(1) {

    //Creer un socket en IPV4 sur le protocol TCP
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		std::cerr << "Socket: create error" << std::endl;

	//Permet de reutiliser la meme addresse
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		std::cerr << "Setsockopt: error" << std::endl;

	servaddr.sin_family			= AF_INET; // IPV4
	servaddr.sin_addr.s_addr	= inet_addr("0.0.0.0"); //htonl(INADDR_ANY); // Adresse IP du server
	servaddr.sin_port			= htons(PORT); // Port du serveur

	if ((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0) // Liaison des parametres du servaddr avec le socket
		std::cerr << "Bind: error" << errno << std::endl;

    std::cout << "Server constructor called" << std::endl;
}

Server::~Server(void) {
    std::cout << "Server destructor called" << std::endl;
}

void Server::start() const{
    int		connfd = 0;
	long    valread;
    std::string    response = "HTTP/1.0 200 OK\r\n\r\n<h1>Webserv</h1>";

	if ((listen(listenfd, 5)) < 0) // Ecoute sur le socket
		std::cerr << "Listen: error" << std::endl;

  	while (1)
	{
		std::cout << "Waiting for new connection..." << std::endl;

		//Attente d'une connexion sur les infos precisé plus haut
        if (!connfd)
            connfd = accept(listenfd, NULL, NULL);
		if (connfd)
			std::cout << "Connection" << std::endl;
		
        char    buffer[30000] = {0};
		valread = read(connfd, buffer, 30000); // Lecture de la demande du client

		(void)valread;
		std::cout << buffer << std::endl;

		send(connfd, response.c_str(), response.size(), 0); // Envoie de la reponse au client
		close(connfd); // Fermeture de la connexion
        connfd = 0;
	}
}

// GET / HTTP/1.1
// Host: localhost
// Connection: keep-alive
// sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="101", "Google Chrome";v="101"
// sec-ch-ua-mobile: ?0
// sec-ch-ua-platform: "macOS"
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.64 Safari/537.36
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
// Sec-Fetch-Site: none
// Sec-Fetch-Mode: navigate
// Sec-Fetch-User: ?1
// Sec-Fetch-Dest: document
// Accept-Encoding: gzip, deflate, br
// Accept-Language: fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7