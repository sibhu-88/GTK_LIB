#include "headers.h"
#include "callbacks.h"
#include "components.h"

GtkWidget *create_headerbar(GtkWidget *content_box)
{
    GtkWidget *headerbar;
    GtkWidget *logo;
    GtkWidget *search_button;
    GtkWidget *search_entry;
    GtkWidget *settings_button;
    GtkWidget *profile_button;

    headerbar = gtk_header_bar_new();
    // gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
    //  gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "Library Management System");

    logo = gtk_image_new_from_file("resources/logo.png");
    gtk_widget_set_size_request(logo, 50, 50); // Set the size of the logo
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar), logo);

    profile_button = gtk_button_new_from_icon_name("avatar-default-symbolic", GTK_ICON_SIZE_BUTTON);
    gtk_button_set_always_show_image(GTK_BUTTON(profile_button), TRUE);
    g_signal_connect(profile_button, "clicked", G_CALLBACK(on_profile_clicked), NULL);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), profile_button);

    settings_button = gtk_button_new_from_icon_name("preferences-system-symbolic", GTK_ICON_SIZE_BUTTON);
    gtk_button_set_always_show_image(GTK_BUTTON(settings_button), TRUE);
    g_signal_connect(settings_button, "clicked", G_CALLBACK(on_settings_clicked), NULL);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), settings_button);

    search_entry = gtk_entry_new();

    GtkWidget **widgets = (GtkWidget **)malloc(2 * sizeof(GtkWidget *));
    widgets[0] = search_entry;
    widgets[1] = content_box;

    search_button = gtk_button_new_from_icon_name("system-search-symbolic", GTK_ICON_SIZE_BUTTON);
    gtk_button_set_always_show_image(GTK_BUTTON(search_button), TRUE);
    g_signal_connect(search_button, "clicked", G_CALLBACK(on_search_book_clicked), widgets);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), search_button);
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_entry), "Search for a book...");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), search_entry);
    return headerbar;
}