#pragma once
#include "afxwin.h"


// CSettingsDlg dialog

class CSettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingsDlg)

public:
	CSettingsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSettingsDlg();

// Dialog Data
	enum { IDD = IDD_SETTINGSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtMaxMem;
	virtual BOOL OnInitDialog();
	CEdit m_edtTimeStep;
	CEdit m_edtNumSteps;
	CEdit m_edtWidth;
	CEdit m_edtHeight;
	UINT m_TimeStep;
	UINT m_NumSteps;
	ULONG m_MaxMem;
	int m_Width;
	int m_Height;
	int last_units;
protected:
	virtual void OnOK();
public:
	CComboBox m_cmbUnits;
	afx_msg void OnCbnSelchangeCmbUnits();
};
