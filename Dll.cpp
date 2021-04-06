#include "pch.h"
//#include "Common.h"
#include <fstream>
#pragma comment(lib, "Wininet.lib")
#include <tchar.h>
using namespace std;

CWininetHttp::CWininetHttp(void) :m_hSession(NULL), m_hConnect(NULL), m_hRequest(NULL)
{
}

CWininetHttp::~CWininetHttp(void)
{
    Release();
}

//  通过HTTP请求：Get或Post方式获取JSON信息
const string CWininetHttp::RequestJsonInfo(const string& lpUrl,
    HttpRequest type/* 请求方式：Hr_Get, Hr_Post */,
    string strHeader/* HTTPS请求头 */,
    string strPostData/* HTTPS请求数据Parmas */)
{
    string strRet = ""/* 储存HTTPS请求返回数据 */;
    try
    {
        if (lpUrl.empty())
        {
            throw Hir_ParamErr;
        }
        Release();
        m_hSession = InternetOpen(_T("Http-connect"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);    //局部

        if (NULL == m_hSession)
        {
            throw Hir_InitErr;
        }

        INTERNET_PORT port = INTERNET_DEFAULT_HTTP_PORT;
        string strHostName = "";
        string strPageName = "";

        ParseURLWeb(lpUrl, strHostName, strPageName, port);
        //   printf("lpUrl:%s,\nstrHostName:%s,\nstrPageName:%s,\nport:%d\n", lpUrl.c_str(), strHostName.c_str(), strPageName.c_str(), (int)port);

        m_hConnect = InternetConnectA(m_hSession, strHostName.c_str(), port, NULL, NULL, INTERNET_SERVICE_HTTP, NULL, NULL);

        if (NULL == m_hConnect)
        {
            cout << "connect error" << endl;
            throw Hir_ConnectErr;
        }

        string strRequestType;
        if (Hr_Get == type)
        {
            strRequestType = "GET";
        }
        else
        {
            strRequestType = "POST";
        }

        m_hRequest = HttpOpenRequestA(m_hConnect, strRequestType.c_str(), strPageName.c_str(), "HTTP/1.1", NULL, NULL, INTERNET_FLAG_RELOAD, NULL);
        if (NULL == m_hRequest)
        {
            cout << "init error" << endl;
            throw Hir_InitErr;
        }

        DWORD dwHeaderSize = (strHeader.empty()) ? 0 : strlen(strHeader.c_str());
        BOOL bRet = FALSE;
        if (Hr_Get == type)
        {
            bRet = HttpSendRequestA(m_hRequest, strHeader.c_str(), dwHeaderSize, NULL, 0);
            /*           cout << "strHostName :" << strHostName << endl;
                       cout << "strPageName :" << strPageName << endl;
                       cout << "header :" << strHeader.c_str() << endl;
                       cout << "data :" << strPostData.c_str() << endl;
                       cout << "dwHeaderSize :" << dwHeaderSize << endl;
                       cout << "bret :" << bRet << endl;*/
        }
        else
        {
            DWORD dwSize = (strPostData.empty()) ? 0 : strlen(strPostData.c_str());
            bRet = HttpSendRequestA(m_hRequest, strHeader.c_str(), dwHeaderSize, (LPVOID)strPostData.c_str(), dwSize);
        }
        if (!bRet)
        {
            cout << "send error" << GetLastError() << endl;
            throw Hir_SendErr;
        }

        char szBuffer[READ_BUFFER_SIZE + 1] = { 0 };
        DWORD dwReadSize = READ_BUFFER_SIZE;
        if (!HttpQueryInfo(m_hRequest, HTTP_QUERY_RAW_HEADERS, szBuffer, &dwReadSize, NULL))
        {
            cout << "request head error" << endl;
            throw Hir_QueryErr;
        }
        if (NULL != strstr(szBuffer, "404"))
        {
            cout << "404" << endl;
            throw Hir_404;
        }

        while (true)
        {
            bRet = InternetReadFile(m_hRequest, szBuffer, READ_BUFFER_SIZE, &dwReadSize);
            if (!bRet || (0 == dwReadSize))
            {
                break;
            }
            szBuffer[dwReadSize] = '\0';
            strRet.append(szBuffer);
        }
    }
    catch (HttpInterfaceError error)
    {
        m_error = error;
    }
    //   return std::move(strRet);
    return UtfToGbk(strRet.c_str());
}

// 解析URL地址
void CWininetHttp::ParseURLWeb(string strUrl, string& strHostName, string& strPageName, WORD& sPort)
{
    sPort = 80;
    string strTemp(strUrl);
    size_t nPos = strTemp.find("http://");
    if (nPos != string::npos)
    {
        strTemp = strTemp.substr(nPos + 7, strTemp.size() - nPos - 7);
    }

    nPos = strTemp.find('/');
    if (nPos == string::npos)    //没有找到
    {
        strHostName = strTemp;
    }
    else
    {
        strHostName = strTemp.substr(0, nPos);
    }

    size_t nPos1 = strHostName.find(':');
    if (nPos1 != string::npos)
    {
        string strPort = strTemp.substr(nPos1 + 1, strHostName.size() - nPos1 - 1);
        strHostName = strHostName.substr(0, nPos1);
        sPort = (WORD)atoi(strPort.c_str());
    }
    if (nPos == string::npos)
    {
        return;
    }
    strPageName = strTemp.substr(nPos, strTemp.size() - nPos);
}

// 关闭句柄
void CWininetHttp::Release()
{
    ReleaseHandle(m_hRequest);
    ReleaseHandle(m_hConnect);
    ReleaseHandle(m_hSession);
}

// 释放句柄
void CWininetHttp::ReleaseHandle(HINTERNET& hInternet)
{
    if (hInternet)
    {
        InternetCloseHandle(hInternet);
        hInternet = NULL;
    }
}

// UTF-8转为GBK2312
char* CWininetHttp::UtfToGbk(const char* utf8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return str;
}