/**
 * all functions that validate or verify something is on this file
 * @file: validate.c
 * @author: ist1113628 (Tiago Nogueira)
 */

#include "./../libraries/init.h"

/** verify if it is a valid date **/
// @param date      date to verify
// return 0 If invalid
// return 1 if valid
int validated_date(Date date){
	short days[12];
	days[0] = 31;
	// if leap year
	days[1] = (date.year % 4 == 0 && 
			(date.year % 100 != 0 ||date.year % 400 == 0))?
								29 : 28;
	days[2] = 31;
	days[3] = 30;
	days[4] = 31;
	days[5] = 30;
	days[6] = 31;
	days[7] = 31;
	days[8] = 30;
	days[9] = 31;
	days[10] = 30;
	days[11] = 31;
	if (days[date.month-1] < date.day || !(date.month > 0) || 
							!(date.month <= 12))
		// if invalid
		return 0;
	return 1;
}

/** verify if is a valid batch **/
// @param batch     batch id to verify
// return 0 If invalid
// return 1 if valid
int eh_batch(char *batch) {
	int len_batch = strlen(batch);
	if (len_batch > MAXBATCHDIGITS){
		return 0;
	}
    // verify if the digits are hexadecimal
	for (int j = 0; j < len_batch; j++){
		if ((batch[j] < '0' || batch[j] > '9') && \
			(batch[j] > 'F' || batch[j] < 'A')){
			return 0;
		}
	}
	return 1;
}

/** validate the arguments of the buffer for c action **/
// @param sys       the system information
// @param batch     the batch to validate
// return 0 if not valid
// return 1 if valid
int validate_c_args(Sys *sys, Batch batch) {
	if (sys->cnt_batch >= MAXBATCHS) {
		puts(EMANYVAC);
		return 0;
	}
	if (batch.doses_remain < 0) {
		puts(EINVQUANT);
		return 0;
	}
	if (!eh_batch(batch.batch)) {
		puts(EINVBATCH);
		return 0;
	}
	for (int j = 0; j < sys->cnt_batch; j++) {
		if (!strncmp(sys->batch[j].batch,batch.batch,MAXBATCHDIGITS)) {
			puts(EDUPBATCH);
			return 0;
		}
	}
	if (!validated_date(batch.date) ||
		datecmp(batch.date,sys->today_date) < 0) {
		puts(EINVDATE);
		return 0;
	}
	return 1;
}

/** return true if not deleted and false if deleted **/
// @param user      user to verify
int verify_not_deleted(User *user) {
	return user->date.year >= 2025;
}

/** verify the arguments of buffer for d action **/
// @param sys       system information
// @param username  username to verify
// @param batch     batch id to verify
// @param date      date to verify
// @param n         mode to verify
// @return j if mode (j) founded of mode (n)
// (then check the mode founded with the mode needed)
// and compare with the mode(n) that is wanted
int verify_args_d(Sys *sys, char *username, char *batch, Date date, int n) {
	int index = hashFunction(username), j = 0;
	User current_user;
	for (int i = 0; i < sys->table[index].cnt; i++) {
		current_user = sys->user[sys->table[index].index[i]];
        // founded same username
		if (!strcmp(current_user.name, username)) {
			j = 1;
			if (n == 1)
				break;
            // founded same date
			if (datecmp(date, current_user.date) <= 0) {
				j = 4;
				if (n == 4)
					break;
                // founded same batch
				if (!strcmp(batch, current_user.batch))
					return n;
			}
		}
	}
	return j;
}

/** verify if the memory allocation was successful **/
// @param sys       system information
// @param a         variable to verify allocation
void verify_mem(Sys *sys, void *a) {
    // if not well allocated
	if (a == NULL) {
		puts(ENOMEM);
		free_sys(sys);
		free(a);
		exit(1);
	}
}
