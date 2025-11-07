#include <iostream>
#include <fstream>
using namespace std;

struct Book {
    int id;
    char title[50];
    char author[50];
    int quantity;
};

// Save books to file
void saveToFile(Book* books, int count) {
    ofstream outFile("books.txt", ios::out);
    for (int i = 0; i < count; i++) {
        outFile << books[i].id << endl;
        outFile << books[i].title << endl;
        outFile << books[i].author << endl;
        outFile << books[i].quantity << endl;
    }
    outFile.close();
}

// Load books from file
void loadFromFile(Book* books, int &count) {
    ifstream inFile("books.txt", ios::in);
    count = 0;
    while (inFile >> books[count].id) {
        inFile.ignore();
        inFile.getline(books[count].title, 50);
        inFile.getline(books[count].author, 50);
        inFile >> books[count].quantity;
        inFile.ignore();
        count++;
    }
    inFile.close();
}

// Display all books
void displayBooks(Book* books, int count) {
    if (count == 0) {
        cout << "No books available.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        cout << "\nBook " << i + 1 << ":\n";
        cout << "ID: " << books[i].id << "\n";
        cout << "Title: " << books[i].title << "\n";
        cout << "Author: " << books[i].author << "\n";
        cout << "Quantity: " << books[i].quantity << "\n";
    }
}

// Search for a book
void searchBook(Book* books, int count) {
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;
    for (int i = 0; i < count; i++) {
        if (books[i].id == id) {
            cout << "\nBook Found:\n";
            cout << "ID: " << books[i].id << "\n";
            cout << "Title: " << books[i].title << "\n";
            cout << "Author: " << books[i].author << "\n";
            cout << "Quantity: " << books[i].quantity << "\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

// Borrow a book
void borrowBook(Book* books, int count) {
    int id;
    cout << "Enter Book ID to borrow: ";
    cin >> id;
    for (int i = 0; i < count; i++) {
        if (books[i].id == id) {
            if (books[i].quantity > 0) {
                books[i].quantity--;
                saveToFile(books, count);
                cout << "Book borrowed successfully!\n";
            } else {
                cout << "Book out of stock!\n";
            }
            return;
        }
    }
    cout << "Book not found.\n";
}

// Return a book
void returnBook(Book* books, int count) {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;
    for (int i = 0; i < count; i++) {
        if (books[i].id == id) {
            books[i].quantity++;
            saveToFile(books, count);
            cout << "Book returned successfully!\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

// Check if book ID already exists
bool isDuplicate(Book* books, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (books[i].id == id) return true;
    }
    return false;
}

int main() {
    Book library[100];
    int bookCount = 0;
	cout<<"Welcome to Library management system\n";
	 cout<<"\n\n\t\t\t GROUP MEMBERS";
	 cout<<"\n\n\t\tName\t\tID No\t\t\tSection";
	 cout<<"\n\n\t1. Milkesa Tesema\tUGR/37436/17\t\t5";
	 cout<<"\n\n\t2. Abenezer Belihu\tUGR/36336/17\t\t5";
	 cout<<"\n\n\t3. Hatsey Abraha\tUGR/37019/17\t\t5";
	 cout<<"\n\n\t4. Asad Yesuf\t\tUGR/36472/17\t\t6";
	 cout<<"\n\n\t5. Zerubabel Asebe\tUGR/38052/17\t\t6";
	 cout<<"\n\n\t6. Robel Yohannes\tUGR/37669/17\t\t5";

	 	cout<<endl;

    loadFromFile(library, bookCount);

    int choice;
    do {
        cout << "\n--- Library Menu ---\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Save to File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            int id;
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            if (isDuplicate(library, bookCount, id)) {
                cout << "Book ID already exists.\n";
            } else {
                library[bookCount].id = id;
                cout << "Enter Title: ";
                cin.getline(library[bookCount].title, 50);
                cout << "Enter Author: ";
                cin.getline(library[bookCount].author, 50);
                cout << "Enter Quantity: ";
                cin >> library[bookCount].quantity;
                bookCount++;
                saveToFile(library, bookCount);
                cout << "Book added successfully!\n";
            }
        }
        else if (choice == 2) {
            displayBooks(library, bookCount);
        }
        else if (choice == 3) {
            searchBook(library, bookCount);
        }
        else if (choice == 4) {
            borrowBook(library, bookCount);
        }
        else if (choice == 5) {
            returnBook(library, bookCount);
        }
        else if (choice == 6) {
            saveToFile(library, bookCount);
            cout << "Books saved to file.\n";
        }
        else if (choice != 7) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    cout << "Exiting program. Goodbye!\n";
    return 0;
}

