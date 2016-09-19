// SerialPortCommunicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SerialPortCommunication.h"
#include "SerialPortCommunicationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialPortCommunicationDlg dialog

CSerialPortCommunicationDlg::CSerialPortCommunicationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialPortCommunicationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSerialPortCommunicationDlg)
	m_disp = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialPortCommunicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerialPortCommunicationDlg)
	DDX_Text(pDX, IDC_RECEIVE_MESSAGE, m_disp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSerialPortCommunicationDlg, CDialog)
	//{{AFX_MSG_MAP(CSerialPortCommunicationDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_RECEIVE, OnReceive)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialPortCommunicationDlg message handlers

BOOL CSerialPortCommunicationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	// TODO: Add extra initialization here
	hCom=CreateFile("COM3",//COM1口
					GENERIC_READ|GENERIC_WRITE, //允许读和写
					0, //独占方式
					NULL,
					OPEN_EXISTING, //打开而不是创建
					0, //同步方式
					NULL);
	if(hCom==(HANDLE)-1)
	{
		AfxMessageBox("打开COM失败!");
		return FALSE;
	}
	
	SetupComm(hCom,100,100); //输入缓冲区和输出缓冲区的大小都是1024
	
	COMMTIMEOUTS TimeOuts;
	//设定读超时
	TimeOuts.ReadIntervalTimeout=MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier=0;
	TimeOuts.ReadTotalTimeoutConstant=0;
	//在读一次输入缓冲区的内容后读操作就立即返回，
	//而不管是否读入了要求的字符。
	
	
	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier=100;
	TimeOuts.WriteTotalTimeoutConstant=500;
	SetCommTimeouts(hCom,&TimeOuts); //设置超时
	
	DCB dcb;
	GetCommState(hCom,&dcb);
	dcb.BaudRate=9600; //波特率为9600
	dcb.ByteSize=8; //每个字节有8位
	dcb.Parity=NOPARITY; //无奇偶校验位
	dcb.StopBits=TWOSTOPBITS; //两个停止位
	SetCommState(hCom,&dcb);
	
	PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);
	


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSerialPortCommunicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSerialPortCommunicationDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSerialPortCommunicationDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSerialPortCommunicationDlg::OnSend() 
{
	// TODO: Add your control notification handler code here

	// TODO: Add your control notification handler code here
	// 在此需要简单介绍百特公司XMA5000的通讯协议：
	//该仪表RS485通讯采用主机广播方式通讯。
	//串行半双工，帧11位，1个起始位(0)，8个数据位，2个停止位(1)
	//如：读仪表显示的瞬时值，主机发送：DC1 AAA BB ETX
	//其中：DC1是标准ASCII码的一个控制符号，码值为11H(十进制的17)
	//在XMA5000的通讯协议中，DC1表示读瞬时值
	//AAA是从机地址码，也就是XMA5000显示仪表的通讯地址
	//BB为通道号，读瞬时值时该值为01
	//ETX也是标准ASCII码的一个控制符号，码值为03H
	//在XMA5000的通讯协议中，ETX表示主机结束符
	
	CString BufferString;
	GetDlgItem(IDC_SEND_MESSAGE)->GetWindowText(BufferString);
	DWORD dwBytesWrite=BufferString.GetLength();
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(hCom,BufferString,dwBytesWrite,& dwBytesWrite,NULL);
	if(!bWriteStat)
	{
		AfxMessageBox("写串口失败!");
	}
	
}
void CSerialPortCommunicationDlg::OnReceive() 
{
	// TODO: Add your control notification handler code here

	char str[100];
	memset(str,'\0',100);
	DWORD wCount=100;//读取的字节数
	BOOL bReadStat;
	bReadStat=ReadFile(hCom,str,wCount,&wCount,NULL);
	if(!bReadStat)
		AfxMessageBox("读串口失败!");
	PurgeComm(hCom, PURGE_TXABORT|
		PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	m_disp=str;
	UpdateData(FALSE);
	
}






















void CSerialPortCommunicationDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	CloseHandle(hCom);	//程序退出时关闭串口
	CDialog::OnClose();
	
}
