#include <bits/stdc++.h>

using namespace std;

int date_diff(time_t time1, time_t time2) {
    double difference = difftime(time2, time1); 
    return difference / (60 * 60 * 24);         
}

class book{
    protected:
        string title;
        string author;
        string publisher;
        int year;
        string ISBN;
        string status;
        time_t borroedate;
        time_t returndate;
    public:
        book(){
            this->borroedate=0;
            this->returndate=0;
        }
        book(string title, string author,string publisher, int year, string ISBN,string status,time_t borrowdate,time_t returndate){
            this->title=title;
            this->author=author;
            this->publisher=publisher;
            this->year=year;
            this->ISBN=ISBN;
            this->status=status;
            this->borroedate=borrowdate;
            this->returndate=returndate;
        }
        book(string title, string author,string publisher, int year, string ISBN,string status){
            this->title=title;
            this->author=author;
            this->publisher=publisher;
            this->year=year;
            this->ISBN=ISBN;
            this->status=status;
            this->borroedate=0;
            this->returndate=0;
        }
        book(string title, string author,string publisher, int year, string ISBN){
            this->title=title;
            this->author=author;
            this->publisher=publisher;
            this->year=year;
            this->ISBN=ISBN;
            this->status="Available";
            this->borroedate=0;
            this->returndate=0;
        }
        string get_title() const{ return title;}
        string get_author() const{ return author;}
        string get_publisher() const{ return publisher;}
        string get_ISBN() const{ return ISBN;}
        int get_year() const{ return year;}
        time_t get_borrowdate() const{ return borroedate;}
        string get_status() const{ return status;}
        time_t get_returndate() const{ return returndate;}

        void set_title(string x){ title=x;}
        void set_author(string x){ author=x;}
        void set_publisher(string x){ publisher=x;}
        void set_ISBN(string x){ ISBN=x;}
        void set_year(int x){ year=x;}
        void set_status(string x){ status=x;}
        void set_borrowdate(time_t now){ borroedate=now;}
        void set_returndate(time_t now){ returndate=now;}
        void displayInfo() const {
            cout << "Title: " << title << ", Author: " << author << ", Publisher: " << publisher
                 << ", Year: " << year << ", ISBN: " << ISBN << ", Status: " << status << endl;
        }
        void inputbook() {
            cout << "Enter Title: ";
            cin.ignore();
            getline(cin,title);
            cout << "Author: ";
            getline(cin,author);
            cout << "Publisher: ";
            getline(cin,publisher);
            cout<<"ISBN: ";
            cin>>ISBN;
            cout<<"Year: ";
            cin>>year;
            cout<<"Status: ";
            cin>>status;
        }
};

class Account{
    public:
        vector<book*> bd_books;
        vector<book*> br_history;
        int fineamount;

        Account(){
            this->fineamount=0;
        }
        Account(int fine){
            fineamount=fine;
        }

        vector<book*>& get_br_history() {return br_history;}
        vector<book*>& get_bd_books() {return bd_books;}
        int getFineAmount() const { return fineamount;}


        void SetFineAmount(int fa) { fineamount=fa;}

        void payFines(int finerate) {
            calculate_fines(finerate);
            cout<<"Amount to be paid is: "<< fineamount<<endl;
            int x;
            cout << "Enter amount to pay: ";
            cin>>x;
            fineamount -=x ;
        }
        void calculate_fines(int finerate) {
            time_t now = time(NULL);
        
            for (auto it : bd_books) {
                // Check if the book is overdue
                int overdue_days = date_diff(it->get_borrowdate(), now) - 15;
                if (overdue_days > 0) {
                    if (it->get_returndate()==it->get_borrowdate()) {
                        fineamount += finerate * overdue_days;
                        it->set_returndate(now);
                    }
                    else {
                        fineamount += finerate * date_diff(it->get_returndate(), now);
                    }
                }

            }
        }
        
        void showFines(int finerate) {
            calculate_fines(finerate);
            cout << "Fine anount: " << fineamount << " rupees." << endl;
        }
        void displayBorrowedBooks() const {
            if(bd_books.size()==0){
                cout<<"No books borrowed currently"<<endl;
                return;
            }
            cout << "Borrowed Books:" << endl;
            for (const auto& book : bd_books) {
                book->displayInfo();
            }
        }
        void displayBorrowHistory() const{
            if(bd_books.size()==0){
                cout<<"No history to Show"<<endl;
                return;
            }
            cout << "Brrowed Book History:" << endl;
            for (const auto& book : br_history) {
                book->displayInfo();
            }
        }
};
class AllUser{
    protected:
        string name;
        string id;
        string role;
    public:
        AllUser(string name, string id, string role){
            this->name=name;
            this->id=id;
            this->role=role;
        }
        AllUser(){}
        void set_name(string x){name=x;}
        void set_id(string x){id=x;}
        void set_role(string x){role=x;}
        string get_name(){ return name;}
        string get_id(){ return id;}
        string get_role(){ return role;}
        void displayInfo() const {
            cout << "Name: " << name << ", ID: " << id << ", Role: " << role << endl;
        }
};
class User:public AllUser{
    protected:
        Account* account;
    public:
        int maxbooks;
        int maxdays;
        int finerate;
        int get_maxbooks(){return maxbooks;}
        int get_maxdays(){return maxdays;}
        int get_finerate(){return finerate;}

        Account * get_account(){ return account;}
        
        User(string name, string id, string role){
            this->name=name;
            this->id=id;
            this->role=role;
            account = new Account();
        }
        User(string name, string id, string role,int fineamount){
            this->name=name;
            this->id=id;
            this->role=role;
            account = new Account(fineamount);
        }
        User(){
            account = new Account();
        }
        
        virtual void borrowBook(book* book) = 0;
        virtual void returnBook(book* book) = 0;
        ~User() {
            delete account;
        }

};

class faculty:public User{
    public:
        faculty(){
            maxbooks=5;
            maxdays=30;
            finerate=0;
        }
        faculty(string name,string id):User(name,id, "Faculty"){
            maxbooks=5;
            maxdays=30;
            finerate=0;
        }
        faculty(string name,string id,int fineamt):User(name,id, "Faculty",fineamt){
            maxbooks=5;
            maxdays=30;
            finerate=0;
        }
        int getmaxbooks(){return maxbooks;}
        int getmaxdays(){return maxdays;}
        void borrowBook(book* bk) {
            if (bk->get_status() != "Available") {
                cout << "Book is not available for borrowing." << endl;
                return;}
            if (account->bd_books.size() >= maxbooks) {
                cout << "Faculty cannot borrow more than " << maxbooks<< " books." << endl;
                return;}
            for(auto it: account->bd_books){
                if(date_diff(it->get_borrowdate(),it->get_returndate())>30){
                    cout << "You have over due books" << endl;
                    return;
                }
            }
            bk->set_status("Borrowed");
            time_t now = time(0);
            bk->set_borrowdate(now);
            bk->set_returndate(now);
            account->bd_books.push_back(bk);
            cout << "Book borrowed successfully." << endl;
        }
        void returnBook(book* bk) {
            auto it = account->bd_books.begin();
            for (; it != account->bd_books.end(); ++it) {
                if (*it == bk) {
                    break;}}
            bk->set_status("Available");
            bk->set_borrowdate(0);
            bk->set_returndate(0);
            account->br_history.push_back(bk);
            account->bd_books.erase(it);
            cout << "Book returned successfully." << endl;
        }
};

class student:public User{
    public:
        student(){
            maxbooks=3;
            maxdays=15;
            finerate=10;
        }
        student(string name,string id):User(name,id, "Student"){
            maxbooks=3;
            maxdays=15;
            finerate=10;
        }
        student(string name,string id,int fineamt):User(name,id, "Student",fineamt){
            maxbooks=3;
            maxdays=15;
            finerate=10;
        }
        int getmaxbooks(){return maxbooks;}
        int getmaxdays(){return maxdays;}
        int getfinerate(){return finerate;}
        void borrowBook(book* bk) {
            if (bk->get_status() != "Available") {
                cout << "Book is not available for borrowing." << endl;
                return;}
            account->calculate_fines(finerate);
            if (account->fineamount > 0) {
                cout << "Outstanding fines must be cleared before borrowing." << endl;
                return;}
            if (account->bd_books.size() >= maxbooks) {
                cout << "Student cannot borrow more than " << maxbooks<< " books." << endl;
                return;}
            
            bk->set_status("Borrowed");
            time_t now = time(0);
            bk->set_borrowdate(now);
            bk->set_returndate(now);
            account->bd_books.push_back(bk);
            cout << "Book borrowed successfully." << endl;
        }
        void returnBook(book* bk) {
            auto it = account->bd_books.begin();
            for (; it != account->bd_books.end(); ++it) {
                if (*it == bk) {
                    bk->set_status("Available");
                    account->calculate_fines(finerate);
                    bk->set_borrowdate(0);
                    bk->set_returndate(0);
                    account->get_br_history().push_back(bk);
                    account->bd_books.erase(it);
                    cout << "Book returned successfully." << endl;
                    break;
                }
            }
            
            
        }

    };





class library{
    protected:
        vector<book>books;
        vector<User*>users;
        vector<AllUser*>librarians;
    public:
        void addBook(const book& book) {books.push_back(book);}
        void addUser(User* user) { 
            users.push_back(user);
        }
        void addLibrarian(AllUser* librarian) { librarians.push_back(librarian);}
        void deleteBook(string ISBN) {
            auto it1 =find_if(books.begin(), books.end(), [&ISBN](book book) {
                return book.get_ISBN() == ISBN;
            });
            
            if (it1 != books.end()) {
                books.erase(it1); 
                cout<<"Book deleted Sucessfully";
            } else {
                cout << "User not found!" << endl;
            }
        }
        void deleteUser(string id) { 
            auto it1 =find_if(users.begin(), users.end(), [&id](User* user) {
                return user->get_id() == id;
            });
            
            if (it1 != users.end()) {
                users.erase(it1); // Remove the user from the vector
                cout<<"User deleted Sucessfully";
                return;
            }
            auto it2 = find_if(librarians.begin(), librarians.end(), [&id](AllUser* user) {
                return user->get_id() == id;
            });
            
            if (it2 != librarians.end()) {
                librarians.erase(it2); 
                cout<<"User deleted Sucessfully";
            } else {
                cout << "User not found!" << endl;
            }
        }


        const vector<book>& getBooks() const {return books;}
        const vector<User*>& getUsers() const {return users;}
        const vector<AllUser*>& getLibrarians() const {return librarians;}

        // const vector<Account>& getAccounts() const {return accounts;}
        book* findBookByTitle(const string& title) {
            for (auto& book : books) {
                if (book.get_title() == title) {
                    return &book;
                }
            }
            return nullptr;
        }
        book* findBookByISBN(const string& ISBN) {
            for (auto& book : books) {
                if (book.get_ISBN() == ISBN) {
                    return &book;
                }
            }
            return nullptr;
        }
        User* findUserById(const string& user_id) {
            for (auto& user : users) {
                if ( user->get_id()== user_id) {
                    return user;
                }
            }
            return nullptr;
        }
        AllUser* findLibrarianById(const string& user_id) {
            
            for (auto& librarian : librarians) {
                if ( librarian->get_id()== user_id) {
                    return librarian;
                }
            }
            return nullptr;
        }
        void displayAllBooks() const {
            if(books.size()==0){
                cout<<"No books to display";
                return;
            }
            cout << "Library Books:" << endl;
            for (const auto& book : books) {
                book.displayInfo();
            }
        }
        void displayAllUsers() const {
            if(users.size()==0){
                cout<<"No users to display"<<endl;
                return;
            }
            cout << "Library Users:" << endl;
            for (const auto& user : users) {
                user->displayInfo();
            }
            for (const auto& librarian : librarians) {
                librarian->displayInfo();
            }

        }
};

class librarian:public AllUser,public library{
    protected:
    public:
        librarian(){}
        librarian(string name,string id){
            this->name=name;
            this->id=id;
            this->role = "Librarian";
        }


};






void saveLibraryState(const library& library) {
    // Open the file in truncation mode to erase previous data
    ofstream file("library.txt", ios::out | ios::trunc);
    if (!file) {
        cerr << "Failed to save library state." << endl;
        return;
    }

    // Save books
    for (const auto& book : library.getBooks()) {
        file << "Book:" << book.get_title() << "," << book.get_author() << "," << book.get_publisher() << ","
             << book.get_year() << "," << book.get_ISBN() << "," << book.get_status() << "," << book.get_borrowdate()
             << "," << book.get_returndate() << endl;
    }

    // Save Students and Faculty
    for (const auto& user : library.getUsers()) {
        file << "User:" << user->get_name() << "," << user->get_id() << "," << user->get_role()
             << "," << user->get_account()->getFineAmount() << endl;
    }

    // Save librarians
    for (const auto& librarian : library.getLibrarians()) {
        file << "User:" << librarian->get_name() << "," << librarian->get_id() << "," << librarian->get_role() << endl;
    }

    // Save accounts (borrowed books and borrowing history)
    for (const auto& user : library.getUsers()) {
        for (auto it : user->get_account()->get_bd_books()) {
            file << "Borrowed Books:" << user->get_id() << "," << it->get_ISBN() << endl;
        }
        for (auto it : user->get_account()->get_br_history()) {
            file << "Borrowing History:" << user->get_id() << "," << it->get_ISBN() << endl;
        }
    }

    file.flush(); // Ensure data is written
    file.close();
}


void loadLibraryState(library& library) {
    ifstream file("library.txt");
    if (!file.is_open()) {
        cerr << "Failed to load library state." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("Book:") == 0) {
            // Parse book data
            string data = line.substr(5);
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = data.find(',')) != string::npos) {
                tokens.push_back(data.substr(0, pos));
                data.erase(0, pos + 1);
            }
            tokens.push_back(data);

            book book(tokens[0], tokens[1], tokens[2], stoi(tokens[3]), tokens[4],tokens[5],stol(tokens[6]),stol(tokens[7]));
            library.addBook(book);
        } else if (line.find("User:") == 0) {
            string data = line.substr(5);
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = data.find(',')) != string::npos) {
                tokens.push_back(data.substr(0, pos));
                data.erase(0, pos + 1);
            }
            tokens.push_back(data);

            if (tokens[2] == "Student") {
                library.addUser(new student(tokens[0],tokens[1],stoi(tokens[3])));
            } else if (tokens[2] == "Faculty") {
                library.addUser(new faculty(tokens[0],tokens[1],stoi(tokens[3])));
            } else if (tokens[2] == "Librarian") {
                library.addLibrarian(new librarian(tokens[0],tokens[1]));
            }
        }else if (line.find("Borrowed Books:") == 0) {

            string data = line.substr(15);
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = data.find(',')) != string::npos) {
                tokens.push_back(data.substr(0, pos));
                data.erase(0, pos + 1);
            }
            tokens.push_back(data);
            library.findUserById(tokens[0])->get_account()->get_bd_books().push_back(library.findBookByISBN(tokens[1]));

        }else if (line.find("Borrowing History:") == 0) {
            string data = line.substr(18);
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = data.find(',')) != string::npos) {
                tokens.push_back(data.substr(0, pos));
                data.erase(0, pos + 1);
            }
            tokens.push_back(data);
            library.findUserById(tokens[0])->get_account()->get_br_history().push_back(library.findBookByISBN(tokens[1]));
        }
    }

    file.close();
}



int main() {
    cout << "Program started" << endl;
    library lib;
    loadLibraryState(lib);
    
    // lib.addBook(book("Book1", "Author1", "Publisher1", 2000, "ISBN1"));
    // lib.addBook(book("Book2", "Author2", "Publisher2", 2001, "ISBN2"));
    // lib.addBook(book("Book3", "Author3", "Publisher3", 2002, "ISBN3"));
    // lib.addBook(book("Book4", "Author4", "Publisher4", 2003, "ISBN4"));
    // lib.addBook(book("Book5", "Author5", "Publisher5", 2004, "ISBN5"));

    // // Add initial users
    // lib.addUser(new student("Student1","S1"));
    // lib.addUser(new student( "Student2","S2"));
    // lib.addUser(new student( "Student3","S3"));
    // lib.addUser(new faculty( "Faculty1","F1"));
    // lib.addUser(new faculty("Faculty2","F2"));
    // lib.addLibrarian(new librarian( "Librarian1","L1"));

    // Save initial state
    // saveLibraryState(lib);
    
    while (true) {
        cout << "Who are you?" << endl;
        cout << "1. Student" << endl;
        cout << "2. Faculty" << endl;
        cout << "3. Librarian" << endl;
        cout << "4. Exit" << endl;
        
        int choice;
        cin >> choice;
        
        if (choice == 4) break;
        
        string userId;
        cout << "Enter your user ID: ";
        cin >> userId;
        if(choice==3){
            AllUser* user = lib.findLibrarianById(userId);
            if (!user) {
                cout << "User not found!" << endl;
                continue;
            }
            while(true){
                cout << "\nMenu Options:" << endl;
                cout << "1. Logout" << endl;
                cout << "2. Display all books" << endl;
                cout << "3. Add a book" << endl;
                cout << "4. Add a user" << endl;
                cout << "5. Delete a book" << endl;
                cout << "6. Delete a user" << endl;

                int option;
                cin>>option;
                if (option == 1) break;
                
                else if (option == 2) {
                    lib.displayAllBooks();
                } 
                else if (option == 3) {
                    book newBook;
                    newBook.inputbook();
                    lib.addBook(newBook);
                    cout << "Book added successfully!" << endl;
                } 
                else if (option == 4) {
                    string name, id, role;
                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin,name);
                    cout << "Enter ID: ";
                    cin >> id;
                    cout << "Enter Role (Student/Faculty/Librarian): ";
                    cin >> role;
                    
                    if (role == "Student") {
                        lib.addUser(new student(name, id));
                    } else if (role == "Faculty") {
                        lib.addUser(new faculty(name, id));
                    } else if (role == "Librarian") {
                        lib.addLibrarian(new librarian(name, id));
                    } else {
                        cout << "Invalid role!" << endl;
                    }
                    cout << "User added successfully!" << endl;
                } 
                else if(option==5){
                    string ISBN;
                    cout<<"Enter ISBN: ";
                    cin>>ISBN;
                    lib.deleteBook(ISBN);
                    cout<<"Book deleted sucessdully";
                }
                else if(option==6){
                    string id;
                    cout<<"Enter id: ";
                    cin>>id;
                    lib.deleteUser(id);
                    cout<<"User deleted sucessdully";
                }
                else {
                    cout << "Invalid option!" << endl;
                }
            }
        }
        else{
            User* user = lib.findUserById(userId);
            if ((choice == 1 && user->get_role() != "Student") || (choice == 2 && user->get_role() != "Faculty")){
                cout << "User role mismatch!" << endl;
                continue;
            };
            if (!user) {
                cout << "User not found!" << endl;
                continue;
            }
            Account* account = user->get_account();

            while(true){
                cout << "\nMenu Options:" << endl;
                cout << "1. Logout" << endl;
                cout << "2. Display all books" << endl;
                if (choice == 1) { 
                
                cout << "3. Display borrowed books" << endl;
                cout << "4. Borrow a book" << endl;
                cout << "5. Return a book" << endl;
                cout << "6. Show fines" << endl;
                cout << "7. Pay Fines"<<endl;
                cout << "8. Display borrowing history" << endl;

                } else if (choice == 2) {
                    cout << "3. Display borrowed books" << endl;
                    cout << "4. Borrow a book" << endl;
                    cout << "5. Return a book" << endl;
                    cout << "8. Display borrowing history" << endl;

                }
                int option;
                cin >> option;
                if (option == 1) break;
                
                if (option == 2) {
                    lib.displayAllBooks();
                } 
                else if ((choice == 1 || choice == 2) && option == 3) {
                    account->displayBorrowedBooks();
                } 
                else if ((choice == 1 || choice == 2) && option == 4) {
                    string bookTitle;
                    cout << "Enter book title to borrow: ";
                    cin.ignore();
                    getline(cin, bookTitle);
                    book* bk = lib.findBookByTitle(bookTitle);
                    if (bk) user->borrowBook(bk);
                    else cout << "Book not found!" << endl;
                } 
                else if ((choice == 1 || choice == 2) && option == 5) {
                    string bookTitle;
                    cout << "Enter book title to return: ";
                    cin.ignore();
                    getline(cin, bookTitle);
                    book* bk = lib.findBookByTitle(bookTitle);
                    if (bk) user->returnBook(bk);
                    else cout << "Book not found!" << endl;
                } 
                else if (choice == 1 && option == 6) {
                    account->showFines(user->get_finerate());
                } 
                else if (choice == 1 && option == 7) {
                    account->payFines(user->get_finerate());
                }
                else if (option==8){
                    account->displayBorrowHistory();
                }
                else {
                    cout << "Invalid option!" << endl;
                }
            }
    }
}
saveLibraryState(lib);
return 0;

}


