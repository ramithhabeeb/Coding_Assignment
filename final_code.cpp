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
            cin.ignore();
            getline(cin,author);
            cout << "Publisher: ";
            cin.ignore();
            getline(cin,publisher);
            cout<<"ISBN: ";
            cin>>ISBN;
            cout<<"Year: ";
            cin>>year;
            cout<<"Status: ";
            cin>>status;
        }
};
// class User{
//     protected:
//         string name;
//         string id;
//         string role;
//     public:
//         void set_name(string x){name=x;}
//         void set_id(string x){id=x;}
//         void set_role(string x){role=x;}
//         string get_name(){ return name;}
//         string get_id(){ return id;}
//         string get_role(){ return role;}
//         virtual Account* get_account(){}=0;
//         User(){}
//         User(string name,string id,string role){
//             this->name=name;
//             this->id=id;
//             this->role=role;
//         }
//         virtual void displayInfo() const {
//             cout << "ID: " << id << ", Name: " << name << ", Role: " << role << endl;
//         }
// };
class User{
    protected:
        string name;
        string id;
        string role;
        Account* account;
    public:
        int maxbooks;
        int maxdays;
        int finerate;
        int get_maxbooks(){return maxbooks;}
        int get_maxdays(){return maxdays;}
        int get_finerate(){return finerate;}

        void set_name(string x){name=x;}
        void set_id(string x){id=x;}
        void set_role(string x){role=x;}
        string get_name(){ return name;}
        string get_id(){ return id;}
        string get_role(){ return role;}

        virtual void displayInfo() const {
            cout << "ID: " << id << ", Name: " << name << ", Role: " << role << endl;
        }

        Account * get_account(){ return account;}
        
        User(string name, string id, string role){
            this->name=name;
            this->id=id;
            this->role=role;
            account = new Account();
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
        int getmaxbooks(){return maxbooks;}
        int getmaxdays(){return maxdays;}
        void borrowBook(book* bk) {
            if (bk->get_status() != "Available") {
                cout << "Book is not available for borrowing." << endl;
                return;}
            if (account->bd_books.size() >= maxbooks) {
                cout << "Faculty cannot borrow more than " << maxbooks<< " books." << endl;
                return;}
            account->calculate_fines(finerate);
            for(auto it: account->bd_books){
                if(date_diff(it->get_borrowdate(),it->get_returndate())>30){
                    cout << "You have over due books" << endl;
                    return;
                }
            }
            bk->set_status("Borrowed");
            time_t now = time(0);
            account->bd_books.push_back(bk);
            cout << "Book borrowed successfully." << endl;
        }
        void returnBook(book* bk) {
            auto it = account->bd_books.begin();
            for (; it != account->bd_books.end(); ++it) {
                if (*it == bk) {
                    break;}}
    
            bk->set_status("Available");
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
            account->bd_books.push_back(bk);
            cout << "Book borrowed successfully." << endl;
        }
        void returnBook(book* bk) {
            auto it = account->bd_books.begin();
            for (; it != account->bd_books.end(); ++it) {
                if (*it == bk) {
                    bk->set_status("Available");
                    account->calculate_fines(finerate);
                    account->get_br_history().push_back(bk);
                    account->bd_books.erase(it);
                    cout << "Book returned successfully." << endl;
                    break;
                }
            }
            
            
        }

    };



class Account{
    public:
        vector<book*> bd_books;
        vector<book*> br_history;
        int fineamount;
        time_t finecaldate;

        Account(){
            this->fineamount=0;
            finecaldate=0;
        }

        vector<book*>& get_br_history() {return br_history;}
        vector<book*>& get_bd_books() {return bd_books;}
        int getFineAmount() const { return fineamount;}
        time_t getFinecaldate() const { return finecaldate;}

        void payFines(int finerate) {
            calculate_fines(finerate);
            cout<<"Amount to be paid is: "<< fineamount<<endl;
            int x;
            cout << "Enter amount to pay: ";
            cin>>x;
            fineamount -=x ;
        }
        void calculate_fines(int finerate){
            time_t now=time(NULL);
            finecaldate=now;
            for(auto it: bd_books){
                if(it->get_returndate()!=finecaldate){
                    if(date_diff(it->get_borrowdate(),finecaldate)>15){
                        if(date_diff(it->get_borrowdate(),it->get_returndate())>15){
                            fineamount+=finerate*date_diff(it->get_returndate(),finecaldate);
                        }
                        else{
                            fineamount+=finerate*(date_diff(it->get_borrowdate(),finecaldate)-15);
                        }
                    }
                    }
                it->set_returndate(finecaldate);
            }
        }
        void showFines(int finerate) {
            calculate_fines(finerate);
            if (fineamount == 0) {
                cout << "No fines." << endl;
                return;
            }
            cout << "Fine anount: " << fineamount << " rupees." << endl;
        }
        void displayBorrowedBooks() const {
            cout << "Borrowed Books:" << endl;
            for (const auto& book : bd_books) {
                book->displayInfo();
            }
        }
        void displayBorrowHistory() const{
            cout << "Brrowed Book History:" << endl;
            for (const auto& book : br_history) {
                book->displayInfo();
            }
        }
};

class library{
    protected:
        vector<book>books;
        vector<User*>users;
        vector<librarian*>librarians;
    public:
        void addBook(const book& book) {books.push_back(book);}
        void addUser(User* user) { users.push_back(user);}
        void addLibrarian(librarian* librarian) { librarians.push_back(librarian);}

        const vector<book>& getBooks() const {return books;}
        const vector<User*>& getUsers() const {return users;}
        const vector<librarian*>& getLibrarians() const {return librarians;}

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
        librarian* findLibrarianById(const string& user_id) {
            
            for (auto& librarian : librarians) {
                if ( librarian->get_id()== user_id) {
                    return librarian;
                }
            }
            return nullptr;
        }
        void displayAllBooks() const {
            cout << "Library Books:" << endl;
            for (const auto& book : books) {
                book.displayInfo();
            }
        }
        void displayAllUsers() const {
            cout << "Library Users:" << endl;
            for (const auto& user : users) {
                user->displayInfo();
            }
            for (const auto& librarian : librarians) {
                librarian->displayInfo();
            }

        }
};

class librarian:public library{
    protected:
        string name;
        string id;
        string role="Librarian";
    public:
        librarian(){}
        librarian(string name,string id){
            this->name=name;
            this->id=id;
        }

        void set_name(string x){name=x;}
        void set_id(string x){id=x;}
        void set_role(string x){role=x;}
        string get_name(){ return name;}
        string get_id(){ return id;}
        string get_role(){ return role;}

        virtual void displayInfo() const {
            cout << "ID: " << id << ", Name: " << name << ", Role: " << role << endl;
        }

};






void saveLibraryState(const library& library) {
    // Open the file in truncation mode to overwrite previous data
    ofstream file("library.txt", ios::trunc);
    if (!file.is_open()) {
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
        << "," << user->get_account()->getFineAmount() << "," << user->get_account()->getFinecaldate()<< endl;
    }
    // Save librarians
    for (const auto& librarian : library.getLibrarians()) {
        file << "User:" << librarian->get_name() << "," << librarian->get_id() << "," << librarian->get_role();
    }
    //Save accounts
    for (const auto& user : library.getUsers()) {
        for(auto it: user->get_account()->get_bd_books() ){
            file << "Borrowed Books:" <<user->get_id()<< "," << it->get_ISBN() << endl;
        }
        for(auto it: user->get_account()->get_br_history() ){
            file << "Borrowing History:" <<user->get_id()<< "," << it->get_ISBN() << endl;
        }
    }
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
            // book.set_status(tokens[5]);
            library.addBook(book);
        } else if (line.find("User:") == 0) {
            // Parse user data
            string data = line.substr(5);
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = data.find(',')) != string::npos) {
                tokens.push_back(data.substr(0, pos));
                data.erase(0, pos + 1);
            }
            tokens.push_back(data);

            if (tokens[2] == "Student") {
                library.addUser(new student(tokens[0],tokens[1]));
            } else if (tokens[2] == "Faculty") {
                library.addUser(new faculty(tokens[0],tokens[1]));
            } else if (tokens[2] == "Librarian") {
                library.addLibrarian(new librarian(tokens[0],tokens[1]));
            }
        }else if (line.find("Borrowed Books") == 0) {
            string data = line.substr(14);
            size_t pos = 0;
            vector<string> tokens;
            while ((pos = data.find(',')) != string::npos) {
                tokens.push_back(data.substr(0, pos));
                data.erase(0, pos + 1);
            }
            tokens.push_back(data);
            library.findUserById(tokens[0])->get_account()->get_bd_books().push_back(library.findBookByISBN(tokens[1]));
        }else if (line.find("Borrowing History:") == 0) {
            string data = line.substr(14);
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
    library lib;
    loadLibraryState(lib);
    
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
        
        User* user = lib.findUserById(userId);
        if (!user) {
            cout << "User not found!" << endl;
            continue;
        }
        
        Account* account = user->get_account();
        
        if ((choice == 1 && user->get_role() != "Student") ||
            (choice == 2 && user->get_role() != "Faculty") ||
            (choice == 3 && user->get_role() != "Librarian")) {
            cout << "User role mismatch!" << endl;
            continue;
        }
        
        while (true) {
            cout << "\nMenu Options:" << endl;
            cout << "1. Display all books" << endl;
            
            if (choice == 1) { 
                cout << "2. Display borrowed books" << endl;
                cout << "3. Borrow a book" << endl;
                cout << "4. Return a book" << endl;
                cout << "5. Show fines" << endl;
                cout << "6. Pay Fines"<<endl;
                cout << "6. Logout" << endl;
            } else if (choice == 2) {
                cout << "2. Display borrowed books" << endl;
                cout << "3. Borrow a book" << endl;
                cout << "4. Return a book" << endl;
                cout << "6. Logout" << endl;
            } else if (choice == 3) {
                cout << "2. Add a book" << endl;
                cout << "3. Add a user" << endl;
                cout << "6. Logout" << endl;
            }
            
            int option;
            cin >> option;
            
            if (option == 6) break;
            
            if (option == 1) {
                lib.displayAllBooks();
            } 
            else if ((choice == 1 || choice == 2) && option == 2) {
                account->displayBorrowedBooks();
            } 
            else if ((choice == 1 || choice == 2) && option == 3) {
                string bookTitle;
                cout << "Enter book title to borrow: ";
                cin.ignore();
                getline(cin, bookTitle);
                book* bk = lib.findBookByTitle(bookTitle);
                if (bk) user->borrowBook(bk);
                else cout << "Book not found!" << endl;
            } 
            else if ((choice == 1 || choice == 2) && option == 4) {
                string bookTitle;
                cout << "Enter book title to return: ";
                cin.ignore();
                getline(cin, bookTitle);
                book* bk = lib.findBookByTitle(bookTitle);
                if (bk) user->returnBook(bk);
                else cout << "Book not found!" << endl;
            } 
            else if (choice == 1 && option == 5) {
                account->showFines(10);
            } 
            else if (choice == 3 && option == 2) {
                book newBook;
                newBook.inputbook();
                lib.addBook(newBook);
                cout << "Book added successfully!" << endl;
            } 
            else if (choice == 3 && option == 3) {
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
            } else {
                cout << "Invalid option!" << endl;
            }
        }
    }
    
    saveLibraryState(lib);
    return 0;
}
