#include <iostream>
#include <string.h>
#include <signal.h>
using namespace std;
#include "../../../src/Tools/SendFile.h"
#include "../../../src/Tools/RecvFile.h"
#include "../../../src/socket/Private/MemoryPool.h"
#include "../../../src/Tools/Tools.h"


#define SERVER 0
#define CLIENT 1

typedef struct CONFIG
{
	char service[64];
	char ip[32];
	int port;
	char dir[255];
	char file[255];
	int maxSend;
}Config,*LPConfig;

static Config config;
Tools tools;

bool runing();
void Server();
void Client();
void Signal(int v)
{
	printf("signal %d\n",v);
	SendFile::getInstance()->closeSend();
	RecvFile::getInstance()->closeRecv();
	tools.freeAll();
	exit(0);
}
void message()
{
	printf("-i/--init          server or client\n");
	printf("-p/--port          server port\n");
	printf("-t/--target        target IP\n");
	printf("-d/--dir           current director, send director or is recv director\n");
	printf("-f/--file          file name or file full path\n");
	printf("-s/--send          set max send byte\n");
	printf("\n *********server is recv,client is send*********\n\n");
	printf("\n *********select one service*********\n\n");
	printf("\n *********file size Better not exceed .long. Value range*********\n\n");
	printf("\n *********max send byte 0 or -1 default is 4096 + 1*********\n\n");
}

int main(int argc, char **argv)
{
	signal(SIGINT, Signal);

	ZeroMemory(&config, sizeof(Config));

	printf("\n\
		*************************************\n\
		*************************************\n\
		*************************************\n\
		*************************************\n\
		*************************************\n\
		**************YZFHKMS-W**************\n\
		*************************************\n\
		*************************************\n\
		*************************************\n\
		*************************************\n\
		*************************************\n\
		*************************************\n\
		*************************************\n\
		\n");
	if (argc > 1)
	{
		for (int i = 1; i < argc - 1; i++)
		{
			if (argv[i] == string("-i") || argv[i] == string("--init"))
			{
				memcpy(config.service, argv[i + 1], strlen(argv[i + 1]));
			}
			else if (argv[i] == string("-p") || argv[i] == string("--port"))
			{
				config.port = atoi(argv[i + 1]);
			}
			else if (argv[i] == string("-t") || argv[i] == string("--target"))
			{
				memcpy(config.ip, argv[i + 1], strlen(argv[i + 1]));
			}
			else if (argv[i] == string("-d") || argv[i] == string("--dir"))
			{
				memcpy(config.dir, argv[i + 1], strlen(argv[i + 1]));
			}
			else if (argv[i] == string("-f") || argv[i] == string("--file"))
			{
				memcpy(config.file, argv[i + 1], strlen(argv[i + 1]));
			}
			else if (argv[i] == string("-s") || argv[i] == string("--send"))
			{
				config.maxSend = atoi(argv[i + 1]);
			}
		}
	}
	else
	{
		message();
		return 0;
	}
	if (runing())
	{
		message();
		return 0;
	}
	printf("runing service .............\n");
	while (true)
	{
		SendFile::getInstance()->runing();
		RecvFile::getInstance()->runing();
		RecvFile::getInstance()->saveAllFile();
	}
	
	return 0;
}

bool runing()
{
	printf("service %s\n",config.service);
	printf("port    %d\n", config.port);
	printf("target    %s\n", config.ip);
	printf("dir    %s\n", config.dir);
	printf("file    %s\n", config.file);
	if (config.service == string("server"))
	{
		Server();
	}
	else if(config.service == string("client"))
	{
		Client();
	}
	else
	{
		printf("please select one service!\n");
		return true;
	}
	return false;
}

void Server()
{
	RecvFile::getInstance()->init(nullptr, config.port);
	RecvFile::getInstance()->setSaveDir(config.dir);
}

void Client()
{
	SendFile::getInstance()->setMaxSendByte(config.maxSend);
	bool ret = SendFile::getInstance()->init(config.ip, config.port);
	if (!ret)
	{
		void *data = nullptr;
		long size = 0;
		FILE *pf = nullptr;
		string file = config.file;
		file = tools.CrossPlatformStringForPath(file);
		pf = fopen(file.c_str(), "rb");
		if (pf)
		{
			fseek(pf, 0, SEEK_END);
			size = ftell(pf);
			printf("file size is :   %ld\n", size);
			rewind(pf);
			data = tools.Allocate(size + 1);
			fread(data, 1, size, pf);
			fclose(pf);
			
			SendFile::getInstance()->sendFile(data, size, tools.PathForFileName(file));
		}
	}
}