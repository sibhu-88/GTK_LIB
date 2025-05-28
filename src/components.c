#include "headers.h"
#include "components.h"
#include "callbacks.h"

// Callback function for row-selected signal
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

    // Create vertical box for sidebar
    side_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(side_box, 200, -1);

    // Create listbox for menu items
    listbox = gtk_list_box_new();
    gtk_box_pack_start(GTK_BOX(side_box), listbox, TRUE, TRUE, 0);

    // Menu items configuration
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

    // Add menu items to listbox
    for (int i = 0; i < G_N_ELEMENTS(menu_items); i++)
    {
        // Create a horizontal box for each row
        GtkWidget *row_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        gtk_widget_set_margin_start(row_box, 10);
        gtk_widget_set_margin_end(row_box, 10);
        gtk_widget_set_margin_top(row_box, 5);
        gtk_widget_set_margin_bottom(row_box, 5);

        // Add icon
        GtkWidget *icon = gtk_image_new_from_icon_name(menu_items[i].icon_name, GTK_ICON_SIZE_BUTTON);
        gtk_box_pack_start(GTK_BOX(row_box), icon, FALSE, FALSE, 0);

        // Add label for all items
        GtkWidget *label = gtk_label_new(menu_items[i].label);
        gtk_box_pack_start(GTK_BOX(row_box), label, TRUE, TRUE, 0);

        // Create listbox row and add row_box
        GtkWidget *row = gtk_list_box_row_new();
        gtk_container_add(GTK_CONTAINER(row), row_box);
        gtk_list_box_insert(GTK_LIST_BOX(listbox), row, -1);

        // Store callback
        g_object_set_data(G_OBJECT(row), "callback", menu_items[i].callback);
    }

    // Connect row-selected signal
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
