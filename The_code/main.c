/**
 * A program exemplifying a data center of vaccines
 * each batch has a vaccine 
 * @file: main.c
 * @author: ist1113628 (Tiago Nogueira)
 */

#include "./../libraries/init.h"

/**vaccine manager
 * @param argc      the amount of args
 * @param argv      param to decide if is pt or not
 * @return allways 0
 */
int main(int argc,char **argv) {
	Sys *sys = malloc(sizeof(Sys));
	int size = 1000; 
    // inicial size for user
	sys->user = malloc(sizeof(User) * size);
	inicialize_sys(sys);
	verify_mem(sys, sys->user);
	if (argc >= 2) { //set the language
		sys->lang = strcmp("pt",argv[1]);
	}
	char action[BUFMAX];
	while (fgets(action, BUFMAX, stdin)) {
		switch (action[0]) {
			case 'q': free_sys(sys); return 0;
			case 'c': create_batch(sys, action); break;
			case 'l': list_batches(sys, action); break;
			case 'a': apply_vaccine(sys, action); break;
			case 'r': delete_batch(sys, action); break;
			case 'd': delete_user(sys, action); break;
			case 'u': list_history_of_user(sys, action); break;
			case 't': time_forward(sys, action); break;
		}
        // allocate more memory if needed
		if (size <= sys->cnt_user + 10) {
			size += 1000;
			sys->user = realloc(sys->user, sizeof(User) * size);
			verify_mem(sys, sys->user);
		}
	}
}
