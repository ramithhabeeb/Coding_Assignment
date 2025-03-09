# Library Management System

This is a C++ program for managing a library system. It allows users (students, faculty) to borrow and return books, manage fines, and view their borrowing history. Librarians can manage books and users in the system.

## Compilation and Execution

### Compile the Program:
Use a C++ compiler to compile the program. For example:
```bash
g++ -o library_management.cpp
```

### Run the Program:
Execute the compiled program:
```bash
./library_management
```

## Features

### User Roles:
- **Student**: Can borrow up to 3 books for 15 days. Fines are charged at ₹10 per day for overdue books.
- **Faculty**: Can borrow up to 5 books for 30 days. No fines are charged.
- **Librarian**: Can add new books and users to the system.

### Book Management:
- Add new books to the library.
- Borrow and return books.
- View the status of books (available/borrowed).

### User Management:
- Add new users (students, faculty, or librarians).
- View borrowed books and borrowing history.
- Pay fines (for students).

### Persistence:
- Save and load library data to/from a file (`library.txt`).

## Usage Guide

### Initial Setup:
- When you run the program for the first time, it will load data from `library.txt` (if the file exists).
- If the file does not exist, the program will start with an empty library.

### Main Menu:
When you run the program, you will see the following menu:
```bash
Who are you?
1. Student
2. Faculty
3. Librarian
4. Exit
```
Choose your role by entering the corresponding number.

### Student Menu:
```bash
Menu Options:
1. Logout
2. Display all books
3. Display borrowed books
4. Borrow a book
5. Return a book
6. Show fines
7. Pay fines
```
- **Display all books**: View all books in the library.
- **Display borrowed books**: View books you have borrowed.
- **Borrow a book**: Borrow a book by entering its title.
- **Return a book**: Return a book by entering its title.
- **Show fines**: View any fines you owe (for students only).
- **Pay fines**: Pay fines (for students only).

### Faculty Menu:
```bash
Menu Options:
1. Logout
2. Display all books
3. Display borrowed books
4. Borrow a book
5. Return a book
```
- **Display all books**: View all books in the library.
- **Display borrowed books**: View books you have borrowed.
- **Borrow a book**: Borrow a book by entering its title.
- **Return a book**: Return a book by entering its title.

### Librarian Menu:
```bash
Menu Options:
1. Logout
2. Display all books
3. Add a book
4. Add a user
5. Delete a Book
6. Delete a User
```
- **Display all books**: View all books in the library.
- **Add a book**: Add a new book to the library by entering its details.
- **Add a user**: Add a new user (student, faculty, or librarian) to the system.
- **Delete a book**: Deletes a book from the library by entering its ISBN.
- **Add a user**: Deletes a user (student, faculty, or librarian) from the system by entering their User ID.

### Exit:
Choose **Exit** from the main menu to save the library state and exit the program.

## Example Workflow

### Add a Book (Librarian):
1. Log in as a librarian.
2. Choose **Add a book**.
3. Enter the book details (title, author, publisher, year, ISBN).

### Borrow a Book (Student):
1. Log in as a student.
2. Choose **Borrow a book**.
3. Enter the title of the book you want to borrow.

### Return a Book (Student):
1. Log in as a student.
2. Choose **Return a book**.
3. Enter the title of the book you want to return.

### Pay Fines (Student):
1. Log in as a student.
2. Choose **Show fines** to view your fines.
3. Choose **Pay fines** to pay the fines.

## File Format (`library.txt`)
The program saves and loads data from a file named `library.txt`. The file format is as follows:

### Books:
```bash
Book:Title,Author,Publisher,Year,ISBN,Status,BorrowDate,ReturnDate
```
**Example:**
```bash
Book:Book1,Author1,Publisher1,2000,ISBN1,Borrowed,1739145600,1741533402
```

### Users:
```bash
User:Name,ID,Role,FineAmount,FineCalDate
```
**Example:**
```bash
User:Student1,S1,Student,0,1741533408
```

### Borrowed Books:
```bash
Borrowed Books:UserID,ISBN
```
**Example:**
```bash
Borrowed Books:S1,ISBN1
```
### Borrowing History:
```bash
Borrowed History:UserID,ISBN
```
**Example:**
```bash
Borrowing History:S1,ISBN1
```


## Contributing
If you'd like to contribute to this project, feel free to:
- Report issues.
- Suggest new features.
- Submit pull requests.



