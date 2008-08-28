#pragma once
#include "afxwin.h"

#include ".\basedlg.h"
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

// CDlgToolsSetting �Ի���

class CDlgToolsSetting : public CBaseDlg
{
	DECLARE_DYNAMIC(CDlgToolsSetting)

public:
	CDlgToolsSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgToolsSetting();

// �Ի�������
	enum { IDD = IDD_DLG_TOOLS };

	virtual void OnApply();
	virtual void OnShow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGuiGroupBox m_staScreenSaver;
	CGuiGroupBox m_staWebContent;
	CGuiGroupBox m_staProgramHistory;
	virtual BOOL OnInitDialog();
};
