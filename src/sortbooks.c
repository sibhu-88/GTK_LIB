#include "headers.h"
#include "components.h"

void sort_books_by_title(GtkWidget *content_box, Book *books)
{
    if (books == NULL)
    {
        show_dialog(GTK_MESSAGE_INFO, "Information", "dialog-information",
                    "No books available to Sort.",
                    "Please add books to the library first.");

        return;
    }
    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    // printf("Sorting books by title...\n");

    int node_count = nodecount(books);

    Book **current = (Book **)calloc(node_count, sizeof(Book *));
    Book *temp = books;
    for (size_t i = 0; i < node_count; i++)
    {
        current[i] = temp;
        temp = temp->next;
    }

    for (size_t i = 0; i < node_count - 1; i++)
    {
        for (size_t j = i + 1; j < node_count; j++)
        {
            if (strcmp(current[i]->title, current[j]->title) > 0)
            {
                Book *temp_book = current[i];
                current[i] = current[j];
                current[j] = temp_book;
            }
        }
    }

    // for (size_t i = 0; i < node_count; i++)
        // printf("Book ID: %d, Title: %s, Author: %s\n", current[i]->book_id, current[i]->title, current[i]->author);

    // printf("Books sorted by title successfully.\n");

    GtkWidget *sort_book_box;
    GtkWidget *title_label;

    sort_book_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(sort_book_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(sort_book_box, GTK_ALIGN_CENTER);

    title_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title_label), "<span weight=\"bold\" size=\"16000\">Sort Books By Title</span>");

    gtk_box_pack_start(GTK_BOX(sort_book_box), title_label, TRUE, TRUE, 0);
    gtk_widget_set_halign(title_label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(title_label, GTK_ALIGN_CENTER);

    GtkListStore *store = gtk_list_store_new(4, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
    GtkTreeIter iter;

    for (size_t i = 0; i < node_count; i++) // FIX: insert all sorted entries
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, current[i]->book_id,
                           1, current[i]->title,
                           2, current[i]->author,
                           3, current[i]->copy,
                           -1);
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

    gtk_box_pack_start(GTK_BOX(sort_book_box), treeview, TRUE, TRUE, 10);
    gtk_container_add(GTK_CONTAINER(content_box), sort_book_box);
    gtk_widget_show_all(content_box);
    free(current);
}

void sort_books_by_author(GtkWidget *content_box, Book *books)
{
    if (books == NULL)
    {
        show_dialog(GTK_MESSAGE_INFO, "Information", "dialog-information",
                    "No books available to Sort.",
                    "Please add books to the library first.");

        return;
    }

    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    // printf("Sorting books by author...\n");

    int node_count = nodecount(books);
    if (node_count <= 1)
        return;

    Book **current = (Book **)calloc(node_count, sizeof(Book *));

    Book *temp = books;
    for (int i = 0; i < node_count; i++)
    {
        current[i] = temp;
        temp = temp->next;
    }

    for (int i = 0; i < node_count; i++)
    {
        for (int j = i + 1; j < node_count; j++)
        {
            if (strcmp(current[i]->author, current[j]->author) > 0)
            {
                Book *tmp = current[i];
                current[i] = current[j];
                current[j] = tmp;
            }
        }
    }

    // for (int i = 0; i < node_count - 1; i++)
        // printf("Book ID: %d, Title: %s, Author: %s\n", current[i]->book_id, current[i]->title, current[i]->author);

    // printf("Books sorted by author successfully.\n");

    GtkWidget *sort_book_box;
    GtkWidget *title_label;

    sort_book_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(sort_book_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(sort_book_box, GTK_ALIGN_CENTER);

    title_label = gtk_label_new(NULL);

    gtk_label_set_markup(GTK_LABEL(title_label), "<span weight=\"bold\" size=\"16000\">Sort Books By Author</span>");

    gtk_box_pack_start(GTK_BOX(sort_book_box), title_label, TRUE, TRUE, 0);
    gtk_widget_set_halign(title_label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(title_label, GTK_ALIGN_CENTER);

    GtkListStore *store = gtk_list_store_new(4, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
    GtkTreeIter iter;

    for (size_t i = 0; i < node_count; i++)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, current[i]->book_id,
                           1, current[i]->title,
                           2, current[i]->author,
                           3, current[i]->copy,
                           -1);
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

    gtk_box_pack_start(GTK_BOX(sort_book_box), treeview, TRUE, TRUE, 10);

    gtk_container_add(GTK_CONTAINER(content_box), sort_book_box);
    gtk_widget_show_all(content_box);
    free(current);
}

int nodecount(Book *books)
{
    int count = 0;
    Book *current = books;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}