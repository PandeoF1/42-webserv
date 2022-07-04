#pragma once

/* File */
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <dirent.h>
/* Server */
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <map>
#include <iostream>
#include <sstream>

#ifndef MSG_NOSIGNAL
# define MSG_NOSIGNAL 0x2000
#endif

# define ACCEPT 0

#include <stdio.h>
#include <iostream>
#include <string.h> 
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <vector>
#include <fcntl.h>

#include "../srcs/Server/Server.hpp"
#include "../srcs/File/File.hpp"
#include "../srcs/Server/Server.hpp"
#include "../srcs/Config/Config.hpp"
#include "../srcs/Config/Location/Location.hpp"
#include "../srcs/Request/Request.hpp"
#include "../srcs/Response/Response.hpp"
#include "../srcs/URL/URL.hpp"
#include "../srcs/Utils/Utils.hpp"

#define				Location_Name "location"
static std::string	Location_Valid_Param[] = {"allow_methods", "root", "alias", "client_body_buffer_size", "index", "cgi_pass", "autoindex", "return"};
#define				Location_Valid_Param_Length 8
#define				Location_Methods 0
#define				Location_Root 1
#define				Location_Cgi 5
#define				Location_Buffer 3
#define             Location_autoindex 6
#define             Location_Return 7


static std::string	Server_Valid_Param[] = {"server_name", "listen", "root", "index", "allow_methods", "client_body_buffer_size", "error_400", "error_403", "error_404", "error_405", "error_413", "error_406", "error_50x"};
#define				Server_Valid_Param_Length 13
#define				Server_IP 1
#define				Server_Root 2
#define				Server_Methods 4


static std::string	Methods_List[] = {"POST", "GET", "DELETE", "PUT"};
#define				Methods_List_Length 4

#define				Buffer_Max 100000
#define				Buffer_Min 1
/* 1 = You can set up multiple parameters declaration with the same name (ex : 2 server_name (the last take the main)), 0 = you can't */
#define             Multiple_Declaration 1

static std::string		url_encoding_characters[]	= {" "  , "\"" , "<" ,   ">" , "\\" ,  "^" ,  "`" ,  "|" , "{",    "}",       "€",        "",       "‚",       "ƒ",       "„",         "…",         "†",        "‡",       "ˆ",        "‰",       "Š",         "‹",        "Œ",      "",       "Ž",     "",    "",         "‘",         "’",         "“",         "”",         "•",          "–",          "—",        "˜",      "™",        "š",       "›",         "œ",      "",      "ž",      "Ÿ",      "¡",   "¢",       "£",       "¤",       "¥",     "¦",      "§",       "¨",       "©",      "ª",      "«",       "¬",       "®",       "¯",       "°",     "±",       "²",      "³",     "´",       "µ",     "¶",       "·",      "¸",      "¹",      "º",     "»",        "¼",    "½",       "¾",      "¿",      "À",      "Á",     "Â",      "Ã",       "Ä",      "Å",     "Æ",      "Ç",       "È",      "É",     "Ê",       "Ë",     "Ì",      "Í",      "Î",      "Ï",       "Ð",      "Ñ",     "Ò",       "Ó",      "Ô",     "Õ",       "Ö",      "×",     "Ø",       "Ù",      "Ú",      "Û",      "Ü",      "Ý",      "Þ",      "ß",      "à",      "á",     "â",      "ã",       "ä",      "å",      "æ",      "ç",      "è",      "é",      "ê",      "ë",      "ì",     "í",      "î",      "ï",       "ð",      "ñ",       "ò",     "ó",      "ô",      "õ",      "ö",      "÷",    "ø",       "ù",       "ú",      "û",      "ü",     "ý",       "þ",     "ÿ"};
static std::string		url_encoding_utf8[] 		= {"%20", "%22", "%3C", "%3E", "%5C", "%5E", "%60", "%7C", "%7B", "%7D", "%E2%82%AC", "%C2%81", "%E2%80%9A", "%C6%92", "%E2%80%9E", "%E2%80%A6", "%E2%80%A0", "%E2%80%A1", "%CB%86", "%E2%80%B0", "%C5%A0",  "%E2%80%B9",  "%C5%92", "%C2%8D",  "%C5%BD", "%C2%8F", "%C2%90", "%E2%80%98", "%E2%80%99",  "%E2%80%9C", "%E2%80%9D", "%E2%80%A2", "%E2%80%93",  "%E2%80%94", "%CB%9C", "%E2%84%A2", "%C5%A1", "%E2%80%BA",  "%C5%93", "%C2%9D", "%C5%BE", "%C5%B8", "%C2%A1", "%C2%A2", "%C2%A3", "%C2%A4", "%C2%A5", "%C2%A6", "%C2%A7",  "%C2%A8", "%C2%A9", "%C2%AA", "%C2%AB",   "%C2%AC",  "%C2%AE",  "%C2%AF", "%C2%B0", "%C2%B1", "%C2%B2", "%C2%B3", "%C2%B4", "%C2%B5", "%C2%B6", "%C2B7", "%C2%B8", "%C2%B9", "%C2%BA", "%C2%BB", "%C2%BC", "%C2%BD", "%C2%BE", "%C2%BF", "%C3%80", "%C3%81", "%C3%82", "%C3%83", "%C3%84", "%C3%85", "%C3%86", "%C3%87", "%C3%88", "%C3%89", "%C3%8A", "%C3%8B", "%C3%8C", "%C3%8D", "%C3%8E", "%C3%8F", "%C3%90", "%C3%91", "%C3%92", "%C3%93", "%C3%94", "%C3%95", "%C3%96", "%C3%97", "%C3%98", "%C3%99", "%C3%9A", "%C3%9B", "%C3%9C", "%C3%9D", "%C3%9E", "%C3%9F", "%C3%A0", "%C3%A1", "%C3%A2", "%C3%A3", "%C3%A4", "%C3%A5", "%C3%A6", "%C3%A7", "%C3%A8", "%C3%A9", "%C3%AA", "%C3%AB", "%C3%AC", "%C3%AD", "%C3%AE", "%C3%AF", "%C3%B0", "%C3%B1", "%C3%B2", "%C3%B3", "%C3%B4", "%C3%B5", "%C3%B6", "%C3%B7", "%C3%B8", "%C3%B9", "%C3%BA", "%C3%BB", "%C3%BC", "%C3%BD", "%C3%BE", "%C3%BF"};
#define					url_encoding_length 136

