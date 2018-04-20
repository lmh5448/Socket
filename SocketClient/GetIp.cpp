// GetIp.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SocketClient.h"
#include "GetIp.h"
#include "afxdialogex.h"


// GetIp 대화 상자입니다.

IMPLEMENT_DYNAMIC(GetIp, CDialogEx)

GetIp::GetIp(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

GetIp::~GetIp()
{
}

void GetIp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GetIp, CDialogEx)
END_MESSAGE_MAP()


// GetIp 메시지 처리기입니다.


void GetIp::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	GetDlgItemText(IDC_EDIT1, m_ip);
	CDialogEx::OnOK();
}
