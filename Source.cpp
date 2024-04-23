#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

class Book {
public:
    int bookId;
    string title;
    string author;
    string genre;
    int quantity;

    void displayBookDetails() const {
        cout << "Book ID: " << bookId << "\nTitle: " << title << "\nAuthor: " << author << "\nGenre: " << genre << "\nQuantity: " << quantity << endl;
    }
};

class BookshopManagementSystem {
private:
    vector<Book> books;
    const string filename = "book_inventory.dat";

public:
    void addBook() {
        Book newBook;
        cout << "Enter Book ID: ";
        cin >> newBook.bookId;
        cin.ignore();  // Clear newline from buffer
        cout << "Enter Title: ";
        getline(cin, newBook.title);
        cout << "Enter Author: ";
        getline(cin, newBook.author);
        cout << "Enter Genre: ";
        getline(cin, newBook.genre);
        cout << "Enter Quantity: ";
        cin >> newBook.quantity;

        books.push_back(newBook);
        saveDataToFile();
        cout << "Book added successfully!" << endl;
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "No books available in the inventory." << endl;
            return;
        }

        cout << "Book Inventory:\n";
        for (const Book& book : books) {
            book.displayBookDetails();
            cout << "------------------------\n";
        }
    }

    void modifyBook(int bookId) {
        for (Book& book : books) {
            if (book.bookId == bookId) {
                cout << "Modify Book ID " << bookId << ":\n";
                cout << "Enter New Title: ";
                getline(cin, book.title);
                cout << "Enter New Author: ";
                getline(cin, book.author);
                cout << "Enter New Genre: ";
                getline(cin, book.genre);
                cout << "Enter New Quantity: ";
                cin >> book.quantity;

                saveDataToFile();
                cout << "Book modified successfully!" << endl;
                return;
            }
        }

        cout << "Book with ID " << bookId << " not found." << endl;
    }

    void loadDataFromFile() {
        ifstream inFile(filename, ios::binary);
        if (!inFile) {
            cout << "No existing data file found. Starting with an empty inventory." << endl;
            return;
        }

        while (!inFile.eof()) {
            Book loadedBook;
            inFile.read(reinterpret_cast<char*>(&loadedBook), sizeof(Book));
            if (inFile.eof()) {
                break;
            }
            books.push_back(loadedBook);
        }

        inFile.close();
    }

    void saveDataToFile() const {
        ofstream outFile(filename, ios::binary);
        for (const Book& book : books) {
            outFile.write(reinterpret_cast<const char*>(&book), sizeof(Book));
        }
        outFile.close();
    }

    ~BookshopManagementSystem() {
        saveDataToFile();
    }

    // Add more functionalities like delete, search, etc., based on your requirements
};

int main() {
    BookshopManagementSystem bookshop;
    bookshop.loadDataFromFile();

    char choice;
    do {
        cout << "Menu:\n1. Add Book\n2. Display All Books\n3. Modify Book\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            bookshop.addBook();
            break;
        case '2':
            bookshop.displayAllBooks();
            break;
        case '3': {
            int bookId;
            cout << "Enter Book ID to modify: ";
            cin >> bookId;
            cin.ignore();  // Clear newline from buffer
            bookshop.modifyBook(bookId);
            break;
        }
        case '4':
            cout << "Exiting the Bookshop Management System. Thank you!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '4');

    return 0;
}
