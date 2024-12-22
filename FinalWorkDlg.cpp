
// FinalWorkDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FinalWork.h"
#include "FinalWorkDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFinalWorkDlg 对话框



CFinalWorkDlg::CFinalWorkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINALWORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFinalWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CFinalWorkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFinalWorkDlg::AddPicture)
	ON_BN_CLICKED(IDC_BUTTON3, &CFinalWorkDlg::BeginProcess)
	ON_MESSAGE(WM_UPDATE_LISTBOX, &CFinalWorkDlg::OnUpdateListBox)
END_MESSAGE_MAP()


// CFinalWorkDlg 消息处理程序

BOOL CFinalWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码
	m_combo.InsertString(0, _T("灰度处理"));
	m_combo.InsertString(1, _T("放大至200%"));
	m_combo.InsertString(2, _T("缩小至50%"));
	m_combo.InsertString(3, _T("顺时针旋转"));
	m_combo.InsertString(4, _T("逆时针旋转"));
	m_combo.InsertString(5, _T("人脸检测"));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFinalWorkDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFinalWorkDlg::OnPaint()
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
HCURSOR CFinalWorkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CFinalWorkDlg::OnUpdateListBox(WPARAM wParam, LPARAM lParam)
{
	int index = (int)wParam;
	CString status = m_imageList[index].status;

	// 更新ListBox中的状态
	CString displayText;
	displayText.Format(_T("%s - %s"), m_imageList[index].filePath, status);

	// 更新ListBox中相应行的文本
	m_list.DeleteString(index);
	m_list.InsertString(index, displayText);
	return 0;
}

void CFinalWorkDlg::AddPicture()
{
	CString fileName;
	TCHAR szFilter[] = _T("JPEG文件(*.jpg)|*.jpg|PNG文件(*.png)|*.png|GIF文件(*.gif)|*.gif|bmp文件(*.bmp)|*.bmp||");
	CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0, szFilter, this);

	if (fileDlg.DoModal() != IDOK)
		return;

	fileName = fileDlg.GetPathName();

	/*
	CImage img;
	img.Load(fileName);
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_Picture1);//获取控件句柄		
	pWnd->GetClientRect(&rect); //获取Picture Control控件的客户区

	CDC* pDC = pWnd->GetDC();//获取picture control的DC

	int oldMode = SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式		
	img.StretchBlt(pDC->m_hDC, rect, SRCCOPY);//从源矩形中复制一个位图到目标矩形，按目标设备设置的模式进行图像的拉伸或压缩
	SetStretchBltMode(pDC->m_hDC, oldMode);
	ReleaseDC(pDC);
	*/

	/*
	m_p1.GetClientRect(rect);
	CDC* pDc = m_p1.GetDC();
	img.Draw(pDc->m_hDC, rect);
	img.Destroy();
	m_p1.ReleaseDC(pDc);
	*/

	//src = imread(fileName.GetBuffer(), 1);

	ImageInfo info;
	info.filePath = fileName;
	info.status = _T("[待处理]");
	m_imageList.Add(info);
	CString text;
	text.Format(_T("%s - %s"), fileName, info.status);
	m_list.AddString(text);

	//m_list.AddString(_T(fileName + "[待处理]"));
}

void CFinalWorkDlg::BeginProcess()
{
	// TODO: 在此添加控件通知处理程序代码
	int index1 = m_combo.GetCurSel();
	int index2 = m_list.GetCurSel();
	CString path = m_imageList[index2].filePath;
	ThreadParams* params = new ThreadParams{index1, path };
	AfxBeginThread(ProcessImageThread, params);
	m_imageList[index2].status = _T("[已处理]");
	AfxGetMainWnd()->PostMessage(WM_UPDATE_LISTBOX, index2, 0);

}

UINT CFinalWorkDlg::ProcessImageThread(LPVOID pParam)
{
	ThreadParams* p = (ThreadParams*)pParam;
	int index = p->comboIndex;
	CString path = p->path;
	int pos1 = path.Find('C');
	int pos2 = path.Find('.');
	CString subRstPath = path.Mid(pos1, pos2 - pos1);
	delete p;
	CString rstPath;
	rstPath.Format("%sresult.png", subRstPath);
	Mat src = imread(path.GetBuffer(), 1);
	Mat result;
	CFinalWorkDlg dlg;
	switch (index)
	{
	case 0:
		result = dlg.imageProcess.RGB_To_Gray(src);
		imwrite(rstPath.GetBuffer(), result);
		/*
		namedWindow("src", WINDOW_NORMAL);
		namedWindow("result", WINDOW_NORMAL);
		resizeWindow("src", 1600, 900);
		resizeWindow("result", 1600, 900);
		imshow("src", src);
		imshow("result", result);
		*/
		break;
	case 1:
		result = dlg.imageProcess.Resize_To_200(src);
		imwrite(rstPath.GetBuffer(), result);
		break;
	case 2:
		result = dlg.imageProcess.Resize_To_50(src);
		imwrite(rstPath.GetBuffer(), result);
		break;
	case 3:
		result = dlg.imageProcess.Rotate_Clockwise_90(src);
		imwrite(rstPath.GetBuffer(), result);
		break;
	case 4:
		result = dlg.imageProcess.Rotate_Counterclockwise_90(src);
		imwrite(rstPath.GetBuffer(), result);
		break;
	case 5:
		result = dlg.imageProcess.Detect_Face(src);
		imwrite(rstPath.GetBuffer(), result);
		break;
	default:
		break;
	}

	return 0;
}

/*
void CFinalWorkDlg::ShowResult(CString src)
{
	CImage img;
	img.Load(TEXT(src));
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_Picture2);//获取控件句柄
	pWnd->GetClientRect(&rect); //获取Picture Control控件的客户区

	CDC* pDC = pWnd->GetDC();//获取picture control的DC

	int oldMode = SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式
	img.StretchBlt(pDC->m_hDC, rect, SRCCOPY);//从源矩形中复制一个位图到目标矩形，按目标设备设置的模式进行图像的拉伸或压缩
	SetStretchBltMode(pDC->m_hDC, oldMode);
	ReleaseDC(pDC);
}
*/
