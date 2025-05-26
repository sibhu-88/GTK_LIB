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
    save_books(books);
}

// Function to handle the "clicked" signal for the "add" button
void add_book_callback(GtkWidget *widget, gpointer data)
{
    GtkWidget **book_entries = (GtkWidget **)data;
    const char *title = gtk_entry_get_text(GTK_ENTRY(book_entries[0]));
    const char *author = gtk_entry_get_text(GTK_ENTRY(book_entries[1]));
    const char *copy_str = gtk_entry_get_text(GTK_ENTRY(book_entries[2]));
    int copy = atoi(copy_str);

    if (strlen(title) == 0 || strlen(author) == 0 || copy <= 0)
    {
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                                         GTK_MESSAGE_ERROR,
                                                         GTK_BUTTONS_OK,
                                                         "Please fill in all fields correctly.");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
        return;
    }

    add_book_to_list(title, author, copy, &books);

    // Clear the entry fields
    gtk_entry_set_text(GTK_ENTRY(book_entries[0]), "");
    gtk_entry_set_text(GTK_ENTRY(book_entries[1]), "");
    gtk_entry_set_text(GTK_ENTRY(book_entries[2]), "");

    // Show a success message
    GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_INFO,
                                                       GTK_BUTTONS_OK,
                                                       "Book added successfully.");
    gtk_dialog_run(GTK_DIALOG(success_dialog));
    gtk_widget_destroy(success_dialog);
}

void issueBook_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget **widget = (GtkWidget **)user_data;

    const gchar *book_id_text = gtk_entry_get_text(GTK_ENTRY(widget[0]));
    const gchar *student_name = gtk_entry_get_text(GTK_ENTRY(widget[1]));
    const gchar *student_id_text = gtk_entry_get_text(GTK_ENTRY(widget[2]));
    GtkWidget *calendar = widget[3];
    Book **books = (Book **)widget[4];


    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);

    char issue_date[20];
    sprintf(issue_date, "%04d-%02d-%02d", year, month + 1, day);

    // Example: use book_id_text, student_id_text, student_name, and issue_date
    printf("Issuing Book ID: %s to %s (ID: %s) on %s\n", book_id_text, student_name, student_id_text, issue_date);

    // Now you can use *(data->books) to access the book list
}
