// MemoryWatcherDlg.h : header file
//

#pragma once

#include <psapi.h>
#include <queue>
#include "afxwin.h"

#include <fstream>
#include <iostream>
using namespace std;

typedef queue<SIZE_T> p_queue;

// CMemoryWatcherDlg dialog
class CMemoryWatcherDlg : public CDialog
{
// Construction
public:
	CMemoryWatcherDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MEMORYWATCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CImage * img;
	p_queue points;
	p_queue points_pagefile;
	DWORD m_ProcessID;
	UINT m_TimeStep;
	UINT m_NumSteps;
	ULONG m_MaxMem;
	HANDLE h;
	CString m_ProcessName;
	int m_ImgWidth;
	int m_ImgHeight;
	bool running;
	wofstream f;
	SIZE_T peak;
	SIZE_T peak_pagefile;
public:
	void DrawImage(void);
	void OnOK(void);
	void OnCancel(void);
	void Clear(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_btnSelect;
	CButton m_btnSettings;
	afx_msg void OnBnClickedBtnSelect();
	afx_msg void OnBnClickedBtnSettings();
	void Restart(void);
	CButton m_btnPause;
	afx_msg void OnBnClickedBtnPause();
};
