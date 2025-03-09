k("Book1", "Author1", "Publisher1", 2000, "ISBN1"));
    lib.addBook(book("Book2", "Author2", "Publisher2", 2001, "ISBN2"));
    lib.addBook(book("Book3", "Author3", "Publisher3", 2002, "ISBN3"));
    lib.addBook(book("Book4", "Author4", "Publisher4", 2003, "ISBN4"));
    lib.addBook(book("Book5", "Author5", "Publisher5", 2004, "ISBN5"));

    // Add initial users
    lib.addUser(new student("Student1","S1"));
    lib.addUser(new student( "Student2","S2"));
    lib.addUser(new student( "Student3","S3"));
    lib.addUser(new faculty( "Faculty1","F1"));
    lib.addUser(new faculty("Faculty2","F2"));
    lib.addLibrarian(new librarian( "Librarian1","L1"));

    // Save initial state
    saveLibraryState(lib);