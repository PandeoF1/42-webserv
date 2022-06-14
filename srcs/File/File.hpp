/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nard <nard@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:52:21 by nard              #+#    #+#             */
/*   Updated: 2022/06/07 16:22:27 by nard             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
# define FILE_HPP

#include "../../includes/webserv.hpp"

class File{
	public:
		File(std::string path);
		File(void);
		~File(void);
	
		/* Return the current path */
		std::string			getPath(void);
		/* Check if the path is accessible */
		static int			checkPath(std::string path);
		/* Check if the file is accessible */
		static int			checkFile(std::string file);
		/* Replace the current path and check it. */
		void				setPath(std::string path);
		/* Return the content of the file */
		static std::string	getFile(std::string file);
		/* Return the list of file/dir in the path */
		static std::string	listDirectory(std::string path);
		/* Return the list of file/dir in the current path */
		std::string			listDirectory(void);
		/* Return the type of the path */
		static int			getType(std::string path);
	public:
		class DirectoryNotAccessible : public std::exception
		{
			public :
				virtual const char *what() const throw()
				{
					return ("[File] Directory is not accessible");
				}
		};
		class FileNotAccessible : public std::exception
		{
			public :
				virtual const char *what() const throw()
				{
					return ("[File] File is not accessible");
				}
		};
		class FileInvalid : public std::exception
		{
			public :
				virtual const char *what() const throw()
				{
					return ("[File] File is invalid");
				}
		};
	private:
		std::string		_path;
		static int		_verbose;
};

#endif