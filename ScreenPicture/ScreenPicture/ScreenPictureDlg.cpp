
// ScreenPictureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenPicture.h"
#include "ScreenPictureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CScreenPictureDlg 对话框



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


// CScreenPictureDlg 消息处理程序

BOOL CScreenPictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	myfont.CreatePointFont(200, TEXT("黑体"));
	GetDlgItem(IDC_DISTIME)->SetFont(&myfont);
	GetDlgItem(IDC_RUN)->SetFont(&myfont);
	GetDlgItem(IDC_MYSTOP)->SetFont(&myfont);
	GetDlgItem(IDC_MYQUIT)->SetFont(&myfont);
	myfont1.CreatePointFont(200, TEXT("黑体"));
	GetDlgItem(IDC_STATIC1)->SetFont(&myfont1);

	GetDlgItem(IDC_RUN)->EnableWindow(0);
	GetDlgItem(IDC_MYSTOP)->EnableWindow(0);
	m_geshi.SetCurSel(0);
#ifdef _DEBUG
	GetDlgItem(IDC_BUTTON1)->ShowWindow(1);           ////////////////////调试宏应用///////调试按钮可见/////////////////////
#endif
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScreenPictureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	     sInfo.lpszTitle = _T("请选择处理结果存储路径");
	     sInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
         sInfo.lpfn = NULL;

	      // 显示文件夹选择对话框  
         LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	     if (lpidlBrowse != NULL)
	    {
		      // 取得文件夹名  
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
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(1);
	m_path= SelFilePath();
	UpdateData(0);
}


void CScreenPictureDlg::OnBnClickedRun()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(1);
	m_timetogo = m_timetogo * 60;
	GetDlgItem(IDC_RUN)->EnableWindow(0);
	GetDlgItem(IDC_MYSTOP)->EnableWindow(1);
	m_pcs = 0;
	SetTimer(1,1000, NULL);
}


void CScreenPictureDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_timetogo -= 1;
	if (m_timetogo == 0)
		{
			CString str;
			str.Format(TEXT("%.2d:%.2d:%.2d"), 0, 0, 0);
			GetDlgItem(IDC_DISTIME)->SetWindowTextW(str);
			///////////////截图///////////////////////////
			//GetScreen();////////////运行一段时间会崩溃
			GetScreen1();///////////测试可以使用，稳定运行
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
	// TODO:  在此添加控件通知处理程序代码
	CScreenPictureDlg::OnBnClickedMystop();
	exit(1);
}


void CScreenPictureDlg::OnBnClickedComfirm()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(1);
	if (m_path.IsEmpty() || m_timetogo == 0)
	{
		MessageBox(TEXT("请输入正确配置"));
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
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_RUN)->EnableWindow(1);
	GetDlgItem(IDC_MYSTOP)->EnableWindow(0);
	KillTimer(1);
	
}
void CScreenPictureDlg::GetScreen()////////////////会发生错误////////////////////////
{
	CWnd *pDesktop = GetDesktopWindow();   
	CDC *pdeskdc = pDesktop->GetDC();  
	CRect re;  
	//获取窗口的大小   
	pDesktop->GetClientRect(&re);    
	CBitmap bmp; 
	bmp.CreateCompatibleBitmap(pdeskdc, re.Width(), re.Height());   
	//创建一个兼容的内存画板   
	CDC memorydc;   
	memorydc.CreateCompatibleDC(pdeskdc); 
	//选中画笔  
	CBitmap *pold = memorydc.SelectObject(&bmp);   
	//绘制图像  
	memorydc.BitBlt(0, 0, re.Width(), re.Height(), pdeskdc, 0, 0, SRCCOPY);  
	//获取鼠标位置，然后添加鼠标图像 
	/*CPoint po;  
	GetCursorPos(&po); 
	HICON hinco = (HICON)GetCursor();   
	memorydc.DrawIcon(po.x - 10, po.y - 10, hinco); */
	//选中原来的画笔   
	memorydc.SelectObject(pold); 
	BITMAP bit;  
	bmp.GetBitmap(&bit);   
	//定义 图像大小（单位：byte）  
	DWORD size = bit.bmWidthBytes * bit.bmHeight;  
	LPSTR lpdata = (LPSTR)GlobalAlloc(GPTR, size);    
	//后面是创建一个bmp文件的必须文件头  
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
	//////////////////选择的路径////////////////////////
	CFile file;   
	CString strFileName = m_path; 
	///////////////////以日期生成文件夹////////////////////////////////
	CTime t = CTime::GetCurrentTime();   
	CString tt = t.Format("\\%Y-%m-%d\\");  
	strFileName += tt;
	CreateDirectory((LPCTSTR)strFileName, NULL);
	////////////////以时间生成文件//////////////////////////////////////////
	/*CString geshi;
	m_geshi.GetLBText(m_geshi.GetCurSel(), geshi);*/
     tt = t.Format("%H-%M-%S");
	strFileName+= tt;    
	strFileName += TEXT(".bmp");
	////////////////////////////写入文件////////////////////////////////////////////
	if (file.Open((LPCTSTR)strFileName, CFile::modeCreate | CFile::modeWrite))  
	{        
		file.Write(&bfh, sizeof(BITMAPFILEHEADER));    
		file.Write(&pbitinfo, sizeof(BITMAPINFOHEADER));      
		file.Write(lpdata, sizeof(DWORD));                            //file.Write(lpdata, size);///////////////发生内存越界///////////////////   
		file.Flush();  
		file.Close();
		DWORD elor = GetLastError();
	}   
	GlobalFree(lpdata); 
	ReleaseDC(pdeskdc);
	DeleteDC(memorydc);
}
void CScreenPictureDlg::GetScreen1()////////////////////可以使用////////////////////
{
	////////获取屏幕的设备描述表/////////////////
	CWnd *pDesktop = GetDesktopWindow();
	CDC *pdeskdc = pDesktop->GetDC();
	//////获取屏幕的大小////////////////////////   
	CRect rect;
	pDesktop->GetClientRect(&rect);
	/////声明图像类对象并实例化////////////////
	CImage image;
	image.Create(rect.Width(), rect.Height(), 24);
	////建立一个兼容的自己DC//////////////////
	CDC dstDC;
	dstDC.CreateCompatibleDC(pdeskdc);
	/////////用图像对象替换自己DC/////////////
	dstDC.SelectObject(image);
	dstDC.BitBlt(0, 0, rect.Width(), rect.Height(), pdeskdc, 0, 0, SRCCOPY);
	///////保存图像/////////////////////////////////////////////////////////////////////////////////////
	//////////////////选择的路径////////////////////////
	CString strFileName = m_path;
	///////////////////以日期生成文件夹////////////////////////////////
	CTime t = CTime::GetCurrentTime();
	CString tt = t.Format("\\%Y-%m-%d\\");
	strFileName += tt;
	CreateDirectory((LPCTSTR)strFileName, NULL);
	////////////////以时间生成文件//////////////////////////////////////////
	CString geshi;
	m_geshi.GetLBText(m_geshi.GetCurSel(), geshi);
	tt = t.Format("%H-%M-%S");
	strFileName += tt;
	strFileName += geshi;
	image.Save(strFileName);
	//////释放资源///////////////////////
	ReleaseDC(pdeskdc);
	DeleteDC(dstDC);
}
void CScreenPictureDlg::OnBnClickedButton1()                                 ///////////////测试按钮/////////////////////////////
{
	// TODO:  在此添加控件通知处理程序代码
	//GetScreen();
	 ::ShellExecute(NULL, TEXT("open"), TEXT("mspaint.exe"),/*调用画图程序*/  m_path, NULL, SW_SHOWMAXIMIZED);
}

void CScreenPictureDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	//CDialogEx::OnOK();
}


HBRUSH CScreenPictureDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if (pWnd == GetDlgItem(IDC_DISTIME))
	{
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(0, 255, 0));
		//hbr = CreateSolidBrush(RGB(0, 0, 0));//控件的背景色为黑色
		return (HBRUSH)::GetStockObject(BLACK_BRUSH);
	}
	else
	{
		return hbr;
	}

}