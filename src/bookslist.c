#include "headers.h"
#include "components.h"

void books_list(GtkWidget *content_box, Book *books)
{
    if (books == NULL)
    {
        GtkWidget *dialiog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                    "No books available to display.");
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

    // Clear existing content
    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    // Main box
    GtkWidget *issued_details_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(issued_details_box, GTK_ALIGN_FILL);
    gtk_widget_set_valign(issued_details_box, GTK_ALIGN_FILL);
    gtk_container_add(GTK_CONTAINER(content_box), issued_details_box);

    // Title label
    gchar *title_markup = g_strdup_printf("<span weight=\"bold\" size=\"16000\">%s</span>", "Books List");
    GtkWidget *title_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title_label), title_markup);
    gtk_widget_set_halign(title_label, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(issued_details_box), title_label, FALSE, FALSE, 5);
    g_free(title_markup);

    // Create GtkListStore (model)
    GtkListStore *store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);

    // Add books to the store
    GtkTreeIter iter;
    Book *current = books;
    while (current)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, current->title,
                           1, current->author,
                           2, current->copy,
                           -1);
        current = current->next;
    }

    // Create GtkTreeView
    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store); // treeview holds a ref

    // Add columns
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // Title Column
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Book Title", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Author Column
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Author Name", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Copies Column
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Book Copies", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    // gtk_widget_set_hexpand(scrolled_window, TRUE);
    // gtk_container_add(GTK_CONTAINER(scrolled_window), treeview);
    gtk_box_pack_start(GTK_BOX(issued_details_box), treeview, TRUE, TRUE, 10);

    gtk_widget_show_all(content_box);
}

void issued_details(GtkWidget *content_box, Book *books) {
    if (books == NULL) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                   "No books available to display.");
        gtk_window_set_title(GTK_WINDOW(dialog), "Information");
        gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "Please add books to the library first.");
        gtk_window_set_icon_name(GTK_WINDOW(dialog), "info");
        gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
        gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *issued_details_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(issued_details_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(issued_details_box, GTK_ALIGN_CENTER);

    GtkWidget *title_label = gtk_label_new(NULL);
    gchar *title_markup = g_strdup_printf("<span weight=\"bold\" size=\"16000\">%s</span>", "Issued Book Details");
    gtk_label_set_markup(GTK_LABEL(title_label), title_markup);
    gtk_box_pack_start(GTK_BOX(issued_details_box), title_label, FALSE, FALSE, 5);
    g_free(title_markup);

    GtkListStore *store = gtk_list_store_new(5, 
        G_TYPE_STRING,  // Book Title
        G_TYPE_STRING,  // Student Name
        G_TYPE_INT,     // Student ID
        G_TYPE_STRING,  // Issue Date
        G_TYPE_STRING   // Return Date
    );

    GtkTreeIter iter;
    Book *current = books;
    while (current) {
        for (int i = 0; i < current->copy; i++) {
            if (current->issues != NULL && strlen(current->issues[i].name) > 0) {
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                    0, current->title,
                    1, current->issues[i].name,
                    2, current->issues[i].id,
                    3, current->issues[i].issue_date,
                    4, current->issues[i].return_date,
                    -1);
            }
        }
        current = current->next;
    }

    GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store); // model owned by treeview now

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Book Title", renderer, "text", 0, NULL);

    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Student Name", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Student ID", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Issue Date", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Return Date", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(treeview), TRUE);
    gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(treeview), GTK_TREE_VIEW_GRID_LINES_BOTH);
    gtk_tree_view_set_enable_search(GTK_TREE_VIEW(treeview), TRUE);
    gtk_tree_view_set_search_column(GTK_TREE_VIEW(treeview), 0); // Search by Book Title
    gtk_tree_view_set_search_equal_func(GTK_TREE_VIEW(treeview), gtk_tree_view_set_search_equal_func, NULL, NULL);
    gtk_tree_view_set_search_entry(GTK_TREE_VIEW(treeview), NULL);
    gtk_box_pack_start(GTK_BOX(issued_details_box), treeview, TRUE, TRUE, 10);
    gtk_widget_set_hexpand(treeview, TRUE);
    gtk_widget_set_vexpand(treeview, TRUE);
    gtk_widget_set_margin_top(treeview, 10);
    gtk_widget_set_margin_bottom(treeview, 10);
    gtk_widget_set_margin_start(treeview, 10);
    gtk_widget_set_margin_end(treeview, 10);
    gtk_widget_set_size_request(treeview, 600, 400);   
         
    gtk_container_add(GTK_CONTAINER(content_box), issued_details_box);
    gtk_widget_show_all(content_box);
}
