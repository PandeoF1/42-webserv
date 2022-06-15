/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:56:12 by nard              #+#    #+#             */
/*   Updated: 2022/06/14 13:53:39 by jbosquet         ###   ########.fr       */
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
#include <sys/stat.h>
#include <map>
#include <iostream>
#include <sstream>

#include "../srcs/File/File.hpp"
#include "../srcs/Server/Server.hpp"
#include "../srcs/Config/Config.hpp"
#include "../srcs/Config/Location/Location.hpp"
#include "../srcs/Request/Request.hpp"
#include "../srcs/Response/Response.hpp"
#include "../srcs/Server/Server.hpp"

#define				Location_Name "location"
static std::string	Location_Valid_Param[] = {"allow_methods", "root", "alias", "client_body_buffer_size", "index", "cgi_pass"};
#define				Location_Valid_Param_Length 6
#define				Location_Methods 0
#define				Location_Root 1
#define				Location_Cgi 5
#define				Location_Buffer 3


static std::string	Server_Valid_Param[] = {"server_name", "listen", "root", "index", "allow_methods"};
#define				Server_Valid_Param_Length 5
#define				Server_IP 1
#define				Server_Root 2
#define				Server_Methods 4


static std::string	Methods_List[] = {"POST", "GET", "DELETE"};
#define				Methods_List_Length 3

#define				Buffer_Max 100000
#define				Buffer_Min 1
/* 1 = You can set up multiple parameters declaration with the same name (ex : 2 server_name (the last take the main)), 0 = you can't */
#define             Multiple_Declaration 1

void	start_servers(void);