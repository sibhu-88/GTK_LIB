#include "headers.h"
#include "components.h"

void delete_book(GtkWidget *content_box, Book **books)
{
    if (*books == NULL)
    {
        show_dialog(GTK_MESSAGE_INFO, "Information", "dialog-information",
                    "No books available to Delete.",
                    "Please add books to the library first.");
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