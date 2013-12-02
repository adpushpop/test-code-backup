
// ClientDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "../../../Common/Src/socket/TcpClient.h"
#include "../../Global/helper.h"


// CClientDlg dialog
class CClientDlg : public CDialogEx, public CTcpClientListener
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEnChangeContent();
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg LRESULT OnUserInfoMsg(WPARAM wp, LPARAM lp);
	afx_msg int OnVKeyToItem(UINT nKey, CListBox* pListBox, UINT nIndex);
	DECLARE_MESSAGE_MAP()
public:
	void SetAppState(EnAppState state);
private:
	virtual ISocketListener::EnHandleResult OnSend(CONNID dwConnID, const BYTE* pData, int iLength);
	virtual ISocketListener::EnHandleResult OnReceive(CONNID dwConnID, const BYTE* pData, int iLength);
	virtual ISocketListener::EnHandleResult OnClose(CONNID dwConnID);
	virtual ISocketListener::EnHandleResult OnError(CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
	virtual ISocketListener::EnHandleResult OnConnect(CONNID dwConnID);
private:
	CEdit m_Content;
	CButton m_Send;
	CListBox m_Info;
	CEdit m_Address;
	CEdit m_Port;
	CButton m_Async;
	CButton m_Start;
	CButton m_Stop;

	BOOL m_bAsyncConn;
	EnAppState m_enState;
	CTcpClient m_Client;
};
