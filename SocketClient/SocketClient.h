
// SocketClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSocketClientApp:
// �� Ŭ������ ������ ���ؼ��� SocketClient.cpp�� �����Ͻʽÿ�.
//

class CSocketClientApp : public CWinApp
{
public:
	CSocketClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSocketClientApp theApp;