#include "headers.h"
#include "components.h"
#include "callbacks.h"

void issue_book(GtkWidget *content_box, Book **books)
{
    if (*books == NULL)
    {
        show_dialog(GTK_MESSAGE_INFO, "Information", "dialog-information",
                    "No books available to Issue.",
                    "Please add books to the library first.");
        return;
    }

    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *issue_book_box;
    GtkWidget *title_label;

    GtkWidget *book_id_label;
    GtkWidget *book_id_entry;
    GtkWidget *student_id_label;
    GtkWidget *student_id_entry;
    GtkWidget *student_name_label;
    GtkWidget *student_name_entry;
    GtkWidget *issue_date_label;
    GtkWidget *calendar;
    GtkWidget *grid;
    GtkWidget *issue_button;

    issue_book_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(issue_book_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(issue_book_box, GTK_ALIGN_CENTER);

    title_label = gtk_label_new("Issue Book");

    book_id_label = gtk_label_new("Book ID:");
    book_id_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(book_id_entry), "Enter Book ID");
    gtk_entry_set_input_purpose(GTK_ENTRY(book_id_entry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_max_length(GTK_ENTRY(book_id_entry), 10);
    gtk_entry_set_width_chars(GTK_ENTRY(book_id_entry), 10);

    student_id_label = gtk_label_new("Student ID:");
    student_id_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(student_id_entry), "Enter Student ID");
    gtk_entry_set_input_purpose(GTK_ENTRY(student_id_entry), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_max_length(GTK_ENTRY(student_id_entry), 10);
    gtk_entry_set_width_chars(GTK_ENTRY(student_id_entry), 10);

    student_name_label = gtk_label_new("Student Name:");
    student_name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(student_name_entry), "Enter Student Name");
    gtk_entry_set_input_purpose(GTK_ENTRY(student_name_entry), GTK_INPUT_PURPOSE_FREE_FORM);
    gtk_entry_set_max_length(GTK_ENTRY(student_name_entry), 100);
    gtk_entry_set_width_chars(GTK_ENTRY(student_name_entry), 30);

    issue_date_label = gtk_label_new("Issue Date:");
    calendar = gtk_calendar_new();
    gtk_calendar_set_display_options(GTK_CALENDAR(calendar), GTK_CALENDAR_SHOW_DAY_NAMES | GTK_CALENDAR_SHOW_HEADING | GTK_CALENDAR_SHOW_WEEK_NUMBERS);

    issue_button = gtk_button_new_with_label("Issue Book");
    gtk_widget_set_halign(issue_button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(issue_button, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(issue_button, 10);
    gtk_widget_set_margin_bottom(issue_button, 10);
    gtk_widget_set_margin_start(issue_button, 10);
    gtk_widget_set_margin_end(issue_button, 10);
    gtk_widget_set_size_request(issue_button, 100, 30);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_attach(GTK_GRID(grid), title_label, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), book_id_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), book_id_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), student_id_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), student_id_entry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), student_name_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), student_name_entry, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), issue_date_label, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), calendar, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), issue_button, 0, 5, 2, 1);
    gtk_widget_set_halign(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), 10);
    gtk_widget_set_margin_bottom(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), 10);
    gtk_widget_set_margin_start(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), 10);

    GtkWidget **issue_entries = malloc(5 * sizeof(GtkWidget *));
    issue_entries[0] = book_id_entry;
    issue_entries[1] = student_name_entry;
    issue_entries[2] = student_id_entry;
    issue_entries[3] = calendar;
    issue_entries[4] = (gpointer)books;

    gtk_box_pack_start(GTK_BOX(issue_book_box), grid, TRUE, TRUE, 0);
    g_signal_connect(issue_button, "clicked", G_CALLBACK(issueButton_clicked), issue_entries);

    gtk_container_add(GTK_CONTAINER(content_box), issue_book_box);
    gtk_widget_show_all(content_box);
}

void issueButton_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget **widget = (GtkWidget **)user_data;

    const char *book_id_text = gtk_entry_get_text(GTK_ENTRY(widget[0]));
    const char *student_name = gtk_entry_get_text(GTK_ENTRY(widget[1]));
    const char *student_id_text = gtk_entry_get_text(GTK_ENTRY(widget[2]));
    GtkWidget *calendar = widget[3];
    Book **books = (Book **)widget[4];

    if (!strlen(book_id_text) || !strlen(student_name) || !strlen(student_id_text) || calendar == NULL)
    {
        show_dialog(GTK_MESSAGE_WARNING, "Warning", "dialog-warning",
                    "Some fields are missing.",
                    "Please fill in all the required information.");
    }

    unsigned int year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);

    char issue_date[20];
    sprintf(issue_date, "%02d-%02d-%04d", day, month + 1, year);

    // printf("Issuing Book ID: %s to %s (ID: %s) on %s\n", book_id_text, student_name, student_id_text, issue_date);

    int book_id = atoi(book_id_text);
    int student_id = atoi(student_id_text);
    Book *book = find_book_by_id(*books, book_id);
    if (book != NULL)
    {
        issueBook_list(book, book_id, student_name, student_id, issue_date);
        gtk_entry_set_text(GTK_ENTRY(widget[0]), "");
        gtk_entry_set_text(GTK_ENTRY(widget[1]), "");
        gtk_entry_set_text(GTK_ENTRY(widget[2]), "");
        gtk_calendar_clear_marks(GTK_CALENDAR(calendar));

        show_dialog(GTK_MESSAGE_INFO, "Success", "dialog-ok",
                    "Book Issued successfully!",
                    "The Issue Details has been saved to the library.");
    }
    else
    {
        show_dialog(GTK_MESSAGE_ERROR, "Error", "dialog-error",
                    "Book Not found.",
                    "An unexpected error occurred while accessing the database.");
    }
    free(widget);
}

void issueBook_list(Book *book, int book_id, const char *name, int student_id, const char *issue_date)
{

    if (book->copy <= 0)
    {
        // printf("No copies available for \"%s\".\n", book->title);

        GtkWidget *error_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
                                                         "No copies available for this book.");
        gtk_window_set_title(GTK_WINDOW(error_dialog), "Error");
        gtk_window_set_default_size(GTK_WINDOW(error_dialog), 300, 100);
        gtk_window_set_position(GTK_WINDOW(error_dialog), GTK_WIN_POS_CENTER);
        gtk_dialog_set_default_response(GTK_DIALOG(error_dialog), GTK_RESPONSE_OK);
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }

    issue *new_issues = realloc(book->issues, sizeof(issue) * (book->total_issues + 1));
    book->issues = new_issues;

    issue *new_issue = &book->issues[book->total_issues];
    strncpy(new_issue->name, name, sizeof(new_issue->name));
    new_issue->student_id = student_id;
    strncpy(new_issue->issue_date, issue_date, sizeof(new_issue->issue_date));
    strcpy(new_issue->return_date, ""); // Initially empty

    book->total_issues++;
    book->copy--;

    // printf("✅Book ID:%d Book \"%s\" issued to %s (ID: %d)\n", book->book_id, book->title, new_issue->name, new_issue->student_id);
}

Book *find_book_by_id(Book *books, int book_id)
{
    Book *current = books;
    while (current != NULL)
    {
        if (current->book_id == book_id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}