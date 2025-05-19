/**
 * some axuliar functions to help the actions functions
 * @file: aux.c
 * @author: ist1113628 (Tiago Nogueira)
 */

#include "init.h"

/** count the digits and if is bigger than the max_digs return -1 **/
// @param arg       argument number to count
// @param buff      buff to verify
// @param max_digs  the limit of digits
// @return -1 when limit exceded
// @return number_of_digs when limit not exceded
int digits_of_buff(int arg, char *buff, int max_digs) {
	int n = 1, digs = 0;
	for (int j = 2; buff[j] != '\n' && n <= arg; j++) {
        // go to argument asked
		if (buff[j] == ' ')
			n++;
        // start counting
		if (n == arg) {
			digs++;
            // verify if exceded the limit
			if (digs == max_digs)
				return -1;
		}
	}
	return digs;
}

/** saves the batch on the sys **/
// @param sys       system information
// @param batch     batch to save
void save_batch(Sys *sys, Batch *batch) {
	printf("%s\n",batch->batch); // print vatch to save
	sys->batch[sys->cnt_batch].batch = strdup(batch->batch);
	verify_mem(sys, sys->batch[sys->cnt_batch].batch);
	sys->batch[sys->cnt_batch].vac_name = strdup(batch->vac_name);
	verify_mem(sys, sys->batch[sys->cnt_batch].vac_name);
	sys->batch[sys->cnt_batch].doses_remain = batch->doses_remain;
	sys->batch[sys->cnt_batch].doses_used = 0;
	sys->batch[sys->cnt_batch].date = batch->date;
	sys->cnt_batch++;
}

/** apply the vaccine to user and create a innoc **/
// @param sys       system information
// @param username  username to get applied
// @param vacname   vaccine to apply
// @return 1 if well applied
// @return 0 if vaccine not founded
int applying_vac_to_user(Sys *sys, char *username, char *vacname) {
	for (int i = 0; i < sys->cnt_batch; i++) {
        // batch with vaccine founded and applied
		if (!strncmp(sys->batch[i].vac_name,vacname,MAXVACNAME) &&
			datecmp(sys->batch[i].date,sys->today_date) >= 0 &&
			sys->batch[i].doses_remain > 0) {
			Batch batch = sys->batch[i];
			sys->batch[i].doses_remain--;
			insert(sys, username);
			sys->user[sys->cnt_user].batch = strdup(batch.batch);
			verify_mem(sys, sys->user[sys->cnt_user].batch);
			sys->batch[i].doses_used++;
			sys->user[sys->cnt_user].name = strdup(username);
			verify_mem(sys, sys->user[sys->cnt_user].name);
			sys->user[sys->cnt_user].date = sys->today_date;
			sys->user[sys->cnt_user].vac_name = strdup(vacname);
			verify_mem(sys, sys->user[sys->cnt_user].vac_name);
			return 1;
		}
	}
    // not found batch with vaccine asked
	return 0;
}

/** search for an innoc for a **/
// @param sys       system information
// @param username  username of innoc to look_up
// @param vacname   vacname of innoc to look_up
// @return index of finded innoc
// @return -1 if not founded
int lookup_for_a(Sys *sys, char *username, char *vacname) {
	unsigned int index = hashFunction(username);
	User current_user;
	for (int i = 0; i < sys->table[index].cnt; i++) {
		current_user = sys->user[sys->table[index].index[i]];
        // innoc founded return index of innoc
		if (!strncmp(current_user.name, username, BUFMAX) &&
			!strncmp(current_user.vac_name, vacname, MAXVACNAME) &&
			!datecmp(current_user.date,sys->today_date)) {
			return sys->table[index].index[i];
		}
	}
    // innoc not founded
	return -1;
}

/** search for an innoc for d based on mode (n) **/
// @param sys       system information
// @param username  username of innoc to look_up
// @param date      date of innoc to look_up
// @param batch     batch id of innoc to look_up
// @param n         mode to look_up
// @return index of finded innoc
// @return -1 if not founded
int lookup_for_d(Sys *sys, char *username, Date date, char *batch, int n) {
    // n == 1 search by username
    // n == 4 search by username and date
    // n == 5 search by username and date and batch
	unsigned int index = hashFunction(username);
	User current_user;
	for (int i = 0; i < sys->table[index].cnt; i++) {
		current_user = sys->user[sys->table[index].index[i]];
        // innoc founded return index of innoc
		if (!strncmp(current_user.name, username, BUFMAX) &&
			n == 1) {
			return sys->table[index].index[i];
		}
        // innoc founded return index of innoc
		if (!strncmp(current_user.name, username, BUFMAX) &&
			!datecmp(current_user.date, date) &&
			n == 4) {
			return sys->table[index].index[i];
		}
        // innoc founded return index of innoc
		if (!strncmp(current_user.name, username, BUFMAX) &&
			!strncmp(current_user.batch, batch, MAXBATCHDIGITS) &&
			!datecmp(current_user.date, date) &&
			n == 5) {
			return sys->table[index].index[i];
		}
	}
    // innoc not founded
	return -1;
}

/** delete innoc **/
// @param sys       system information
// @param i         index of innoc to delete
void delete_innoc(Sys *sys, int i) {
    // delete on hash_table
	delete_hash(sys, i); 
    // set an invalid date to innoc to say it was deleted
	free_user(&sys->user[i]);
	sys->user[i].date.day = 22;
	sys->user[i].date.month = 5;
	sys->user[i].date.year = 2006;
}
