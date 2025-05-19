/**
 * all functions that frees allocated memory
 * @file: frees.c
 * @author: ist1113628 (Tiago Nogueira)
 */

#include "./../libraries/init.h"

/** free the allocated memory for an user **/
// @param user		user to free
void free_user(User *user) {
	free(user->name);
	free(user->vac_name);
	free(user->batch);
}

/** free the allocated memory for a batch **/
// @param batch		batch to free
void free_batch(Batch *batch) {
	free(batch->vac_name);
	free(batch->batch);
}

/** free the allocated memory of the system **/
// @param sys		system information to free
void free_sys(Sys *sys) {
	for (int i = 0; i < sys->cnt_user; i++) {
		if (verify_not_deleted(&sys->user[i]))
			free_user(&sys->user[i]);
	}
	for (int i = 0; i < sys->cnt_batch; i++) {
		free_batch(&sys->batch[i]);
	}
	for (int i = 0; i < TABLESIZE; i++) {
		if (sys->table[i].cnt)
			free(sys->table[i].index);
	}
	free(sys->user);
	free(sys);
}
