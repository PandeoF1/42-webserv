/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:54:51 by nard              #+#    #+#             */
/*   Updated: 2022/06/15 15:16:15 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(void)
{
	// Config *config = Config::createConfig("config.conf");
	// std::cout << config[0].getServerName() << std::endl;

	start_servers();
 	return (0);
}