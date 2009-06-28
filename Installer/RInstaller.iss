; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{005ECA83-394D-4D5E-A42D-10F1E22AAE95}
AppName=Family007
AppVerName=Family007 2.3
AppPublisherURL=http://www.family007.com/
AppSupportURL=http://www.family007.com/
AppUpdatesURL=http://www.family007.com/
DefaultDirName={pf}\Family007
DisableDirPage=No
DefaultGroupName=Family007
DisableProgramGroupPage=No
LicenseFile=D:\workspace\current\Installer\License.txt
OutputDir=D:\workspace
OutputBaseFilename=Family007
Compression=lzma
SolidCompression=yes

[Languages]
Name: english; MessagesFile: compiler:Default.isl

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked

[Files]
Source: ..\Release\exts.dll; DestDir: {app}; Flags: restartreplace uninsrestartdelete
Source: ..\Release\PCCtrller.exe; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion
Source: ..\Release\mfc71.dll; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion
Source: ..\Release\msvcp71.dll; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion
Source: ..\Release\msvcr71.dll; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion
Source: ..\Release\nwist.dll; DestDir: {app}; Flags: replacesameversion uninsneveruninstall onlyifdoesntexist
Source: ..\Release\PacketsGrasper.dll; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion
Source: ..\Release\Repair.exe; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion
Source: ..\Release\WinLock.dll; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion
Source: ..\Release\zlib1.dll; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion
Source: ..\Release\wsut.dll; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion
Source: ..\Release\nwrs.exe; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion
Source: ..\Release\logger.dll; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion
Source: ..\Release\Family007.exe; DestDir: {app}; Flags: restartreplace uninsrestartdelete replacesameversion; AfterInstall : EnableAutoRun
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
[Icons]
Name: {group}\Websnow; Filename: {app}\Family007.exe
Name: {commondesktop}\Websnow; Filename: {app}\Family007.exe; Tasks: desktopicon
Name: {group}\{cm:UninstallProgram, Websnow}; Filename: {uninstallexe}

[Run]



Filename: {app}\nwrs.exe; Parameters: /service; Tasks: ; Languages: 
Filename: {app}\Repair.exe; Parameters: /silence /installer
[Code]
//importing a custom DLL function, first for Setup, then for uninstall
function CheckProgram(lpStatus: String):Integer;
external 'CheckProgram@{app}\wsut.dll stdcall uninstallonly';

function CheckStatus(lpStatus: String):Integer;
external 'CheckStatus@{app}\wsut.dll stdcall uninstallonly';

function CallUtility(lpStatus: String):Integer;
external 'CallUtility@{app}\wsut.dll stdcall uninstallonly';

var
ResultCode : Integer;
Status : Integer;
MsgForm: TSetupForm ;
PwdEdit: TPasswordEdit;
ShouldExitDirectly : Boolean;		{检测密码是否失败}
ChkPwdSucc : Boolean;	{检测密码成功}
 LaunchAsWindow: TNewCheckBox; {开机随windows一起启动}

function CheckString(Password : String) : Boolean;
begin
  {检测password}
  if Password = '' then begin
     MsgBox('You must enter the password.', mbError, MB_OK);
     Result := False;
  end else begin
    Status := CheckStatus(Password);
    if (0 = Status) then begin
      {注销服务}
      ChkPwdSucc := True;		{检测密码成功， 保存在变量当中}
      CallUtility(Password);		{调用卸载其他部分的代码}
      Result := True;
    end else begin
      MsgBox('Wrong password.', mbError, MB_OK);
      Result := False
    end;
  end;
end;

 {在PASSWORD界面按下OK按钮}
procedure PwdFormOK(Sender: TObject);
begin
	if CheckString(PwdEdit.Text) = True then begin
		MsgForm.Close();
	end else begin
		MsgBox('The password you entered is not correct. Please try again.', mbError, MB_OK);
	end;
end;

{在PASSWORD界面按下Cancel按钮}
procedure PwdFormCancel(Sender: TObject);
begin
	 if ExitSetupMsgBox() = True then
	begin
		ShouldExitDirectly := True;
		MsgForm.Close();
	end;
end;

procedure MsgFormClose(Sender: TObject; var CanClose: Boolean);
begin
	if ChkPwdSucc = False then begin
		CanClose := ExitSetupMsgBox();
	end;
end;

procedure CheckPwdMsgBox();
var
  MsgLabel: TLabel;
  MsgOkButton:TButton;
  MsgCancelButton:TButton;
begin
  MsgForm:= CreateCustomForm();
  MsgForm.ClientWidth := ScaleX(400);
  MsgForm.ClientHeight := ScaleY(120);
  MsgForm.OnCloseQuery := @MsgFormClose;
  MsgForm.Caption := 'Check password';
  MsgForm.Center;

  {标签}
  MsgLabel := TLabel.Create(MsgForm);
  MsgLabel.Parent := MsgForm;
  MsgLabel.Left := ScaleX(20);
  MsgLabel.Top := ScaleY(20);
  MsgLabel.Caption:= 'Please provide the password, then click OK to continue. Passwords are case-sensitive.';
  MsgLabel.Parent := MsgForm;

  {密码}
  PwdEdit:=TPasswordEdit.Create(MsgForm);
  PwdEdit.Parent := MsgForm;
  PwdEdit.Width := ScaleX(MsgForm.ClientWidth - 40);
  PwdEdit.Height := ScaleY(23);
  PwdEdit.Left := ScaleX(20);
  PwdEdit.Top := ScaleY(40);

  MsgOkButton := TButton.Create(MsgForm);
  MsgOkButton.Parent := MsgForm;
  MsgOkButton.Width := ScaleX(75);
  MsgOkButton.Height := ScaleY(23);
  MsgOkButton.Left := MsgForm.ClientWidth - MsgOkButton.Width*2 - ScaleX(30);
  MsgOkButton.Top := MsgForm.ClientHeight - ScaleY(23 + 10);
  MsgOkButton.Caption := 'OK';
  MsgOkButton.OnClick := @PwdFormOK;

  MsgCancelButton := TButton.Create(MsgForm);
  MsgCancelButton.Parent := MsgForm;
  MsgCancelButton.Width := ScaleX(75);
  MsgCancelButton.Height := ScaleY(23);
  MsgCancelButton.Left := MsgForm.ClientWidth - MsgCancelButton.Width - ScaleX(20);
  MsgCancelButton.Top := MsgForm.ClientHeight - ScaleY(23 + 10);
  MsgCancelButton.Caption := 'Cancel';
  MsgCancelButton.OnClick := @PwdFormCancel;

  MsgForm.ShowModal()
end;

{开机自动运行选项}
procedure EnableAutoRun() {
	RegWriteExpandStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Run', 'Websnow',  ExpandConstant('{app}')+'\Family007.exe');
}
function AutoRunText(Sender: TWizardPage): Boolean;
begin
	if LaunchAsWindow.Checked = True then begin
		EnableAutoRun();
	end;
	Result:=True;
end;
procedure AutoRunCustomWizard();
var
 Page: TWizardPage;
begin

	Page := CreateCustomPage(wpSelectProgramGroup, 'Autorun as windows start', 'TButton and others');
	Page.OnNextButtonClick := @AutoRunText
	LaunchAsWindow := TNewCheckBox.Create(Page);
	LaunchAsWindow.Top := ScaleY(30);
	LaunchAsWindow.Width := Page.SurfaceWidth;
	LaunchAsWindow.Height := ScaleY(17);
	LaunchAsWindow.Caption := 'Auto run';
	LaunchAsWindow.Checked := True;
	LaunchAsWindow.Parent := Page.Surface;
end;

procedure InitializeWizard();
begin
	{AutoRunCustomWizard();} {不在弹出对话框，无论什么时候都直接修改成自动安装}
end;
{弹出对话框}
function InitializeUninstall(): Boolean;
begin
	ShouldExitDirectly := False;
	ChkPwdSucc := True;
    CheckPwdMsgBox();
    if ShouldExitDirectly = True then begin
		Result := False;
	end else begin
		Result:=True
	end;
end;

function UninstallNeedRestart(): Boolean;
begin
  Result := True;
end;
[UninstallRun]
Filename: {app}\Repair.exe; Parameters: /uninstaller
