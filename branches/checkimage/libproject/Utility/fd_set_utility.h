#ifndef _UTILITY_FD_SET_UTILITY_H__
#define _UTILITY_FD_SET_UTILITY_H__

fd_set* FDSET_Add(fd_set * a, fd_set * b);		// ��A��Ԫ�ؼӵ�B��
fd_set* FDSET_Add(fd_set * a, SOCKET   s);	
fd_set* FDSET_Set(fd_set * a, fd_set * b);		// ʹ��A=B
fd_set* FDSET_Del(fd_set * a, fd_set * b);		// ��A��ɾ������B��Ԫ��
fd_set* FDSET_Del(fd_set * a, SOCKET   s);

#endif
