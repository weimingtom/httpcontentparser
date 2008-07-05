#include "stdafx.h"
#include ".\fd_set_utility.h"
#include <assert.h> 

fd_set* FDSET_Add(fd_set * a, fd_set * b) {
	if (a == NULL || b == NULL) return NULL;

	for (int i=0; i < b->fd_count; ++i) {
		if (FD_ISSET(b->fd_array[i], a) == false)
			FD_SET(b->fd_array[i], a);
	}

	return a;
}
fd_set* FDSET_Add(fd_set * a, SOCKET   s) {
	if (a == NULL) return NULL;
	if (FD_ISSET(s, a) == false)
		FD_SET(s, a);
	return a;
}
fd_set* FDSET_Set(fd_set * a, fd_set * b) {
	if (a == NULL || b == NULL) return NULL;
	for (int i = 0; i < b->fd_count; ++i) {
		FD_SET(b->fd_array[i], a);
	}

	return a;
}
fd_set* FDSET_Del(fd_set * a, fd_set * b) {
	if (a == NULL || b == NULL) return NULL;
	for (int i = 0; i < b->fd_count; ++i) {
		FD_CLR(b->fd_array[i], a);
	}
	return a;
}
fd_set* FDSET_Del(fd_set * a, SOCKET   s) {
	if (a == NULL) return NULL;
	FD_CLR(s, a);
	return a;
}