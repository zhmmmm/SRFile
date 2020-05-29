#include "socket/PlatformSocket.h"

//int main()
//{
//
//	Socket sock;
//	sock.init();
//	auto s = sock.socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	sock.m_sock = s;
//	auto si = sock.setSin_family(nullptr, 12345);
//	sock.bind(s, si);
//	sock.listen(s, 100);
//
//	char buf[256] = { 0 };
//	int ret = 0;
//	SOCKET socket = -1;
//	while (true)
//	{
//		socket = sock.accept(sock.m_sock);
//		if (socket != INVALID_SOCKET)
//		{
//			break;
//		}
//	}
//	if (socket != -1)
//	{
//		std::cout << "ÓÃ»§ " << socket << " connect" << std::endl;
//		while (true)
//		{
//			ZeroMemory(buf, sizeof(buf));
//			ret = sock.recv(socket, buf, 256);
//			if (ret > 0)
//				std::cout << "recv " << buf << std::endl;
//			std::string data;
//			std::cin >> buf;
//			data = buf;
//			sock.send(socket, (char*)data.c_str(), data.length());
//		}
//	}
//
//
//
//
//
//
//	system("pause");
//	return 0;
//}

int main()
{

	Socket sock;
	sock.init();
	auto s = sock.socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sock.m_sock = s;
	auto si = sock.setSin_family(nullptr, 12345);
	sock.bind(s, si);
	sock.listen(s, 100);

	char buf[256] = { 0 };
	int ret = 0;
	int socket = -1;
	while (true)
	{
		socket = sock.accept(sock.m_sock);
		if (socket != -1)
		{
			break;
		}
	}
	if (socket != -1)
	{
		std::cout << "user  " << socket << " connect" << std::endl;
		while (true)
		{
			ZeroMemory(buf, sizeof(buf));
			ret = sock.recv(socket, buf, 256);
			if (ret > 0)
				std::cout << "recv " << buf << " len " << ret << std::endl;
			std::string data;
			printf("plase input data: ");
			std::cin >> buf;
			data = buf;
			ret = sock.send(socket, (char*)data.c_str(), data.length());
		}
	}


	return 0;
}