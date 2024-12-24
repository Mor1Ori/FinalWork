
// FinalWorkDlg.h: 头文件
//
#include "CImageProcess.h"
#pragma once
#define WM_UPDATE_LISTBOX (WM_USER + 100)


// CFinalWorkDlg 对话框
class CFinalWorkDlg : public CDialogEx
{
// 构造
public:
	CFinalWorkDlg(CWnd* pParent = nullptr);	// 标准构造函数
	LRESULT OnUpdateListBox(WPARAM wParam, LPARAM lParam);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINALWORK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void AddPicture();
	CImageProcess imageProcess;
	CComboBox m_combo;
	afx_msg void BeginProcess();
	CListBox m_list;


	struct ImageInfo
	{
		CString filePath;
		CString status;
	};
	CArray<ImageInfo, ImageInfo&> m_imageList;

	static UINT ProcessImageThread(LPVOID pParam);



	struct ThreadParams
	{
		//Mat src;
		//Mat result;
		int comboIndex;
		CString path;
	};
	afx_msg void ShowResult();
	afx_msg void CancelProcess();
	afx_msg void DeleteImg();
};
