// ClientUDP.cpp: 实现文件
//

#include "pch.h"
#include "ReReClient.h"
#include "ClientUDP.h"
#include "ReReClientDlg.h"


// ClientUDP

ClientUDP::ClientUDP()
{
}

ClientUDP::~ClientUDP()
{
}


// ClientUDP 成员函数


void ClientUDP::OnSend(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (nErrorCode)
	{
		AfxMessageBox(_T("Error occurred"));
		return;
	}

	CAsyncSocket::OnSend(nErrorCode);
}


void ClientUDP::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	// A buffer for the incoming data.
	char m_szBuffer[4096];
	// What ReceiveFrom Returns.
	int nRead;
	// To save ReceiveFrom IP
	CString host;
	// To save ReceiveFrom Port
	UINT port;
	// 如果错误，需要显示错误信息
	int error;
	CString tempStr;
	CString errStr=_T("Error occurred");
	// 接收服务器的回复
	nRead = ReceiveFrom(m_szBuffer, sizeof(m_szBuffer), host, port,0);

	switch (nRead)
	{
	// 如果未发生错误， ReceiveFrom() 则返回已接收的字节数。 
	// 如果连接已关闭，则返回0。 
	// 否则，将返回值 SOCKET_ERROR，并通过调用 GetLastError() 来检索特定的错误代码。
	case 0:
		// this->Close();
		break;
	case SOCKET_ERROR:
		error = GetLastError();
		tempStr.Format(_T("%d"), error);
		AfxMessageBox(_T("Error occurred: ") + tempStr);
		Close();
	default:
		// terminate the string
		m_szBuffer[nRead] = _T('\0'); 
		CString strTextOut(m_szBuffer);

		// 显示收到的信息
		CReReClientDlg* pdlg = (CReReClientDlg*)AfxGetMainWnd();
		pdlg->displayString(strTextOut);
		this->Close();
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
