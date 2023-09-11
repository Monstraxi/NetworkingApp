#include <iostream>
#include <WS2tcpip.h>

int main()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		std::cerr << "WSAStartup failed!" << std::endl;
		return -1;
	}

	if (LOBYTE(wsadata.wVersion) != 2 && HIBYTE(wsadata.wHighVersion) != 2)
	{
		std::cerr << "Winsock version 2.2 is not available!" << std::endl;
		WSACleanup();
		return -1;
	}

	int status;
	addrinfo hints;
	addrinfo* servInfo;
	memset(&hints, 0, sizeof(hints));

	char ipstr[INET6_ADDRSTRLEN];

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	status = getaddrinfo("www.youtube.com", NULL, &hints, &servInfo);

	if (status != 0)
	{
		std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
		return -1;
	}

	for (addrinfo* p = servInfo; p != nullptr; p = p->ai_next)
	{
		void* addr;
		char* ipVer;

		if (p->ai_family == AF_INET)
		{
			sockaddr_in* ipV4 = (sockaddr_in*)p->ai_addr;
			addr = &(ipV4->sin_addr);
			ipVer = "IPv4";
		}
		else
		{
			sockaddr_in6* ipV6 = (sockaddr_in6*)p->ai_addr;
			addr = &(ipV6->sin6_addr);
			ipVer = "IPv6";
		}

		inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
		std::cout << ipVer << ": " << ipstr << std::endl;
	}

	WSACleanup();
}