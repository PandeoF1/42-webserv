/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:54:51 by nard              #+#    #+#             */
/*   Updated: 2022/06/15 14:19:12 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(void)
{
	std::map<int, Config> config = Config::createConfig("config.conf");
	//Config::print(config);
	// std::cout << "Ip : " <<  config[0]["index"] << std::endl;
	// std::cout << "Port : " <<  config[0]["port"] << std::endl;
	// std::cout << config[0].getLocation()[0]["allow_methods"] << std::endl;
	// std::cout << "`" << config[1].getLocation()[0]["alias"] << "`" << std::endl;
	// std::cout << config[0].getLocation_str()["/put_test"]["allow_methods"] << std::endl;
	// std::cout << "Size : " << config.size() << std::endl;
	// std::cout << "Size : " << config[0].getLocation().size() << std::endl;
	// std::cout << "Size : " << config[0].getLocation_str().size() << std::endl;
	// start_servers();
 	return (0);
}