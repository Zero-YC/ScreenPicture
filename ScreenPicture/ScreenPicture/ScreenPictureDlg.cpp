
// ScreenPictureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScreenPicture.h"
#include "ScreenPictureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScreenPictureDlg �Ի���



CScreenPictureDlg::CScreenPictureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScreenPictureDlg::IDD, pParent)
	, m_path(_T(""))
	, m_timetogo(0)
	, m_pcs(0)
	, m_getpcs(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CScreenPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMFIRM, m_comfirm);
	DDX_Control(pDX, IDC_RESET, m_reset);
	DDX_Control(pDX, IDC_SELPATH, m_selectPath);
	DDX_Control(pDX, IDC_RUN, m_run);
	DDX_Control(pDX, IDC_MYSTOP, m_stop);
	DDX_Control(pDX, IDC_MYQUIT, m_quit);
	DDX_Control(pDX, IDC_DISTIME, m_time);
	DDX_Text(pDX, IDC_EDIT1, m_path);
	//  DDX_Text(pDX, IDC_EDIT3, m_getpcs);
	DDX_Text(pDX, IDC_EDIT2, m_timetogo);
	DDX_Text(pDX, IDC_STATIC2, m_pcs);
	DDX_Text(pDX, IDC_EDIT3, m_getpcs);
	DDX_Control(pDX, IDC_COMBO1, m_geshi);
}

BEGIN_MESSAGE_MAP(CScreenPictureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELPATH, &CScreenPictureDlg::OnBnClickedSelpath)
	ON_BN_CLICKED(IDC_RUN, &CScreenPictureDlg::OnBnClickedRun)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MYQUIT, &CScreenPictureDlg::OnBnClickedMyquit)
	ON_BN_CLICKED(IDC_COMFIRM, &CScreenPictureDlg::OnBnClickedComfirm)
	ON_BN_CLICKED(IDC_RESET, &CScreenPictureDlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_MYSTOP, &CScreenPictureDlg::OnBnClickedMystop)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CScreenPictureDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CScreenPictureDlg ��Ϣ�������

BOOL CScreenPictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	myfont.CreatePointFont(200, TEXT("����"));
	GetDlgItem(IDC_DISTIME)->SetFont(&myfont);
	GetDlgItem(IDC_RUN)->SetFont(&myfont);
	GetDlgItem(IDC_MYSTOP)->SetFont(&myfont);
	GetDlgItem(IDC_MYQUIT)->SetFont(&myfont);
	myfont1.CreatePointFont(200, TEXT("����"));
	GetDlgItem(IDC_STATIC1)->SetFont(&myfont1);

	GetDlgItem(IDC_RUN)->EnableWindow(0);
	GetDlgItem(IDC_MYSTOP)->EnableWindow(0);
	m_geshi.SetCurSel(0);
#ifdef _DEBUG
	GetDlgItem(IDC_BUTTON1)->ShowWindow(1);           ////////////////////���Ժ�Ӧ��///////���԰�ť�ɼ�/////////////////////
#endif
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CScreenPictureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CScreenPictureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CScreenPictureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CScreenPictureDlg::SelFilePath()
 {
          TCHAR  szFolderPath[MAX_PATH] = { 0 };
         CString strFolderPath = TEXT("");
	     BROWSEINFO      sInfo;
         ::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	     sInfo.pidlRoot = 0;
	     sInfo.lpszTitle = _T("��ѡ�������洢·��");
	     sInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
         sInfo.lpfn = NULL;

	      // ��ʾ�ļ���ѡ��Ի���  
         LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	     if (lpidlBrowse != NULL)
	    {
		      // ȡ���ļ�����  
		       if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
			       {
			       strFolderPath = szFolderPath;
			      }
		    }
	    if (lpidlBrowse != NULL)
		  {
		       ::CoTaskMemFree(lpidlBrowse);
	   }
			return strFolderPath;
}

void CScreenPictureDlg::OnBnClickedSelpath()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(1);
	m_path= SelFilePath();
	UpdateData(0);
}


void CScreenPictureDlg::OnBnClickedRun()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(1);
	m_timetogo = m_timetogo * 60;
	GetDlgItem(IDC_RUN)->EnableWindow(0);
	GetDlgItem(IDC_MYSTOP)->EnableWindow(1);
	m_pcs = 0;
	SetTimer(1,1000, NULL);
}


void CScreenPictureDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_timetogo -= 1;
	if (m_timetogo == 0)
		{
			CString str;
			str.Format(TEXT("%.2d:%.2d:%.2d"), 0, 0, 0);
			GetDlgItem(IDC_DISTIME)->SetWindowTextW(str);
			///////////////��ͼ///////////////////////////
			//GetScreen();////////////����һ��ʱ������
			GetScreen1();///////////���Կ���ʹ�ã��ȶ�����
			////////////////////////////////////////////
			m_pcs += 1;
			str.Format(TEXT("%d"), m_pcs);
			GetDlgItem(IDC_STATIC2)->SetWindowTextW(str);
			if (m_pcs==m_getpcs)
			{
				KillTimer(1);
			}
			UpdateData(1);
			m_timetogo = m_timetogo * 60;
			
		}
	else
	{
		int second, minute, house;
		if (m_timetogo / 3600 >= 1)
		{
			house = m_timetogo / 3600;
			minute = (m_timetogo % 3600)/60;
			second = m_timetogo - house * 3600 - minute*60;
		}
		else
		{
			if (m_timetogo / 60 >= 1)
			{
				house = 0;
				minute = m_timetogo / 60;
				second = m_timetogo % 60;
			}
			else
			{
				second = m_timetogo;
				house = 0;
				minute = 0;
				
			}
		}
		
		CString str;
		str.Format(TEXT("%.2d:%.2d:%.2d"), house, minute, second);
		GetDlgItem(IDC_DISTIME)->SetWindowTextW(str);
	}
		
	CDialogEx::OnTimer(nIDEvent);
}


void CScreenPictureDlg::OnBnClickedMyquit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CScreenPictureDlg::OnBnClickedMystop();
	exit(1);
}


void CScreenPictureDlg::OnBnClickedComfirm()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(1);
	if (m_path.IsEmpty() || m_timetogo == 0)
	{
		MessageBox(TEXT("��������ȷ����"));
		return;
	}
	else
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(0);
		GetDlgItem(IDC_SELPATH)->EnableWindow(0);
		GetDlgItem(IDC_EDIT2)->EnableWindow(0);
		GetDlgItem(IDC_EDIT3)->EnableWindow(0);
		GetDlgItem(IDC_COMFIRM)->EnableWindow(0);
		GetDlgItem(IDC_COMBO1)->EnableWindow(0);

		GetDlgItem(IDC_RUN)->EnableWindow(1);
		GetDlgItem(IDC_MYSTOP)->EnableWindow(1);
	}
	
}


void CScreenPictureDlg::OnBnClickedReset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->EnableWindow(1);
	GetDlgItem(IDC_SELPATH)->EnableWindow(1);
	GetDlgItem(IDC_EDIT2)->EnableWindow(1);
	GetDlgItem(IDC_EDIT3)->EnableWindow(1);
	GetDlgItem(IDC_COMFIRM)->EnableWindow(1);
	GetDlgItem(IDC_COMBO1)->EnableWindow(1);

	GetDlgItem(IDC_EDIT1)->SetWindowTextW(TEXT(""));
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(TEXT(""));
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(TEXT(""));

	GetDlgItem(IDC_RUN)->EnableWindow(0);
	GetDlgItem(IDC_MYSTOP)->EnableWindow(0); 
	

}


void CScreenPictureDlg::OnBnClickedMystop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_RUN)->EnableWindow(1);
	GetDlgItem(IDC_MYSTOP)->EnableWindow(0);
	KillTimer(1);
	
}
void CScreenPictureDlg::GetScreen()////////////////�ᷢ������////////////////////////
{
	CWnd *pDesktop = GetDesktopWindow();   
	CDC *pdeskdc = pDesktop->GetDC();  
	CRect re;  
	//��ȡ���ڵĴ�С   
	pDesktop->GetClientRect(&re);    
	CBitmap bmp; 
	bmp.CreateCompatibleBitmap(pdeskdc, re.Width(), re.Height());   
	//����һ�����ݵ��ڴ滭��   
	CDC memorydc;   
	memorydc.CreateCompatibleDC(pdeskdc); 
	//ѡ�л���  
	CBitmap *pold = memorydc.SelectObject(&bmp);   
	//����ͼ��  
	memorydc.BitBlt(0, 0, re.Width(), re.Height(), pdeskdc, 0, 0, SRCCOPY);  
	//��ȡ���λ�ã�Ȼ��������ͼ�� 
	/*CPoint po;  
	GetCursorPos(&po); 
	HICON hinco = (HICON)GetCursor();   
	memorydc.DrawIcon(po.x - 10, po.y - 10, hinco); */
	//ѡ��ԭ���Ļ���   
	memorydc.SelectObject(pold); 
	BITMAP bit;  
	bmp.GetBitmap(&bit);   
	//���� ͼ���С����λ��byte��  
	DWORD size = bit.bmWidthBytes * bit.bmHeight;  
	LPSTR lpdata = (LPSTR)GlobalAlloc(GPTR, size);    
	//�����Ǵ���һ��bmp�ļ��ı����ļ�ͷ  
	BITMAPINFOHEADER pbitinfo; 
	pbitinfo.biBitCount = 24;   
	pbitinfo.biClrImportant = 0;  
	pbitinfo.biCompression = BI_RGB;   
	pbitinfo.biHeight = bit.bmHeight;  
	pbitinfo.biPlanes = 1;   
	pbitinfo.biSize = sizeof(BITMAPINFOHEADER);    
	pbitinfo.biSizeImage = size;  
	pbitinfo.biWidth = bit.bmWidth;   
	pbitinfo.biXPelsPerMeter = 0; 
	pbitinfo.biYPelsPerMeter = 0;   
	GetDIBits(pdeskdc->m_hDC, bmp, 0, pbitinfo.biHeight, lpdata, (BITMAPINFO*) &pbitinfo, DIB_RGB_COLORS);  
	BITMAPFILEHEADER bfh;  
	bfh.bfReserved1 = bfh.bfReserved2 = 0;  
	bfh.bfType = ((WORD)('M' << 8) | 'B');  
	bfh.bfSize = size + 54;  
	bfh.bfOffBits = 54;   
	//////////////////ѡ���·��////////////////////////
	CFile file;   
	CString strFileName = m_path; 
	///////////////////�����������ļ���////////////////////////////////
	CTime t = CTime::GetCurrentTime();   
	CString tt = t.Format("\\%Y-%m-%d\\");  
	strFileName += tt;
	CreateDirectory((LPCTSTR)strFileName, NULL);
	////////////////��ʱ�������ļ�//////////////////////////////////////////
	/*CString geshi;
	m_geshi.GetLBText(m_geshi.GetCurSel(), geshi);*/
     tt = t.Format("%H-%M-%S");
	strFileName+= tt;    
	strFileName += TEXT(".bmp");
	////////////////////////////д���ļ�////////////////////////////////////////////
	if (file.Open((LPCTSTR)strFileName, CFile::modeCreate | CFile::modeWrite))  
	{        
		file.Write(&bfh, sizeof(BITMAPFILEHEADER));    
		file.Write(&pbitinfo, sizeof(BITMAPINFOHEADER));      
		file.Write(lpdata, sizeof(DWORD));                            //file.Write(lpdata, size);///////////////�����ڴ�Խ��///////////////////   
		file.Flush();  
		file.Close();
		DWORD elor = GetLastError();
	}   
	GlobalFree(lpdata); 
	ReleaseDC(pdeskdc);
	DeleteDC(memorydc);
}
void CScreenPictureDlg::GetScreen1()////////////////////����ʹ��////////////////////
{
	////////��ȡ��Ļ���豸������/////////////////
	CWnd *pDesktop = GetDesktopWindow();
	CDC *pdeskdc = pDesktop->GetDC();
	//////��ȡ��Ļ�Ĵ�С////////////////////////   
	CRect rect;
	pDesktop->GetClientRect(&rect);
	/////����ͼ�������ʵ����////////////////
	CImage image;
	image.Create(rect.Width(), rect.Height(), 24);
	////����һ�����ݵ��Լ�DC//////////////////
	CDC dstDC;
	dstDC.CreateCompatibleDC(pdeskdc);
	/////////��ͼ������滻�Լ�DC/////////////
	dstDC.SelectObject(image);
	dstDC.BitBlt(0, 0, rect.Width(), rect.Height(), pdeskdc, 0, 0, SRCCOPY);
	///////����ͼ��/////////////////////////////////////////////////////////////////////////////////////
	//////////////////ѡ���·��////////////////////////
	CString strFileName = m_path;
	///////////////////�����������ļ���////////////////////////////////
	CTime t = CTime::GetCurrentTime();
	CString tt = t.Format("\\%Y-%m-%d\\");
	strFileName += tt;
	CreateDirectory((LPCTSTR)strFileName, NULL);
	////////////////��ʱ�������ļ�//////////////////////////////////////////
	CString geshi;
	m_geshi.GetLBText(m_geshi.GetCurSel(), geshi);
	tt = t.Format("%H-%M-%S");
	strFileName += tt;
	strFileName += geshi;
	image.Save(strFileName);
	//////�ͷ���Դ///////////////////////
	ReleaseDC(pdeskdc);
	DeleteDC(dstDC);
}
void CScreenPictureDlg::OnBnClickedButton1()                                 ///////////////���԰�ť/////////////////////////////
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//GetScreen();
	 ::ShellExecute(NULL, TEXT("open"), TEXT("mspaint.exe"),/*���û�ͼ����*/  m_path, NULL, SW_SHOWMAXIMIZED);
}

void CScreenPictureDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	//CDialogEx::OnOK();
}


HBRUSH CScreenPictureDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	if (pWnd == GetDlgItem(IDC_DISTIME))
	{
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(0, 255, 0));
		//hbr = CreateSolidBrush(RGB(0, 0, 0));//�ؼ��ı���ɫΪ��ɫ
		return (HBRUSH)::GetStockObject(BLACK_BRUSH);
	}
	else
	{
		return hbr;
	}

}