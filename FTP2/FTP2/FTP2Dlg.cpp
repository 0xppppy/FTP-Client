
// FTP2Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FTP2.h"
#include "FTP2Dlg.h"
#include "afxdialogex.h"

#include "FtpSocket.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CFTP2Dlg 对话框

CFTP2Dlg::CFTP2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FTP2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFTP2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFTP2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(CONNECT, &CFTP2Dlg::OnBnClickedConnect)
	ON_BN_CLICKED(UP, &CFTP2Dlg::OnBnClickedUp)
	ON_BN_CLICKED(DOWNLOAD, &CFTP2Dlg::OnBnClickedDownload)
	ON_BN_CLICKED(IDC_BUTTON2, &CFTP2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFTP2Dlg::OnBnClickedButton3)
	ON_NOTIFY(LVN_ENDLABELEDIT, LIST, &CFTP2Dlg::OnLvnEndlabeleditList)
	ON_NOTIFY(NM_DBLCLK, LIST, &CFTP2Dlg::OnNMDblclkList)
	ON_BN_CLICKED(IDC_BUTTON4, &CFTP2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CFTP2Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CFTP2Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &CFTP2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON8, &CFTP2Dlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CFTP2Dlg 消息处理程序
BOOL CFTP2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//----------------------------------------------------------------------------------------------
	init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFTP2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{

	CDialogEx::OnSysCommand(nID, lParam);

}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFTP2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFTP2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//
CListCtrl* ListEdit = NULL;
CEdit* FtpPath = NULL;
FtpSocket* Ftp;

void CFTP2Dlg::init()
{

	Ftp = new FtpSocket();

	//初始化ListEdit
	ListEdit = (CListCtrl*)GetDlgItem(LIST);
	ListEdit->InsertColumn(0, _T("NAME"), LVCFMT_LEFT, 200);//插入列
	ListEdit->InsertColumn(1, _T("SIZE"), LVCFMT_LEFT, 100);
	ListEdit->InsertColumn(2, _T("KIND"), LVCFMT_LEFT, 140);
	ListEdit->InsertColumn(3, _T("TIME OF CHANGE"), LVCFMT_LEFT, 230);

	FtpPath = (CEdit*)GetDlgItem(PATH);

	CEdit* pBoxOne = (CEdit*)GetDlgItem(IPCONTROL);
	pBoxOne->SetWindowTextW(_T("127.0.0.1"));
	pBoxOne = (CEdit*)GetDlgItem(PORT);
	pBoxOne->SetWindowTextW(_T("21"));
	pBoxOne = (CEdit*)GetDlgItem(NAME);
	pBoxOne->SetWindowTextW(_T("2016212060"));
	pBoxOne = (CEdit*)GetDlgItem(PASSWORD);
	pBoxOne->SetWindowTextW(_T("2060"));

	CButton* Button = (CButton*)GetDlgItem(IDC_BUTTON2);
	Button->EnableWindow(0);
	Button = (CButton*)GetDlgItem(IDC_BUTTON3);
	Button->EnableWindow(0);
	Button = (CButton*)GetDlgItem(IDC_BUTTON4);
	Button->EnableWindow(0);
	Button = (CButton*)GetDlgItem(IDC_BUTTON5);
	Button->EnableWindow(0);
	Button = (CButton*)GetDlgItem(IDC_BUTTON6);
	Button->EnableWindow(0);
	Button = (CButton*)GetDlgItem(IDC_BUTTON7);
	Button->EnableWindow(0);
	Button = (CButton*)GetDlgItem(IDC_BUTTON8);
	Button->EnableWindow(0);
	Button = (CButton*)GetDlgItem(UP);
	Button->EnableWindow(0);
	Button = (CButton*)GetDlgItem(DOWNLOAD);
	Button->EnableWindow(0);
	Button = (CButton*)GetDlgItem(CONNECT);
	Button->EnableWindow(1);

	CEdit* Edit = (CEdit*)GetDlgItem(IPCONTROL);
	Edit->EnableWindow(1);
	Edit = (CEdit*)GetDlgItem(NAME);
	Edit->EnableWindow(1);
	Edit = (CEdit*)GetDlgItem(PASSWORD);
	Edit->EnableWindow(1);
	Edit = (CEdit*)GetDlgItem(PORT);
	Edit->EnableWindow(1);
}

//连接按钮
void CFTP2Dlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码

	CEdit* Edit = (CEdit*)GetDlgItem(IPCONTROL);
	CStringW a;
	CStringA IPAddress;
	Edit->GetWindowText(a);
	IPAddress = a;

	Edit = (CEdit*)GetDlgItem(NAME);
	CStringA UserName;
	Edit->GetWindowText(a);
	UserName = a;
		
	Edit = (CEdit*)GetDlgItem(PASSWORD);
	CStringA PassWord;
	Edit->GetWindowText(a);
	PassWord = a;

	Edit = (CEdit*)GetDlgItem(PORT);
	CStringA Port;
	Edit->GetWindowText(a);
	Port = a;

	int i = Ftp->Connect(atoi(Port), IPAddress, UserName, PassWord);
	if(i==-1)
		AfxMessageBox(_T("IP或端口出错"));
	else	if (i == 0)
		AfxMessageBox(_T("密码出错"));
	else if ( i == 1)
	{
		AfxMessageBox(_T("连接成功"));

		CButton* Button = (CButton*)GetDlgItem(CONNECT);
		Button->EnableWindow(0);

		Button = (CButton*)GetDlgItem(IDC_BUTTON2);
		Button->EnableWindow(1);
		Button = (CButton*)GetDlgItem(IDC_BUTTON3);
		Button->EnableWindow(1);
		Button = (CButton*)GetDlgItem(IDC_BUTTON4);
		Button->EnableWindow(1);
		Button = (CButton*)GetDlgItem(IDC_BUTTON5);
		Button->EnableWindow(1);
		Button = (CButton*)GetDlgItem(IDC_BUTTON6);
		Button->EnableWindow(1);
		Button = (CButton*)GetDlgItem(IDC_BUTTON7);
		Button->EnableWindow(1);
		Button = (CButton*)GetDlgItem(IDC_BUTTON8);
		Button->EnableWindow(1);
		Button = (CButton*)GetDlgItem(UP);
		Button->EnableWindow(1);
		Button = (CButton*)GetDlgItem(DOWNLOAD);
		Button->EnableWindow(1);

		Edit = (CEdit*)GetDlgItem(IPCONTROL);
		Edit->EnableWindow(0);
		Edit = (CEdit*)GetDlgItem(NAME);
		Edit->EnableWindow(0);
		Edit = (CEdit*)GetDlgItem(PASSWORD);
		Edit->EnableWindow(0);
		Edit = (CEdit*)GetDlgItem(PORT);
		Edit->EnableWindow(0);


		ReflashFileFind();
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}

//刷新文件列表
void CFTP2Dlg::ReflashFileFind()
{
	if (Ftp->IsConnect())
	{
		ListEdit->DeleteAllItems();
		CString FileDirectory = (CString)Ftp->GetFileDirectory();
		CString FileInformation;

		int i = 0;
		FileDirectory.Replace(_T("\r\n"), _T("\n"));
		while (TRUE)
		{
			FileInformation != _T("");
			AfxExtractSubString(FileInformation, FileDirectory, i);
			i++;
			if (FileInformation == _T(""))
				break;
			int i = FileInformation.Find(_T("  "));
			while (FileInformation.Find(_T("  ")) != -1)
				FileInformation.Replace(_T("  "), _T(" "));//第一个参数是空格，第二个参数是空字符串。
			CString a;
			AfxExtractSubString(a, FileInformation, 0, ' ');
			CString time;
			AfxExtractSubString(time, FileInformation, 1, ' ');
			time = a + " " + time;
			AfxExtractSubString(a, FileInformation, 2, ' ');
			CString kind = _T("");
			CStringA size = "";
			CString name;
			if (a.Find(_T("<")) != -1)
				kind = a;
			else
				size = a;
			a = _T("");
			AfxExtractSubString(a, FileInformation, 3, ' ');
			int n = 3;
			while (a != _T(""))
			{
				name = name + " " + a;
				n = n + 1;
				AfxExtractSubString(a, FileInformation, n, ' ');
			}
			int nRow = ListEdit->InsertItem(0, name.Trim());//插入行
			int intsize = atoi(size.Trim());
			CStringW size2=_T("");
			if (intsize != 0)
			{
				size2.Format(_T("%d"), intsize);
				if (intsize > 1024)
				{
					intsize = intsize / 1024;
					size2.Format(_T("%d"), intsize+1);
					size2 = size2 + _T("KB");
				}
				if (intsize > 1024)
				{
					intsize = intsize / 1024;
					size2.Format(_T("%d"), intsize + 1);
					size2 = size2 + _T("MB");
				}
				if (intsize > 1024)
				{
					intsize = intsize / 1024;
					size2.Format(_T("%d"), intsize + 1);
					size2 = size2 + _T("GB");
				}
			}
			ListEdit->SetItemText(nRow, 1, size2);
			ListEdit->SetItemText(nRow, 2, kind.Trim());
			ListEdit->SetItemText(nRow, 3, time.Trim());
		}
		CStringW path;
		path = _T("当前目录：") + (CStringW)Ftp->PWD();
		FtpPath->SetWindowText(path);
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}

//上传文件按钮
void CFTP2Dlg::OnBnClickedUp()
{
	if (Ftp->IsConnect())
	{
		// TODO: 在此添加控件通知处理程序代码
		CStringA Path = "";
		CStringA FileName = "";
		CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY,
			_T("All Files (*.*)|*.*|"));

		if (dlgFile.DoModal())
		{
			FileName = dlgFile.GetFileName();
			Path = dlgFile.GetPathName();

			if (FileName != "" && Path != "")
				if (Ftp == NULL)
					AfxMessageBox(_T("No Connection"));
				else
				{
					Ftp->UpConnect(Path, FileName);
					AfxMessageBox(_T("上传完成"));
				}
		}
		ReflashFileFind();
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}

//下载按钮
void CFTP2Dlg::OnBnClickedDownload()
{
	if (Ftp->IsConnect())
	{

		// TODO: 在此添加控件通知处理程序代码
		TCHAR szBuffer[MAX_PATH] = { 0 };
		BROWSEINFO bi;
		ZeroMemory(&bi, sizeof(BROWSEINFO));
		bi.hwndOwner = NULL;
		bi.pszDisplayName = szBuffer;
		bi.lpszTitle = _T("选择下载目录:");
		bi.ulFlags = BIF_RETURNFSANCESTORS;
		LPITEMIDLIST idl = SHBrowseForFolder(&bi);
		if (NULL != idl)
		{
			CStringA Path = "";
			CStringA FileName = "";
			SHGetPathFromIDList(idl, szBuffer);
			Path = szBuffer;

			POSITION pos = ListEdit->GetFirstSelectedItemPosition();
			while (pos != NULL) //如果可能选中多个
				if (pos != NULL) //这样就算选择多个也只取第一个
				{
					int nItem = ListEdit->GetNextSelectedItem(pos);
					FileName = ListEdit->GetItemText(nItem, 0);
					if(Ftp->DownloadConnect(Path + "\\" + FileName, FileName))
						AfxMessageBox(_T("下载完成"));
					else
						AfxMessageBox(_T("下载失败"));
				}
		}
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}

//打开文件夹
void CFTP2Dlg::OnBnClickedButton2()
{
	if (Ftp->IsConnect())
	{
		POSITION pos = ListEdit->GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nItem = ListEdit->GetNextSelectedItem(pos);
			CStringA FileName;
			FileName = ListEdit->GetItemText(nItem, 0);
			CString dir = ListEdit->GetItemText(nItem, 2);
			if (dir != _T("<DIR>"))
			{
				AfxMessageBox(_T("不是一个目录"));
				return;
			}
			Ftp->ChangeFileFolder(FileName);
			ReflashFileFind();
		}
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}

//返回上级目录
void CFTP2Dlg::OnBnClickedButton3()
{
	if (Ftp->IsConnect())
	{
		Ftp->ChangeFileFolder("..");
		ReflashFileFind();
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}


//编辑结束
void CFTP2Dlg::OnLvnEndlabeleditList(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (Ftp->IsConnect())
	{
		NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
		// TODO: 在此添加控件通知处理程序代码
		*pResult = 0;

		CStringA oldName, newName;
		newName = pDispInfo->item.pszText;
		int tIndex = pDispInfo->item.iItem;
		ListEdit->SetFocus();

		if ((!newName.IsEmpty()) && tIndex >= 0)
		{
			oldName = ListEdit->GetItemText(tIndex, 0);

			Ftp->ReName(oldName, newName);
		}
		ReflashFileFind();
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}

//双击
void CFTP2Dlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (Ftp->IsConnect())
	{

		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		// TODO: 在此添加控件通知处理程序代码
		*pResult = 0;
		OnBnClickedButton2();
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}

//新建文件夹
void CFTP2Dlg::OnBnClickedButton4()
{
	if (Ftp->IsConnect())
	{
		ReflashFileFind();
		CStringA FileName;
		CStringA Name = "new folder";
		int num = 0;
		int n = 1;
		FileName = ListEdit->GetItemText(0, 0);
		boolean flag = false;
		while (true) {
			while (FileName != "")
			{
				FileName = ListEdit->GetItemText(n, 0);
				if (Name == FileName)
				{
					num++;
					CStringA str;
					str.Format("%d", num);
					Name = "new folder " + str;
					flag = false;
					break;
				}
				n++;
			}
			if (flag)
				break;
			flag = true;
		}
		Ftp->MKD(Name);

		int nRow = ListEdit->InsertItem(0, (CString)Name);//插入行
		ListEdit->SetItemText(nRow, 2, _T("<DIR>"));

		ListEdit->SetItemState(nRow, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
		ListEdit->SetSelectionMark(nRow);

		OnBnClickedButton5();

		//ReflashFileFind();
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}

//删除按钮
void CFTP2Dlg::OnBnClickedButton6()
{
	if (Ftp->IsConnect())
	{

		// TODO: 在此添加控件通知处理程序代码
		POSITION pos = ListEdit->GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nItem = ListEdit->GetNextSelectedItem(pos);
			CStringA FileName;
			FileName = ListEdit->GetItemText(nItem, 0);
			CString dir = ListEdit->GetItemText(nItem, 2);
			if (dir == _T("<DIR>"))
			{
				int i = Ftp->RMD(FileName);
				if (i == 0)
					AfxMessageBox(_T("文件夹不为空"));
				if (i == -1)
					AfxMessageBox(_T("失败，刷新后重试"));
			}
			else
			{
				int i = Ftp->DELE(FileName);
				if (i == -1)
					AfxMessageBox(_T("失败，刷新后重试"));
			}
			ReflashFileFind();
		}
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}

//刷新按钮
void CFTP2Dlg::OnBnClickedButton7()
{
	if (Ftp->IsConnect())
	{
		// TODO: 在此添加控件通知处理程序代码
		ReflashFileFind();
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}

//重命名
void CFTP2Dlg::OnBnClickedButton5()
{
	if (Ftp->IsConnect())
	{
		// TODO: 在此添加控件通知处理程序代码
		POSITION pos = ListEdit->GetFirstSelectedItemPosition();
		int tIndex = ListEdit->GetNextSelectedItem(pos);

		if (tIndex >= 0)
		{
			ListEdit->SetFocus();
			CEdit* pEdit = ListEdit->EditLabel(tIndex);
		}
	}
	else
	{
		ListEdit->DeleteAllItems();
		init();
		AfxMessageBox(_T("连接超时"));
	}
}


void CFTP2Dlg::OnBnClickedButton8()
{

	ListEdit->DeleteAllItems();
	// TODO: 在此添加控件通知处理程序代码
	Ftp->QUIT();
	AfxMessageBox(_T("Goodbye"));
	init();

}

