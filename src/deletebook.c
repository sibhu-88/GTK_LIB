#include "headers.h"
#include "components.h"
#include "callbacks.h"

void delete_book(GtkWidget *content_box, Book **books)
{
    if (*books == NULL)
    {
        show_dialog(GTK_MESSAGE_INFO, "Information", "dialog-information",
                    "No books available to Delete.",
                    "Please add books to the library first.");
        return;
    }
    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *delete_book_box;
    GtkWidget *title_label;
    GtkWidget *book_id_label;
    GtkWidget *book_id_entry;
    GtkWidget *grid;
    GtkWidget *delete_button;

    delete_book_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(delete_book_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(delete_book_box, GTK_ALIGN_CENTER);

    title_label = gtk_label_new("Delete Book");
    gtk_widget_set_halign(title_label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(title_label, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(title_label, 10);
    gtk_widget_set_margin_bottom(title_label, 10);
    gtk_widget_set_margin_start(title_label, 10);
    gtk_widget_set_margin_end(title_label, 10);

    book_id_label = gtk_label_new("Book ID:");
    book_id_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(book_id_entry), "Enter Book ID");
    gtk_entry_set_input_purpose(GTK_ENTRY(book_id_entry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_max_length(GTK_ENTRY(book_id_entry), 10);
    gtk_entry_set_width_chars(GTK_ENTRY(book_id_entry), 10);

    delete_button = gtk_button_new_with_label("Delete Book");
    gtk_widget_set_halign(delete_button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(delete_button, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(delete_button, 10);
    gtk_widget_set_margin_bottom(delete_button, 10);
    gtk_widget_set_margin_start(delete_button, 10);
    gtk_widget_set_margin_end(delete_button, 10);
    gtk_widget_set_size_request(delete_button, 200, 30);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_attach(GTK_GRID(grid), title_label, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), book_id_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), book_id_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), delete_button, 0, 2, 2, 1);

    GtkWidget **return_entries = malloc(2 * sizeof(GtkWidget *));
    return_entries[0] = book_id_entry;
    return_entries[1] = (gpointer)books;

    gtk_box_pack_start(GTK_BOX(delete_book_box), grid, TRUE, TRUE, 0);
    g_signal_connect(delete_button, "clicked", G_CALLBACK(deleteButton_clicked), return_entries);

    gtk_container_add(GTK_CONTAINER(content_box), delete_book_box);
    gtk_widget_show_all(content_box);
}

void deleteButton_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget **widget = (GtkWidget **)user_data;
    const char *book_id_text = gtk_entry_get_text(GTK_ENTRY(widget[0]));

    if (!strlen(book_id_text))
    {
        show_dialog(GTK_MESSAGE_WARNING, "Warning", "dialog-warning",
                    "Book ID is missing.",
                    "Please enter the Book ID to delete.");
        return;
    }

    int book_id = atoi(book_id_text);
    Book **books = (Book **)widget[1];
    Book *book = find_book_by_id(*books, book_id);
    // printf("Searching for Book ID: %d\n", book_id);
    if (book != NULL)
    {
        delete_book_from_list(books, book_id);
        gtk_entry_set_text(GTK_ENTRY(widget[0]), "");
        show_dialog(GTK_MESSAGE_INFO, "Success", "dialog-ok",
                    "Book Deleted successfully!",
                    "The book has been removed from the library.");
    }
    else
    {
        show_dialog(GTK_MESSAGE_ERROR, "Error", "dialog-error",
                    "Book Not found.",
                    "An unexpected error occurred while accessing the database.");
    }
    free(widget);
    // printf("Book with ID %d deleted successfully.\n", book_id);
}

void delete_book_from_list(Book **books, int book_id)
{
    Book *current = *books;
    Book *previous = NULL;

    while (current != NULL)
    {
        if (current->book_id == book_id)
        {
            if (previous == NULL)
            {
                *books = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            // printf("In DS function Book with ID %d deleted successfully.\n", book_id);
            return;
        }
        previous = current;
        current = current->next;
    }
}