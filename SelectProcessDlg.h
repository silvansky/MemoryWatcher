#pragma once
#include "afxwin.h"
//#include <psapi.h>

// CSelectProcessDlg dialog

class CSelectProcessDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectProcessDlg)

public:
	CSelectProcessDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectProcessDlg();

// Dialog Data
	enum { IDD = IDD_SELECTPROCESSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbProcesses;
	BOOL OnInitDialog(void);
private:
	DWORD procs[1024];
	int numprocs;
	DWORD m_ProcessID;
	CString m_ProcessName;
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	DWORD GetSelectedProcessID(void);
	CString GetSelectedProcessName(void);
};

CString GetCurrentProcessName();