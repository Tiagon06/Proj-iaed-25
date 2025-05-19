/**
 * this file declares all functions that are used across files
 * @file: init.h
 * @author: ist1113628 (Tiago Nogueira)
 */

#pragma once
#include "./sys.h"

/*--------------------------------actions------------------------------------*/
void create_batch(Sys *sys,char *buff);			 // c action
void list_batches(Sys *sys, char *buff);			 // l action
void apply_vaccine(Sys *sys, char *buff);		 // a action
void delete_batch(Sys *sys, char *buff);		 // r action
void delete_user(Sys *sys, char *buff);			 // d action
void list_history_of_user(Sys *sys, char *buff); // u action
void time_forward(Sys *sys, char *buff);		 // t action
/*---------------------------------prints------------------------------------*/
void print_batch(Batch *batch); // print an entire batch
void print_user(User *user);	// print an entire user
                                //puts the d errors based on m
void print_errors_d(Sys *sys, char *username, char *batch, int m);
/*----------------------------verifies/validate------------------------------*/
int validated_date(Date); // return 1 if valid date or 0 if invalid
// return 1 if arguments are valid to save the batch or 0 if invalid
int validate_c_args(Sys *sys, Batch batch);
// return true if not deleted and false if deleted
int verify_not_deleted(User *user);
// verify the arguments of buffer for d action and returns the mode(j) founded
int verify_args_d(Sys *sys, char *username, char *batch, Date date, int n);
// check if the memory was well allocated
void verify_mem(Sys *sys, void *a);
int eh_batch(char *batch); // return 1 if valid batch or 0 if invalid
/*-----------------------------------frees-----------------------------------*/
void free_user(User *user); // free an user allocated memory
void free_batch(Batch *batch); // free a batch allocated memory
void free_sys(Sys *sys); // free the system allocated memory
/*----------------------------------compares---------------------------------*/
// same retuns 0; a_bigger returns 1; b_bigger retuns -1 
int datecmp(Date date_a, Date date_b); 
// compares 2 users based on mode (n) and returns mode(n) if same or 0 if not
int usercmp_for_d(User *user, char *username, char *batch, Date date, int n);
/*----------------------------------hashtable--------------------------------*/
// get the index of the key on the table
unsigned int hashFunction(const char* key);
// insert the index of the innoc on the hash table
void insert(Sys *sys, const char *key);
// delete index of innoc on hash table
void delete_hash(Sys *sys, int i);
/*--------------------------------aux_functions------------------------------*/
// return the index where the innoc is or -1 if not founded
int lookup_for_a(Sys *sys, char *key, char *vacname);
// return the index where the innoc is or -1 if not founded
int lookup_for_d(Sys *sys, char *key, Date date, char *batch, int n);
// return number of digits or return -1 if goes beyond the max_digs
int digits_of_buff(int arg, char *buff, int max_digs);
void save_batch(Sys *sys, Batch *batch); // saves the batch on the sys
// return 1 if applied with success or 0 if batch with vacname not found
int applying_vac_to_user(Sys *sys, char *username, char *vacname);
void delete_innoc(Sys *sys, int i); // delete innoc of index i of sys
/*-----------------------------------init------------------------------------*/
// inicialize the system to work properlly
void inicialize_sys(Sys *sys);
// the sorting algoritm for batch when created
void insertion_sort_batch(Sys *sys);
