/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:54:51 by nard              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/06/23 14:36:37 by jbosquet         ###   ########.fr       */
=======
/*   Updated: 2022/06/23 11:22:40 by tnard            ###   ########lyon.fr   */
>>>>>>> jbosquet
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(void)
{
<<<<<<< HEAD
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
=======
	std::map<int, Config> config = Config::createConfig("config.conf");
	Config::returnPath(config[0], "/post_body/post_body/post_body/post_body");
	Config::print(config);
	Server::start_servers(config);
>>>>>>> jbosquet
 	return (0);
}