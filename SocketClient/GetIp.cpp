// GetIp.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SocketClient.h"
#include "GetIp.h"
#include "afxdialogex.h"


// GetIp ��ȭ �����Դϴ�.

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


// GetIp �޽��� ó�����Դϴ�.


void GetIp::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	GetDlgItemText(IDC_EDIT1, m_ip);
	CDialogEx::OnOK();
}
