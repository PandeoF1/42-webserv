#include "Response.hpp"

Response::Response(Request &request, Server &server) : _request(request), _server(server)
{
	_content = "";
	set_extension();
	create_response();
}

Response::~Response(void)
{
}

void	Response::set_extension(void)
{
	int i = _request.get_target_path().find_last_of('.');
	if (i != std::string::npos)
		_extension = _request.get_target_path().substr(i, _request.get_target_path().size() - i);
	else
		_extension = "";
}

void	Response::set_return(std::string return_path)
{
	_return = return_path;
}

std::string	Response::get_extension(std::string file) const
{
	int i = file.find_last_of('.');
	if (i != std::string::npos)
		return (file.substr(i, file.size() - i));
	return ("text/plain");
}

std::string	Response::get_content_type(void) const
{
	if (!_extension.compare(".aac"))
		return ("audio/aac");
	if (!_extension.compare(".abw"))
		return ("application/x-abiword");
	if (!_extension.compare(".arc"))
		return ("application/octet-stream");
	if (!_extension.compare(".avi"))
		return ("video/x-msvideo");
	if (!_extension.compare(".azw"))
		return ("application/vnd.amazon.ebook");
	if (!_extension.compare(".bin"))
		return ("application/octet-stream");
	if (!_extension.compare(".bmp"))
		return ("image/bmp");
	if (!_extension.compare(".bz"))
		return ("application/x-bzip");
	if (!_extension.compare(".bz2"))
		return ("application/x-bzip2");
	if (!_extension.compare(".csh"))
		return ("application/x-csh");
	if (!_extension.compare(".css"))
		return ("text/css");
	if (!_extension.compare(".csv"))
		return ("text/csv");
	if (!_extension.compare(".doc"))
		return ("application/msword");
	if (!_extension.compare(".docx"))
		return ("application/vnd.openxmlformats-officedocument.wordprocessingml.document");
	if (!_extension.compare(".eot"))
		return ("application/vnd.ms-fontobject");
	if (!_extension.compare(".epub"))
		return ("application/epub+zip");
	if (!_extension.compare(".gif"))
		return ("image/gif");
	if (!_extension.compare(".htm"))
		return ("text/html");
	if (!_extension.compare(".html"))
		return ("text/html");
	if (!_extension.compare(".ico"))
		return ("image/x-icon");
	if (!_extension.compare(".ics"))
		return ("text/calendar");
	if (!_extension.compare(".jar"))
		return ("application/java-archive");
	if (!_extension.compare(".jpeg"))
		return ("image/jpeg");
	if (!_extension.compare(".jpg"))
		return ("image/jpeg");
	if (!_extension.compare(".js"))
		return ("application/javascript");
	if (!_extension.compare(".json"))
		return ("application/json");
	if (!_extension.compare(".mid"))
		return ("audio/midi");
	if (!_extension.compare(".midi"))
		return ("audio/midi");
	if (!_extension.compare(".mpeg"))
		return ("video/mpeg");
	if (!_extension.compare(".mpkg"))
		return ("application/vnd.apple.installer+xml");
	if (!_extension.compare(".odp"))
		return ("application/vnd.oasis.opendocument.presentation");
	if (!_extension.compare(".ods"))
		return ("application/vnd.oasis.opendocument.spreadsheet");
	if (!_extension.compare(".odt"))
		return ("application/vnd.oasis.opendocument.text");
	if (!_extension.compare(".oga"))
		return ("audio/ogg");
	if (!_extension.compare(".ogv"))
		return ("video/ogg");
	if (!_extension.compare(".ogx"))
		return ("application/ogg");
	if (!_extension.compare(".otf"))
		return ("font/otf");
	if (!_extension.compare(".png"))
		return ("image/png");
	if (!_extension.compare(".pdf"))
		return ("application/pdf");
	if (!_extension.compare(".ppt"))
		return ("application/vnd.ms-powerpoint");
	if (!_extension.compare(".pptx"))
		return ("application/vnd.openxmlformats-officedocument.presentationml.presentation");
	if (!_extension.compare(".rar"))
		return ("application/x-rar-compressed");
	if (!_extension.compare(".rtf"))
		return ("application/rtf");
	if (!_extension.compare(".sh"))
		return ("application/x-sh");
	if (!_extension.compare(".svg"))
		return ("image/svg+xml");
	if (!_extension.compare(".swf"))
		return ("application/x-shockwave-flash");
	if (!_extension.compare(".tar"))
		return ("application/x-tar");
	if (!_extension.compare(".tif"))
		return ("image/tiff");
	if (!_extension.compare(".tiff"))
		return ("image/tiff");
	if (!_extension.compare(".ts"))
		return ("application/typescript");
	if (!_extension.compare(".ttf"))
		return ("font/ttf");
	if (!_extension.compare(".vsd"))
		return ("application/vnd.visio");
	if (!_extension.compare(".wav"))
		return ("audio/x-wav");
	if (!_extension.compare(".weba"))
		return ("audio/webm");
	if (!_extension.compare(".webm"))
		return ("video/webm");
	if (!_extension.compare(".webp"))
		return ("image/webp");
	if (!_extension.compare(".woff"))
		return ("font/woff");
	if (!_extension.compare(".woff2"))
		return ("font/woff2");
	if (!_extension.compare(".xhtml"))
		return ("application/xhtml+xml");
	if (!_extension.compare(".xls"))
		return ("application/vnd.ms-excel");
	if (!_extension.compare(".xlsx"))
		return ("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
	if (!_extension.compare(".xml"))
		return ("application/xml");
	if (!_extension.compare(".xul"))
		return ("application/vnd.mozilla.xul+xml");
	if (!_extension.compare(".zip"))
		return ("application/zip");
	if (!_extension.compare(".3gp"))
		return ("video/3gpp");
	if (!_extension.compare(".3g2"))
		return ("video/3gpp2");
	if (!_extension.compare(".7z"))
		return ("application/x-7z-compressed");
	if (!_extension.compare(".mp3"))
		return ("audio/mpeg");
	if (!_extension.compare(".mp4"))
		return ("video/mp4");
	if (!_extension.compare(".m4a"))
		return ("audio/mp4");
	if (!_extension.compare(".m4v"))
		return ("video/mp4");
	if (!_extension.compare(".mov"))
		return ("video/quicktime");
	return ("text/plain");
}

std::string	Response::get_text_code(int code) const
{
	switch(_request.get_code())
	{
		case 200:
			return ("OK");
		case 201:
			return ("Created");
		case 202:
			return ("Accepted");
		case 204:
			return ("No Content");
		case 301:
			return ("Moved Permanently");
		case 302:
			return ("Found");
		case 303:
			return ("See Other");
		case 304:
			return ("Not Modified");
		case 307:
			return ("Temporary Redirect");
		case 308:
			return ("Permanent Redirect");
		case 400:
			return ("Bad Request");
		case 401:
			return ("Unauthorized");
		case 403:	
			return ("Forbidden");
		case 404:
			return ("Not Found");
		case 405:
			return ("Method Not Allowed");
		case 500:
			return ("Internal Server Error");
		case 501:
			return ("Not Implemented");
		case 502:
			return ("Bad Gateway");
		case 503:
			return ("Service Unavailable");
		case 504:
			return ("Gateway Timeout");
		default:
			return ("Unknown Error Code");
	}
}

std::string	Response::get_error_page(std::string paths_from_config) const
{
	std::vector<std::string>	paths;

	paths = split_with_space(paths_from_config);
	if (paths.size() == 0)
		return ("");
	for (int i = 0; i < paths.size(); i++)
		if (File::getType(paths[i]) == 2)
			return (paths[i]);
	return ("");
}

void	Response::fill_content_with_error_code(int code)
{
	File file;
	std::string content;
	std::string used_extension = ".html";
	Config config = _server.get_config();

	_request.set_code(code);
	try
	{
		if (config["error_" + Utils::int_to_string(code)].empty())
		{
			try {
				if (code >= 500)
					content = file.getFile("utils/errors_pages/50x.html");
				else
					content = file.getFile("utils/errors_pages/" + Utils::int_to_string(code) + ".html");
			}
			catch (std::exception &e) {
				content = "<h1>" + Utils::int_to_string(code) + " " + get_text_code(code) + "</h1>";
			}
		}
		else
		{
			std::string	error_page = get_error_page(config["error_" + Utils::int_to_string(code)]);
			content = file.getFile(error_page);
			used_extension = get_extension(error_page);
		}

	}
	catch(std::exception& e)
	{
		try {
			if (code >= 500)
				content = file.getFile("utils/errors_pages/50x.html");
			else
				content = file.getFile("utils/errors_pages/" + Utils::int_to_string(code) + ".html");
		}
		catch (std::exception &e) {
			content = "<h1>" + Utils::int_to_string(code) + " " + get_text_code(code) + "</h1>";
		}
	}
	_content = content;
	_content_length = content.length();
	_extension = used_extension;
}

std::vector<std::string>	Response::split_file_and_directory(std::string line) const
{
	std::string 				delimiter = "\n";
	std::vector<std::string>	words;
	size_t 			pos;
	int 			i = 0;
	if (line.size() == 0)
		return (words);
	while ((i = line.find_first_of(delimiter)) != std::string::npos)
	{
		words.push_back(line.substr(0, i));
		line.erase(0, i + 1);
	}
	words.push_back(line);
	words[words.size() - 1].erase(words[words.size() - 1].size() - 1, 1);
	return (words);
}

void	Response::autoindex(std::string directory, std::string indexFile, Location location)
{
	std::vector<std::string> listedDirectory;
		
	try {
		listedDirectory = split_file_and_directory(File::listDirectory(directory + _request.get_target_path() + indexFile));
	}
	catch (std::exception &e) {
		fill_content_with_error_code(403);
		return ;
	}

	// if (listedDirectory.size() == 0)
	// 	fill_content_with_error_code(403);
	if (location["autoindex"] != "on")
		fill_content_with_error_code(404);
	else
	{
		std::string	templateFile;
		try
		{
			templateFile = File::getFile("utils/template_pages/autoindex.html");
		}
		catch(const std::exception& e)
		{
			templateFile = "<html><head><title>Webserv - Index of $path</title></head><body><h1>Index of $path</h1><ul>$files_and_directories</ul></body></html>";
			std::cerr << e.what() << '\n';
		}

		int i = templateFile.find("$path");
		templateFile.erase(i, 5);
		templateFile.insert(i, _request.get_target_path() + indexFile);

		i = templateFile.find("$path");
		templateFile.erase(i, 5);
		templateFile.insert(i, _request.get_target_path() + indexFile);

		//Fill temp with files and directories
		std::string temp;
		for (i = 0; i < listedDirectory.size(); i++)
		{
			std::stringstream ss;
			ss << File::getFileSize(directory + _request.get_target_path() + indexFile + listedDirectory[i]);
			temp += "<li><a href=\"" + URL::encode(_request.get_target_path() + indexFile + listedDirectory[i]) + "\">" + listedDirectory[i] + " - " + ss.str() + " byte(s)" + "</a></li>";
		}
		i = templateFile.find("$files_and_directories");
		templateFile.erase(i, 23);

		//Main directory
		std::string main_directory = "<li><a href=\"/\">/</a></li>";
		templateFile.insert(i, main_directory);
		i += main_directory.size();

		//Parent directory
		std::string parent_directory;
		if (_request.get_target_path() == "/")
			parent_directory = "";
		else
			parent_directory = "<li><a href=\"" +  URL::encode(Config::getPathBefore(Config::getPathBefore(_request.get_target_path() + indexFile))) + "\">../</a></li>";

		templateFile.insert(i, parent_directory);
		i += parent_directory.size();

		//Insert the list of files and directories
		templateFile.insert(i, temp);
		
		_content = templateFile;
		_content_length = _content.length();
		_extension = ".html";
	}
}

std::vector<std::string>	Response::split_with_space(std::string line) const
{
	std::vector<std::string>	words;

	if (line.size() == 0)
		return (words);
	int k = 0;
	int j = -1;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			//to prevent segfault from starting at words[1] instead of words[0]
			if (i != 0)
				k++;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			i--;
		}
		else
		{
			//to create a new word in the vector
			if (j != k)
			{
				j = k;
				words.push_back("");
			}
			words[k].push_back(line[i]);
		}
	}
	return (words);
}

std::string	Response::get_index_file(std::string directory, std::string indexs_from_config) const
{
	std::vector<std::string>	indexs;

	indexs = split_with_space(indexs_from_config);
	if (indexs.size() == 0)
		return ("index.html");
	for (int i = 0; i < indexs.size(); i++)
	{
		if (File::getType(directory + _request.get_target_path() + indexs[i]) != -1)
			return (indexs[i]);
	}
	return ("index.html");
}

std::string	Response::get_directory_index(std::string directory, std::string indexs_from_config)
{
	std::vector<std::string>	indexs;

	indexs = split_with_space(indexs_from_config);
	if (indexs.size() == 0)
		return ("index.html");
	for (int i = 0; i < indexs.size(); i++)
	{
		if (File::getType(directory + indexs[i]) != -1)
			return (indexs[i]);
	}
	return ("index.html");
}


std::string	Response::get_return(void) const
{
	return (this->_return);
}

std::string	Response::inLocationOrConfig(Location location, Config config, std::string what)
{
	what = URL::encode(what);
	if (!location[what].empty())
		return (location[what]);
	else if (!config[what].empty())
		return (config[what]);
	return ("");
}

void	Response::content_fill_from_file(void)
{
	if (_request.get_code() >= 300)
	{
		fill_content_with_error_code(_request.get_code());
		return ;
	}

	std::string	content;
	Location location;

	std::string root, indexs_from_config;
	
	try {
		location = Config::returnPath(_server.get_config(), URL::encode(_request.get_target_path()));
	}
	catch (const std::exception& e){ std::cout << RED << "JE PETE A L'EXCEPTION" << RST << std::endl;}

	if (!location["return"].empty())
	{
		// std::string return_path = location["return_path"];
		// int			return_code = location["return_code"];
		std::string return_path = location["return"];
		int			return_code = 301;

		set_return(return_path);
		_request.set_code(return_code);
		return ;
	}

	if ((root = inLocationOrConfig(location, _server.get_config(), "root")).empty())
		root = "www";
	if ((indexs_from_config = inLocationOrConfig(location, _server.get_config(), "index")).empty())
		indexs_from_config = "index.html";

	std::cout << GRN << location["index"] << RST << std::endl;

	std::string indexFile = "";
	if (_request.get_target_path()[_request.get_target_path().find_first_of("/") + 1] == ' ' || _request.get_target_path()[_request.get_target_path().find_first_of("/") + 1] == '\0')
		indexFile = get_index_file(root, indexs_from_config);

	switch(File::getType(root + _request.get_target_path() + indexFile))
	{

		case -1: //Not exist
			std::cout << RED << "SA ME FAIT CHIER" << RST << std::endl;
			if (_request.get_target_path() != "/")
			{
				fill_content_with_error_code(404);
				break;
			}
			indexFile = "";
		case 1: //Directory
			if (_request.get_target_path().find_last_of('/') != _request.get_target_path().size() - 1)
			{
				std::string	target_path_with_slash = _request.get_target_path() + "/";
				_request.set_target_path_force(target_path_with_slash);
			}
			// std::cout << RED << root + _request.get_target_path() + get_index_file(root, indexs_from_config) << RST << std::endl;
			if (File::getType(root + get_directory_index(root, indexs_from_config)) == 1)
			{
				set_return(get_directory_index(root, indexs_from_config));
				_request.set_code(301);
				return ;
			}
			if (File::getType(root + _request.get_target_path() + get_index_file(root, indexs_from_config)) == -1)
			{
				autoindex(root, indexFile, location);
				break;
			} 
			else
				indexFile = get_index_file(root, indexs_from_config);
		case 2: //File
			std::cout << File::getFileSize(root + _request.get_target_path() + indexFile) << std::endl;
			std::cout << "'"<<_server.get_config()["client_body_buffer_size"] << "'" << std::endl;
			if (_server.get_config()["client_body_buffer_size"].empty() && File::getFileSize(root + _request.get_target_path() + indexFile) > 100 * 1000000)
			{
				fill_content_with_error_code(413);
				break;
			}
			else if (!_server.get_config()["client_body_buffer_size"].empty() && File::getFileSize(root + _request.get_target_path() + indexFile) > (Utils::string_to_int(_server.get_config()["client_body_buffer_size"]) * 1000000))
			{
				fill_content_with_error_code(413);
				break;
			}
			try
			{
				if (_request.get_target_path().find(".php") != std::string::npos)
				{
					std::cout << "Hey, PHP" << std::endl;
					std::map<std::string, std::string>	envp = Utils::envToMap(_server.get_envp());

					char	**arg;
					int		fd[2];
					int		fd1[2];
					int		fd2[2];

					pipe(fd);
					pipe(fd1);
					pipe(fd2);
					arg = (char **)malloc(sizeof(char *) * 2);
					arg[0] = strdup("/usr/bin/php-cgi");
					arg[1] = NULL;
					std::cout << "Command : " << arg[0] << " " << arg[1] << std::endl;
					int pid = 0;
					if ((pid = fork()) == 0)
					{
						dup2(fd2[0], 0);
						dup2(fd[1], 1);
						dup2(fd1[1], 2);
						close(fd[0]);
						close(fd[1]);
						close(fd1[0]);
						close(fd1[1]);
						close(fd2[0]);
						close(fd2[1]);
						std::cout << "Return error : " << execve("/usr/bin/php-cgi", arg, _server.get_envp()) << std::endl;
						exit(-1);
					}
					write(fd2[1], File::getFile(root + _request.get_target_path() + indexFile).c_str(), File::getFileSize(root + _request.get_target_path() + indexFile));
					close(fd2[1]);
					int	exit_code = 0;
					waitpid(pid, &exit_code, 0);
					close(fd[1]);
					close(fd1[1]);
					close(fd2[0]);
					std::string res = Utils::read_fd(fd[0]);
					std::string err = Utils::read_fd(fd1[0]);
					close(fd[0]);
					close(fd1[0]);
					std::cout.flush();
					std::cerr << "Exit code : " << exit_code << std::endl;
					std::cerr << "Return : " << res << std::endl;
					std::cerr << "Error : " << err << std::endl;
					std::cout.flush();
					free(arg[0]);
					free(arg);
					if (res.find("Content-type") == std::string::npos || exit_code != 0)
					{
						fill_content_with_error_code(500);
						break;
					}
					content += res;
				}
				else
					content += File::getFile(root + _request.get_target_path() + indexFile);
			}
			catch(const std::exception& e)
			{
				fill_content_with_error_code(403);
				break ;
			}
			
			_content = content;
			if (_request.get_target_path().find(".php") != std::string::npos)
			{
				int	tmp = content.find("\r\n\r\n");
				_content_length = content.length() - tmp - 4;
			}
			else
				_content_length = _content.length();
			_extension = get_extension(_request.get_target_path() + indexFile);
			break;
	}
}

void	Response::create_response(void)
{
	content_fill_from_file();
	_response = "HTTP/1.1 ";
	_response += Utils::Utils::int_to_string(_request.get_code()) + " " + get_text_code(_request.get_code()) + "\r\n";
	_response += "Server: Webserv/1.0.0\r\n";
	_response += "Content-Length: " + Utils::Utils::int_to_string(_content_length) + "\r\n";
	if (_request.get_code() >= 301 && _request.get_code() <= 308)
		_response += "Location: " + get_return() + "\r\n";
	if (_request.get_target_path().find(".php") == std::string::npos || _request.get_code() == 500)
	{
		_response += "Content-Type: " + get_content_type() + "\r\n";
		_response += "\r\n";
	}
	_response += _content + "\r\n";

	//std::cout<< _response;
}

std::string		Response::get_response(void) const
{
	return (_response);
}
