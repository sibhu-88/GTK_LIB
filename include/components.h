GtkWidget *create_headerbar();
GtkWidget *create_dashboard();
GtkWidget *create_sidemenu(GtkWidget *content_box);
void create_home(GtkWidget *container);
void add_book(GtkWidget *content_box, Book **books);
void delete_book(GtkWidget *content_box, Book **books);
void issue_book(GtkWidget *content_box, Book **books);
void return_book(GtkWidget *content_box, Book **books);
void sort_books(GtkWidget *content_box, Book *books);
void books_list(GtkWidget *content_box, Book *books);
void issued_details(GtkWidget *content_box, Book *books);
void save_all_data(Book *books);
void restore_books_data(Book **books);

void add_book_to_list(const char *title, const char *author, int copy, Book **books);
void issueBook_list(Book *book, int book_id, const char *name, int student_id, const char *issue_date);
void returnBook(GtkWidget *button, Book *book, int book_id, int student_id, const char *return_date);

Book *find_book_by_id(Book *books, int book_id);
void show_dialog(GtkMessageType type, const gchar *title, const gchar *icon_name, const gchar *message, const gchar *secondary);