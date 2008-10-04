#ifndef _MAINUI_CDLGSCREENSAVER_H__
#define _MAINUI_CDLGSCREENSAVER_H__

#include ".\basedlg.h"
#include "afxwin.h"
#include <Guilib1.5\GuiCheckBox.h>
#include <Guilib1.5\GuiComboBoxExt.h>
#include <Guilib1.5\GuiLinkButton.h>
#include <Guilib1.5\GuiButton.h>
#include <Guilib1.5\GuiSliderCtrl.h>
#include <Guilib1.5\GuiMiniTool.h>
#include <Guilib1.5\GuiEdit.h> 
#include <Guilib1.5\GuiGroupBox.h>
#include <Guilib1.5\GuiRadioButton.h>
#include <Guilib1.5\GuiComboFont.h>
#include "afxcmn.h"

// CDlgScreenSaver �Ի���

class CDlgScreenSaver : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgScreenSaver)

public:
	CDlgScreenSaver(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgScreenSaver();

// �Ի�������
	enum { IDD = IDD_DLG_SCREEN_SAVER };

	virtual void OnRestore();
	virtual void OnApply();
	virtual void OnShow();

	void initializeSetting();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_staFunction;
	CGuiGroupBox m_staTimespan;
	CGuiGroupBox m_staAutoClear;
	CSliderCtrl m_sliderSaveTimespan;
	CSliderCtrl m_sliderAutoclearTimespan;
	
	BOOL m_bEnableScreensave;
	BOOL m_bEnableAutoclean;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkScreensave();
	afx_msg void OnBnClickedChkAutoclean();
	afx_msg void OnBnClickedBtnClear();
protected:
	void enableAutoSave();
	void enableAutoclean();
};

#endif  // _MAINUI_CDLGSCREENSAVER_H__