/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:54:51 by nard              #+#    #+#             */
/*   Updated: 2022/06/23 14:39:21 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(void)
{
	try {
		std::map<int, Config> config = Config::createConfig("config.conf");
		Config::print(config);
		Server::start_servers(config);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	// std::map<int, Config> config = Config::createConfig("config.conf");
	// Config::returnPath(config[0], "/post_body/post_body/post_body/post_body");
	// Config::print(config);
}