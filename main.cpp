/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nard <nard@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:54:51 by nard              #+#    #+#             */
/*   Updated: 2022/06/07 16:31:57 by nard             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(void)
{
	Config *config = Config::createConfig("config.conf");
	std::cout << config[0].getServerName() << std::endl;
 	return (0);
}