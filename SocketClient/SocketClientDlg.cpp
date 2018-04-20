
// SocketClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "SocketClient.h"
#include "SocketClientDlg.h"
#include "afxdialogex.h"
#include "GetIp.h"
#include <WinSock2.h> 
#include <Windows.h> 
#include <process.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <malloc.h> 
#include <locale.h>

#pragma comment(lib,"ws2_32") 
#pragma warning(disable : 4996) 
#define PORT_NUM    20001 
#define MAX_MSG_LEN 256 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSocketClientDlg ��ȭ ����



CSocketClientDlg::CSocketClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSocketClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSocketClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSocketClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSocketClientDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSocketClientDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CSocketClientDlg �޽��� ó����

BOOL CSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ip = "127.0.0.1";
	/*GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);*/
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);

	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSocketClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketClientDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetIp getip;
	bool check = true;
	char buf[16];
	//ip�Է¹����� ip���´���Ȯ��
	do {
		if (getip.DoModal() == IDOK) {
			m_ip = getip.getIp();
			if (m_ip == "") {
				m_ip = "127.0.0.1";
			}
			sprintf_s(buf, "%S", m_ip);
			if (inet_addr(buf) == -1) {
				check = true;
				AfxMessageBox(L"IP���Ŀ� �°� �Է����ּ���. (xxx.xxx.xxx.xxx)");
			}
			else {
				check = false;
				m_ip = CString(buf);
			}
		}
		else {
			return;
		}
	} while (check);
}


void CSocketClientDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	m_client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_client_socket == -1) {
		AfxMessageBox(_T("socket ���� ����"));
		return;
	}
	sockaddr_in srv_addr = { 0 };
	srv_addr.sin_family = AF_INET;
	char buf[16];
	sprintf(buf, "%S", m_ip);
	srv_addr.sin_addr.s_addr = inet_addr(buf);
	srv_addr.sin_port = htons(PORT_NUM);

	int re;
	re = connect(m_client_socket, (LPSOCKADDR)&srv_addr, sizeof(sockaddr_in));
	if (re == -1) {
		AfxMessageBox(_T("connect ����"));
		return;
	}
	AfxMessageBox(_T("����Ϸ�"));
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	return;
}


void CSocketClientDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char szFilter[] = "bitmap(*.bmp)|*.bmp| All Files(*.*)|*.*||";
	
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, CString(szFilter));
	if (dlg.DoModal() == IDOK) {
		m_file_path = dlg.GetPathName();
		msg_buf = new char[MAX_MSG_LEN];
		//�ѱ۱������� �ȵǴ��κ�
		_wsetlocale(LC_ALL, L"korean");
		sprintf(msg_buf, "%s %S", "open",(LPTSTR)(LPCTSTR)m_file_path);

		send(m_client_socket, msg_buf, 256, 0);

		recv(m_client_socket, msg_buf, 256, 0);
		if (strcmp("OK", msg_buf) == 0) {
			GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
		}
		else {
			AfxMessageBox(L"���Ͽ��� ���� �ٽýõ�...");
		}
		TRACE("%s", msg_buf);

		delete(msg_buf);
	}
}


void CSocketClientDlg::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	msg_buf = new char[MAX_MSG_LEN];

	sprintf(msg_buf, "%s", "start");

	send(m_client_socket, msg_buf, 256, 0);

	delete(msg_buf);
}
