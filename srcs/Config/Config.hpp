/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:21:22 by nard              #+#    #+#             */
/*   Updated: 2022/06/10 15:23:12 by tnard            ###   ########lyon.fr   */
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

		std::string			getServerName(void) const;
		std::string			getIndex(void) const;
		std::string			getRoot(void) const;
		std::string			getAllow_methods(void) const;
		std::string			getListen_ip(void) const;
		int					getListen_port(void) const;
		std::map<int, Location>	getLocation(void) const;

		std::string			operator[](std::string index) const;

		void				setServerName(std::string data);
		void				setIndex(std::string data);
		void				setRoot(std::string data);
		void				setAllow_methods(std::string data);
		void				setListen_ip(std::string data);
		void				setListen_port(int data);

		/* Return the map of the config file */	
		static std::map<int, Config> createConfig(std::string path);
		/* Return the pos of the last bracket */
		static int			findEndBracket(std::string content, size_t pos);
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
	private:

		static int	_verbose;
		std::map<std::string, std::string>	_data;
		std::string	_serverName;
		std::string	_index;
		std::string	_root;
		std::string	_allow_methods;
		std::string	_listen_ip;
		int			_listen_port;

		std::map<int, Location>	_location;
	public:
		class IndexOutOfRange : public std::exception
		{
			virtual const char *what() const throw ()
			{
				return ("[Config] Index out of range !");
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
					static std::string s = std::string("[Config] Syntax invalid at line : " + std::string(number) + "!");
					return (s.c_str());
				}
		};
};

#endif