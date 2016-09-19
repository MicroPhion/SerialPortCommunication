// SerialPortCommunicationDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm1.h"
//}}AFX_INCLUDES

#if !defined(AFX_SERIALPORTCOMMUNICATIONDLG_H__7EE987AD_3437_453C_9D3D_9BE190AC535E__INCLUDED_)
#define AFX_SERIALPORTCOMMUNICATIONDLG_H__7EE987AD_3437_453C_9D3D_9BE190AC535E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSerialPortCommunicationDlg dialog

class CSerialPortCommunicationDlg : public CDialog
{
// Construction
public:
	HANDLE hCom;  //全局变量，串口句柄
	
public:
	CSerialPortCommunicationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSerialPortCommunicationDlg)
	enum { IDD = IDD_SERIALPORTCOMMUNICATION_DIALOG };
	CString	m_disp;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialPortCommunicationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSerialPortCommunicationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	afx_msg void OnReceive();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALPORTCOMMUNICATIONDLG_H__7EE987AD_3437_453C_9D3D_9BE190AC535E__INCLUDED_)
