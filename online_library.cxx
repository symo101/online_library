#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Book {
public:
    Book(int id, std::string title, std::string author, bool isAvailable = true) 
        : id(id), title(title), author(author), isAvailable(isAvailable) {}

    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    bool getIsAvailable() const { return isAvailable; }
    void setIsAvailable(bool availability) { isAvailable = availability; }

    void displayBook() const {
        std::cout << "Book ID: " << id << ", Title: " << title 
                  << ", Author: " << author << ", Available: " 
                  << (isAvailable ? "Yes" : "No") << std::endl;
    }

private:
    int id;
    std::string title;
    std::string author;
    bool isAvailable;
};

class User {
public:
    User(int id, std::string name) : id(id), name(name) {}

    int getId() const { return id; }
    std::string getName() const { return name; }

    void displayUser() const {
        std::cout << "User ID: " << id << ", Name: " << name << std::endl;
    }

private:
    int id;
    std::string name;
};

class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
        std::cout << "Book added: " << book.getTitle() << std::endl;
    }

    void removeBook(int bookId) {
        books.erase(std::remove_if(books.begin(), books.end(),
            [bookId](const Book& book) { return book.getId() == bookId; }), books.end());
        std::cout << "Book removed with ID: " << bookId << std::endl;
    }

    void addUser(const User& user) {
        users.push_back(user);
        std::cout << "User added: " << user.getName() << std::endl;
    }

    void removeUser(int userId) {
        users.erase(std::remove_if(users.begin(), users.end(),
            [userId](const User& user) { return user.getId() == userId; }), users.end());
        std::cout << "User removed with ID: " << userId << std::endl;
    }

    void borrowBook(int userId, int bookId) {
        auto user = findUser(userId);
        auto book = findBook(bookId);
        if (user && book && book->getIsAvailable()) {
            book->setIsAvailable(false);
            std::cout << user->getName() << " borrowed " << book->getTitle() << std::endl;
        } else {
            std::cout << "Borrowing failed!" << std::endl;
        }
    }

    void returnBook(int userId, int bookId) {
        auto user = findUser(userId);
        auto book = findBook(bookId);
        if (user && book && !book->getIsAvailable()) {
            book->setIsAvailable(true);
            std::cout << user->getName() << " returned " << book->getTitle() << std::endl;
        } else {
            std::cout << "Returning failed!" << std::endl;
        }
    }

    void searchBooksByTitle(const std::string& title) const {
        for (const auto& book : books) {
            if (book.getTitle().find(title) != std::string::npos) {
                book.displayBook();
            }
        }
    }

    void searchBooksByAuthor(const std::string& author) const {
        for (const auto& book : books) {
            if (book.getAuthor().find(author) != std::string::npos) {
                book.displayBook();
            }
        }
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayBook();
        }
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user.displayUser();
        }
    }

private:
    std::vector<Book> books;
    std::vector<User> users;

    Book* findBook(int bookId) {
        for (auto& book : books) {
            if (book.getId() == bookId) {
                return &book;
            }
        }
        return nullptr;
    }

    User* findUser(int userId) {
        for (auto& user : users) {
            if (user.getId() == userId) {
                return &user;
            }
        }
        return nullptr;
    }
};

int main() {
    Library library;

    // Adding Books
    library.addBook(Book(1, "1984", "George Orwell"));
    library.addBook(Book(2, "Mount Kenya", "John Kanini"));
    library.addBook(Book(3, "The Great Nation", "Jomo Kenyatta"));

    // Adding Users
    library.addUser(User(1, "Otieno"));
    library.addUser(User(2, "Kimani"));

    // Display all books and users
    library.displayAllBooks();
    library.displayAllUsers();

    // Borrow and return books
    library.borrowBook(1, 1);
    library.returnBook(1, 1);

    // Search for books
    library.searchBooksByTitle("1984");
    library.searchBooksByAuthor("Harper Lee");

    return 0;
}