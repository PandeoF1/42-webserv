#include "../http.h"

char	*ft_request(char *page)
{
	char		*content;
	char		**a;
	char		**b;
	char		*tmp;
	int			i;

	content = NULL;
	char *convert = "localhost";
	const char	*ip = host_to_ip(convert);
	SOCKET		sock;
	SOCKADDR_IN	sin;

	if (!http_create_socket(&sock, &sin, ip))
		return (NULL);
	content = http_request(sock, convert, page);
	//printf("%s\n", content);
	closesocket(sock);
	//free(convert);
	return (content);
}
