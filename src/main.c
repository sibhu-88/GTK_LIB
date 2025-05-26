#include "headers.h"
#include "components.h"

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "LIBRARY MANAGEMENT SYSTEM");

    GdkScreen *screen = gdk_screen_get_default();
    int width = gdk_screen_get_width(screen) - 100;
    int height = gdk_screen_get_height(screen) - 100;

    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *dasbord = create_dashboard();
    gtk_container_add(GTK_CONTAINER(window), dasbord);

    gtk_widget_show_all(window);
}

int main()
{
    GtkApplication *app;
    app = gtk_application_new("org.gtk.Linrary", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status;
    status = g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);
    return status;
}
