/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:36:59 by jbosquet          #+#    #+#             */
/*   Updated: 2022/06/23 10:44:41 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../includes/webserv.hpp"

class Utils 
{

    public:
        static int string_to_int(std::string string);
        static std::string int_to_string(int integer);

};

