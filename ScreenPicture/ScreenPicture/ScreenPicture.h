
// ScreenPicture.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CScreenPictureApp: 
// �йش����ʵ�֣������ ScreenPicture.cpp
//

class CScreenPictureApp : public CWinApp
{
public:
	CScreenPictureApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CScreenPictureApp theApp;