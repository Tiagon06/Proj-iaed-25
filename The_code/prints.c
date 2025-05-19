/**
 * all print functions
 * @file: prints.c
 * @author: ist1113628 (Tiago Nogueira)
 */

#include "./../libraries/init.h"

/** print the errors based on the what was not found (m) **/
// @param sys       system information
// @param username  username of innoc
// @param batch     batch id of innoc
// @param m         mode that was not founded
void print_errors_d(Sys *sys, char *username, char *batch, int m) {
	if (m == 0) { // username not founded
		printf("%s: ", username);
		puts(ENOUSER);
		return;
	}
	if (m == 1) { // date not founded
		puts(EINVDATE);
		return;
	}
	if (m == 4) { // batch not founded
		printf("%s: ", batch);
		puts(ENOBATCH);
		return;
	}
}

/** print the batch **/
// @param batch     batch to print
void print_batch(Batch *batch) {
	printf("%s %s %.2d-%.2d-%.4d %d %d\n", 
			batch->vac_name, batch->batch, batch->date.day,
			batch->date.month, batch->date.year,
			batch->doses_remain, batch->doses_used);
}

/** print the user **/
// @param user      user to print
void print_user(User *user) {
	printf("%s %s %.2hd-%.2hd-%.4hd\n",user->name,user->batch,\
		   user->date.day,user->date.month,user->date.year);
}
