#include "headers.h"
#include "callbacks.h"
#include "components.h"

Book *books = NULL;

void dashboard_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    // printf("Dashboard clicked!\n");
    create_home(content_box);
}

void addbook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    // printf("Add Book clicked!\n");
    add_book(content_box, &books);
}

void bookslist_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    // printf("Books List clicked!\n");
    books_list(content_box, books);
}

void sortbooks_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    // printf("Sort Books clicked!\n");

    GtkWidget *menu = gtk_menu_new();

    GtkWidget *menu_item1 = gtk_menu_item_new_with_label("Sort by Title");
    GtkWidget *menu_item2 = gtk_menu_item_new_with_label("Sort by Author");

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item1);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item2);

    g_signal_connect(menu_item1, "activate", G_CALLBACK(sort_by_title_clicked), content_box);
    g_signal_connect(menu_item2, "activate", G_CALLBACK(sort_by_author_clicked), content_box);

    gtk_widget_show_all(menu);

    gtk_menu_popup_at_widget(
        GTK_MENU(menu),
        GTK_WIDGET(row),
        GDK_GRAVITY_NORTH_EAST,
        GDK_GRAVITY_NORTH_WEST,
        NULL);
}

void deletebook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    // printf("Delete Book clicked!\n");
    delete_book(content_box, &books);
}

void issuebook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    // printf("Issue Book clicked!\n");
    issue_book(content_box, &books);
}

void returnbook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    // printf("Return Book clicked!\n");
    return_book(content_box, &books);
}

void issueddetails_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    // printf("Issued Details clicked!\n");
    issued_details(content_box, books);
}

void save_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box)
{
    // printf("Save clicked!\n");
    save_all_data(books);
}

void sort_by_title_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *content_box = GTK_WIDGET(user_data);
    // printf("Sort by Title clicked\n");

    extern Book *books;
    Book *temp = books;
    sort_books_by_title(content_box, temp);
}

void sort_by_author_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *content_box = GTK_WIDGET(user_data);
    // printf("Sort by Author clicked\n");
    extern Book *books;
    Book *temp = books;
    sort_books_by_author(content_box, temp);
}

void on_profile_clicked(GtkWidget *widget, gpointer data)
{
    // printf("Profile clicked!\n");
    GtkWidget *menu = gtk_menu_new();

    GtkWidget *menu_item1 = gtk_menu_item_new_with_label("Profile Details");
    GtkWidget *menu_item2 = gtk_menu_item_new_with_label("Logout");

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item1);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item2);

    // g_signal_connect(menu_item1, "activate", G_CALLBACK(profile_detail), NULL);
    // g_signal_connect(menu_item2, "activate", G_CALLBACK(logout_user), NULL);

    gtk_widget_show_all(menu);

    gtk_menu_popup_at_widget(
        GTK_MENU(menu),
        GTK_WIDGET(widget),
        GDK_GRAVITY_SOUTH_WEST,
        GDK_GRAVITY_NORTH_WEST,
        NULL);
}

void on_settings_clicked(GtkWidget *widget, gpointer data)
{
    // printf("Settings clicked!\n");
    GtkWidget *menu = gtk_menu_new();

    GtkWidget *menu_item1 = gtk_menu_item_new_with_label("Change Password");
    GtkWidget *menu_item2 = gtk_menu_item_new_with_label("Preferences");

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item1);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item2);

    // g_signal_connect(menu_item1, "activate", G_CALLBACK(change_password), NULL);
    // g_signal_connect(menu_item2, "activate", G_CALLBACK(preferences), NULL);

    gtk_widget_show_all(menu);

    gtk_menu_popup_at_widget(
        GTK_MENU(menu),
        GTK_WIDGET(widget),
        GDK_GRAVITY_SOUTH_WEST,
        GDK_GRAVITY_NORTH_WEST,
        NULL);
}

void on_search_book_clicked(GtkWidget *widget, gpointer data)
{
    GtkWidget **widgets = (GtkWidget **)data;
    GtkWidget *search_entry = widgets[0];
    GtkWidget *content_box = widgets[1];

    const gchar *search_text = gtk_entry_get_text(GTK_ENTRY(search_entry));
    if (g_strcmp0(search_text, "") == 0)
    {
        show_dialog(GTK_MESSAGE_ERROR, "Error", "dialog-error", "Search field is empty.", NULL);
        return;
    }

    // printf("Searching for book: %s\n", search_text);
    extern Book *books;
    Book *temp = books;
    search_book(temp, search_text);
    
    gtk_entry_set_text(GTK_ENTRY(search_entry), "");
    //free(widgets);                                   
}