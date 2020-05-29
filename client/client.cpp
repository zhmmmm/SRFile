#include "socket/PlatformSocket.h"

//int main()
//{
//
//	Socket sock;
//	sock.init();
//	auto s = sock.socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	auto si = sock.setSin_family("127.0.0.1", 12345);
//	auto ret = sock.connects(s, (sockaddr*)si, sizeof(sockaddr_in));
//	if (!ret)
//	{
//		char buf[256] = { 0 };
//		int ret = 0;
//		while (true)
//		{
//			ZeroMemory(buf, sizeof(buf));
//			ret = sock.recv(s, buf, 256);
//			if (ret > 0)
//			{
//				std::cout << "recv " << buf << std::endl;
//			}
//
//			std::string data;
//			std::cin >> buf;
//			data = buf;
//			sock.send(s, (char*)data.c_str(), data.length());
//		}
//	}
//
//	system("pause");
//	return 0;
//}

int main()
{

	Socket sock;
	sock.init();

	auto s = sock.socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	printf("create socket %d \n", s);
	auto si = sock.setSin_family("127.0.0.1", 12345);
	auto ret = sock.connects(s, (sockaddr*)si, sizeof(*si));
	std::cout << "connect ret " << ret << std::endl;
	if (!ret)
	{
		char buf[256] = { 0 };
		int ret = 0;
		int sc = 0;
		while (true)
		{
			ZeroMemory(buf, sizeof(buf));
			ret = sock.recv(s, buf, 256);
			if (ret > 0)
			{
				std::cout << "recv " << buf << " len " << ret << std::endl;
			}

			std::string data;
			printf("plase input data: ");
			std::cin >> buf;
			data = buf;
			ret = sock.send(s, (char*)data.c_str(), data.length());
			sc++;
			if (sc == 3)
			{
				sock.close();
				//shutdowns(s, SHUT_RDWR);
			}
		}
	}

	return 0;
}