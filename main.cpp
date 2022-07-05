#include "includes/webserv.hpp"

int main(int argc, char *argv[], char *envp[])
{
	(void)argc, (void)argv;
	try {
		std::map<int, Config> config = Config::createConfig("config.conf");
		//Config::returnPath(config[0], "/post_body/post_body/post_body/post_body");
		//Config::print(config);
		Server::start_servers(config, envp);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	// std::map<int, Config> config = Config::createConfig("config.conf");
	// Config::print(config);
}