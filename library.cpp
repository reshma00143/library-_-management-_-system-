#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool issued;
};

vector<Book> books;
const string FILE_NAME = "library.txt";

void saveData() {
    ofstream file(FILE_NAME);

    for (const auto &b : books) {
        file << b.id << '\n';
        file << b.title << '\n';
        file << b.author << '\n';
        file << b.issued << '\n';
    }
}

void loadData() {
    ifstream file(FILE_NAME);
    Book b;

    while (file >> b.id) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!getline(file, b.title)) break;
        if (!getline(file, b.author)) break;
        if (!(file >> b.issued)) break;

        file.ignore(numeric_limits<streamsize>::max(), '\n');
        books.push_back(b);
    }
}

int findBook(int id) {
    for (int i = 0; i < (int)books.size(); i++) {
        if (books[i].id == id)
            return i;
    }
    return -1;
}

void addBook() {
    Book b;

    cout << "Enter Book ID: ";
    if (!(cin >> b.id)) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (findBook(b.id) != -1) {
        cout << "Book ID already exists!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Book Title: ";
    getline(cin, b.title);

    cout << "Enter Author Name: ";
    getline(cin, b.author);

    if (b.title.empty() || b.author.empty()) {
        cout << "Title and author cannot be empty!\n";
        return;
    }

    b.issued = false;
    books.push_back(b);
    saveData();

    cout << "Book added successfully!\n";
}

void displayBooks() {
    if (books.empty()) {
        cout << "No books available!\n";
        return;
    }

    cout << "\n===== BOOK LIST =====\n";

    for (const auto &b : books) {
        cout << "Book ID: " << b.id << '\n';
        cout << "Title: " << b.title << '\n';
        cout << "Author: " << b.author << '\n';
        cout << "Status: "
             << (b.issued ? "Issued" : "Available") << "\n\n";
    }
}

void searchBook() {
    int id;

    cout << "Enter Book ID to Search: ";
    if (!(cin >> id)) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findBook(id);

    if (index == -1) {
        cout << "Book not found!\n";
        return;
    }

    cout << "Book ID: " << books[index].id << '\n';
    cout << "Title: " << books[index].title << '\n';
    cout << "Author: " << books[index].author << '\n';
    cout << "Status: "
         << (books[index].issued ? "Issued" : "Available") << '\n';
}

void issueBook() {
    int id;

    cout << "Enter Book ID to Issue: ";
    if (!(cin >> id)) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findBook(id);

    if (index == -1) {
        cout << "Book not found!\n";
        return;
    }

    if (books[index].issued) {
        cout << "Book is already issued!\n";
        return;
    }

    books[index].issued = true;
    saveData();

    cout << "Book issued successfully!\n";
}

void returnBook() {
    int id;

    cout << "Enter Book ID to Return: ";
    if (!(cin >> id)) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int index = findBook(id);

    if (index == -1) {
        cout << "Book not found!\n";
        return;
    }

    if (!books[index].issued) {
        cout << "This book was not issued!\n";
        return;
    }

    books[index].issued = false;
    saveData();

    cout << "Book returned successfully!\n";
}

int main() {
    loadData();

    int choice;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6:
                saveData();
                cout << "Thank you for using Library Management System!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
