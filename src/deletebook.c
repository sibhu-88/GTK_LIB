#include "headers.h"
#include "components.h"

void delete_book(GtkWidget *content_box, Book **books)
{
    if (*books == NULL)
    {
        GtkWidget *dialiog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                    "No books available to Delete.");
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

    GtkWidget *delete_book_box;
    GtkWidget *title_label;

    delete_book_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(delete_book_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(delete_book_box, GTK_ALIGN_CENTER);

    title_label = gtk_label_new("Delete Book");

    gtk_box_pack_start(GTK_BOX(delete_book_box), title_label, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(content_box), delete_book_box);
    gtk_widget_show_all(content_box); // Show all widgets in the container
}