#include "headers.h"
#include "components.h"

void save_all_data(Book *books)
{
    if (books == NULL)
    {
        show_dialog(GTK_MESSAGE_INFO, "Information", "dialog-information",
                    "No books available to Save.",
                    "Please add books to the library first.");
        return;
    }

    // Save book list to books_data.xls
    FILE *book_file = fopen("books_data.xls", "w");

    fprintf(book_file, "Book ID\tTitle\tAuthor\tCopies\tTotal Issues\n");
    Book *current = books;
    while (current != NULL)
    {
        fprintf(book_file, "%d\t%s\t%s\t%d\t%d\n",
                current->book_id, current->title, current->author,
                current->copy, current->total_issues);
        current = current->next;
    }
    fclose(book_file);

    // Save issued book details to issued_books_data.xls
    FILE *issue_file = fopen("issued_books_data.xls", "w");

    fprintf(issue_file, "Book ID\tTitle\tStudent Name\tStudent ID\tIssue Date\tReturn Date\n");
    current = books;
    while (current)
    {
        for (int i = 0; i < current->total_issues; ++i)
        {
            fprintf(issue_file, "%d\t%s\t%s\t%d\t%s\t%s\n",
                    current->book_id,
                    current->title,
                    current->issues[i].name,
                    current->issues[i].student_id,
                    current->issues[i].issue_date,
                    strlen(current->issues[i].return_date) > 0 ? current->issues[i].return_date : "N/A");
        }
        current = current->next;
    }
    fclose(issue_file);

    // ✅ Final single dialog on success
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                               "All book data saved successfully.");
    gtk_window_set_title(GTK_WINDOW(dialog), "Save Complete");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    printf("Data saved to 'books_data.xls' and 'issued_books_data.xls'\n");
}
