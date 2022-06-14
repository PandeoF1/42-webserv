/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:54:51 by nard              #+#    #+#             */
/*   Updated: 2022/06/14 15:55:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(void)
{
	std::map<int, Config> config = Config::createConfig("config.conf");
	std::cout << "Ip : " <<  config[0]["index"] << std::endl;
	std::cout << "Port : " <<  config[0]["port"] << std::endl;
	std::cout << config[1]["root"] << std::endl;
	std::cout << "`" << config[1].getLocation()[0]["alias"] << "`" << std::endl;
	std::cout << config[0].getLocation_str()["/put_test"]["allow_methods"] << std::endl;
	std::cout << "Size : " << config.size() << std::endl;
	std::cout << "Size : " << config[0].getLocation().size() << std::endl;
	std::cout << "Size : " << config[0].getLocation_str().size() << std::endl;
	// start_servers();
 	return (0);
}