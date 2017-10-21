//server 服务器

#include <stdio.h>
#include <winsock2.h>
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
	// SOCKET socket(int af, int type, int protocol);  
	// 第一个参数，指定地址簇(TCP/IP只能是AF_INET，也可写成PF_INET)  
	// 第二个，选择套接字的类型(流式套接字)，第三个，特定地址家族相关协议（0为自动）
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	//绑定IP和端口
	sockaddr_in addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8888);
	addrSrv.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//开始监听
	listen(sockSrv, 5);

	//循环接收数据
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	while (true)
	{
		printf("等待连接...\n");
		sClient = accept(sockSrv, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));

		//接收数据
		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			printf(revData);
		}

		//发送数据
		char * sendData = "你好，TCP客户端！\n";
		send(sClient, sendData, strlen(sendData), 0);
		closesocket(sClient);
	}
	printf("end\n");
	closesocket(sockSrv);
	WSACleanup();
	return 0;
}
