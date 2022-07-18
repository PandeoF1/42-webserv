#include "includes/webserv.hpp"

int main(int argc, char *argv[], char *envp[])
{
	if (argc != 2 && argc != 1)
	{
		std::cout << "Usage: " << argv[0] << " <config>" << std::endl;
		return (1);
	}
	try {
		std::map<int, Config> config;
		if (argc == 1)
			config = Config::createConfig("config.conf");
		else
			config = Config::createConfig(argv[1]);
		Config::print(config);
		Server::start_servers(config, envp);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
}