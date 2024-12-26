#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Book structure
struct Book {
  int bookID;
  string bookName;
  string author;
  double price;
  double discount;
};

// Function to display admin menu options
void displayAdminMenu() {
  cout << "========== Admin Menu ==========\n";
  cout << "1. Manage Books\n";
  cout << "2. View Books\n";
  cout << "3. Logout\n";
  cout << "4. Exit\n";
  cout << "===============================\n";
}

// Function to display customer menu options
void displayCustomerMenu() {
  cout << "========== Customer Menu ==========\n";
  cout << "1. View Books\n";
  cout << "2. Search Books\n";
  cout << "3. Buy a Book\n";
  cout << "4. Create New Account\n";
  cout << "5. Logout\n";
  cout << "6. Exit\n";
  cout << "===================================\n";
}

// Function to manage books (add, view, search) - only accessible to admin
void manageBooks() {
  ifstream bookFile("books.txt");
  if (!bookFile) {
    // ofstream createFile("books.txt");
    // if (!createFile) {
    //   cout << "Error: Unable to create books file." << endl;
    //   return;
    // }
    // createFile.close();
  }

  int choice;
  cout << "1. View Books\n";
  cout << "2. Add Book\n";
  cout << "3. Search Book\n";
  cout << "Enter your choice: ";
  cin >> choice;

  if (choice == 1) {
    string line;
    ifstream bookAppend("books.txt", ios::app);
    if (!bookAppend) {
      cout << "Error: Unable to open books file for appending." << endl;
      return;
    }
    while (getline(bookFile, line)) {
      cout << line << endl;
    }
  } else if (choice == 2) {
    ofstream bookAppend("books.txt", ios::app);
    if (!bookAppend) {
      cout << "Error: Unable to open books file for appending." << endl;
      return;
    }

    Book newBook;
    cout << "Enter Book ID: ";
    cin >> newBook.bookID;
    cin.ignore();
    cout << "Enter Book Name: ";
    getline(cin, newBook.bookName);
    cout << "Enter Author: ";
    getline(cin, newBook.author);
    cout << "Enter Price: ";
    cin >> newBook.price;
    cout << "Enter Discount: ";
    cin >> newBook.discount;

    bookAppend << newBook.bookID << "\t" << newBook.bookName << "\t"
               << newBook.author << "\t" << newBook.price << "\t"
               << newBook.discount << endl;

    bookAppend.close();
    cout << "Book added successfully.\n";
  } else if (choice == 3) {
    string searchTerm;
    cout << "Enter Book Name to search: ";
    cin.ignore();
    getline(cin, searchTerm);

    string line;
    bool found = false;
    while (getline(bookFile, line)) {
      size_t pos = line.find(searchTerm);
      if (pos != string::npos) {
        cout << "Book found: " << line << endl;
        found = true;
        break;
      }
    }

    if (!found) {
      cout << "Book not found.\n";
    }
  } else {
    cout << "Invalid choice.\n";
  }

  bookFile.close();
}

// Function to handle user login for both admin and customer
void userLogin() {
  string userType;
  string username, password, storedUsername, storedPassword;
  bool loggedIn = false;

  cout << "Enter user type (admin/customer): ";
  cin >> userType;

  if (userType == "admin") {
    cout << "Enter admin username: ";
  } else if (userType == "customer") {
    cout << "Enter customer username: ";
  } else {
    cout << "Invalid user type.\n";
    return;
  }

  cin >> username;
  cout << "Enter password: ";
  cin >> password;

  ifstream userFile("users.txt");
  if (!userFile) {
    cout << "Error: Unable to open user file." << endl;
    return;
  }

  while (userFile >> storedUsername >> storedPassword) {
    if (username == storedUsername && password == storedPassword) {
      cout << "Login successful.\n";
      loggedIn = true;
      break;
    }
  }

  if (!loggedIn) {
    cout << "Login failed. Invalid credentials.\n";
  }

  userFile.close();

  if (loggedIn && userType == "admin") {
    char adminChoice = '0';
    while (adminChoice != '3') {
      displayAdminMenu();
      cout << "Enter your choice: ";
      cin >> adminChoice;

      if (adminChoice == '1') {
        manageBooks();
      } else if (adminChoice == '2') {
        ifstream bookFile("books.txt");
        if (!bookFile) {
          cout << "Error: Unable to open books file." << endl;
          return;
        }

        string line;
        while (getline(bookFile, line)) {
          cout << line << endl;
        }

        bookFile.close();
      } else if (adminChoice == '3') {
        cout << "Logging out...\n";
      } else if (adminChoice == '4') {
        cout << "Exiting the program...\n";
        exit(0);
      } else {
        cout << "Invalid choice. Please try again.\n";
      }
    }
  } else if (loggedIn && userType == "customer") {
    char customerChoice = '0';
    while (customerChoice != '5') {
      displayCustomerMenu();
      cout << "Enter your choice: ";
      cin >> customerChoice;

      if (customerChoice == '1') {
        ifstream bookFile("books.txt");
        if (!bookFile) {
          cout << "Error: Unable to open books file." << endl;
          return;
        }

        string line;
        while (getline(bookFile, line)) {
          cout << line << endl;
        }

        bookFile.close();
      } else if (customerChoice == '2') {
        string searchTerm;
        cout << "Enter Book Name to search: ";
        cin.ignore();
        getline(cin, searchTerm);

        ifstream bookFile("books.txt");
        if (!bookFile) {
          cout << "Error: Unable to open books file." << endl;
          return;
        }

        string line;
        bool found = false;
        while (getline(bookFile, line)) {
          size_t pos = line.find(searchTerm);
          if (pos != string::npos) {
            cout << "Book found: " << line << endl;
            found = true;
            break;
          }
        }

        if (!found) {
          cout << "Book not found.\n";
        }

        bookFile.close();
      } else if (customerChoice == '3') {
        int bookID;

        cout << "Enter Book ID to buy: ";
        cin >> bookID;

        ifstream bookFile("books.txt");
        if (!bookFile) {
          cout << "Error: Unable to open books file." << endl;
          return;
        }

        Book selectedBook;
        bool bookFound = false;
        while (bookFile >> selectedBook.bookID >> selectedBook.bookName >>
               selectedBook.author >> selectedBook.price >>
               selectedBook.discount) {
          if (bookID == selectedBook.bookID) {
            bookFound = true;
            break;
          }
        }
        bookFile.close();

        if (!bookFound) {
          cout << "Book not found.\n";
        } else {

          double discountedPrice =
              selectedBook.price -
              (selectedBook.price * selectedBook.discount / 100.0);
          cout << fixed << setprecision(2);
          cout << "Book purchased successfully!\n";
          cout << "Book ID: " << selectedBook.bookID << endl;
          cout << "Book Name: " << selectedBook.bookName << endl;
          cout << "Author: " << selectedBook.author << endl;
          cout << "Price: LKR" << selectedBook.price << endl;
          cout << "Discount: " << selectedBook.discount << "%" << endl;
          cout << "Discounted Price: LKR" << discountedPrice << endl;
        }
      } else if (customerChoice == '4') {
        string newUsername, newPassword;
        cout << "Enter new username: ";
        cin >> newUsername;
        cout << "Enter new password: ";
        cin >> newPassword;

        ofstream userFile("users.txt", ios::app);
        if (!userFile) {
          cout << "Error: Unable to open user file for appending." << endl;
          return;
        }

        userFile << newUsername << "\t" << newPassword << endl;
        cout << "Account created successfully!\n";
        userFile.close();
      } else if (customerChoice == '5') {
        cout << "Logging out...\n";
      } else if (customerChoice == '6') {
        cout << "Exiting the program...\n";
        exit(0);
      } else {
        cout << "Invalid choice. Please try again.\n";
      }
    }
  }
}

// Function to store user data
void storeUserData() {
  ifstream file("users.txt");
  if (!file) {
    ofstream userFile("users.txt");
    string adminUsername = "admin";
    string adminPassword = "admin";
    userFile << adminUsername << "\t" << adminPassword << endl;

    userFile.close();
  }
  file.close();

  ifstream bookfile("books.txt");
  if (!bookfile) {
    ofstream bookFile("books.txt");
  }
  bookfile.close();
}

int main() {
  storeUserData(); // Creating an admin user (You can add more users manually)

  int choice;

  do {
    cout << "========== Welcome to Nethra Bookshop ==========\n";
    cout << "1. User Login\n";
    cout << "2. Create New Customer Account\n";
    cout << "3. Exit\n";
    cout << "===============================================\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
      userLogin();
    } else if (choice == 2) {
      string newUsername, newPassword;
      cout << "Enter new username: ";
      cin >> newUsername;
      cout << "Enter new password: ";
      cin >> newPassword;

      ofstream userFile("users.txt", ios::app);
      if (!userFile) {
        cout << "Error: Unable to open user file for appending." << endl;
        return 1;
      }

      userFile << newUsername << "\t" << newPassword << endl;
      cout << "Account created successfully!\n";
      userFile.close();
    } else if (choice == 3) {
      cout << "Exiting the program...\n";
      exit(0);
    } else {
      cout << "Invalid choice. Please try again.\n";
    }
  } while (choice != 3);

  return 0;
}
