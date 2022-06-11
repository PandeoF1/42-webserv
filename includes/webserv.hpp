/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:56:12 by nard              #+#    #+#             */
/*   Updated: 2022/06/11 22:57:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
/* File */
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <dirent.h>
/* Server */
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <iostream>
#include <sstream>

#include "../srcs/File/File.hpp"
#include "../srcs/Server/Server.hpp"
#include "../srcs/Config/Config.hpp"
#include "../srcs/Config/Location/Location.hpp"
#include "../srcs/Request/Request.hpp"
#include "../srcs/Server/Server.hpp"

#define				Location_Name "location"
static std::string	Location_Valid_Param[] = {"allow_methods", "root", "alias", "client_body_buffer_size", "index", "cgi_pass"};
#define				Location_Valid_Param_Length 6


static std::string	Server_Valid_Param[] = {"server_name", "listen", "root", "index", "allow_methods"};
#define				Server_Valid_Param_Length 5
#define				Server_IP 1

void	start_servers(void);