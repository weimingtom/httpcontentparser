========================================================================
    �ģ��� : Rules_management_exe ��Ŀ�ſ�
========================================================================

Ӧ�ó�����Ϊ����������� Rules_management_exe ��Ŀ����������
��д��ִ���ļ�(EXE)����㡣

���ļ�����
�����Ŀ��ÿ���ļ�������ժҪ��

Rules_management_exe.vcproj
    ������Ӧ�ó��������ɵ� VC++ ��Ŀ������Ŀ�ļ���
    �������й����ɴ��ļ��� Visual C++ �汾����Ϣ���Լ�
    �й�ʹ��Ӧ�ó�����ѡ���
    ƽ̨�����ú���Ŀ���ܵ���Ϣ��

Rules_management_exe.idl
    ���ļ�������Ŀ�ж�������Ϳ⡢
    �ӿں� co-class �� IDL ���塣
    ���ļ����� MIDL ����������������:
        C++ �ӿڶ���� GUID ����(Rules_management_exe.h)
        GUID ����(Rules_management_exe_i.c)
        ���Ϳ�(Rules_management_exe.tlb)
        ���ʹ������(Rules_management_exe_p.c and dlldata.c)

Rules_management_exe.h
    ���ļ������� Rules_management_exe.idl �ж������� C++
    �ӿڶ���� GUID �����������ڱ����ڼ��� MIDL �������ɡ�
Rules_management_exe.cpp
    ���ļ���������ӳ��� WinMain ��ʵ�֡�
Rules_management_exe.rc
    ���ǳ���ʹ�õ����� Microsoft Windows ��Դ
    ���б�


/////////////////////////////////////////////////////////////////////////////
������׼�ļ�:

StdAfx.h��StdAfx.cpp
    ��Щ�ļ�����������Ϊ Rules_management_exe.pch
    ��Ԥ����ͷ(PCH)�ļ��Լ���Ϊ StdAfx.obj ��Ԥ���������ļ���

Resource.h
    ���Ƕ�����Դ ID �ı�׼ͷ�ļ���

/////////////////////////////////////////////////////////////////////////////
����/���(stub) DLL ��Ŀ��ģ�鶨���ļ�:

Rules_management_exeps.vcproj
    ���ļ������ɴ���/���(stub) DLL (���б�Ҫ)����Ŀ�ļ���
	����Ŀ�е� IDL �ļ��������ٰ���һ���ӿڣ����ұ���
	�����ɴ���/���(stub) DLL ֮ǰ�ȱ��� IDL �ļ���	�˹�������
	dlldata.c��Rules_management_exe_i.c �� Rules_management_exe_p.c����Щ��
	���ɴ���/���(stub) DLL ����ġ�

Rules_management_exeps.def
    ��ģ�鶨���ļ�Ϊ�������ṩ
    �йش���/���(stub) ����ĵ�������Ϣ��
/////////////////////////////////////////////////////////////////////////////
