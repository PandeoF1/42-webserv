/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nard <nard@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:21:22 by nard              #+#    #+#             */
/*   Updated: 2022/06/08 00:21:10 by nard             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "../../includes/webserv.hpp"

# define BLU "\033[0;34m"
# define GRN "\033[0;32m"
# define RED "\033[0;31m"
# define RST "\033[0m"

class Config {
	public:
		~Config(void);

		std::string		getServerName(void) const;

		static int		isEndOfFile(std::string content, int pos);
		static int		findEndBracket(std::string content, int pos);
		static Config	*createConfig(std::string path);
		static int		getLineOfPos(std::string content, int pos);
	private:
		Config(void);

		static int	_verbose;
		std::string	_serverName;
	public:
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