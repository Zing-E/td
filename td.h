#ifndef TD_H
#define TD_H

#include <stdbool.h>

typedef struct {
	char *name;
	size_t index;
	bool status;
} td_T;

typedef struct TD_LIST_T {
	td_T *td;
	struct TD_LIST_T *next;
	struct TD_LIST_T *prev;
} td_list_T;

td_T *new_td(char *, size_t, bool);
void td_list_insert(td_list_T **, td_T *);
td_list_T *td_list_index(td_list_T *, size_t);
size_t td_list_last_index(td_list_T *);
void td_list_delete(td_list_T **, size_t);
void td_list_free(td_list_T *);

#endif
