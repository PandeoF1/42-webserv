/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:39:11 by jbosquet          #+#    #+#             */
/*   Updated: 2022/06/23 10:42:39 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

std::string Utils::int_to_string(int integer)
{
	std::stringstream ss;
	std::string return_string;

	ss << integer;
	return (ss.str());
}

int Utils::string_to_int(std::string str)
{
	std::stringstream ss;
	int return_int;

	ss << str;
	ss >> return_int;
	return (return_int);
}