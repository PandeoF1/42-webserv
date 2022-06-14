/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:52:24 by nard              #+#    #+#             */
/*   Updated: 2022/06/14 15:18:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "File.hpp"

/*
TODO:
	Repair checkFile()
*/

int File::_verbose = 0;

File::File(std::string path) : _path(path)
{
	if (this->getPath()[this->getPath().length() - 1] != '/')
		this->setPath(this->_path + '/');
	File::checkPath(path);
	if (_verbose)
		std::cout << "File constructor called" << std::endl;
}

File::File(void) : _path("./")
{
	File::checkPath(_path);
	if (_verbose)
		std::cout << "File constructor called" << std::endl;
}

File::~File(void){
	if (_verbose)
		std::cout << "File destructor called" << std::endl;
}

std::string File::getPath(void)
{
	return (this->_path);
}

void File::setPath(std::string path)
{
	if (File::checkPath(path))
		this->_path = path;
}

int	File::checkPath(std::string path)
{
	if (_verbose)
		std::cout << "File::checkPath called" << std::endl;
	if (access(path.c_str(), F_OK) != -1)
		return (1);
	throw DirectoryNotAccessible();
	return (0);
}
/* To repair */
int	File::checkFile(std::string path)
{
	if (_verbose)
		std::cout << "File::checkFile called" << std::endl;
	if (access(path.c_str(), F_OK) != -1)
		return (1);
	throw FileNotAccessible();
	return (0);
}

std::string File::listDirectory(std::string path)
{
	DIR				*dir;
	struct dirent	*ent;
	std::string		dirlist;

	if ((dir = opendir (path.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			if (ent->d_name[0] != '.')
			{
				dirlist += ent->d_name;
				dirlist += '\n';
			}
		}
		dirlist[dirlist.length() - 1] = '\0';
		closedir (dir);
	}
	else
		throw DirectoryNotAccessible();
	return (dirlist);
}

std::string File::listDirectory(void)
{
	DIR				*dir;
	struct dirent	*ent;
	std::string		dirlist;

	if ((dir = opendir (this->getPath().c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			dirlist += ent->d_name;
			dirlist += '\n';
		}
		dirlist[dirlist.length() - 1] = '\0';
		closedir (dir);
	}
	else
		throw DirectoryNotAccessible();
	return (dirlist);
}

std::string File::getFile(std::string file)
{
	if (_verbose)
		std::cout << "Film::getFile called" << std::endl;
	if (file.empty() || file.length() == 0)
		throw FileInvalid();
	std::ifstream myfile(file.c_str());
	if (!myfile || !myfile.is_open())
		throw FileNotAccessible();
	std::string file_content((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());
	return (file_content);
}
