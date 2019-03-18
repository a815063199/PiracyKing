#pragma once
#include "utility.hpp"

int connect_server(char* server_ip, int server_port);

class CSocketRecv
{
public:
	CSocketRecv(int* pkq, int* pfd, TASK_QUE* ptask);
	~CSocketRecv();

	void operator()();

private:
    int* 			m_pKq;
    int*			m_pServerSockfd;
    TASK_QUE*    	m_pQueTaskData;
};

class CSocketSend
{
public:
	CSocketSend(TASK_QUE* p, int* pKq);
	~CSocketSend();

	void operator()();

private:
    TASK_QUE* 	m_pQueSendMsg;
    int* 		m_pKq;
};

class CTaskProc
{
public:
    CTaskProc(TASK_QUE* p1, TASK_QUE* p2, EVENT_NOTICE* p3);
    ~CTaskProc();

    void operator()();

private:
    TASK_QUE* 		m_pQueSendMsg;
    TASK_QUE* 		m_pQueTaskData;
    EVENT_NOTICE*	m_pEventNotice;
};

class CClientMng
{
public:
	CClientMng();
	~CClientMng();

public:
	void start();

	int regist();

	int login();

	int logout();

	int init(std::string ip, int port);

	void recv_muticast();

	void recv_broadcast();

	void game_start();

private:
	
    int connect_server(std::string ip, int port);

    int init_thread();

private:
	CSocketRecv 	m_socketRecv;

	CSocketSend		m_socketSend;

	CTaskProc		m_taskProc;

private:
	int             m_nKq;

    int             m_nServerSockfd;
    
	SOCKETFD_QUE 	m_queSocketFD;

	TASK_QUE 		m_queTaskData;

	TASK_QUE 		m_queSendMsg;

	EVENT_NOTICE  	m_cEventNotice;


};
