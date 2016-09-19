; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSerialPortCommunicationDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SerialPortCommunication.h"

ClassCount=3
Class1=CSerialPortCommunicationApp
Class2=CSerialPortCommunicationDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SERIALPORTCOMMUNICATION_DIALOG

[CLS:CSerialPortCommunicationApp]
Type=0
HeaderFile=SerialPortCommunication.h
ImplementationFile=SerialPortCommunication.cpp
Filter=N

[CLS:CSerialPortCommunicationDlg]
Type=0
HeaderFile=SerialPortCommunicationDlg.h
ImplementationFile=SerialPortCommunicationDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_RECEIVE_MESSAGE

[CLS:CAboutDlg]
Type=0
HeaderFile=SerialPortCommunicationDlg.h
ImplementationFile=SerialPortCommunicationDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SERIALPORTCOMMUNICATION_DIALOG]
Type=1
Class=CSerialPortCommunicationDlg
ControlCount=8
Control1=IDC_SEND_MESSAGE,edit,1350631552
Control2=IDC_RECEIVE_MESSAGE,edit,1350631552
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RECEIVE,button,1342242816
Control7=IDC_SEND,button,1342242816
Control8=IDC_CLOSE,button,1342242816

