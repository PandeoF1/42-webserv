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

std::string Response::check_accept_type(std::string str)
{
	if (ACCEPT == 1)
	{
		if (_request.get_content_type_map()["*/*"])
			return (str);
		if (!_request.get_content_type_map()[str])
		{
			if (str.find_first_of('/') == std::string::npos)
			{
				fill_content_with_error_code(406);
				return ("");
			}
			else
			{
				std::string temp = str.substr(0, str.find_first_of('/') + 1);
				temp += "*";
				if (!_request.get_content_type_map()[temp])
				{
					fill_content_with_error_code(406);
					return ("");
				}
				return (str);
			}
		}
	}
	return (str);
}

std::string	Response::get_content_type(void)
{
	if (!_extension.compare(".aac"))
		return (check_accept_type("audio/aac"));
	if (!_extension.compare(".abw"))
		return (check_accept_type("application/x-abiword"));
	if (!_extension.compare(".arc"))
		return (check_accept_type("application/octet-stream"));
	if (!_extension.compare(".avi"))
		return (check_accept_type("video/x-msvideo"));
	if (!_extension.compare(".azw"))
		return (check_accept_type("application/vnd.amazon.ebook"));
	if (!_extension.compare(".bin"))
		return (check_accept_type("application/octet-stream"));
	if (!_extension.compare(".bmp"))
		return (check_accept_type("image/bmp"));
	if (!_extension.compare(".bz"))
		return (check_accept_type("application/x-bzip"));
	if (!_extension.compare(".bz2"))
		return (check_accept_type("application/x-bzip2"));
	if (!_extension.compare(".csh"))
		return (check_accept_type("application/x-csh"));
	if (!_extension.compare(".css"))
		return (check_accept_type("text/css"));
	if (!_extension.compare(".csv"))
		return (check_accept_type("text/csv"));
	if (!_extension.compare(".doc"))
		return (check_accept_type("application/msword"));
	if (!_extension.compare(".docx"))
		return (check_accept_type("application/vnd.openxmlformats-officedocument.wordprocessingml.document"));
	if (!_extension.compare(".eot"))
		return (check_accept_type("application/vnd.ms-fontobject"));
	if (!_extension.compare(".epub"))
		return (check_accept_type("application/epub+zip"));
	if (!_extension.compare(".gif"))
		return (check_accept_type("image/gif"));
	if (!_extension.compare(".htm"))
		return (check_accept_type("text/html"));
	if (!_extension.compare(".html"))
		return (check_accept_type("text/html"));
	if (!_extension.compare(".ico"))
		return (check_accept_type("image/x-icon"));
	if (!_extension.compare(".ics"))
		return (check_accept_type("text/calendar"));
	if (!_extension.compare(".jar"))
		return (check_accept_type("application/java-archive"));
	if (!_extension.compare(".jpeg"))
		return (check_accept_type("image/jpeg"));
	if (!_extension.compare(".jpg"))
		return (check_accept_type("image/jpeg"));
	if (!_extension.compare(".js"))
		return (check_accept_type("application/javascript"));
	if (!_extension.compare(".json"))
		return (check_accept_type("application/json"));
	if (!_extension.compare(".mid"))
		return (check_accept_type("audio/midi"));
	if (!_extension.compare(".midi"))
		return (check_accept_type("audio/midi"));
	if (!_extension.compare(".mpeg"))
		return (check_accept_type("video/mpeg"));
	if (!_extension.compare(".mpkg"))
		return (check_accept_type("application/vnd.apple.installer+xml"));
	if (!_extension.compare(".odp"))
		return (check_accept_type("application/vnd.oasis.opendocument.presentation"));
	if (!_extension.compare(".ods"))
		return (check_accept_type("application/vnd.oasis.opendocument.spreadsheet"));
	if (!_extension.compare(".odt"))
		return (check_accept_type("application/vnd.oasis.opendocument.text"));
	if (!_extension.compare(".oga"))
		return (check_accept_type("audio/ogg"));
	if (!_extension.compare(".ogv"))
		return (check_accept_type("video/ogg"));
	if (!_extension.compare(".ogx"))
		return (check_accept_type("application/ogg"));
	if (!_extension.compare(".otf"))
		return (check_accept_type("font/otf"));
	if (!_extension.compare(".png"))
		return (check_accept_type("image/png"));
	if (!_extension.compare(".pdf"))
		return (check_accept_type("application/pdf"));
	if (!_extension.compare(".ppt"))
		return (check_accept_type("application/vnd.ms-powerpoint"));
	if (!_extension.compare(".pptx"))
		return (check_accept_type("application/vnd.openxmlformats-officedocument.presentationml.presentation"));
	if (!_extension.compare(".rar"))
		return (check_accept_type("application/x-rar-compressed"));
	if (!_extension.compare(".rtf"))
		return (check_accept_type("application/rtf"));
	if (!_extension.compare(".sh"))
		return (check_accept_type("application/x-sh"));
	if (!_extension.compare(".svg"))
		return (check_accept_type("image/svg+xml"));
	if (!_extension.compare(".swf"))
		return (check_accept_type("application/x-shockwave-flash"));
	if (!_extension.compare(".tar"))
		return (check_accept_type("application/x-tar"));
	if (!_extension.compare(".tif"))
		return (check_accept_type("image/tiff"));
	if (!_extension.compare(".tiff"))
		return (check_accept_type("image/tiff"));
	if (!_extension.compare(".ts"))
		return (check_accept_type("application/typescript"));
	if (!_extension.compare(".ttf"))
		return (check_accept_type("font/ttf"));
	if (!_extension.compare(".vsd"))
		return (check_accept_type("application/vnd.visio"));
	if (!_extension.compare(".wav"))
		return (check_accept_type("audio/x-wav"));
	if (!_extension.compare(".weba"))
		return (check_accept_type("audio/webm"));
	if (!_extension.compare(".webm"))
		return (check_accept_type("video/webm"));
	if (!_extension.compare(".webp"))
		return (check_accept_type("image/webp"));
	if (!_extension.compare(".woff"))
		return (check_accept_type("font/woff"));
	if (!_extension.compare(".woff2"))
		return (check_accept_type("font/woff2"));
	if (!_extension.compare(".xhtml"))
		return (check_accept_type("application/xhtml+xml"));
	if (!_extension.compare(".xls"))
		return (check_accept_type("application/vnd.ms-excel"));
	if (!_extension.compare(".xlsx"))
		return (check_accept_type("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"));
	if (!_extension.compare(".xml"))
		return (check_accept_type("application/xml"));
	if (!_extension.compare(".xul"))
		return (check_accept_type("application/vnd.mozilla.xul+xml"));
	if (!_extension.compare(".zip"))
		return (check_accept_type("application/zip"));
	if (!_extension.compare(".3gp"))
		return (check_accept_type("video/3gpp"));
	if (!_extension.compare(".3g2"))
		return (check_accept_type("video/3gpp2"));
	if (!_extension.compare(".7z"))
		return (check_accept_type("application/x-7z-compressed"));
	if (!_extension.compare(".mp3"))
		return (check_accept_type("audio/mpeg"));
	if (!_extension.compare(".mp4"))
		return (check_accept_type("video/mp4"));
	if (!_extension.compare(".m4a"))
		return (check_accept_type("audio/mp4"));
	if (!_extension.compare(".m4v"))
		return (check_accept_type("video/mp4"));
	if (!_extension.compare(".mov"))
		return (check_accept_type("video/quicktime"));
	return (check_accept_type("text/plain"));
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
		case 406:
			return ("Not Acceptable");
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

	paths = Utils::split_with_space(paths_from_config);
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

std::string	Response::get_index_file(std::string directory, std::string indexs_from_config) const
{
	std::vector<std::string>	indexs;

	indexs = Utils::split_with_space(indexs_from_config);
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

	indexs = Utils::split_with_space(indexs_from_config);
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
	catch (const std::exception& e){ 
		// std::cout << RED << "JE PETE A L'EXCEPTION" << RST << std::endl;
	}

	if (!location["return"].empty())
	{
		std::string return_path = location["return_path"];
		int			return_code = Utils::string_to_int(location["return_code"]);

		set_return(return_path);
		_request.set_code(return_code);
		return ;
	}

	if ((root = inLocationOrConfig(location, _server.get_config(), "root")).empty())
		root = "www";
	if ((indexs_from_config = inLocationOrConfig(location, _server.get_config(), "index")).empty())
		indexs_from_config = "index.html";

	// std::cout << GRN << location["index"] << RST << std::endl;

	std::string indexFile = "";
	if (_request.get_target_path()[_request.get_target_path().find_first_of("/") + 1] == ' ' || _request.get_target_path()[_request.get_target_path().find_first_of("/") + 1] == '\0')
		indexFile = get_index_file(root, indexs_from_config);

	switch(File::getType(root + _request.get_target_path() + indexFile))
	{

		case -1: //Not exist
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
					std::map<int, std::string>	envp = Utils::envToMap(_server.get_envp());
					char	**arg;
					int		fd[2];
					int		fd1[2];
					int		fd2[2];
					
					int		saveStdin = dup(STDIN_FILENO);
					int		saveStdout = dup(STDOUT_FILENO);
					envp[envp.size()] = "SERVER_PROTOCOL=HTTP/1.1";
					if (_request.get_query_string().empty())
						envp[envp.size()] = "REQUEST_URI=" + _request.get_target_path();
					else
						envp[envp.size()] = "REQUEST_URI=" + _request.get_target_path() + std::string("?") + _request.get_query_string();
					envp[envp.size()] = "SERVER_PORT=" + _server.get_config()["port"];
					envp[envp.size()] = "PATH_INFO=" + _request.get_target_path();
					envp[envp.size()] = "PATH_TRANSLATED=" + _request.get_target_path();

					try
					{
						Location tmp = Config::returnPath(_server.get_config(), URL::encode(_request.get_target_path()));
						envp[envp.size()] = "SCRIPT_NAME=" + _request.get_target_path();
						envp[envp.size()] = "SCRIPT_FILENAME=" + _request.get_target_path();
						if (tmp["cgi_pass"].find("php") != std::string::npos)
							envp[envp.size()] = "REDIRECT_STATUS=200";
						else
						{
							envp[envp.size()] = "SERVER_SOFTWARE=webserv/1.0";
							envp[envp.size()] = "SERVER_NAME=" + _server.get_config()["ip"];
							envp[envp.size()] = "GATEWAY_INTERFACE=CGI/1.1";
							envp[envp.size()] = "REQUEST_METHOD=" + _request.get_method();
						}
					}
					catch(const std::exception& e) {}
					envp[envp.size()] = "QUERY_STRING=" + _request.get_query_string();
					envp[envp.size()] = "REMOTE_ADDR=" + _request.getIp();
					envp[envp.size()] = "CONTENT_TYPE=text/html"; // set content type and content length (content_length)
					envp[envp.size()] = "CONTENT_LENGTH=65";
					char	**env = Utils::mapToEnv(envp);
					pipe(fd);
					pipe(fd1);
					pipe(fd2);
					arg = (char **)malloc(sizeof(char *) * 2);
					arg[0] = strdup("./php-cgi");
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
						std::cout << "Return error : " << execve("./php-cgi", arg, env/*_server.get_envp()*/) << std::endl;
						exit(-1);
					}
					else if (pid == -1)
					{
						std::cerr << RED << "Fork crashed." << RST << std::endl;
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
					dup2(saveStdin, STDIN_FILENO);
					dup2(saveStdout, STDOUT_FILENO);
					close(fd[0]);
					close(fd1[0]);
					close(saveStdin);
					close(saveStdout);
					//std::cerr << "Exit code : " << exit_code << std::endl;
					//std::cerr << "Return : " << res << std::endl;
					//std::cerr << "Error : " << err << std::endl;
					//exit(0);
					int	x = 0;
					while (arg[x])
						free(arg[x++]);
					free(arg);
					x = 0;
					while (env[x])
						free(env[x++]);
					free(env);
					if ((res.find("Content-type") == std::string::npos && res.find("Content-Type") == std::string::npos) || exit_code != 0 || err.find("Status: 500") != std::string::npos || (err.find("Status: 500") != std::string::npos && err.find("Status: 500") >= 20))
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
	_response += Utils::int_to_string(_request.get_code()) + " " + get_text_code(_request.get_code()) + "\r\n";
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
