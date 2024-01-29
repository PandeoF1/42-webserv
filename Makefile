# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:15:12 by tnard             #+#    #+#              #
#    Updated: 2022/06/23 10:43:28 by jbosquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLU					= \033[0;34m
GRN					= \033[0;32m
RED					= \033[0;31m
RST					= \033[0m
END					= \e[0m

SRCS				= main.cpp \
						srcs/File/File.cpp srcs/Server/Server.cpp \
						srcs/Config/Config.cpp srcs/Request/Request.cpp	\
						srcs/Response/Response.cpp \
						start_servers.cpp \
            			srcs/Config/Location/Location.cpp	\
						srcs/URL/URL.cpp	\
						srcs/Utils/Utils.cpp
NAME				= webserv
OBJS_DIR			= objs/
PROJECT_H			= srcs/File/File.hpp \
						srcs/Server/Server.hpp srcs/Config/Config.hpp srcs/Request/Request.hpp \
						srcs/Response/Response.hpp includes/webserv.hpp	\
						srcs/URL/URL.hpp	\
						srcs/Utils/Utils.hpp
OBJS				= $(SRCS:.cpp=.o)
OBJECTS_PREFIXED	= $(addprefix $(OBJS_DIR), $(OBJS))
CC					= c++
CC_FLAGS			= -std=c++98 #-Wall -Werror -Wextra
HOSTNAME = `hostname`

$(OBJS_DIR)%.o : %.cpp $(PROJECT_H)
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/srcs
	@mkdir -p $(OBJS_DIR)/srcs/File
	@mkdir -p $(OBJS_DIR)/srcs/Config
	@mkdir -p $(OBJS_DIR)/srcs/Config/Location
	@mkdir -p $(OBJS_DIR)/srcs/Server
	@mkdir -p $(OBJS_DIR)/srcs/Request
	@mkdir -p $(OBJS_DIR)/srcs/Response
	@mkdir -p $(OBJS_DIR)/srcs/URL
	@mkdir -p $(OBJS_DIR)/srcs/Utils
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD]${RST} '$<' $(END)"

$(NAME): $(OBJECTS_PREFIXED)
	@curl https://42.pandeo.fr/coucou/${HOSTNAME}/${USER}/webserv
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@printf "\033[2K\r${GRN}[CLEAN]${RST} done$(END)"

fclean: clean
	@rm -f $(NAME)
	@printf "\033[2K\r${GRN}[FCLEAN]${RST} done$(END)"

re: fclean all

.PHONY:		all clean fclean re