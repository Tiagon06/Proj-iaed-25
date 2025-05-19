/**
 * the file that defines all consts, structs and includes all libraries
 * @file: sys.h
 * @author: ist1113628 (Tiago Nogueira)
 */

#pragma once

/*----------all libraries used-----------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* -------------------------consts----------------------------*/
#define BUFMAX		   65536 // Max per input
#define MAXBATCHDIGITS 21	 // Max digits per batch
#define MAXBATCHS	   1000  // Max number of batches
#define MAXVACNAME	   50	 // Max digits per vaccine
#define TABLESIZE	   10007 // size of the hastable

/* -------------------------errors----------------------------*/
// error for too many vaccines
#define EMANYVAC	(sys->lang)?\
	"too many vaccines" : "demasidas vacinas"
// error for duplicate batch number
#define EDUPBATCH	(sys->lang)?\
	"duplicate batch number" : "número de lote duplicado"
// error for invalid batch
#define EINVBATCH	(sys->lang)?\
	"invalid batch" : "lote inválido"
// error for invalid name
#define EINVNAME	(sys->lang)?\
	"invalid name" : "nome inválido"
// error for invalid date
#define EINVDATE	(sys->lang)?\
	"invalid date" : "data inválida"
// error for invalid quantity
#define EINVQUANT	(sys->lang)?\
	"invalid quantity" : "quantidade inválida"
// error for no such vaccine
#define ENOVAC		(sys->lang)?\
	"no such vaccine" : "vacina inexistente"
// error for no stock
#define ENOSTOCK	(sys->lang)?\
	"no stock" : "esgotado"
// error for already vaccinated
#define EALREADYVAC (sys->lang)?\
	"already vaccinated" : "já vacinado"
// error for no such batch
#define ENOBATCH	(sys->lang)?\
	"no such batch" : "lote inexistente"
// error for no such user
#define ENOUSER		(sys->lang)?\
	"no such user" : "utente inexistente"
// error for no memory
#define ENOMEM		(sys->lang)?\
	"no memory" : "sem memória"
#define EINVCOM      (sys->lang)?\
    "invalid command" : "comando inválido"

/*---------------------the struct of the program-------------------------*/
typedef struct{
	short day;
	short month;
	short year;
}Date; // struct for date

typedef struct{
	char *name;
	char *vac_name;
	char *batch;
	Date date;
}User; // struct for innocs

typedef struct {
	char *batch;
	char *vac_name;
	Date date;
	int doses_remain;
	int doses_used;
}Batch; // struct for batches

typedef struct {
	int *index;
	int cnt; // number of collisions
} Index_User; // location of innocs on user

typedef struct{
	User *user;
	Batch batch[MAXBATCHS];
	int cnt_batch; // number of batches on sys
	int cnt_user; // number of innocs on sys
	Date today_date;
	short lang; // the language
	Index_User table[TABLESIZE]; // hashtable
}Sys; // the system data
