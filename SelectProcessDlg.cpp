// SelectProcessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MemoryWatcher.h"
#include "SelectProcessDlg.h"
#include <psapi.h>

// CSelectProcessDlg dialog

IMPLEMENT_DYNAMIC(CSelectProcessDlg, CDialog)

CSelectProcessDlg::CSelectProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectProcessDlg::IDD, pParent)
{

}

CSelectProcessDlg::~CSelectProcessDlg()
{
}

void CSelectProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_PROCESSES, m_cmbProcesses);
}


BEGIN_MESSAGE_MAP(CSelectProcessDlg, CDialog)
END_MESSAGE_MAP()


// CSelectProcessDlg message handlers

BOOL CSelectProcessDlg::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	// initialization
	DWORD cbNeeded;
	EnumProcesses(procs, sizeof(procs), &cbNeeded);
	numprocs = cbNeeded / sizeof(DWORD);
	HANDLE hProcess;
	HMODULE hMod;
	wchar_t str[255];
	for (int i = 0; i < numprocs; i++)
	{
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, procs[i]);
		if (hProcess)
		{
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			{
				GetModuleBaseName(hProcess, hMod, str, 255);
				m_cmbProcesses.AddString(str);
				m_cmbProcesses.SetItemDataPtr(m_cmbProcesses.GetCount() - 1, (void*)&procs[i]);
			}
			CloseHandle(hProcess);
		}
	}
	return TRUE;
}

void CSelectProcessDlg::OnOK()
{
	int i = m_cmbProcesses.GetCurSel();
	if (i != -1)
	{
		m_ProcessID = *(DWORD*)m_cmbProcesses.GetItemDataPtr(i);
		m_cmbProcesses.GetWindowTextW(m_ProcessName);
	}
	else
	{
		MessageBox(L"You must select process!", L"Error!", MB_ICONERROR);
		return;
	}
	CDialog::OnOK();
}

void CSelectProcessDlg::OnCancel()
{
	m_ProcessID = 0;
	m_ProcessName = CString(L"(none)");
	CDialog::OnCancel();
}

DWORD CSelectProcessDlg::GetSelectedProcessID(void)
{
	return m_ProcessID;
}

CString CSelectProcessDlg::GetSelectedProcessName(void)
{
	return m_ProcessName;
}

CString GetCurrentProcessName()
{
	CString res(L"ERROR");
	HMODULE hMod;
	DWORD cbNeeded;
	wchar_t str[255];
	if (EnumProcessModules(GetCurrentProcess(), &hMod, sizeof(hMod), &cbNeeded))
		if (GetModuleBaseName(GetCurrentProcess(), hMod, str, 255))
			res.Format(L"%s", str);
	return res;
}
