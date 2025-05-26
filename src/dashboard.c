#include "headers.h"
#include "components.h"

GtkWidget *create_dashboard()
{
    GtkWidget *dashboard;
    GtkWidget *headerbar;
    GtkWidget *dashboard_box;
    GtkWidget *side_box;
    GtkWidget *content_box;
    GtkWidget *side_menu;

    dashboard = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
   
    content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(content_box, GTK_ALIGN_CENTER);

    headerbar = create_headerbar(content_box);
    gtk_box_pack_start(GTK_BOX(dashboard), headerbar, FALSE, FALSE, 0);

    dashboard_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(dashboard), dashboard_box, TRUE, TRUE, 0);  
    
    side_menu = create_sidemenu(content_box);
    gtk_box_pack_start(GTK_BOX(dashboard_box), side_menu, FALSE, FALSE, 0);
    
    gtk_box_pack_start(GTK_BOX(dashboard_box), content_box, TRUE, TRUE, 0);

    create_home(content_box);
    //gtk_box_pack_start(GTK_BOX(content_box), home, TRUE, TRUE, 0);

    return dashboard;
}