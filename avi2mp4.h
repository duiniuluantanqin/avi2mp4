
// avi2mp4.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cavi2mp4App:
// �йش����ʵ�֣������ avi2mp4.cpp
//

class Cavi2mp4App : public CWinAppEx
{
public:
	Cavi2mp4App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cavi2mp4App theApp;