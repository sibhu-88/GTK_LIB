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
    gtk_box_pack_start(GTK_BOX(add_book_box), title_label, FALSE, FALSE, 5);
    g_free(title_markup);

    book_title_label = gtk_label_new("Book Title:");
    book_title_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(book_title_entry), "Enter Book Title");
    gtk_entry_set_input_purpose(GTK_ENTRY(book_title_entry), GTK_INPUT_PURPOSE_FREE_FORM);
    gtk_entry_set_max_length(GTK_ENTRY(book_title_entry), 100);
    gtk_entry_set_width_chars(GTK_ENTRY(book_title_entry), 30);

    author_label = gtk_label_new("Author:");
    author_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(author_entry), "Enter Author Name");
    gtk_entry_set_input_purpose(GTK_ENTRY(author_entry), GTK_INPUT_PURPOSE_FREE_FORM);
    gtk_entry_set_max_length(GTK_ENTRY(author_entry), 100);
    gtk_entry_set_width_chars(GTK_ENTRY(author_entry), 30);

    copy_label = gtk_label_new("Number of Copies:");
    copy_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(copy_entry), "Enter Number of Copies");
    gtk_entry_set_input_purpose(GTK_ENTRY(copy_entry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_max_length(GTK_ENTRY(copy_entry), 3);
    gtk_entry_set_width_chars(GTK_ENTRY(copy_entry), 10);

    add_button = gtk_button_new_with_label("Add Book");
    gtk_widget_set_halign(add_button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(add_button, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(add_button, 10);
    gtk_widget_set_margin_bottom(add_button, 10);
    gtk_widget_set_size_request(add_button, 100, 30);

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

    GtkWidget **book_entries = malloc(5 * sizeof(GtkWidget *));
    book_entries[0] = book_title_entry;
    book_entries[1] = author_entry;
    book_entries[2] = copy_entry;
    book_entries[3] = content_box;
    book_entries[4] = (gpointer)books;

    g_signal_connect(add_button, "clicked", G_CALLBACK(add_book_callback), book_entries);

    gtk_box_pack_start(GTK_BOX(add_book_box), title_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(add_book_box), grid, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(content_box), add_book_box);
    gtk_widget_show_all(content_box); // Show all widgets in the container
}

void add_book_callback(GtkWidget *widget, gpointer data)
{
    GtkWidget **book_entries = (GtkWidget **)data;
    const char *title = gtk_entry_get_text(GTK_ENTRY(book_entries[0]));
    const char *author = gtk_entry_get_text(GTK_ENTRY(book_entries[1]));
    const char *copy_str = gtk_entry_get_text(GTK_ENTRY(book_entries[2]));
    Book **books = (Book **)book_entries[4];
    int copy = atoi(copy_str);

    if (strlen(title) == 0 || strlen(author) == 0 || copy <= 0)
    {
        show_dialog(GTK_MESSAGE_WARNING, "Warning", "dialog-warning",
                    "Some fields are missing.",
                    "Please fill in all the required information.");

        return;
    }

    add_book_to_list(title, author, copy, books);

    gtk_entry_set_text(GTK_ENTRY(book_entries[0]), "");
    gtk_entry_set_text(GTK_ENTRY(book_entries[1]), "");
    gtk_entry_set_text(GTK_ENTRY(book_entries[2]), "");

    show_dialog(GTK_MESSAGE_INFO, "Success", "dialog-ok",
                "Book added successfully!",
                "The book has been saved to the library.");
}

void add_book_to_list(const char *title, const char *author, int copy, Book **books)
{
    Book *new_book = malloc(sizeof(Book));
    if (new_book == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    new_book->total_issues = 0;
    strcpy(new_book->title, title);
    strcpy(new_book->author, author);
    new_book->copy = copy;
    new_book->issues = NULL;

    int book_id = 1;
    int id_found;
    do
    {
        id_found = 0;
        Book *temp = *books;
        while (temp != NULL)
        {
            if (temp->book_id == book_id)
            {
                id_found = 1;
                break;
            }
            temp = temp->next;
        }
        if (id_found)
        {
            ++book_id;
        }
    } while (id_found);

    new_book->book_id = book_id;

    // printf("Adding Book ID:%d book: %s by %s with %d copies\n", new_book->book_id, new_book->title, new_book->author, new_book->copy);

    if ((*books) == NULL || (*books)->book_id > new_book->book_id)
    {
        new_book->next = *books;
        *books = new_book;
        return;
    }
    else
    {
        Book *current = *books;
        while (current->next != NULL && current->next->book_id < new_book->book_id)
        {
            current = current->next;
        }
        new_book->next = current->next;
        current->next = new_book;
    }
}

void restore_books_data(Book **books)
{
    FILE *book_file = fopen("books_data.xls", "r");
    if (!book_file)
    {
        printf("No saved books found.\n");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), book_file); // Skip header

    while (fgets(line, sizeof(line), book_file))
    {
        Book *new_book = malloc(sizeof(Book));
        if (!new_book)
        {
            fprintf(stderr, "Memory allocation failed\n");
            fclose(book_file);
            return;
        }

        sscanf(line, "%d\t%99[^\t]\t%99[^\t]\t%d\t%d",
               &new_book->book_id,
               new_book->title,
               new_book->author,
               &new_book->copy,
               &new_book->total_issues);

        new_book->issues = NULL;
        new_book->next = NULL;

        if (*books == NULL)
        {
            *books = new_book;
        }
        else
        {
            Book *current = *books;
            while (current->next != NULL)
                current = current->next;
            current->next = new_book;
        }
    }

    fclose(book_file);
    // printf("Books loaded successfully from books_data.xls\n");

    FILE *issue_file = fopen("issued_books_data.xls", "r");
    if (!issue_file)
    {
        printf("Issued books data file not found.\n");
        return;
    }

    fgets(line, sizeof(line), issue_file); // Skip header

    while (fgets(line, sizeof(line), issue_file))
    {
        int book_id, student_id;
        char title[100], name[100], issue_date[20], return_date[20];

        sscanf(line, "%d\t%99[^\t]\t%99[^\t]\t%d\t%19[^\t]\t%19[^\n]",
               &book_id, title, name, &student_id, issue_date, return_date);

        Book *current = *books;
        while (current)
        {
            if (current->book_id == book_id)
            {
                current->issues = realloc(current->issues, sizeof(issue) * (current->total_issues));
                if (!current->issues)
                {
                    fprintf(stderr, "Memory allocation failed for issues\n");
                    fclose(issue_file);
                    return;
                }

                issue *new_issue = &current->issues[current->total_issues - 1]; // already loaded from book file
                strcpy(new_issue->name, name);
                new_issue->student_id = student_id;
                strcpy(new_issue->issue_date, issue_date);
                strcpy(new_issue->return_date, return_date);
                break;
            }
            current = current->next;
        }
    }

    fclose(issue_file);
    // printf("Issued data loaded successfully from issued_books_data.xls\n");
}
