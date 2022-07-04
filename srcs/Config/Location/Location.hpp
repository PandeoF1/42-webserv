#ifndef LOCATION_HPP
# define LOCATION_HPP

#include "../../../includes/webserv.hpp"

class Location{
	public:
		Location(void);
		~Location(void);

		static Location		extractLocation(std::string content, size_t pos);
		static int			isValidParameter(std::string content, size_t pos);
		static std::string	removeBracket(std::string content);

		void				setLocation(std::string index, std::string value);
		std::string			operator[](std::string index) const;
		std::map<std::string, std::string>	getData(void) const;
		/* Check the value of the parameter */
		int					isValidValue(std::string param, std::string value);
	private:
		static int _verbose;
		std::map<std::string, std::string>	_data;
};

#endif