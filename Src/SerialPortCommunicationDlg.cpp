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
	hCom=CreateFile("COM3",//COM1��
					GENERIC_READ|GENERIC_WRITE, //�������д
					0, //��ռ��ʽ
					NULL,
					OPEN_EXISTING, //�򿪶����Ǵ���
					0, //ͬ����ʽ
					NULL);
	if(hCom==(HANDLE)-1)
	{
		AfxMessageBox("��COMʧ��!");
		return FALSE;
	}
	
	SetupComm(hCom,100,100); //���뻺����������������Ĵ�С����1024
	
	COMMTIMEOUTS TimeOuts;
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout=MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier=0;
	TimeOuts.ReadTotalTimeoutConstant=0;
	//�ڶ�һ�����뻺���������ݺ���������������أ�
	//�������Ƿ������Ҫ����ַ���
	
	
	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier=100;
	TimeOuts.WriteTotalTimeoutConstant=500;
	SetCommTimeouts(hCom,&TimeOuts); //���ó�ʱ
	
	DCB dcb;
	GetCommState(hCom,&dcb);
	dcb.BaudRate=9600; //������Ϊ9600
	dcb.ByteSize=8; //ÿ���ֽ���8λ
	dcb.Parity=NOPARITY; //����żУ��λ
	dcb.StopBits=TWOSTOPBITS; //����ֹͣλ
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
	// �ڴ���Ҫ�򵥽��ܰ��ع�˾XMA5000��ͨѶЭ�飺
	//���Ǳ�RS485ͨѶ���������㲥��ʽͨѶ��
	//���а�˫����֡11λ��1����ʼλ(0)��8������λ��2��ֹͣλ(1)
	//�磺���Ǳ���ʾ��˲ʱֵ���������ͣ�DC1 AAA BB ETX
	//���У�DC1�Ǳ�׼ASCII���һ�����Ʒ��ţ���ֵΪ11H(ʮ���Ƶ�17)
	//��XMA5000��ͨѶЭ���У�DC1��ʾ��˲ʱֵ
	//AAA�Ǵӻ���ַ�룬Ҳ����XMA5000��ʾ�Ǳ��ͨѶ��ַ
	//BBΪͨ���ţ���˲ʱֵʱ��ֵΪ01
	//ETXҲ�Ǳ�׼ASCII���һ�����Ʒ��ţ���ֵΪ03H
	//��XMA5000��ͨѶЭ���У�ETX��ʾ����������
	
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
		AfxMessageBox("д����ʧ��!");
	}
	
}
void CSerialPortCommunicationDlg::OnReceive() 
{
	// TODO: Add your control notification handler code here

	char str[100];
	memset(str,'\0',100);
	DWORD wCount=100;//��ȡ���ֽ���
	BOOL bReadStat;
	bReadStat=ReadFile(hCom,str,wCount,&wCount,NULL);
	if(!bReadStat)
		AfxMessageBox("������ʧ��!");
	PurgeComm(hCom, PURGE_TXABORT|
		PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	m_disp=str;
	UpdateData(FALSE);
	
}






















void CSerialPortCommunicationDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	CloseHandle(hCom);	//�����˳�ʱ�رմ���
	CDialog::OnClose();
	
}
