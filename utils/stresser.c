#include "http.h"

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
}

int main(int argc, char *argv[])
{
	int64_t time;
	int64_t moy = 0;
	int		n_moy = 0;
	int64_t between;

	if (argc != 3)
	{
		printf("./stresser [nb_test] [print (1 oui, 0 non)\n");
		exit(0);
	}
	while (n_moy != atoi(argv[1]))
	{
		time = get_time();
		if (atoi(argv[2]))
			printf("Output : {\n%s\n}\n", ft_request("/"));
		between = get_time() - time;
		moy += between;
		n_moy++;
	}
	dprintf(1, "\nmoy : %ld", moy / n_moy);
	
	/*time = get_time();
	while (get_time() - time <= 10000)
	{
		ft_request("/");
		n_moy++;
		dprintf(1, "\033[2K\r%d\e[0m", n_moy);	
	}*/
	printf("\n");
}