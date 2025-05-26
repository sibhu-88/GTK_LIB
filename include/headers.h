#ifndef HEADERS_H
#define HEADERS_H
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name[100];
    int id;
    char issue_date[100];
    char return_date[100];
} issue;

typedef struct book {
    int book_id;          
    char title[100];
    char author[100];
    int copy;              
    int total_issues;       
    issue *issues;          
    struct book *next;
} Book;


#endif
