#include "headers.h"
#include "components.h"

void sort_books(GtkWidget *content_box, Book *books)
{
    if (books == NULL)
    {
        show_dialog(GTK_MESSAGE_INFO, "Information", "dialog-information",
                    "No books available to Sort.",
                    "Please add books to the library first.");

        return;
    }

    gtk_container_foreach(GTK_CONTAINER(content_box), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *sort_book_box;
    GtkWidget *title_label;

    sort_book_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(sort_book_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(sort_book_box, GTK_ALIGN_CENTER);

    title_label = gtk_label_new("Sort Book");

    gtk_box_pack_start(GTK_BOX(sort_book_box), title_label, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(content_box), sort_book_box);
    gtk_widget_show_all(content_box); // Show all widgets in the container
}