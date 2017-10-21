//client 客户机

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

int main(int argc, char* argv[])
{
	//初始化WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	//创建套接字
	SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//绑定IP和端口
	sockaddr_in addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8888);
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//建立连接
    connect(sClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//发送消息
	char * sendData = "你好，TCP服务端，我是客户端!\n";
	send(sClient, sendData, strlen(sendData), 0);
	
   //接收消息
	char recData[255];
	int ret = recv(sClient, recData, 255, 0);
	if (ret > 0)
	{
		recData[ret] = 0x00;
		printf(recData);
	}

	printf("end linking......\n");
	closesocket(sClient);
	WSACleanup();
	return 0;
}
