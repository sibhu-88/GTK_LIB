#include "headers.h"
#include "callbacks.h"
#include "components.h"

Book *books = NULL;

void dashboard_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    printf("Dashboard clicked!\n");
    create_home(content_box);
}

void addbook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    printf("Add Book clicked!\n");
    add_book(content_box, &books);
}

void bookslist_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    printf("Books List clicked!\n");
    books_list(content_box, books);
}

void sortbooks_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    printf("Sort Books clicked!\n");
    sort_books(content_box, books);
}

void deletebook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    printf("Delete Book clicked!\n");
    delete_book(content_box, &books);
}

void issuebook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    printf("Issue Book clicked!\n");
    issue_book(content_box, &books);
}

void returnbook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    printf("Return Book clicked!\n");
    return_book(content_box, &books);
}

void issueddetails_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    printf("Issued Details clicked!\n");
    issued_details(content_box, books);
}

void save_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    printf("Save clicked!\n");
    save_all_data(books);
}

