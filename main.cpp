/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:54:51 by nard              #+#    #+#             */
/*   Updated: 2022/06/23 11:22:40 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(void)
{
	std::map<int, Config> config = Config::createConfig("config.conf");
	Config::returnPath(config[0], "/post_body/post_body/post_body/post_body");
	Config::print(config);
	Server::start_servers(config);
 	return (0);
}