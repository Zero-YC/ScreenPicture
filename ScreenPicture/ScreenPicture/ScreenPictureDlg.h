
// ScreenPictureDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CScreenPictureDlg �Ի���
class CScreenPictureDlg : public CDialogEx
{
// ����
public:
	CScreenPictureDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCREENPICTURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString SelFilePath();
	CButton m_comfirm;
	CButton m_reset;
	CButton m_selectPath;
	CButton m_run;
	CButton m_stop;
	CButton m_quit;
	CStatic m_time;
	CString m_path;
	afx_msg void OnBnClickedSelpath();
	afx_msg void OnBnClickedRun();
	int m_timetogo;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMyquit();
	int m_pcs;
	CFont myfont,myfont1;
	afx_msg void OnBnClickedComfirm();
	afx_msg void OnBnClickedReset();
	int m_getpcs;
	afx_msg void OnBnClickedMystop();
	void GetScreen();
	void GetScreen1();
	CString filename;
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	CComboBox m_geshi;
};
