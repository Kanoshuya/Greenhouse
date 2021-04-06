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

//���ӿ��ƽӿ���Ҫ��header
string header_c = "appid:16061207412271144\r\n"
"appKey:d8a9baa854dda89192d3f726ef3ded1a2477bb64e98e4b194edd15e062aac066\r\n"
"appsecret:5bccc7af4aa68013bdb8b1b9d7dcd053";

//����˫�̵���
string Durl = "iot.linkdotter.com:8097/api/service/public//third/ctr?&sg=F4052B2F00002EF4";
int switch_on[6];

//�ļ�����
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

//�ļ���ȡ
string Fread()
{
	system("cls");
	ifstream infile;
	infile.open("SenDataDesc.txt");   //���ļ����������ļ��������� 
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ�������� 

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

//��ȡ1�Ŵ���������
string GetSensor_01()
{
	string url = "capi.chiplinkdata.com/agr/iot/iotDeviceShadow/getDev?sn=LTF2052C2300002F23";
	string res = req.RequestJsonInfo(url.c_str(), Hr_Get, header, "");
	//	res = GetSenDataDesc(res);
	return res;
}

//��ȡ2�Ŵ�����
string GetSensor_02()
{
	string url = "capi.chiplinkdata.com/agr/iot/iotDeviceShadow/getDev?sn=LTF2052C2300002F25";
	string res = req.RequestJsonInfo(url.c_str(), Hr_Get, header, "");
	//	res = GetSenDataDesc(res);
	return res;
}

//��ȡģ������
string GetModel()
{
	string url = "capi.chiplinkdata.com/agr/iot/iotDeviceShadow/getDev?sn=LTF4052B2F00002EF4";
	string res = req.RequestJsonInfo(url.c_str(), Hr_Get, header, "");
	return res;
}

//������
int Roll_Open()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=0&cmd=2");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("����ɹ�") != string::npos)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//��������
int Roll_Close()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=0&cmd=3");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("����ɹ�") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//ֹͣ�����豸
int Roll_Stop()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=0&cmd=0");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("����ɹ�") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//���촰
int Window_Open()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=1&cmd=3");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("����ɹ�") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//�����촰
int Window_Close()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=1&cmd=2");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("����ɹ�") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//ֹͣ�촰
int Window_Stop()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0E&addr=1&cmd=0");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("����ɹ�") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//����
int Temp_Up()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0F&addr=0&cmd=1");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("����ɹ�") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//����
int Temp_Down()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0F&addr=0&cmd=3");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("����ɹ�") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//ֹͣ����װ��
int Temp_Shutdown()
{
	string url = Durl;
	url.append("&sn=25052B3100002F0F&addr=0&cmd=0");
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res << endl;
	if (res.find("����ɹ�") != -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//��⿪��״̬
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

//���͵��̵����豸�����ź�
string Control_Act(string sg, string sn, string addr, string cmd)
{
	string url = "iot.linkdotter.com:8097/api/service/public//third/ctr?";
	url.append("sg=" + sg + "&sn=" + sn + "&addr=" + addr + "&cmd=" + cmd);
	//	cout << cmd << endl;
	string res = req.RequestJsonInfo(url.c_str(), Hr_Post, header_c, "");
	//	cout << res;
	int head = res.find("����ɹ�");
	if (!(head == string::npos))
	{
		res = "����ͳɹ�!";
	}
	else
	{
		res = "�豸������!";
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

//��ȡ��������dataDesc����
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

	//����ѯ�����dataDesc�ֶβ��ָ��Ƶ��ַ�����
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

	//	Fsave(desc.append("\r\n , ��Դ��" + sign),"SenDataDesc.txt");

	return desc;
}

string GetT_Soil(int sensor)
{
	string res = GetSenDataDesc(sensor);
	int head = res.find("�����¶�");
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
	int head = res.find("����ʪ��");
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
	int head = res.find("����EC");
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
	int head = res.find("�����¶�");
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
	int head = res.find("����ʪ��");
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
	int head = res.find("����ǿ��");
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
	case 1:Dev_name = "\\\"dev_name\\\":\\\"����ǿ��\\\""; break;
	case 2:Dev_name = "\\\"dev_name\\\":\\\"�����¶�\\\""; break;
	case 3:Dev_name = "\\\"dev_name\\\":\\\"����ʪ��\\\""; break;
	case 4:Dev_name = "\\\"dev_name\\\":\\\"�����¶�\\\""; break;
	case 5:Dev_name = "\\\"dev_name\\\":\\\"����ʪ��\\\","; break;
	case 6:Dev_name = "\\\"dev_name\\\":\\\"����EC"; break;
	default:
		break;
	}
	Dev_name = OnlineCheck_Act(Dev_name, sensor);
	return Dev_name;
}