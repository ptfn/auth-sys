#include <gtk/gtk.h>
#include "db.h"

GListStore *
create_client_list(void)
{
    GListStore *store = g_list_store_new(G_TYPE_POINTER);

    client_t *client1 = g_new(client1, 1);
    client1->name = "Bob";
    client1->key = "Key1";
    client1->login = "Bob12";
    client1->password = "1234";
    g_list_store_append(store, client1);

    client_t *client2 = g_new(client2, 1);
    client1->name = "Alice";
    client1->key = "Key2";
    client1->login = "Alice21";
    client1->password = "4321";
    g_list_store_append(store, client2);

    client_t *client3 = g_new(client3, 1);
    client1->name = "Charlie";
    client1->key = "Key3";
    client1->login = "Charlie31";
    client1->password = "1111";
    g_list_store_append(store, client3);

    return store;
}

static char* 
get_name_client(GObject *item) {
    client_t *client = (client_t*) item;
    return client->name;
}

static char* 
get_key_client(GObject *item) {
    client_t *client = (client_t*) item;
    return client->key;
}

static char* 
get_login_client(GObject *item) {
    client_t *client = (client_t*) item;
    return client->login;
}

static char* 
get_pass_client(GObject *item) {
    client_t *client = (client_t*) item;
    return client->password;
}

static void
quit_activated(GSimpleAction *action, GVariant *parameter, GApplication *application) {
    g_application_quit (application);
}

static void
create_window(void)
{
    GtkWidget *win;

    win = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(win), "New Window");
    gtk_window_set_default_size(GTK_WINDOW(win), 320, 200);
    gtk_widget_show(win); 
}

static void
app_activate (GApplication *application) {
    GtkApplication *app = GTK_APPLICATION (application);
    GtkWidget *win = gtk_application_window_new (app);

    gtk_window_set_title (GTK_WINDOW (win), "AuthSys");
    gtk_window_set_default_size (GTK_WINDOW (win), 800, 600);

    gtk_application_window_set_show_menubar (GTK_APPLICATION_WINDOW (win), TRUE);
    gtk_window_present (GTK_WINDOW (win));
}

static void
app_startup (GApplication *application) {
    GtkApplication *app = GTK_APPLICATION (application);

    GSimpleAction *act_quit = g_simple_action_new ("quit", NULL);
    g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (act_quit));
    g_signal_connect (act_quit, "activate", G_CALLBACK (quit_activated), application);

    GSimpleAction *act_new = g_simple_action_new ("add", NULL);
    g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (act_new));
    g_signal_connect (act_new, "activate", G_CALLBACK (create_window), application);

    GMenu *menubar = g_menu_new ();
    GMenuItem *menu_item_menu = g_menu_item_new ("Menu", NULL);
    GMenuItem *menu_item_client = g_menu_item_new ("Client", NULL);
    GMenuItem *menu_item_user = g_menu_item_new ("User", NULL);
    GMenuItem *menu_item_help = g_menu_item_new ("Help", NULL);

    GMenu *menu_main = g_menu_new ();
    GMenu *menu_client = g_menu_new();
    GMenu *menu_user = g_menu_new();
    GMenu *menu_help = g_menu_new();
    
    GMenuItem *menu_item_quit = g_menu_item_new ("Quit", "app.quit");
    GMenuItem *menu_item_info = g_menu_item_new ("Help", NULL);

    GMenuItem *menu_item_add_client = g_menu_item_new ("Add", "app.add");
    GMenuItem *menu_item_delete_client = g_menu_item_new ("Delete", NULL);
    GMenuItem *menu_item_update_client = g_menu_item_new ("Update", NULL);
    GMenuItem *menu_item_list_client = g_menu_item_new ("List", NULL);
    
    GMenuItem *menu_item_add_user = g_menu_item_new ("Add", NULL);
    GMenuItem *menu_item_delete_user = g_menu_item_new ("Delete", NULL);
    GMenuItem *menu_item_update_user = g_menu_item_new ("Update", NULL);
    GMenuItem *menu_item_list_user = g_menu_item_new ("List", NULL);    

    g_menu_append_item(menu_main, menu_item_quit);
    g_menu_append_item(menu_help, menu_item_info);
    g_menu_append_item(menu_client, menu_item_add_client);
    g_menu_append_item(menu_client, menu_item_delete_client);
    g_menu_append_item(menu_client, menu_item_update_client);
    g_menu_append_item(menu_client, menu_item_list_client);
    g_menu_append_item(menu_user, menu_item_add_user);
    g_menu_append_item(menu_user, menu_item_delete_user);
    g_menu_append_item(menu_user, menu_item_update_user);
    g_menu_append_item(menu_user, menu_item_list_user);

    g_object_unref(menu_item_quit);
    g_object_unref(menu_item_info);
    g_object_unref(menu_item_add_client);
    g_object_unref(menu_item_delete_client);
    g_object_unref(menu_item_update_client);
    g_object_unref(menu_item_list_client);
    g_object_unref(menu_item_add_user);
    g_object_unref(menu_item_delete_user);
    g_object_unref(menu_item_update_user);
    g_object_unref(menu_item_list_user);

    g_menu_item_set_submenu(menu_item_menu, G_MENU_MODEL (menu_main));
    g_menu_item_set_submenu(menu_item_client, G_MENU_MODEL (menu_client));
    g_menu_item_set_submenu(menu_item_user, G_MENU_MODEL (menu_user));
    g_menu_item_set_submenu(menu_item_help, G_MENU_MODEL (menu_help));

    g_object_unref(menu_main);
    g_object_unref(menu_client);
    g_object_unref(menu_user);
    g_object_unref(menu_help);

    g_menu_append_item(menubar, menu_item_menu);
    g_menu_append_item(menubar, menu_item_client);
    g_menu_append_item(menubar, menu_item_user);
    g_menu_append_item(menubar, menu_item_help);

    g_object_unref(menu_item_menu);
    g_object_unref(menu_item_client);
    g_object_unref(menu_item_user);
    g_object_unref(menu_item_help);

    GListStore *client_list = create_client_list();
    GtkWidget *column_view = gtk_column_view_new(GTK_SELECTION_MODEL(g_list_store_get_model(client_list)));

    GtkColumnViewColumn *name_column = gtk_column_view_column_new(
        "Name",
        gtk_label_new(NULL),
        (GtkListItemFactoryFunc) get_name_client
    );
    gtk_column_view_append_column(GTK_COLUMN_VIEW(column_view), username_column);

    GtkColumnViewColumn *key_column = gtk_column_view_column_new(
        "Key",
        gtk_label_new(NULL),
        (GtkListItemFactoryFunc) get_key_client
    );

    GtkColumnViewColumn *login_column = gtk_column_view_column_new(
        "Login",
        gtk_label_new(NULL),
        (GtkListItemFactoryFunc) get_login_client
    );

    GtkColumnViewColumn *password_column = gtk_column_view_column_new(
        "Password",
        gtk_label_new(NULL),
        (GtkListItemFactoryFunc) get_pass_client
    );

    gtk_column_view_append_column(GTK_COLUMN_VIEW(column_view), email_column);

    gtk_window_set_child(GTK_WINDOW(window), column_view);

    gtk_widget_show(window);
 
    gtk_application_set_menubar (GTK_APPLICATION (app), G_MENU_MODEL (menubar));
}

#define APPLICATION_ID "com.github.ptfn"

int
main (int argc, char **argv) {
    GtkApplication *app;
    int stat;

    app = gtk_application_new (APPLICATION_ID, G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "startup", G_CALLBACK (app_startup), NULL);
    g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);

    stat = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return stat;
}
