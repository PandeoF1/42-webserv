/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:21:22 by nard              #+#    #+#             */
/*   Updated: 2022/06/23 10:40:31 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "../../includes/webserv.hpp"

# define BLU "\033[0;34m"
# define GRN "\033[0;32m"
# define RED "\033[0;31m"
# define RST "\033[0m"

class Location;
class Config {
	public:
		Config(void);
		~Config(void);

		std::map<int, Location>	getLocation(void) const;
		std::map<std::string, Location>	getLocation_str(void) const;

		std::string				operator[](std::string index) const;

		void					setData(std::string index, std::string value);
		void					setLocation(std::string index, Location value);

		/* Print all data from config */
		static void				print(std::map<int, Config>);

		std::map<std::string, std::string>	getData(void) const;

		/* Return the map of the config file */	
		static std::map<int, Config> createConfig(std::string path);
		/* Return the pos of the last bracket */
		static int			findEndBracket(std::string content, size_t pos);
		/* Check the value of the parameter */
		int					isValidValue(std::string param, std::string value);
		/* Return the content of the pos bracket */
		static std::string	getBracket(std::string content, size_t pos);
		/* Return the line of the pos in content */
		static int			getLineOfPos(std::string content, size_t pos);
		/* Return the current word */
		static std::string	getWord(std::string content, size_t pos);
		/* Return all word before the new line */
		static std::string	getDataBeforeLine(std::string content, size_t pos);
		/* Check if the server bracket is valid */
		static int			isValidServer(std::string content, size_t pos);
		/* Check if we are at the end of the config file */
		static int			isEndOfFile(std::string content, size_t pos);
		/* Check if we are at the end of a bracket */
		static int			isEndOfBracket(std::string content, size_t pos);
		/* Check if the current word is the same of value */
		static int			isSameWord(std::string content, size_t pos, std::string word);
		/* Extract all the parameters of server bracket */
		static Config		extractConfig(std::string content);
		/* Check the format of the parameters */
		static int			isValidParameter(std::string content, size_t pos);
		/* Return the number of space / tab */
		static std::string	removeWhiteSpace(std::string content);
		/* Check if the ip is valid */
		static int			isValidIp(std::string ip);
		/* Check if the port is valid */
		static int			isValidPort(std::string	port);
		/* Check if the list of methods is valid */
		static int			isValidMethods(std::string	value);
		/* Return the number of value */
		static int			getNumberOfValue(std::string value);
		/* Return the path without a / in less (ex : /test/hey to: /test/) */
		static std::string	getPathBefore(std::string path);
		/* Return the location from the path */
		static Location		returnPath(Config config, std::string path);
	private:

		static int	_verbose;
		std::map<std::string, std::string>	_data;
		std::map<int, Location>				_location;
		std::map<std::string, Location>				_location_str;
	public:
		class IndexOutOfRange : public std::exception
		{
			virtual const char *what() const throw ()
			{
				return ("[Config] Index out of range !");
			}
		};
		class SyntaxInvalidValue : public std::exception
		{
			public:
				std::string	_param;
				std::string	_value;
				~SyntaxInvalidValue() throw() {}
				SyntaxInvalidValue(std::string param, std::string value) : _param(param), _value(value) {}
				virtual const char *what() const throw ()
				{
					static std::string s = std::string("[Config] Syntax invalid value for parameter \033[0;34m") + _param + std::string("\033[0m : \033[0;34m") + _value + std::string("\033[0m");
					return (s.c_str());
				}
		};
		class SyntaxInvalidAt : public std::exception
		{
			public :
				int _line;
				SyntaxInvalidAt(int line) : _line(line) {}
				virtual const char *what() const throw()
				{
					int	len = 0;
					int tmp = _line;
					int	cp	= _line;
					while (tmp > 0)
						tmp /= 10, len++;
					char number[len + 1];
					number[len + 1] = '\0';
					tmp = 0;
					while (tmp < len + 1)
					{
						number[len--] = cp % 10 + '0';
						cp /= 10;
					}
					static std::string s = std::string("[Config] Syntax invalid at line : " + std::string(RED) + std::string(number) + std::string(RST) + "!");
					return (s.c_str());
				}
		};
};

#endif