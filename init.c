/**
 * the initialize functions and the sorting are here
 * @file: init.c
 * @author: ist1113628 (Tiago Nogueira)
 */

#include "./init.h"

/** inicialize the system to work properlly **/
// @param sys       system information
void inicialize_sys(Sys *sys) {
	sys->today_date.day = 1;
	sys->today_date.month = 1;
	sys->today_date.year = 2025;
	sys->lang = 1;
	sys->cnt_user = 0;
	sys->cnt_batch = 0;
	for (int i = 0; i < TABLESIZE; i++) {
		sys->table[i].cnt = 0;
	}
	return;
}

/** the sorting algoritm **/
// @param sys       system information
void insertion_sort_batch(Sys *sys) {
	int j = sys->cnt_batch - 1;
    // element to sort (the rest is already sorted)
	Batch batch = sys->batch[j]; 
	j--;
    // find the place to insert and insert it
	while (j >= 0 && (datecmp(batch.date, sys->batch[j].date) < 0
			|| (datecmp(batch.date, sys->batch[j].date) == 0
			&& strcmp(batch.batch, sys->batch[j].batch) < 0))) {
		sys->batch[j + 1] = sys->batch[j];
		j--;
	}
	sys->batch[j + 1] = batch;
}
