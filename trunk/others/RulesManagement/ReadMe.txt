========================================================================
    �ģ��� : RulesManagement ��Ŀ�ſ�
========================================================================

Ӧ�ó�����Ϊ����������� RulesManagement ��Ŀ����������
��д��̬���ӿ�(DLL)����㡣

���ļ�����
�����Ŀ��ÿ���ļ�������ժҪ��

RulesManagement.vcproj
    ������Ӧ�ó��������ɵ� VC++ ��Ŀ������Ŀ�ļ���
    �������й����ɴ��ļ��� Visual C++ �汾����Ϣ���Լ�
    �й�ʹ��Ӧ�ó�����ѡ���
    ƽ̨�����ú���Ŀ���ܵ���Ϣ��

RulesManagement.idl
    ���ļ�������Ŀ�ж�������Ϳ⡢
    �ӿں� co-class �� IDL ���塣
    ���ļ����� MIDL ����������������:
        C++ �ӿڶ���� GUID ����(RulesManagement.h)
        GUID ����(RulesManagement_i.c)
        ���Ϳ�(RulesManagement.tlb)
        ���ʹ������(RulesManagement_p.c and dlldata.c)

RulesManagement.h
    ���ļ������� RulesManagement.idl �ж������� C++
    �ӿڶ���� GUID �����������ڱ����ڼ��� MIDL �������ɡ�
RulesManagement.cpp
    ���ļ���������ӳ��� DLL ������ʵ�֡�
RulesManagement.rc
    ���ǳ���ʹ�õ����� Microsoft Windows ��Դ
    ���б�

RulesManagement.def
    ��ģ�鶨���ļ�Ϊ�������ṩ�й� DLL �����
    ��������Ϣ���������������ݵĵ���:
        DllGetClassObject  
        DllCanUnloadNow    
        GetProxyDllInfo    
        DllRegisterServer	
        DllUnregisterServer

/////////////////////////////////////////////////////////////////////////////
������׼�ļ�:

StdAfx.h��StdAfx.cpp
    ��Щ�ļ�����������Ϊ RulesManagement.pch
    ��Ԥ����ͷ(PCH)�ļ��Լ���Ϊ StdAfx.obj ��Ԥ���������ļ���

Resource.h
    ���Ƕ�����Դ ID �ı�׼ͷ�ļ���

/////////////////////////////////////////////////////////////////////////////
����/���(stub) DLL ��Ŀ��ģ�鶨���ļ�:

RulesManagementps.vcproj
    ���ļ������ɴ���/���(stub) DLL (���б�Ҫ)����Ŀ�ļ���
	����Ŀ�е� IDL �ļ��������ٰ���һ���ӿڣ����ұ���
	�����ɴ���/���(stub) DLL ֮ǰ�ȱ��� IDL �ļ���	�˹�������
	dlldata.c��RulesManagement_i.c �� RulesManagement_p.c����Щ��
	���ɴ���/���(stub) DLL ����ġ�

RulesManagementps.def
    ��ģ�鶨���ļ�Ϊ�������ṩ
    �йش���/���(stub) ����ĵ�������Ϣ��
/////////////////////////////////////////////////////////////////////////////
