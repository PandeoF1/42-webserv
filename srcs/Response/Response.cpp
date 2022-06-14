#include "Response.hpp"

Response::Response(Request &request) : _request(request)
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
	return ("text/plain");
}

std::string	Response::get_text_code(void) const
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
		case 304:
			return ("Not Modified");
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

void	Response::fill_content_with_error_code(int code)
{
	File file;
	std::string content;

	_request.set_code(code);
	try {
		content = file.getFile("errors_pages/" + std::to_string(code) + ".html");
	}
	catch (std::exception &e) {
		content = "<h1>404 Not Found</h1>";
	}	
	_content = content;
	_content_length = content.length();
	_extension = ".html";
}

void	Response::content_fill_from_file(void)
{
	std::string	content;
	std::string directory = "www";

	//A recup de la config plus tard
	std::string indexFile;
	if (_request.get_target_path()[_request.get_target_path().find_first_of("/") + 1] == ' ' || _request.get_target_path()[_request.get_target_path().find_first_of("/") + 1] == '\0')
		indexFile = "index.html";
	else
		indexFile = "";

	if (File::getType(directory + _request.get_target_path() + indexFile) == -1) { // Not exist
		fill_content_with_error_code(404);
	} else if (File::getType(directory + _request.get_target_path() + indexFile) == 1) { // Directory
		std::string listedDirectory = File::listDirectory(directory + _request.get_target_path() + indexFile);
		std::cout << listedDirectory << std::endl;
		if (listedDirectory.empty())
			fill_content_with_error_code(403);
		else
		{
			content = "<html><body><h1>Index of " + _request.get_target_path() + indexFile + "</h1></body></html>";
			_content = content;
			_content_length = _content.length();
			_extension = ".html";
		}
	} else if (File::getType(directory + _request.get_target_path() + indexFile) == 2) { // File
		content += File::getFile(directory + _request.get_target_path() + indexFile);
		_content = content;
		_content_length = _content.length();
		_extension = get_extension(_request.get_target_path() + indexFile);
	}
}

void	Response::create_response(void)
{
	content_fill_from_file();
	_response = "HTTP/1.1 ";
	_response += std::to_string(_request.get_code()) + " " + get_text_code() + "\r\n";
	_response += "Server: Webserv/1.0.0\r\n";
	_response += "Content-Type: " + get_content_type() + "\r\n";
	_response += "Content-Length: " + std::to_string(_content_length) + "\r\n\r\n";
	_response += _content + "\r\n";

	std::cout << _response;
}

std::string		Response::get_response(void) const
{
	return (_response);
}