#pragma once

class PCCtrllerApp : public CWinApp
{
public:
	PCCtrllerApp(void);
	~PCCtrllerApp(void);

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	int getAppModel() const { return appmodel_;}
	
private:
	int initializeAppModel();
	int  appmodel_;
};

extern PCCtrllerApp theApp;