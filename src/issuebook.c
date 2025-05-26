#include "headers.h"
#include "components.h"
#include "callbacks.h"

void issue_book(GtkWidget *content_box, Book **books)
{
    if (*books == NULL)
    {
        GtkWidget *dialiog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                    "No books available to Issue.");
        gtk_window_set_title(GTK_WINDOW(dialiog), "Information");
        gtk_window_set_default_size(GTK_WINDOW(dialiog), 300, 100);
        gtk_window_set_position(GTK_WINDOW(dialiog), GTK_WIN_POS_CENTER);
        gtk_dialog_set_default_response(GTK_DIALOG(dialiog), GTK_RESPONSE_OK);
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialiog), "Please add books to the library first.");
        gtk_window_set_icon_name(GTK_WINDOW(dialiog), "info");
        gtk_window_set_resizable(GTK_WINDOW(dialiog), FALSE);
        gtk_window_set_modal(GTK_WINDOW(dialiog), TRUE);
        gtk_dialog_run(GTK_DIALOG(dialiog));
        gtk_widget_destroy(dialiog);
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
    student_id_label = gtk_label_new("Student ID:");
    student_id_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(student_id_entry), "Enter Student ID");
    student_name_label = gtk_label_new("Student Name:");
    student_name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(student_name_entry), "Enter Student Name");
    issue_date_label = gtk_label_new("Issue Date:");
    calendar = gtk_calendar_new();
    gtk_calendar_set_display_options(GTK_CALENDAR(calendar), GTK_CALENDAR_SHOW_DAY_NAMES | GTK_CALENDAR_SHOW_HEADING | GTK_CALENDAR_SHOW_WEEK_NUMBERS);
    issue_button = gtk_button_new_with_label("Issue Book");

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
    g_signal_connect(issue_button, "clicked", G_CALLBACK(issueBook_clicked), issue_entries);

    gtk_container_add(GTK_CONTAINER(content_box), issue_book_box);
    gtk_widget_show_all(content_box); // Show all widgets in the container
}

// void issueBook(Book *book, int book_id, const char *name, int student_id)
// {
//     if (book->copy <= 0)
//     {
//         printf("No copies available for \"%s\".\n", book->title);
//         return;
//     }

//     // Reallocate issues array to store a new record
//     book->issues = realloc(book->issues, sizeof(issue) * (book->total_issues + 1));
//     if (!book->issues)
//     {
//         printf("Memory allocation failed!\n");
//         return;
//     }

//     // Fill new issue record
//     issue *new_issue = &book->issues[book->total_issues];
//     strcpy(new_issue->name, name);
//     new_issue->id = id;
//     strcpy(new_issue->issue_date, issue_date);
//     strcpy(new_issue->return_date, return_date);

//     book->total_issues++;
//     book->copy--; // One less available copy

//     printf("Book \"%s\" issued to %s (ID: %d)\n", book->title, name, id);
// }

void return_book(GtkWidget *content_box, Book **books)
{
    if (*books == NULL)
    {
        GtkWidget *dialiog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                    "No books available to Return.");
        gtk_window_set_title(GTK_WINDOW(dialiog), "Information");
        gtk_window_set_default_size(GTK_WINDOW(dialiog), 300, 100);
        gtk_window_set_position(GTK_WINDOW(dialiog), GTK_WIN_POS_CENTER);
        gtk_dialog_set_default_response(GTK_DIALOG(dialiog), GTK_RESPONSE_OK);
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialiog), "Please add books to the library first.");
        gtk_window_set_icon_name(GTK_WINDOW(dialiog), "info");
        gtk_window_set_resizable(GTK_WINDOW(dialiog), FALSE);
        gtk_window_set_modal(GTK_WINDOW(dialiog), TRUE);
        gtk_dialog_run(GTK_DIALOG(dialiog));
        gtk_widget_destroy(dialiog);
        return;
    }
    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *return_book_box;
    GtkWidget *title_label;
    GtkWidget *id_label;
    GtkWidget *id_entry;
    GtkWidget *return_button;
    GtkWidget *grid;

    return_book_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(return_book_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(return_book_box, GTK_ALIGN_CENTER);

    title_label = gtk_label_new("Return Book");

    gtk_box_pack_start(GTK_BOX(return_book_box), title_label, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(content_box), return_book_box);
    gtk_widget_show_all(content_box); // Show all widgets in the container
}

// void returnBook(Book *book, int book_id, int student_id)
// {
//     int found = 0;
//     for (int i = 0; i < book->total_issues; ++i)
//     {
//         if (book->issues[i].id == id)
//         {
//             found = 1;

//             // Shift remaining records left
//             for (int j = i; j < book->total_issues - 1; ++j)
//             {
//                 book->issues[j] = book->issues[j + 1];
//             }

//             book->total_issues--;
//             book->issues = realloc(book->issues, sizeof(issue) * book->total_issues);
//             book->copy++; // Return increases available copies

//             printf("Book returned by ID: %d\n", id);
//             break;
//         }
//     }

//     if (!found)
//     {
//         printf("No issued book found for ID: %d\n", id);
//     }
// }
