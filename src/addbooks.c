#include "headers.h"
#include "callbacks.h"
#include "components.h"

void add_book(GtkWidget *content_box, Book **books)
{
    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *add_book_box;
    GtkWidget *title_label;
    GtkWidget *book_title_label;
    GtkWidget *book_title_entry;
    GtkWidget *author_label;
    GtkWidget *author_entry;
    GtkWidget *copy_label;
    GtkWidget *copy_entry;
    GtkWidget *add_button;
    GtkWidget *grid;

    add_book_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(add_book_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(add_book_box, GTK_ALIGN_CENTER);

    gchar *title_markup = g_strdup_printf("<span weight=\"bold\" size=\"16000\">%s</span>", "Add Books");
    title_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title_label), title_markup);
    gtk_widget_set_halign(title_label, GTK_ALIGN_CENTER);
    //gtk_box_pack_start(GTK_BOX(book_list_box), title_label, FALSE, FALSE, 5);
    g_free(title_markup);

    book_title_label = gtk_label_new("Book Title:");
    book_title_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(book_title_entry), "Enter Book Title");
    gtk_entry_set_max_length(GTK_ENTRY(book_title_entry), 100); 
    gtk_entry_set_width_chars(GTK_ENTRY(book_title_entry), 30);
    
    author_label = gtk_label_new("Author:");
    author_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(author_entry), "Enter Author Name");
    gtk_entry_set_max_length(GTK_ENTRY(author_entry), 100);
    gtk_entry_set_width_chars(GTK_ENTRY(author_entry), 30); 

    copy_label = gtk_label_new("Number of Copies:");
    copy_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(copy_entry), "Enter Number of Copies");
    gtk_entry_set_max_length(GTK_ENTRY(copy_entry), 3); 
    gtk_entry_set_width_chars(GTK_ENTRY(copy_entry), 10); 
    gtk_entry_set_input_purpose(GTK_ENTRY(copy_entry), GTK_INPUT_PURPOSE_NUMBER);

    add_button = gtk_button_new_with_label("Add Book");
    gtk_widget_set_halign(add_button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(add_button, GTK_ALIGN_CENTER);
    
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    gtk_grid_attach(GTK_GRID(grid), title_label, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), book_title_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), book_title_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), author_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), author_entry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), copy_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), copy_entry, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), add_button, 0, 4, 2, 1);

    gtk_widget_set_halign(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), 10);
    gtk_widget_set_margin_bottom(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), 10);
    gtk_widget_set_margin_start(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), 10);
    gtk_widget_set_margin_end(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), 10);
   

    // Connect the add button to a function to handle adding the book
    GtkWidget **book_entries = malloc(4 * sizeof(GtkWidget *));
    book_entries[0] = book_title_entry;
    book_entries[1] = author_entry;
    book_entries[2] = copy_entry;
    book_entries[3] = content_box;

    g_signal_connect(add_button, "clicked", G_CALLBACK(add_book_callback), book_entries);

    gtk_box_pack_start(GTK_BOX(add_book_box), title_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(add_book_box), grid, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(content_box), add_book_box);
    gtk_widget_show_all(content_box); // Show all widgets in the container
}

void add_book_to_list(const char *title, const char *author, int copy, Book **books)
{
    Book *new_book = malloc(sizeof(Book));
    if (new_book == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    new_book->book_id = (*books == NULL) ? 1 : (*books)->book_id + 1; // Assign a new book ID
    new_book->total_issues = 0;
    strcpy(new_book->title, title);
    strcpy(new_book->author, author);
    new_book->copy = copy;
    new_book->issues = NULL;

    printf("Adding Book ID:%d book: %s by %s with %d copies\n", new_book->book_id, new_book->title, new_book->author, new_book->copy);

    if ((*books) == NULL)
    {
        new_book->next = *books;
        *books = new_book;
        return;
    }
    else
    {
        Book *current = *books;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_book;
    }
    new_book->next = NULL;
}
