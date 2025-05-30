#include "headers.h"
#include "components.h"
#include "callbacks.h"

static void row_selected_callback(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    if (row)
    {
        GCallback callback = (GCallback)g_object_get_data(G_OBJECT(row), "callback");
        if (callback)
        {
            ((void (*)(GtkListBox *, GtkListBoxRow *, GtkWidget *))callback)(listbox, row, content_box);
        }
    }
}

GtkWidget *create_sidemenu(GtkWidget *content_box)
{
    GtkWidget *side_box;
    GtkWidget *listbox;

    side_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(side_box, 200, -1);

    listbox = gtk_list_box_new();
    gtk_box_pack_start(GTK_BOX(side_box), listbox, TRUE, TRUE, 0);

    const struct
    {
        const gchar *label;
        const gchar *icon_name;
        GCallback callback;
    } menu_items[] = {
        {"Dashboard", "go-home-symbolic", G_CALLBACK(dashboard_clicked)},
        {"Add Book", "document-new-symbolic", G_CALLBACK(addbook_clicked)},
        {"Books List", "view-list-symbolic", G_CALLBACK(bookslist_clicked)},
        {"Sort Books", "view-sort-ascending-symbolic", G_CALLBACK(sortbooks_clicked)},
        {"Delete Book", "edit-delete-symbolic", G_CALLBACK(deletebook_clicked)},
        {"Issue Book", "document-send-symbolic", G_CALLBACK(issuebook_clicked)},
        {"Return Book", "document-revert-symbolic", G_CALLBACK(returnbook_clicked)},
        {"Issued Details", "document-properties-symbolic", G_CALLBACK(issueddetails_clicked)},
        {"Save", "document-save-symbolic", G_CALLBACK(save_clicked)}};

    for (int i = 0; i < G_N_ELEMENTS(menu_items); i++)
    {
        GtkWidget *row_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        gtk_widget_set_margin_start(row_box, 10);
        gtk_widget_set_margin_end(row_box, 10);
        gtk_widget_set_margin_top(row_box, 15);
        gtk_widget_set_margin_bottom(row_box, 15);

        GtkWidget *icon = gtk_image_new_from_icon_name(menu_items[i].icon_name, GTK_ICON_SIZE_BUTTON);
        gtk_box_pack_start(GTK_BOX(row_box), icon, FALSE, FALSE, 0);
        gtk_widget_set_halign(icon, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(icon, GTK_ALIGN_CENTER);

        GtkWidget *label = gtk_label_new(NULL);
        gchar *markup = g_strdup_printf("<span size=\"large\">%s</span>", menu_items[i].label); // or size="15000" for precise control
        gtk_label_set_markup(GTK_LABEL(label), markup);
        g_free(markup);

        gtk_box_pack_start(GTK_BOX(row_box), label, TRUE, TRUE, 0);
        gtk_widget_set_halign(label, GTK_ALIGN_START);
        gtk_widget_set_valign(label, GTK_ALIGN_CENTER);

        GtkWidget *row = gtk_list_box_row_new();
        gtk_container_add(GTK_CONTAINER(row), row_box);
        gtk_list_box_insert(GTK_LIST_BOX(listbox), row, -1);

        g_object_set_data(G_OBJECT(row), "callback", menu_items[i].callback);
    }

    g_signal_connect(listbox, "row-selected", G_CALLBACK(row_selected_callback), content_box);

    return side_box;
}

void show_dialog(GtkMessageType type, const gchar *title, const gchar *icon_name, const gchar *message, const gchar *secondary)
{
    GtkWidget *dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_MODAL,
        type,
        GTK_BUTTONS_OK,
        "%s", message);

    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "%s", secondary);
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_window_set_icon_name(GTK_WINDOW(dialog), icon_name);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void search_book(Book *books, const char *search_text)
{
    if (g_strcmp0(search_text, "") == 0)
    {
        show_dialog(GTK_MESSAGE_ERROR, "Error", "dialog-error", "Search field is empty.", "Please enter a title or author to search.");
        return;
    }

    Book *temp = books;
    int found = 0;
    while (temp != NULL)
    {
        if (strcmp(temp->title, search_text) == 0 || strcmp(temp->author, search_text) == 0)
        {
            GtkWidget *dialog = gtk_dialog_new_with_buttons("Search Result",
                                                            NULL,
                                                            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                            "_OK",
                                                            GTK_RESPONSE_OK,
                                                            NULL);
            gtk_window_set_icon_name(GTK_WINDOW(dialog), "dialog-information");
            gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
            gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
            gtk_widget_set_size_request(dialog, 300, 60);
            gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
            gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
            gtk_window_set_title(GTK_WINDOW(dialog), "Book Found");
            GtkWidget *book_info = gtk_label_new(g_strdup_printf("Title: %s\nAuthor: %s\nCopies: %d",
                                                                 temp->title,
                                                                 temp->author,
                                                                 temp->copy));
                                                                 
            gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), book_info, FALSE, FALSE, 0);


            gtk_widget_show_all(dialog);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            found = 1;
            return;
        }
        temp = temp->next;
    }
    if (!found)
    {
        show_dialog(GTK_MESSAGE_ERROR, "Error", "dialog-error", "No book found with the given title or author.", "Please try again.");
        return;
    }
}