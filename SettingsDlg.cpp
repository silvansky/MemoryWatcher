// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MemoryWatcher.h"
#include "SettingsDlg.h"


// CSettingsDlg dialog

IMPLEMENT_DYNAMIC(CSettingsDlg, CDialog)

CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDlg::IDD, pParent)
{
	m_TimeStep = 1000;
	m_NumSteps = 30;
	m_MaxMem = 20 * 1024 * 1024; // 20 MB
	m_Width = 600;
	m_Height = 400;
}

CSettingsDlg::~CSettingsDlg()
{
}

void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_MAXMEM, m_edtMaxMem);
	DDX_Control(pDX, IDC_EDT_TIME_STEP, m_edtTimeStep);
	DDX_Control(pDX, IDC_EDT_NUMSTEPS, m_edtNumSteps);
	DDX_Control(pDX, IDC_EDT_WIDTH, m_edtWidth);
	DDX_Control(pDX, IDC_EDT_HEIGHT, m_edtHeight);
	DDX_Control(pDX, IDC_CMB_UNITS, m_cmbUnits);
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_CMB_UNITS, &CSettingsDlg::OnCbnSelchangeCmbUnits)
END_MESSAGE_MAP()


// CSettingsDlg message handlers

BOOL CSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString tmp;
	tmp.Format(L"%u", m_MaxMem);
	m_edtMaxMem.SetWindowTextW(tmp);
	tmp.Format(L"%u", m_NumSteps);
	m_edtNumSteps.SetWindowTextW(tmp);
	tmp.Format(L"%u", m_TimeStep);
	m_edtTimeStep.SetWindowTextW(tmp);
	tmp.Format(L"%d", m_Width);
	m_edtWidth.SetWindowTextW(tmp);
	tmp.Format(L"%d", m_Height);
	m_edtHeight.SetWindowTextW(tmp);
	m_cmbUnits.SetCurSel(0);
	last_units = 0;
	return TRUE;
}

void CSettingsDlg::OnOK()
{
	CString tmp;
	m_edtMaxMem.GetWindowTextW(tmp);
	int k, i;
	i = m_cmbUnits.GetCurSel();
	switch (i)
	{
	case 0:
		{
			k = 1;
			break;
		}
	case 1:
		{
			k = 1024;
			break;
		}
	case 2:
		{
			k = 1024 * 1024;
			break;
		}
	default:
		{
			k = 1;
		}
	}
	m_MaxMem = ULONG(abs(_wtof(tmp.GetBuffer()) * k));
	m_edtNumSteps.GetWindowTextW(tmp);
	m_NumSteps = abs(_wtoi(tmp.GetBuffer()));
	m_edtTimeStep.GetWindowTextW(tmp);
	m_TimeStep = abs(_wtoi(tmp.GetBuffer()));
	m_edtWidth.GetWindowTextW(tmp);
	m_Width = abs(_wtoi(tmp.GetBuffer()));
	m_edtHeight.GetWindowTextW(tmp);
	m_Height = abs(_wtoi(tmp.GetBuffer()));
	if ( (!m_MaxMem) || (!m_NumSteps) || (!m_TimeStep) || (!m_Width) || (!m_Height) )
	{
		MessageBox(L"Invalid values!", L"Error!", MB_ICONERROR);
		return;
	}
	CDialog::OnOK();
}

void CSettingsDlg::OnCbnSelchangeCmbUnits()
{
	int i;
	i = m_cmbUnits.GetCurSel();
	if (i == last_units) return; // nothing to do
	CString tmp;
	m_edtMaxMem.GetWindowTextW(tmp);
	ULONG t = ULONG(_wtof(tmp.GetBuffer()));
	int k = last_units - i;
	switch(k)
	{
	case 1:
		{
			t *= 1024;
			break;
		}
	case 2:
		{
			t *= 1024 * 1024;
			break;
		}
	case -1:
		{
			t /= 1024;
			break;
		}
	case -2:
		{
			t /= 1024 * 1024;
			break;
		}
	default:
		{
			// do nothing
		}
	}
	last_units = i;
	tmp.Format(L"%u", t);
	m_edtMaxMem.SetWindowTextW(tmp);
}
