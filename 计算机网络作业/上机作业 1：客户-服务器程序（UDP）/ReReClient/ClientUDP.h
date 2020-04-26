#pragma once

// ClientUDP 命令目标

class ClientUDP : public CAsyncSocket
{
public:
	ClientUDP();
	virtual ~ClientUDP();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


