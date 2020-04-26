
// ReReClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ReReClient.h"
#include "ReReClientDlg.h"
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


// CReReClientDlg 对话框



CReReClientDlg::CReReClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RERECLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReReClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REQUESTCOMMAND, cmdText);
	DDX_Control(pDX, IDC_SERVERIP, addressText);
	DDX_Control(pDX, IDC_SERVERPORT, portText);
	DDX_Control(pDX, IDC_WHATRETURNS, replyText);
}

BEGIN_MESSAGE_MAP(CReReClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Send, &CReReClientDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CReReClientDlg 消息处理程序

BOOL CReReClientDlg::OnInitDialog()
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

	addressText.SetWindowTextW(_T("localhost"));
	portText.SetWindowTextW(_T("9630"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CReReClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CReReClientDlg::OnPaint()
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
HCURSOR CReReClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CReReClientDlg::displayString(CString str)
{
	replyText.SetWindowTextW(str);
}



void CReReClientDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码

	CString cmd, host, strport;
	// 获取输入的请求
	cmdText.GetWindowTextW(cmd);
	// 获取输入的 IP
	addressText.GetWindowTextW(host);
	// 获取输入的端口号
	portText.GetWindowTextW(strport);
	int port = _wtoi(strport);

	char cmdchar[4096];

	// 生成 UDP Socket
	BOOL createFlag = usock.Create(0, SOCK_DGRAM, FD_READ);
	if (createFlag == 0)
	{
		MessageBox(_T("Socket create failed."));
		usock.Close();
		return;
	}

	// WideChar 占用空间太大，将其转换为占用较小空间的 Multibyte
	int len = WideCharToMultiByte(CP_ACP, 0, cmd, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, cmd, -1, cmdchar, len, NULL, NULL);

	// 发送请求
	BOOL sendToFlag = usock.SendTo(cmdchar, strlen(cmdchar), port, host, 0);
	if (sendToFlag == 0)
	{
		MessageBox(_T("Message send failed."));
		usock.Close();
		return;
	}
}
