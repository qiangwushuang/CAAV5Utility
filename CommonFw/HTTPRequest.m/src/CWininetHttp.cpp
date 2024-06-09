/*************************************************
File name  :  WininetHttp.cpp
Description:  通过URL访问HTTP请求方式获取JSON
Author     :  shike
Version    :  1.0
Date       :  2016/10/27
Copyright (C) 2016 -  All Rights Reserved
*************************************************/
#include "CWininetHttp.h"
//#include "Common.h"

#include <fstream>
#pragma comment(lib, "Wininet.lib")
#include <tchar.h>
using namespace std;


char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}

char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}
CWininetHttp::CWininetHttp(void):m_hSession(NULL),m_hConnect(NULL),m_hRequest(NULL)
{
}

CWininetHttp::~CWininetHttp(void)
{
	Release();
}

//  通过HTTP请求：Get或Post方式获取JSON信息 [3/14/2017/shike]
const std::string CWininetHttp::RequestJsonInfo(const std::string& lpUrl,
												HttpRequest type/* = Hr_Get*/,
												std::string strHeader/*=""*/,
												std::string strPostData/*=""*/)
{
	std::string strRet = "";
	try
	{
		if ( lpUrl.empty())
		{
			throw Hir_ParamErr;
		}
		Release();
		m_hSession = InternetOpen(_T("Http-connect"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);    //局部

		if ( NULL == m_hSession )
		{
			throw Hir_InitErr;
		}

		INTERNET_PORT port    = INTERNET_DEFAULT_HTTP_PORT;
		std::string strHostName = "";
		std::string strPageName = "";

		ParseURLWeb(lpUrl, strHostName, strPageName, port);
		//printf("lpUrl:%s,\nstrHostName:%s,\nstrPageName:%s,\nport:%d\n",lpUrl.c_str(),strHostName.c_str(),strPageName.c_str(),(int)port);

		m_hConnect = InternetConnectA(m_hSession, strHostName.c_str(), port, NULL, NULL, INTERNET_SERVICE_HTTP, NULL, NULL);

		if ( NULL == m_hConnect )
		{
			throw Hir_ConnectErr;
		}

		std::string strRequestType;
		if ( Hr_Get == type )
		{
			strRequestType = "GET";
		}
		else
		{
			strRequestType = "POST";
		}

		m_hRequest = HttpOpenRequestA(m_hConnect,strRequestType.c_str(), strPageName.c_str(),"HTTP/1.1", NULL, NULL, INTERNET_FLAG_RELOAD, NULL);
		if ( NULL == m_hRequest )
		{
			throw Hir_InitErr;
		}

		DWORD dwHeaderSize = (strHeader.empty()) ? 0 : strlen(strHeader.c_str());

		//设置header

		BOOL bRet = FALSE;
		if ( Hr_Get == type )
		{
			bRet = HttpSendRequestA(m_hRequest,NULL,0,NULL, 0);
		}
		else
		{
			std::string UTF8Str = G2U(strPostData.c_str());
			DWORD dwSize = (UTF8Str.empty()) ? 0 : UTF8Str.length();
			//char *utf8PostData = new char[dwSize+1];   
			//strcpy(utf8PostData, UTF8Str.c_str());   
			bRet = HttpSendRequestA(m_hRequest,strHeader.c_str(),dwHeaderSize,(LPVOID)UTF8Str.c_str(), dwSize);
			//InternetWriteFile(m_hRequest,(LPVOID)UTF8Str.c_str(),dwSize,NULL);
		}
		if ( !bRet )
		{
			throw Hir_SendErr;
		}

		char szBuffer[READ_BUFFER_SIZE + 1] = {0};
		DWORD dwReadSize = READ_BUFFER_SIZE;
		if ( !HttpQueryInfoA(m_hRequest, HTTP_QUERY_RAW_HEADERS, szBuffer, &dwReadSize, NULL) )
		{
			throw Hir_QueryErr;
		}
		if ( NULL != strstr(szBuffer, "404") )
		{
			throw Hir_404;
		}

		while( true )
		{
			bRet = InternetReadFile(m_hRequest, szBuffer, READ_BUFFER_SIZE, &dwReadSize);
			if ( !bRet || (0 == dwReadSize) )
			{
				break;
			}
			szBuffer[dwReadSize]='\0';
			strRet.append(U2G(szBuffer));
		}
	}
	catch(HttpInterfaceError error)
	{
		m_error = error;
	}
	return static_cast<string>(strRet);
}


// 解析URL地址 [3/14/2017/shike]
void CWininetHttp::ParseURLWeb( std::string strUrl, std::string& strHostName, std::string& strPageName, WORD& sPort)
{
	sPort = 80;
	string strTemp(strUrl);
	std::size_t nPos = strTemp.find("http://");
	if (nPos != std::string::npos)
	{
		strTemp = strTemp.substr(nPos + 7, strTemp.size() - nPos - 7);
	}

	nPos = strTemp.find('/');
	if ( nPos == std::string::npos )    //没有找到
	{
		strHostName = strTemp;
	}
	else
	{
		strHostName = strTemp.substr(0, nPos);
	}

	std::size_t nPos1 = strHostName.find(':');
	if ( nPos1 != std::string::npos )
	{
		std::string strPort = strTemp.substr(nPos1 + 1, strHostName.size() - nPos1 - 1);
		strHostName = strHostName.substr(0, nPos1);
		sPort = (WORD)atoi(strPort.c_str());
	}
	if ( nPos == std::string::npos )
	{
		return ;
	}
	strPageName = strTemp.substr(nPos, strTemp.size() - nPos);
}

// 关闭句柄 [3/14/2017/shike]
void CWininetHttp::Release()
{
	ReleaseHandle(m_hRequest); 
	ReleaseHandle(m_hConnect); 
	ReleaseHandle(m_hSession);
}

// 释放句柄 [3/14/2017/shike]
void CWininetHttp::ReleaseHandle( HINTERNET& hInternet )
{
	if (hInternet) 
	{ 
		InternetCloseHandle(hInternet); 
		hInternet = NULL; 
	}
}

// UTF-8转为GBK2312 [3/14/2017/shike]
char* CWininetHttp::UtfToGbk(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}

