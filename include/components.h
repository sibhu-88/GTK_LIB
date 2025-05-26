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
void save_books(Book *books);

void add_book_to_list(const char *title,const char *author, int copy, Book **books);
void issueBook(Book *book, int book_id, const char *name, int student_id);
void returnBook(Book *book, int book_id,int student_id);