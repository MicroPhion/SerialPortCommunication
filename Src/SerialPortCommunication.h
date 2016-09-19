// SerialPortCommunication.h : main header file for the SERIALPORTCOMMUNICATION application
//

#if !defined(AFX_SERIALPORTCOMMUNICATION_H__D79B65F6_D556_412B_8F9B_56557A985340__INCLUDED_)
#define AFX_SERIALPORTCOMMUNICATION_H__D79B65F6_D556_412B_8F9B_56557A985340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSerialPortCommunicationApp:
// See SerialPortCommunication.cpp for the implementation of this class
//

class CSerialPortCommunicationApp : public CWinApp
{
public:
	CSerialPortCommunicationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialPortCommunicationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSerialPortCommunicationApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALPORTCOMMUNICATION_H__D79B65F6_D556_412B_8F9B_56557A985340__INCLUDED_)
