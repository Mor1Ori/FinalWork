
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
	ON_BN_CLICKED(IDC_BUTTON2, &CFinalWorkDlg::ShowResult)
	ON_BN_CLICKED(IDC_BUTTON4, &CFinalWorkDlg::CancelProcess)
	ON_BN_CLICKED(IDC_BUTTON5, &CFinalWorkDlg::DeleteImg)
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
	m_combo.InsertString(6, _T("边缘检测"));
	m_combo.InsertString(7, _T("图像滤波"));


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

	ImageInfo info;
	info.filePath = fileName;
	info.status = _T("[待处理]");
	m_imageList.Add(info);
	CString text;
	text.Format(_T("%s - %s"), fileName, info.status);
	m_list.AddString(text);
}

void CFinalWorkDlg::BeginProcess()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_list.GetCurSel() == LB_ERR)
	{
		AfxMessageBox("请选择列表中的一项 ");
	}
	else if (m_combo.GetCurSel() == LB_ERR)
	{
		AfxMessageBox("请选择一种处理方式");
	}
	else
	{
		int index1 = m_combo.GetCurSel();
		int index2 = m_list.GetCurSel();
		CString path = m_imageList[index2].filePath;
		CString status = m_imageList[index2].status;
		if (status == _T("[已取消处理]"))
		{
			AfxMessageBox("该项已被取消");
		}
		else
		{
			ThreadParams* params = new ThreadParams{ index1, path };
			AfxBeginThread(ProcessImageThread, params);
			m_imageList[index2].status = _T("[已处理]");
			AfxGetMainWnd()->PostMessage(WM_UPDATE_LISTBOX, index2, 0);
		}
	}

	
}


UINT CFinalWorkDlg::ProcessImageThread(LPVOID pParam)
{
	ThreadParams* p = (ThreadParams*)pParam;
	int index = p->comboIndex;
	CString path = p->path;
	int pos = path.Find('.');
	CString subRstPath = path.Left(pos);
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
	case 6:
		result = dlg.imageProcess.Edge_Detect(src);
		imwrite(rstPath.GetBuffer(), result);
		break;
	case 7:
		result = dlg.imageProcess.Gaussian_Blur(src);
		imwrite(rstPath.GetBuffer(), result);
		break;
	default:
		break;
	}

	return 0;
}


void CFinalWorkDlg::ShowResult()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_list.GetCurSel() == LB_ERR)
	{
		AfxMessageBox("请选择列表中的一项");
	}
	else
	{
		int index = m_list.GetCurSel();
		CString status = m_imageList[index].status;
		if (status != _T("[已处理]"))
		{
			AfxMessageBox("该项未被处理");
		}
		else
		{
			CString src = m_imageList[index].filePath;
			CString result;
			int pos = src.Find('.');
			CString subRstPath = src.Left(pos);
			result.Format("%sresult.png", subRstPath);

			Mat srcc = imread(src.GetBuffer(), 1);
			Mat rst = imread(result.GetBuffer(), 1);

			
			namedWindow("src", WINDOW_NORMAL);
			namedWindow("result", WINDOW_NORMAL);
			resizeWindow("src", srcc.cols, srcc.rows);
			resizeWindow("result", rst.cols, rst.rows);
			imshow("src", srcc);
			imshow("result", rst);
		}
	}
	
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

void CFinalWorkDlg::CancelProcess()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_list.GetCurSel() == LB_ERR)
	{
		AfxMessageBox("请选择列表中的一项");
	}
	else
	{
		int index = m_list.GetCurSel();
		m_imageList[index].status = _T("[已取消处理]");
		AfxGetMainWnd()->PostMessage(WM_UPDATE_LISTBOX, index, 0);
	}
}


void CFinalWorkDlg::DeleteImg()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_list.GetCurSel() == LB_ERR)
	{
		AfxMessageBox("请选择列表中的一项");
	}
	else
	{
		int index = m_list.GetCurSel();
		CString status = m_imageList[index].status;
		if (status != _T("[已处理]"))
		{
			AfxMessageBox("该项未被处理");
		}
		else
		{
			CString src = m_imageList[index].filePath;
			CString dltpath;
			int pos = src.Find('.');
			CString subRstPath = src.Left(pos);
			dltpath.Format("%sresult.png", subRstPath);
			if (DeleteFile(dltpath))
			{
				AfxMessageBox(_T("文件删除成功"));
			}
			m_list.DeleteString(index);
			m_imageList.RemoveAt(index);
		}

	}
}
