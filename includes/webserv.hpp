/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:56:12 by nard              #+#    #+#             */
/*   Updated: 2022/06/15 14:55:41 by jbosquet         ###   ########.fr       */
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

#include "../srcs/File/File.hpp"
#include "../srcs/Server/Server.hpp"
#include "../srcs/Config/Config.hpp"
#include "../srcs/Request/Request.hpp"
#include "../srcs/Response/Response.hpp"
#include "../srcs/Server/Server.hpp"
#include "../srcs/URL/URL.hpp"

void start_servers(void);

static std::string		url_encoding_characters[]	= {" "  , "\""};
static std::string		url_encoding_utf8[] 		= {"%20", "%22"};
#define					url_encoding_length 2