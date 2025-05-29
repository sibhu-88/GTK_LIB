void dashboard_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box);
void addbook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box);
void bookslist_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box);
void sortbooks_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box);
void deletebook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box);
void issuebook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box);
void returnbook_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box);
void issueddetails_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box);
void save_clicked(GtkListBox *listbox, GtkListBoxRow *row, GtkWidget *content_box);

void add_book_callback(GtkWidget *widget, gpointer data);
void issueButton_clicked(GtkWidget *button, gpointer user_data);
void returnBook_clicked(GtkWidget *button, gpointer user_data);
void deleteButton_clicked(GtkWidget *button, gpointer user_data);

void sort_by_title_clicked(GtkWidget *button, gpointer user_data);
void sort_by_author_clicked(GtkWidget *button, gpointer user_data);

void on_profile_clicked(GtkWidget *widget, gpointer data);
void on_settings_clicked(GtkWidget *widget, gpointer data);
void on_search_book_clicked(GtkWidget *widget, gpointer data);