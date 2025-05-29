#include "headers.h"
#include "components.h"

void apply_css_style(const char *css_file_path)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GError *error = NULL;

    gtk_css_provider_load_from_path(provider, css_file_path, &error);
    if (error)
    {
        g_printerr("Error loading CSS file: %s\n", error->message);
        g_error_free(error);
        return;
    }
    GdkScreen *screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}

static void activate(GtkApplication *app, gpointer user_data)
{
    apply_css_style("style.css");

    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "LIBRARY MANAGEMENT SYSTEM");

    GdkScreen *screen = gdk_screen_get_default();
    int width = gdk_screen_get_width(screen) - 80;
    int height = gdk_screen_get_height(screen) - 80;

    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    extern Book *books;
    restore_books_data(&books);

    GtkWidget *dashboard = create_dashboard();
    gtk_container_add(GTK_CONTAINER(window), dashboard);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.Library", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
