#pragma once


// GetIp ��ȭ �����Դϴ�.

class GetIp : public CDialogEx
{
	DECLARE_DYNAMIC(GetIp)
public:
	CString m_ip;

public:
	GetIp(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GetIp();
	CString getIp() { return m_ip; };
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
