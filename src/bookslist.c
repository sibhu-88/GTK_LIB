#include "headers.h"
#include "components.h"

void books_list(GtkWidget *content_box, Book *books)
{
    if (!books)
    {
        show_dialog(GTK_MESSAGE_INFO, "Information", "dialog-information",
                    "No books available to display.",
                    "Please add books to the library first.");

        return;
    }

    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(main_box, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_box, GTK_ALIGN_FILL);
    gtk_container_add(GTK_CONTAINER(content_box), main_box);

    GtkWidget *title = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title), "<span weight=\"bold\" size=\"16000\">Books List</span>");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(main_box), title, FALSE, FALSE, 5);

    GtkListStore *store = gtk_list_store_new(4, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
    GtkTreeIter iter;

    for (Book *b = books; b; b = b->next)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, b->book_id, 1, b->title, 2, b->author, 3, b->copy, -1);
    }

    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);

    const gchar *columns[] = {"Book ID", "Book Title", "Author Name", "Book Copies"};
    for (int i = 0; i < 4; i++)
    {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *col = gtk_tree_view_column_new_with_attributes(columns[i], renderer, "text", i, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);
    }

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview), TRUE);
    gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(treeview), GTK_TREE_VIEW_GRID_LINES_BOTH);
    gtk_widget_set_hexpand(treeview, TRUE);
    gtk_widget_set_vexpand(treeview, TRUE);
    gtk_widget_set_size_request(treeview, 500, 400);

    gtk_box_pack_start(GTK_BOX(main_box), treeview, TRUE, TRUE, 10);
    gtk_widget_show_all(content_box);
}

void issued_details(GtkWidget *content_box, Book *books)
{
    if (!books)
    {
        show_dialog(GTK_MESSAGE_INFO, "Information", "dialog-information",
                    "No books available to display.",
                    "Please add books to the library first.");

        return;
    }

    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(main_box, GTK_ALIGN_FILL);
    gtk_widget_set_valign(main_box, GTK_ALIGN_FILL);
    gtk_container_add(GTK_CONTAINER(content_box), main_box);

    GtkWidget *title = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title), "<span weight=\"bold\" size=\"16000\">Issued Book Details</span>");
    gtk_widget_set_halign(title, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(main_box), title, FALSE, FALSE, 5);

    GtkListStore *store = gtk_list_store_new(6, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
    GtkTreeIter iter;

    for (Book *b = books; b; b = b->next)
    {
        for (int i = 0; i < b->total_issues; i++)
        {
            if (b->issues && strlen(b->issues[i].name) > 0)
            {
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                                   0, b->book_id,
                                   1, b->title,
                                   2, b->issues[i].name,
                                   3, b->issues[i].student_id,
                                   4, b->issues[i].issue_date,
                                   5, b->issues[i].return_date ? b->issues[i].return_date : "",
                                   -1);
            }
        }
    }

    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);

    const gchar *columns[] = {"Book ID", "Book Title", "Student Name", "Student ID", "Issue Date", "Return Date"};
    for (int i = 0; i < 6; i++)
    {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *col = gtk_tree_view_column_new_with_attributes(columns[i], renderer, "text", i, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);
    }

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview), TRUE);
    gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(treeview), GTK_TREE_VIEW_GRID_LINES_BOTH);
    gtk_widget_set_hexpand(treeview, TRUE);
    gtk_widget_set_vexpand(treeview, TRUE);
    gtk_widget_set_size_request(treeview, 600, 400);

    gtk_box_pack_start(GTK_BOX(main_box), treeview, TRUE, TRUE, 10);
    gtk_widget_show_all(content_box);
}
