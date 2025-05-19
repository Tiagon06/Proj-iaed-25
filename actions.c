/**
 * all actions asked from main
 * @file: actions.c
 * @author: ist1113628 (Tiago Nogueira)
 */

#include "./init.h"

/** asks for a batch if the input is valid save it to the system **/
// @param sys		system information
// @param buff		buffer with the input
void create_batch(Sys *sys,char *buff) {
	// verify digits of batch
	if (digits_of_buff(1, buff, MAXBATCHDIGITS) < 0) {
		puts(EINVBATCH);
		return;
	}
	// verify digits of vac_name
	if (digits_of_buff(4, buff, MAXVACNAME) < 0) {
		puts(EINVNAME);
		return;
	}
	Batch batch;
	batch.batch = malloc(MAXBATCHDIGITS + 5);
	verify_mem(sys, batch.batch);
	batch.vac_name = malloc(MAXVACNAME + 5);
	verify_mem(sys, batch.vac_name);
	if (sscanf(buff, "%*s %s %hd-%hd-%hd %d %s",batch.batch, 
		&batch.date.day, &batch.date.month, &batch.date.year,
		&batch.doses_remain, batch.vac_name) != 6) {
		free_batch(&batch);
		return;
	}
	// verify the inputs
	if (validate_c_args(sys,batch) == 0) {
		free_batch(&batch);
		return;
	}
	// write the batch to the system
	save_batch(sys, &batch);
	// sort the added batch
	insertion_sort_batch(sys);
	free_batch(&batch);
	return;
}

/** print the batches of the asked vaccine or all batches **/
// @param sys		system information
// @param buff		buffer with the input
void list_batches(Sys *sys, char *buff) {
	// remove the final '\n' to strtok work properlly
	buff[strcspn(buff, "\n")] = '\0';
	char *vac_name = strtok(buff," ");
	int n = 0; // analize if the user asked for some vaccine
	vac_name = strtok(NULL," ");
	while (vac_name != NULL) {
		n = 1; // user asked for a vaccine
		for (int i = 0; i < sys->cnt_batch; i++) {
			if (!strcmp(sys->batch[i].vac_name,vac_name)) {
				print_batch(&sys->batch[i]);
				n = 2; // batch with vaccine founded and printed
			}
		}
		// vaccine asked not founded
		if (n == 1) {
			printf("%s: ",vac_name);
			puts(ENOVAC);
		}
		vac_name = strtok(NULL," ");
	}
	// no vaccine asked so print all batches
	if (n == 0) {
		for (int i = 0; i < sys->cnt_batch; i++) {
			print_batch(&sys->batch[i]);
		}
	}
}

/** apply a vaccine to someone and save 
 * the action on the system and print the batch used **/
// @param sys		system information
// @param buff		buffer with the input
void apply_vaccine(Sys *sys, char *buff) {
	char username[BUFMAX], vacname[MAXVACNAME];
	if (buff[2] == '\"') { // verify if the name is between " or not
		if (sscanf(buff, "%*s \"%[^\"]\" %s", username, vacname) != 2) {
			return;
		}
	}
	else {
		if (sscanf(buff, "%*s %s %s", username, vacname) != 2) {
			return;
		}
	}
	// verify if vaccinated today by the vaccine asked
	if (lookup_for_a(sys, username, vacname) >= 0) { 
			puts(EALREADYVAC);
			return;
	}
	// apply the vaccine to the user and print the batch used
	if (applying_vac_to_user(sys, username, vacname)) {
		printf("%s\n",sys->user[sys->cnt_user].batch);
		sys->cnt_user++;
		return;
	}
	puts(ENOSTOCK);
	return;
}

/** delete the batch on the system **/
// @param sys		system information
// @param buff		buffer with the input
void delete_batch(Sys *sys, char *buff) {
	char batch[MAXBATCHDIGITS];
	// no batch inserted
	if (sscanf(buff, "%*s %s", batch) < 1) {
		puts(ENOBATCH);
		return;
	}
	for (int i = 0; i < sys->cnt_batch; i++){
		if (!strcmp(sys->batch[i].batch,batch)){
			// if batch used then make it unusable
			if (sys->batch[i].doses_used > 0){
				sys->batch[i].doses_remain = 0;
				printf("%d\n",sys->batch[i].doses_used);
			}
			// if batch not used delete it from sys
			else{
				printf("%d\n",sys->batch[i].doses_used);
				free_batch(&sys->batch[i]);
				memmove(&sys->batch[i], &sys->batch[i + 1],
					(sys->cnt_batch-i - 1) * sizeof(Batch));
				sys->cnt_batch--;
				}
			return;
			}
		}
	// batch not found
	printf("%s: ",batch);
	puts(ENOBATCH);
	return;
}

/** delete a user innoc by name or date or batch and
 * print number of delections **/
// @param sys		system information
// @param buff		buffer with the input
void delete_user(Sys *sys, char *buff) {
	char username[BUFMAX], batch[MAXBATCHDIGITS];
	Date date;
	// n == 1 by username
	// n == 4 by username and date
	// n == 5 by username and date and batch
	// j == number of delections
	// m == error indicator
	int n, j = 0, m;
	if (buff[2] == '\"') { // if username is between " or not
		if ((n = sscanf(buff, "%*s \"%[\"]\" %hd-%hd-%hd %s", username, 
		   &date.day, &date.month, &date.year, batch)) < 1)
			return;
	}
	else
		if ((n = sscanf(buff, "%*s %s %hd-%hd-%hd %s", username, 
		   &date.day, &date.month, &date.year, batch)) < 1)
			return;
	// m == to what error to print
	if (n != (m = verify_args_d(sys, username, batch, date, n))) {
		print_errors_d(sys, username, batch, m);
		return;
	}
	User current_user;
	int index = hashFunction(username);
	int i = 0;
	while (i < sys->table[index].cnt) {
		current_user = sys->user[sys->table[index].index[i]];
		// user founded then delete and increment j
		if (n == usercmp_for_d(
			&current_user, username, batch, date, n)) {
			delete_innoc(sys, sys->table[index].index[i]);
			j++;
		}else i++; // if not founded one step forward
	}
	printf("%d\n",j); // print delections
}

/** print all innocs of an username asked or 
 * print all innocs if no username asked **/
// @param sys		system information
// @param buff		buffer with the input
void list_history_of_user(Sys *sys, char *buff) {
	char username[BUFMAX];
	int n = 0; // username asked or not
	if ((buff[2] != '\"')? // verify if username between " or not
		sscanf(buff, "%*s %s", username) > 0 :
		sscanf(buff, "%*s \"%[^\"]\"", username) > 0) {
		int index = hashFunction(username);
		n = 1; // username asked
		User current_user;
		for (int i = 0; i < sys->table[index].cnt; i++) {
			current_user = sys->user[sys->table[index].index[i]];
			if (!strcmp(username, current_user.name)) {
				n = 2; // username founded and print
				print_user(&current_user);
			}
		}
		// username asked but not founded
		if (n == 1) {
			printf("%s: ",username);
			puts(ENOUSER);
			return;
		}
	}
	// no user asked so print all innocs
	if (n == 0)
		for (int i = 0; i < sys->cnt_user; i++) {
			// verify if is deleted or not
			if (verify_not_deleted(&sys->user[i])) {
				print_user(&sys->user[i]);
			}
		}
}

/** advance time **/
// @param sys		system information
// @param buff		buffer with the input
void time_forward(Sys *sys, char *buff) {
	Date date;
	if (sscanf(buff, "%*s %hd-%hd-%hd",
		&date.day, &date.month, &date.year) < 3) {
		return;
	}
	// verify if time goes forward and if is valid
	if (!validated_date(date) || datecmp(date, sys->today_date) < 0) {
		puts(EINVDATE);
		return;
	}
	// set new today_date and print the new today_date
	sys->today_date = date;
	printf("%.2hd-%.2hd-%.4hd\n",date.day,date.month,date.year);
	return;
}
