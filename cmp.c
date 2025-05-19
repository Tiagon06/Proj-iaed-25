/**
 * all functions that compares something
 * @file: cmp.c
 * @author: ist1113628 (Tiago Nogueira)
 */

#include "init.h"

/** compares 2 dates **/
// @param date_a		date to compare
// @param date_b		date to compare
// @return 1 if date_a bigger
// @return -1 if date_b bigger
// @return 0 if same date
int datecmp(Date date_a, Date date_b) {
	if (date_a.year != date_b.year) {
		if (date_a.year > date_b.year)
			return 1;
		else
			return -1;
	}
	if (date_a.month != date_b.month) {
		if (date_a.month > date_b.month)
			return 1;
		else
			return -1;
	}
	if (date_a.day != date_b.day) {
		if (date_a.day > date_b.day)
			return 1;
		else
			return -1;
	}
	return 0;
}

/** compares 2 users based on mode (n) **/
// @param user		user to get compared
// @param name		name of user 
// @param batch		batch id of user
// @param date		date of user
// @param n			mode to compare
// @return n if same
// @return 0 if different
int usercmp_for_d(User *user, char *name, char *batch, Date date, int n) {
	// n == 1 compare by username
	// n == 4 compare by username and date
	// n == 5 compare by username and date and batch
	if (!strcmp(user->name, name)) {
		if (n == 1)
			return n;
		if (!datecmp(user->date, date)) {
			if (n == 4)
				return n;
			if (!strcmp(user->batch, batch))
				if (n == 5)
					return n;
		}
	}
	// not same
	return 0;
}
