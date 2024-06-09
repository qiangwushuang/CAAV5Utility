#include "HttpConnect.h"

#include <iostream>

#ifdef WIN32
#pragma comment(lib,"ws2_32.lib")
#endif

HttpConnect::HttpConnect()
{
#ifdef WIN32
	//�˴�һ��Ҫ��ʼ��һ�£�����gethostbyname����һֱΪ��
	WSADATA wsa = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
}

HttpConnect::~HttpConnect()
{

}
void HttpConnect::socketHttp(std::string host,int port, std::string request)
{
	int sockfd;
	struct sockaddr_in address;
	struct hostent *server;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	server = gethostbyname(host.c_str());
	memcpy((char *)&address.sin_addr.s_addr,(char*)server->h_addr, server->h_length);

	if(-1 == connect(sockfd,(struct sockaddr *)&address,sizeof(sockaddr))){
		std::cout <<"connection error!"<<std::endl;
		return;
	}

#ifdef WIN32
	//std::string sData = G2U(request.c_str());
	send(sockfd, request.c_str(),request.length()+1,0);
#else
	write(sockfd,request.c_str(),request.size());
#endif
 	char buf[1024*1024] = {0};


	int offset = 0;
	int rc;

#ifdef WIN32
	while(rc = recv(sockfd, buf+offset, 1024,0))
#else
	while(rc = read(sockfd, buf+offset, 1024))
#endif
	{
		std::string sBuf = buf;
		if (sBuf.find("201") > 0)
		{
			break;
		}
	}

#ifdef WIN32
	closesocket(sockfd);
#else
	close(sockfd);
#endif
	buf[offset] = 0;
	std::cout << buf << std::endl;

}

void HttpConnect::postData(std::string host,int port, std::string path, std::string post_content)
{
	//POST����ʽ
	//std::stringstream stream;
	/*stream << "POST " << path;
	stream << " HTTP/1.0\r\n";
	stream << "Host: "<< host << "\r\n";
	stream << "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
	stream << "Content-Type:multipart/form-data; boundary=--------------------------081656392089719011260648\r\n";
	stream << "Content-Length:" << post_content.length()<<"\r\n";
	stream << "Connection:close\r\n\r\n";*/
	//stream << post_content.c_str();

	socketHttp(host,port, post_content);
}

void HttpConnect::getData(std::string host, std::string path, std::string get_content)
{
	//GET����ʽ
	std::stringstream stream;
	stream << "GET " << path << "?" << get_content;
	stream << " HTTP/1.0\r\n";
	stream << "Host: " << host << "\r\n";
	stream <<"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
	stream <<"Connection:close\r\n\r\n";

	socketHttp(host,80, stream.str());
}