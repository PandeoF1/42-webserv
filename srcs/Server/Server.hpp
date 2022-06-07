/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:01:31 by jbosquet          #+#    #+#             */
/*   Updated: 2022/06/07 12:25:38 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "../../includes/webserv.hpp"

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 80
#define MAXLINE 4086

class Server {

public:
    Server(void);
    ~Server(void);
    // Server(const & Config config);

    void start() const;

private:
    int					listenfd;
	int					opt;
	struct sockaddr_in	servaddr;
};

#endif