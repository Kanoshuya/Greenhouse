// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include <iostream>
#include <windows.h>
#include <wininet.h>

using namespace std;

#endif //PCH_H

//每次读取的字节数
#define READ_BUFFER_SIZE        4096

enum HttpInterfaceError
{
    Hir_Success = 0,        //成功
    Hir_InitErr,            //初始化失败
    Hir_ConnectErr,            //连接HTTP服务器失败
    Hir_SendErr,            //发送请求失败
    Hir_QueryErr,            //查询HTTP请求头失败
    Hir_404,                //页面不存在
    Hir_IllegalUrl,            //无效的URL
    Hir_CreateFileErr,        //创建文件失败
    Hir_DownloadErr,        //下载失败
    Hir_QueryIPErr,            //获取域名对应的地址失败
    Hir_SocketErr,            //套接字错误
    Hir_UserCancel,            //用户取消下载
    Hir_BufferErr,            //文件太大，缓冲区不足
    Hir_HeaderErr,            //HTTP请求头错误
    Hir_ParamErr,            //参数错误，空指针，空字符
    Hir_UnknowErr,
};
enum HttpRequest
{
    Hr_Get,
    Hr_Post
};
class CWininetHttp
{
public:
    CWininetHttp(void);
    ~CWininetHttp(void);

public:
    //  通过HTTP请求：Get或Post方式获取JSON信息 [3/14/2017/shike]
    const std::string RequestJsonInfo(const std::string& strUrl,
        HttpRequest type = Hr_Get,
        std::string lpHeader = "",
        std::string lpPostData = "");
protected:
    // 解析卡口Json数据 [3/14/2017/shike]
    void ParseJsonInfo(const std::string& strJsonInfo);

    // 关闭句柄 [3/14/2017/shike]
    void Release();

    // 释放句柄 [3/14/2017/shike]
    void ReleaseHandle(HINTERNET& hInternet);

    // 解析URL地址 [3/14/2017/shike]
    void ParseURLWeb(std::string strUrl, std::string& strHostName, std::string& strPageName, WORD& sPort);

    // UTF-8转为GBK2312 [3/14/2017/shike]
    char* UtfToGbk(const char* utf8);

private:
    HINTERNET            m_hSession;
    HINTERNET            m_hConnect;
    HINTERNET            m_hRequest;
    HttpInterfaceError    m_error;
};
__declspec(dllexport) string GetSensor_01();
__declspec(dllexport) string GetSensor_01();              //获取1号传感器的数据
__declspec(dllexport) string GetSensor_02();              //获取2号传感器的数据
__declspec(dllexport) string GetModel();                  //获取模型数据

__declspec(dllexport) string OnlineCheck(int sensor, int Dev_num);               //查看设备状态
    /*
        sensor:
            1 - 传感器1
            2 - 传感器2
        Dev_num:
            1 - 光照强度
            2 - 空气温度
            3 - 空气湿度
            4 - 土壤温度
            5 - 土壤湿度
            6 - 土壤EC
    */

__declspec(dllexport) string GetT_Soil(int sensor);                 //土壤温度
__declspec(dllexport) string GetH_Soil(int sensor);                 //土壤湿度
__declspec(dllexport) string GetEc_Soil(int sensor);                //土壤EC
__declspec(dllexport) string GetT_Air(int sensor);                  //空气温度
__declspec(dllexport) string GetH_Air(int sensor);                  //空气湿度
__declspec(dllexport) string GetS_Sun(int sensor);                  //光照强度
__declspec(dllexport) string GetSenDataDesc(int sensor);            //获取传感器参数
    /*
        sensor:
            1 - 传感器1
            2 - 传感器2
    */

__declspec(dllexport) string Control(int choice, int cmd);                   //单继电器设备控制
    /*
        choice:
            1 - 水循环
            2 - 水泵
            3 - 通风
            4 - 补光
            5 - 模拟水
        cmd:
            1 - 打开
            0 - 关闭
    */

__declspec(dllexport) int Roll_Open();                    //打开遮阳设备
__declspec(dllexport) int Roll_Close();                   //收起遮阳设备
__declspec(dllexport) int Roll_Stop();                    //停止

__declspec(dllexport) int Window_Open();                  //打开天窗
__declspec(dllexport) int Window_Close();                 //关闭天窗
__declspec(dllexport) int Window_Stop();                  //停止

__declspec(dllexport) int Temp_Up();                      //升温
__declspec(dllexport) int Temp_Down();                    //降温
__declspec(dllexport) int Temp_Shutdown();                //停止冷热装置



__declspec(dllexport) string Fread();                       //读取文件内保存内容
