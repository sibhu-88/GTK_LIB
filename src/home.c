#include "headers.h"
#include "components.h"

void create_home(GtkWidget *container)
{
    GtkWidget *home_box;
    GtkWidget *label;
    GtkWidget *image;
    GtkWidget *center_box;

    // Clear existing children from the container
    gtk_container_foreach(GTK_CONTAINER(container), (GtkCallback)gtk_widget_destroy, NULL);

    // Create a vertical box to center the content
    center_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(center_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(center_box, GTK_ALIGN_CENTER);

    // Create a vertical box for the home content
    home_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(home_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(home_box, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(home_box, 10);
    gtk_widget_set_margin_end(home_box, 10);
    gtk_widget_set_margin_top(home_box, 10);
    gtk_widget_set_margin_bottom(home_box, 10);

    label = gtk_label_new("Welcome to the Library Management System");
    gtk_box_pack_start(GTK_BOX(home_box), label, TRUE, TRUE, 0);

    image = gtk_image_new_from_file("resources/vector_india.png");
    gtk_widget_set_size_request(image, 300, 300); // Set the size of the image
    gtk_box_pack_start(GTK_BOX(home_box), image, TRUE, TRUE, 0);

    extern Book *books;
    restore_books_data(&books);

    gtk_box_pack_start(GTK_BOX(center_box), home_box, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(container), center_box);
    gtk_widget_show_all(container); // Show all widgets in the container
}