#include"stdafx.h"
#include <fstream>
#include "FtpSocket.h"

FtpSocket::FtpSocket()
{
	isConnect = FALSE;
}

FtpSocket::~FtpSocket()
{
	isConnect = FALSE;
	if (socketMsg.IsConnect())
		socketMsg.CloseCon();
	if (socketData.IsConnect())
		socketData.CloseCon();
}

//建立连接
int FtpSocket::Connect(int MsgPort, const CStringA IPAddress, const CStringA UserName, const CStringA Password)
{
	//Establishing connection
	memset(this->IPAddress, '\0', 20);
	strcpy_s(this->IPAddress, IPAddress.GetString());
	if (!socketMsg.Connect(MsgPort, this->IPAddress))// this->IPAddress))
		return -1;
	this->MsgPort = MsgPort;
	char* receive = new char[1024];
	receive = socketMsg.RecvMsg(BUFFSIZE);
	char i[3];
	memcpy(i, receive, 3);

	if (atoi(i) != 220)
		return -2;//端口错误
	//登陆
	socketMsg.SendMsg("PASV\r\n\0");
	receive = socketMsg.RecvMsg(BUFFSIZE);
	memcpy(i, receive, 3);
	if (atoi(i) != 530)
		return -2;
	socketMsg.SendMsg("USER " + UserName + "\r\n\0");
	receive = socketMsg.RecvMsg(BUFFSIZE);
	memcpy(i, receive, 3);
	if (atoi(i) != 331)
		return -3;
	socketMsg.SendMsg("PASS " + Password + "\r\n\0");
	receive = socketMsg.RecvMsg(BUFFSIZE);
	memcpy(i, receive, 3);
	if (atoi(i) != 230)
		return 0;//密码错误
	isConnect = TRUE;
	return 1;
}

boolean FtpSocket::IsConnect()
{
	socketMsg.SendMsg("NOOP\r\n\0");
	CStringA receive = socketMsg.RecvMsg(BUFFSIZE);
	char i[3];
	memcpy(i, receive, 3);
	if (atoi(i) == 200)
		return TRUE;
	return FALSE;
}

//得到当前目录下的文件列表
CStringA FtpSocket::GetFileDirectory()
{
	PASV();
	socketMsg.SendMsg("LIST\r\n\0");
	char* receive = new char[1024];
	receive = socketMsg.RecvMsg(BUFFSIZE);
	char i[3];
	memcpy(i, receive, 3);
	if (atoi(i) != 125)
		return "";
	CStringA FileDirectory = (CStringA)socketData.RecvMsg(BUFFSIZE);
	socketMsg.RecvMsg(BUFFSIZE);
	return FileDirectory;
}

//上传文件
void FtpSocket::UpConnect(const CStringA LocalFile, const CStringA FtpFile)
{
	PASV();
	socketMsg.SendMsg("STOR " + FtpFile + "\r\n\0");
	CStringA a=socketMsg.RecvMsg(BUFFSIZE);
	FileUp(LocalFile);
	socketMsg.RecvMsg(BUFFSIZE);
}

void FtpSocket::FileUp(const CStringA LocalFile)
{
	int FILEUPBUFFSIZE = 1024;
	char* buffer = new char[FILEUPBUFFSIZE];
	std::ifstream in;
	//打开文件

	in.open(LocalFile,std::ios::binary);
	memset(buffer, 0, FILEUPBUFFSIZE);
	in.seekg(0, std::ios_base::end);
	int sp = in.tellg();//文件大小
	int total_size = 0;
	while (sp > 0) {
		in.clear();
		in.seekg(total_size, std::ios_base::beg);
		memset(buffer, 0, FILEUPBUFFSIZE);
		in.read(buffer, FILEUPBUFFSIZE);
		int size = sp < FILEUPBUFFSIZE ? sp : FILEUPBUFFSIZE;
		total_size += size;
		socketData.SendMsg(buffer, size);
		sp -= size;
	}
	in.close();
	socketData.CloseCon();

}

//下载文件
boolean FtpSocket::DownloadConnect(const CStringA strRemoteFile, const CStringA Name)
{

	socketMsg.SendMsg("SIZE " + Name + "\r\n\0");
	int size=-1;
	char* buffer = new char[1024];
	buffer = socketMsg.RecvMsg(BUFFSIZE);
	sscanf_s(buffer, "213 %d\r\n", &size);
	memset(buffer, 0, 1024);
	if (size < 0)
		return FALSE;
	PASV();
	socketMsg.SendMsg("RETR " + Name + "\r\n\0");
	socketMsg.RecvMsg(BUFFSIZE);
	FileDownload(strRemoteFile, size);
	socketMsg.RecvMsg(BUFFSIZE);
	return TRUE;
}

void FtpSocket::FileDownload(const CStringA FileURL, const int filesize)
{
	int FILEDOWNLOADBUFFSIZE = 1024;

	int size = filesize;
	std::ofstream out;
	out.open(FileURL, std::ios::binary);

	if (!out.is_open())
		return;
	char* sendbuffer = new char[FILEDOWNLOADBUFFSIZE];
	while (size > 0) {
		memset(sendbuffer, '\0', FILEDOWNLOADBUFFSIZE);
		sendbuffer = socketData.RecvMsg(BUFFSIZE);
		int s = size < FILEDOWNLOADBUFFSIZE ? size : FILEDOWNLOADBUFFSIZE;
		if (strcmp(sendbuffer, "NAK") == 0) {
			out.close();
			return;
		}
		else {
			out.write(sendbuffer, s);
		}
		size = size - FILEDOWNLOADBUFFSIZE;
	}
	out.close();
}

//使用被动模式，并获得文件传输端口
void FtpSocket::PASV()
{
	int a1 = 0, a2 = 0, a3 = 0, a4 = 0, p1 = 0, p2 = 0;
	if (socketData.IsConnect())
		socketData.CloseCon();
	socketMsg.SendMsg("PASV\r\n\0");
	sscanf_s(socketMsg.RecvMsg(BUFFSIZE), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", &a1, &a2, &a3, &a4, &p1, &p2);
	DataPort = (p1 * 256) + p2;
	if (!socketData.Connect(DataPort, IPAddress))
		return;

}

//获得当前目录
CStringA FtpSocket::PWD()
{
	socketMsg.SendMsg("PWD\r\n\0");// , 6);
	char* buffer = socketMsg.RecvMsg(BUFFSIZE);
	char* path = new char[20];
	memset(path, '/0', 20);
	char* p;
	path = strtok_s(buffer, "\"", &p);
	path = strtok_s(NULL, "\"", &p);
	return (CStringA)path;
}

//更改当前目录
void FtpSocket::ChangeFileFolder(CStringA Folder)
{
	socketMsg.SendMsg("CWD " + Folder + "\r\n\0");
	socketMsg.RecvMsg(BUFFSIZE);
}

//新建文件夹
void FtpSocket::MKD(CStringA Folder)
{
	socketMsg.SendMsg("MKD " + Folder + "\r\n\0");
	socketMsg.RecvMsg(BUFFSIZE);
}

//重命名
void FtpSocket::ReName(CStringA oldName, CStringA newName)
{
	socketMsg.SendMsg("RNFR " + oldName + "\r\n\0");
	CStringA aaa=socketMsg.RecvMsg(BUFFSIZE);
	socketMsg.SendMsg("RNTO " + newName + "\r\n\0");
	aaa = socketMsg.RecvMsg(BUFFSIZE);
}

//删除目录
int FtpSocket::RMD(CStringA Folder)
{
	socketMsg.SendMsg("RMD " + Folder + "\r\n\0");
	char* receive = new char[1024];
	receive = socketMsg.RecvMsg(BUFFSIZE);
	char i[3];
	memcpy(i, receive, 3);
	if (atoi(i) != 250)
	{
		socketMsg.RecvMsg(BUFFSIZE);
		if (atoi(i) == 550)
			return 0;
		return -1;
	}
	else
		return 1;
}

//删除文件
int FtpSocket::DELE(CStringA Name)
{
	socketMsg.SendMsg("DELE " + Name + "\r\n\0");
	char* receive = new char[1024];
	receive = socketMsg.RecvMsg(BUFFSIZE);
	char i[3];
	memcpy(i, receive, 3);
	if (atoi(i) != 250)
	{
		socketMsg.RecvMsg(BUFFSIZE);
		return -1;
	}
	else
		return 1;
}

//退出
void FtpSocket::QUIT()
{
	socketMsg.SendMsg("QUIT\r\n\0");
	socketMsg.RecvMsg(BUFFSIZE);
}