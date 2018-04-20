#pragma once


// GetIp 대화 상자입니다.

class GetIp : public CDialogEx
{
	DECLARE_DYNAMIC(GetIp)
public:
	CString m_ip;

public:
	GetIp(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GetIp();
	CString getIp() { return m_ip; };
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
