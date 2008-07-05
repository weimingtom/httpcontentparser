#ifndef _UTILITY_FD_SET_UTILITY_H__
#define _UTILITY_FD_SET_UTILITY_H__

fd_set* FDSET_Add(fd_set * a, fd_set * b);		// 将A中元素加到B中
fd_set* FDSET_Add(fd_set * a, SOCKET   s);	
fd_set* FDSET_Set(fd_set * a, fd_set * b);		// 使得A=B
fd_set* FDSET_Del(fd_set * a, fd_set * b);		// 从A中删除所有B中元素
fd_set* FDSET_Del(fd_set * a, SOCKET   s);

#endif
