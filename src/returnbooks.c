#include "headers.h"
#include "components.h"
#include "callbacks.h"

void return_book(GtkWidget *content_box, Book **books)
{
    if (*books == NULL)
    {
        show_dialog(GTK_MESSAGE_INFO, "Information", "dialog-information",
                    "No books available to Return.",
                    "Please add books to the library first.");
        return;
    }
    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *return_book_box;
    GtkWidget *title_label;
    GtkWidget *book_id_label;
    GtkWidget *book_id_entry;
    GtkWidget *student_id_label;
    GtkWidget *student_id_entry;
    GtkWidget *student_name_label;
    GtkWidget *student_name_entry;
    GtkWidget *return_date_label;
    GtkWidget *calendar;
    GtkWidget *return_button;
    GtkWidget *grid;

    return_book_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(return_book_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(return_book_box, GTK_ALIGN_CENTER);

    title_label = gtk_label_new("Return Book");

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

    return_date_label = gtk_label_new("Return Date:");
    calendar = gtk_calendar_new();
    gtk_calendar_set_display_options(GTK_CALENDAR(calendar), GTK_CALENDAR_SHOW_DAY_NAMES | GTK_CALENDAR_SHOW_HEADING | GTK_CALENDAR_SHOW_WEEK_NUMBERS);

    return_button = gtk_button_new_with_label("Return Book");
    gtk_widget_set_halign(return_button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(return_button, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(return_button, 10);
    gtk_widget_set_margin_bottom(return_button, 10);
    gtk_widget_set_margin_start(return_button, 10);
    gtk_widget_set_margin_end(return_button, 10);
    gtk_widget_set_size_request(return_button, 100, 30);

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
    gtk_grid_attach(GTK_GRID(grid), return_date_label, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), calendar, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), return_button, 0, 5, 2, 1);
    gtk_widget_set_halign(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), 10);
    gtk_widget_set_margin_bottom(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), 10);
    gtk_widget_set_margin_start(gtk_grid_get_child_at(GTK_GRID(grid), 0, 4), 10);

    GtkWidget **return_entries = malloc(5 * sizeof(GtkWidget *));
    return_entries[0] = book_id_entry;
    return_entries[1] = student_name_entry;
    return_entries[2] = student_id_entry;
    return_entries[3] = calendar;
    return_entries[4] = (gpointer)books;

    gtk_box_pack_start(GTK_BOX(return_book_box), grid, TRUE, TRUE, 0);
    g_signal_connect(return_button, "clicked", G_CALLBACK(returnBook_clicked), return_entries);

    gtk_container_add(GTK_CONTAINER(content_box), return_book_box);
    gtk_widget_show_all(content_box); // Show all widgets in the container
}

void returnBook_clicked(GtkWidget *button, gpointer user_data)
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
        return;
    }

    unsigned int year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);

    char return_date[20];
    sprintf(return_date, "%02d-%02d-%04d", day, month + 1, year);

    int book_id = atoi(book_id_text);
    int student_id = atoi(student_id_text);
    Book *book = find_book_by_id(*books, book_id);
    if (book != NULL)
    {
        returnBook(button, book, book_id, student_id, return_date);
        gtk_entry_set_text(GTK_ENTRY(widget[0]), "");
        gtk_entry_set_text(GTK_ENTRY(widget[1]), "");
        gtk_entry_set_text(GTK_ENTRY(widget[2]), "");
        gtk_calendar_clear_marks(GTK_CALENDAR(calendar));

        show_dialog(GTK_MESSAGE_INFO, "Success", "dialog-ok",
                    "Book Returned successfully!",
                    "The Return Details has been saved to the library.");
    }
    else
    {
        show_dialog(GTK_MESSAGE_ERROR, "Error", "dialog-error",
                    "Book Not found.",
                    "An unexpected error occurred while accessing the database.");
        return;
    }
    // printf("Returning Book ID: %s by %s (ID: %s) on %s\n", book_id_text, student_name, student_id_text, return_date);
}

void returnBook(GtkWidget *button, Book *book, int book_id, int student_id, const char *return_date)
{
    int found = 0;

    for (int i = 0; i < book->total_issues; ++i)
    {
        if (book->book_id == book_id && book->issues[i].student_id == student_id)
        {
            found = 1;

            if (book->issues[i].return_date && strcmp(book->issues[i].return_date, "N/A") != 0)
            {
                // printf("⚠️ Book already returned by student ID: %d\n", student_id);
                show_dialog(GTK_MESSAGE_ERROR, "Error", "dialog-error",
                            "Book already returned by the student.",
                            "This book has already been returned. No further action required.");
            }

            strncpy(book->issues[i].return_date, return_date, sizeof(book->issues[i].return_date));
            book->copy++;

            // printf("✅ Book returned by student ID: %d on %s\n", student_id, return_date);
            break;
        }
    }

    if (!found)
    {
        // printf("❌ No issued book found for student ID: %d\n", student_id);
        show_dialog(GTK_MESSAGE_ERROR, "Error", "dialog-error",
                    "No issued book found for the student.",
                    "An unexpected error occurred while accessing the database.");
        return;
    }
}
