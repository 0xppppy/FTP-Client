#pragma once
#include "Socket.h"
#include <afxinet.h>
class FtpSocket {
private:
	Socket socketMsg, socketData;
	bool isConnect;
	char IPAddress[20];
	int MsgPort;
	int DataPort;
	int BUFFSIZE = 1024;

	void FileDownload(const CStringA FileURL, const int filesize);
	void FileUp(const CStringA LocalFile);
	void PASV();

public:
	FtpSocket();
	~FtpSocket();
	int Connect(const int MsgPort, const CStringA IPAddress, const CStringA UserName, const CStringA Password);
	boolean IsConnect();
	boolean DownloadConnect(const CStringA strRemoteFile, const CStringA Name);
	void ChangeFileFolder(const CStringA Folder);
	void MKD(CStringA Folder);
	void ReName(CStringA oldName, CStringA newName);
	int RMD(CStringA Folder);
	int DELE(CStringA Name);
	void QUIT();
	CStringA GetFileDirectory();
	void UpConnect(const CStringA LocalFile, const CStringA FtpFile);
	CStringA PWD();

};