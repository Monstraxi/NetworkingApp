#include <iostream>
#include <winsock2.h>

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
}