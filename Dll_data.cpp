#include "pch.h"
#include <fstream>
#include <tchar.h>
#include <string>
#include <cassert>

using namespace std;

CWininetHttp req;
//token
string header = "Content-type:json:charset=utf-8\r\n"
"X-Access-AppCode:tkeyJ0eXxA0xiOdJhbGcixdJIUzI1NiJ9xabfbjnxy20201123";

//连接控制接口需要的header
string header_c = "appid:16061207412271144\r\n"
"appKey:d8a9baa854dda89192d3f726ef3ded1a2477bb64e98e4b194edd15e062aac066\r\n"
"appsecret:5bccc7af4aa68013bdb8b1b9d7dcd053";

//控制双继电器
string Durl = "iot.linkdotter.com:8097/api/service/public//third/ctr?&sg=F4052B2F00002EF4";
int switch_on[6];

//文件保存
int Fsave(string data, string File_name)
{
	FILE* fp;
	fp = fopen(File_name.c_str(), "a");
	if (fp == NULL)
	{
		printf("File open error!\n");
		return 0;
	}
	for (int i = 0; i < data.length(); i++) {
		if (data[i] == '{');
		else if (data[i] == '}');
		else if (data[i] == '\\' || data[i] == '\"' || data[i] == ',')  fprintf(fp, " ");
		else	fprintf(fp, "%c", data[i]);
	}
	fprintf(fp, "\r\n");
	fclose(fp);
	return 1;
}

//文件读取
string Fread()
{
	system("cls");
	ifstream infile;
	infile.open("SenDataDesc.txt");   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

	string s, data;
	while (getline(infile, s))
	{
		data.append(s);
		data.append("\r\n");
		//	cout << s << endl;
	}
	infile.close();
	return data;
}

//读取1号传感器数据
string GetSensor_01()
{
	string url = "capi.chiplinkdata.com/agr/iot/iotDeviceShadow/getDev?sn=LTF2052C2300002F23";
	string res = req.RequestJsonInfo(url.c_str(), Hr_Get, header, "");
	//	res = GetSenDataDesc(res);
	return res;
}

//读取2号传感器
string GetSensor_02()
{
	string url = "capi.chiplinkdata.com/agr/iot/iotDeviceShadow/getDev?sn=LTF2052C2300002F25";
	string res = req.RequestJsonInfo(url.c_str(), Hr_Get, header, "");
	//	res = GetSenDataDesc(res);
	return res;
}

//读取模型数据
string GetModel()
{
	string url = "capi.chiplinkdata.com/agr/iot/iotDeviceShadow/getDev?sn=LTF4052B2F00002EF4";
	string res = req.RequestJsonInfo(url.c_str(), Hr_Get, header, "");
	return res;
}

//打开遮阳
int Roll_Open()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=0&cmd=2");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("请求成功") != string::npos)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//收起遮阳
int Roll_Close()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=0&cmd=3");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("请求成功") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//停止遮阳设备
int Roll_Stop()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=0&cmd=0");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("请求成功") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//打开天窗
int Window_Open()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=1&cmd=3");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("请求成功") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//收起天窗
int Window_Close()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=1&cmd=2");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("请求成功") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//停止天窗
int Window_Stop()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=1&cmd=0");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("请求成功") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//升温
int Temp_Up()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0F&addr=0&cmd=1");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("请求成功") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//降温
int Temp_Down()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0F&addr=0&cmd=3");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("请求成功") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//停止冷热装置
int Temp_Shutdown()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0F&addr=0&cmd=0");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("请求成功") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//检测开关状态
string Switch_Check(int cmd)
{
	//	cout << "Snum " << Snum << " now is " << switch_on[Snum] << endl;
	if (cmd == 0)
	{
		return "0";
	}
	else
	{
		return "1";
	}
}

//发送单继电器设备控制信号
string Control_Act(string sg, string sn, string addr, string cmd)
{
	string url = "iot.linkdotter.com:8097/api/service/public//third/ctr?";
	url.append("sg=" + sg + "&sn=" + sn + "&addr=" + addr + "&cmd=" + cmd);
	//	cout << cmd << endl;
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res;
	int head = res.find("请求成功");
	if (!(head == string::npos))
	{
		res = "命令发送成功!";
	}
	else
	{
		res = "设备不在线!";
	}
	return res;
}

string Control(int choice, int cmd)
{
	string sg, sn, addr, cmds;
	switch (choice)
	{
	case 1:sg = "F4052B2F00002EF4"; sn = "26052B3200002F12"; addr = "0"; cmds = Switch_Check(cmd); break;
	case 2:sg = "F4052B2F00002EF4"; sn = "26052B3200002F12"; addr = "1"; cmds = Switch_Check(cmd); break;
	case 3:sg = "F4052B2F00002EF4"; sn = "26052B3200002F12"; addr = "2"; cmds = Switch_Check(cmd); break;
	case 4:sg = "F4052B2F00002EF4"; sn = "26052B3200002F11"; addr = "0"; cmds = Switch_Check(cmd); break;
	case 5:sg = "F4052B2F00002EF4"; sn = "26052B3200002F11"; addr = "1"; cmds = Switch_Check(cmd); break;
	case 6:sg = "F4052B2F00002EF4"; sn = "26052B3200002F11"; addr = "2"; cmds = Switch_Check(cmd); break;
	default:
		break;
	}
	string msg = Control_Act(sg, sn, addr, cmds);
	return msg;
}

//获取传感器的dataDesc内容
string GetSenDataDesc(int sensor)
{
	string data, sign;
	switch (sensor)
	{
	case 1:data = GetSensor_01(); sign = " Sensor01"; break;
	case 2:data = GetSensor_02(); sign = " Sensor02"; break;
	default:
		break;
	}

	//将查询结果的dataDesc字段部分复制到字符串中
	string desc = "dataDesc";
	int flag = 0, head = 0;
	head = data.find(desc);
	if (head == string::npos)
	{
		return "DataDesc find Error!";
	}
	flag = data.rfind("updateD");
	if (flag == string::npos)
	{
		return "UpdateD find Error!";
	}
	desc.assign(data, head + 11, flag - head - 13);

	//	Fsave(desc.append("\r\n , 来源：" + sign),"SenDataDesc.txt");

	return desc;
}

string GetT_Soil(int sensor)
{
	string res = GetSenDataDesc(sensor);
	int head = res.find("土壤温度");
	if (head == string::npos)
	{
		return "Looking for keyword Error!";
	}
	int flag = res.find(",", head);
	if (!(head == string::npos))
	{
		res = res.substr(head, flag - head);
	}
	return res;
}

string GetH_Soil(int sensor)
{
	string res = GetSenDataDesc(sensor);
	int head = res.find("土壤湿度");
	if (head == string::npos)
	{
		return "Looking for keyword Error!!";
	}
	int flag = res.find(",", head);
	if (!(head == string::npos))
	{
		res = res.substr(head, flag - head);
	}
	return res;
}

string GetEc_Soil(int sensor)
{
	string res = GetSenDataDesc(sensor);
	int head = res.find("土壤EC");
	if (head == string::npos)
	{
		return "Looking for keyword Error!";
	}
	int flag = res.find("\"", head);
	if (!(head == string::npos))
	{
		res = res.substr(head, flag - head);
	}
	return res;
}

string GetT_Air(int sensor)
{
	string res = GetSenDataDesc(sensor);
	int head = res.find("空气温度");
	if (head == string::npos)
	{
		return "Looking for keyword Error!";
	}
	int flag = res.find(",", head);
	if (!(head == string::npos))
	{
		res = res.substr(head, flag - head);
	}
	return res;
}

string GetH_Air(int sensor)
{
	string res = GetSenDataDesc(sensor);
	int head = res.find("空气湿度");
	if (head == string::npos)
	{
		return "Looking for keyword Error!";
	}
	int flag = res.find(",", head);
	if (!(head == string::npos))
	{
		res = res.substr(head, flag - head);
	}
	return res;
}

string GetS_Sun(int sensor)
{
	string res = GetSenDataDesc(sensor);
	int head = res.find("光照强度");
	if (head == string::npos)
	{
		return "Looking for keyword Error!";
	}
	int flag = res.find(",", head);
	if (!(head == string::npos))
	{
		res = res.substr(head, flag - head);
	}
	return res;
}

string OnlineCheck_Act(string Dev_name, int sensor)
{
	int head, flag;
	string data, sign, newStr;
	switch (sensor)
	{
	case 1:data = GetSensor_01(), sign = "2F23\\\""; break;
	case 2:data = GetSensor_02(), sign = "2F25\\\""; break;
	default:
		break;
	}
	//	cout << data << endl;
	head = data.find(Dev_name);
	//	cout << head << endl;
	//	system("pause");
	if (head == string::npos)
	{
		return "Find Error!";
	}
	newStr.assign(data, head, 1000);
	flag = newStr.find(sign) + head;
	if (flag == string::npos)
	{
		return "Find Error!";
	}
	newStr.assign(data, head, flag - head + 6);
	return newStr;
}

string OnlineCheck(int sensor, int Dev_num)
{
	string Dev_name;
	switch (Dev_num)
	{
	case 1:Dev_name = "\\\"dev_name\\\":\\\"光照强度\\\""; break;
	case 2:Dev_name = "\\\"dev_name\\\":\\\"空气温度\\\""; break;
	case 3:Dev_name = "\\\"dev_name\\\":\\\"空气湿度\\\""; break;
	case 4:Dev_name = "\\\"dev_name\\\":\\\"土壤温度\\\""; break;
	case 5:Dev_name = "\\\"dev_name\\\":\\\"土壤湿度\\\","; break;
	case 6:Dev_name = "\\\"dev_name\\\":\\\"土壤EC"; break;
	default:
		break;
	}
	Dev_name = OnlineCheck_Act(Dev_name, sensor);
	return Dev_name;
}