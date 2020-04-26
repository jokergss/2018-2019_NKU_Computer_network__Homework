
// ReReClientDlg.h: 头文件
//

#pragma once
#include "ClientUDP.h"


// CReReClientDlg 对话框
class CReReClientDlg : public CDialogEx
{
// 构造
public:
	CReReClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RERECLIENT_DIALOG };
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
	// 请求命令
	CEdit cmdText;
	// 服务器地址
	CEdit addressText;
	// 服务器端口号
	CEdit portText;
	// 返回内容
	CEdit replyText;
	// UDP socket
	ClientUDP usock;
	void displayString(CString str);
	afx_msg void OnBnClickedSend();
};
