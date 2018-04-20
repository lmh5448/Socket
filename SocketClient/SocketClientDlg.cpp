
// SocketClientDlg.cpp : 구현 파일
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


// CSocketClientDlg 대화 상자



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


// CSocketClientDlg 메시지 처리기

BOOL CSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ip = "127.0.0.1";
	/*GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);*/
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);

	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSocketClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketClientDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetIp getip;
	bool check = true;
	char buf[16];
	//ip입력받을때 ip가맞는지확인
	do {
		if (getip.DoModal() == IDOK) {
			m_ip = getip.getIp();
			if (m_ip == "") {
				m_ip = "127.0.0.1";
			}
			sprintf_s(buf, "%S", m_ip);
			if (inet_addr(buf) == -1) {
				check = true;
				AfxMessageBox(L"IP형식에 맞게 입력해주세요. (xxx.xxx.xxx.xxx)");
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	m_client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_client_socket == -1) {
		AfxMessageBox(_T("socket 생성 에러"));
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
		AfxMessageBox(_T("connect 에러"));
		return;
	}
	AfxMessageBox(_T("연결완료"));
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	return;
}


void CSocketClientDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char szFilter[] = "bitmap(*.bmp)|*.bmp| All Files(*.*)|*.*||";
	
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, CString(szFilter));
	if (dlg.DoModal() == IDOK) {
		m_file_path = dlg.GetPathName();
		msg_buf = new char[MAX_MSG_LEN];
		//한글깨짐으로 안되던부분
		_wsetlocale(LC_ALL, L"korean");
		sprintf(msg_buf, "%s %S", "open",(LPTSTR)(LPCTSTR)m_file_path);

		send(m_client_socket, msg_buf, 256, 0);

		recv(m_client_socket, msg_buf, 256, 0);
		if (strcmp("OK", msg_buf) == 0) {
			GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
		}
		else {
			AfxMessageBox(L"파일열기 실패 다시시도...");
		}
		TRACE("%s", msg_buf);

		delete(msg_buf);
	}
}


void CSocketClientDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	msg_buf = new char[MAX_MSG_LEN];

	sprintf(msg_buf, "%s", "start");

	send(m_client_socket, msg_buf, 256, 0);

	delete(msg_buf);
}
