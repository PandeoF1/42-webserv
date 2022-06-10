/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:52:21 by nard              #+#    #+#             */
/*   Updated: 2022/06/10 14:58:33 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

#include "../../../includes/webserv.hpp"

class Location{
	public:
		Location(void);
		~Location(void);

		static Location	extractLocation(std::string content, size_t pos);

		std::string getName(void);
		std::string getAllow_methods(void);

		void		setName(std::string);
		void		setAllow_methods(std::string);
	private:
		static int _verbose;
		std::string	_name;
		std::string	_allow_methods;
		
};

#endif