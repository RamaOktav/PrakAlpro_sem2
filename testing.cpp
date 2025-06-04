#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <string.h>
#include <iomanip>
#include <fstream>

using namespace std;

string FileUSer = "dataUSer.txt";
struct Akun {
    string Nama;
    string pass;
};

int jumlahAkun = 0;
void mainPage();
void menu();
void login(int batas);
void registerUser();
int HitungBaris();

int HitungBaris() {
    ifstream akunPengguna(FileUSer);
    string baris;
    int jumlahBaris = 0;
    while (getline(akunPengguna, baris)) {
        if (!baris.empty()) jumlahBaris++;
    }
    akunPengguna.close();
    return jumlahBaris;
}

void login(int batas) {
    if (HitungBaris() == 0) {
        cout << "Belum ada user, silakan register dulu.\n";
        registerUser();
        return;
    }

    ifstream akunPengguna(FileUSer);
    Akun* Pengguna = new Akun;
    jumlahAkun = HitungBaris();
    string nama[jumlahAkun], password[jumlahAkun];
    cout << "===========MENU LOGIN==========\n";
    cout << "Masukkan Username    : ";
    cin >> Pengguna->Nama;
    cout << "Masukkan Password    : ";
    cin >> Pengguna->pass;
    int i = 0;
    bool check = false;
    while (akunPengguna >> nama[i] >> password[i] && i < jumlahAkun) {
        if (Pengguna->Nama == nama[i] && Pengguna->pass == password[i]) {
            cout << "LOGIN BERHASIL\n";
            check = true;
        }
        i++;
    }
    akunPengguna.close();
    delete Pengguna;
    if (check) {
        system("pause");
        mainPage();
    } else {
        cout << "Password atau Username mu salah\n";
        batas--;
        cout << "Kesempatan tinggal " << batas << " Kali\n";
        if (batas > 0) login(batas);
        else { // Tambahan: jika kesempatan habis, kembali ke menu
             system("pause");
             menu();
        }
    }
}

void registerUser() {
    ofstream akunBaru(FileUSer, ios::app);
    Akun* Pengguna = new Akun;
    cout << "Masukkan Usernama    : ";
    cin >> Pengguna->Nama;
    cout << "Masukkan Password    : ";
    cin >> Pengguna->pass;
    akunBaru << Pengguna->Nama << " " << Pengguna->pass << endl;
    jumlahAkun++;
    delete Pengguna;
    system("pause");
    menu(); // kembali ke menu login/register setelah register
}

struct Book {
    int bookId;
    string title;
    string author;
    string type;
    int stock;
    int publishedYear;
};
struct Member {
    int memberId;
    string name;
    string dateOfBirth;
    string address;
    string email;
    long long int phone;
};
struct Staff {
    int staffId;
    string name;
    string role;
    string email;
};
struct Loan {
    int id;
    int memberId;
    int staffId;
    int bookId;
    string loanDate;
    string returnDate;
    string status;
};
struct GlobalSize {
    static constexpr int book = 30;
    static constexpr int member = 50;
    static constexpr int staff = 10;
    static constexpr int loan = 100;
};

Book books[GlobalSize::book];
Member members[GlobalSize::member] = {
    {1, "John Doe", "1990-04-25", "1234 Elm Street, Springfield, IL", "john.doe@email.com", 5551234567},
    {2, "Jane Smith", "1985-08-12", "5678 Oak Avenue, Los Angeles, CA", "jane.smith@email.com", 5559876543},
    {3, "Albert Einstein", "1879-03-14", "Princeton, New Jersey, USA", "albert.einstein@email.com", 5555555555},
    {4, "Marie Curie", "1867-11-07", "Paris, France", "marie.curie@email.com", 5551239876},
    {5, "Mahatma Gandhi", "1869-10-02", "Porbandar, Gujarat, India", "mahatma.gandhi@email.com", 5557418520},
    {-1, "Sentinel Value", "", "", "", 0 }
};
Staff staff[GlobalSize::staff] = {
    {1, "Alice Johnson", "Librarian", "alice.johnson@email.com"},
    {2, "Bob Smith", "Library Manager", "bob.smith@email.com"},
    {3, "Charlie Brown", "Library Assistant", "charlie.brown@email.com"},
    {4, "Diana White", "Head Librarian", "diana.white@email.com"},
    {5, "Eve Green", "Technician", "eve.green@email.com"},
    {-1, "Sentinel Value", "", ""}
};
Loan loans[GlobalSize::loan] = {
    {1, 1, 3, 1, "2025-02-01", "2025-02-15", "Returned"},
    {2, 2, 3, 2, "2025-02-05", "2025-02-20", "Returned"},
    {3, 3, 3, 3, "2025-02-10", "2025-02-25", "Loaned"},
    {4, 4, 3, 4, "2025-02-12", "2025-02-26", "Loaned"},
    {5, 5, 3, 5, "2025-02-14", "2025-02-28", "Returned"},
    {-1, -1, -1, -1, "Sentinel Value", "Sentinel Value", "Sentinel Value"}
};

void enterToContinue() {
    cout << "\nPress 'Enter' to continue...";
    cin.ignore();
}
void invalidChoice() {
    cout << "Invalid choice. Please try again.\n";
    enterToContinue();
}
void clearScreen() {
#ifdef _WIN32 // for Windows
    system("cls");
#elif defined(linux) // for Linux
    cout << "\n";
    system("clear");
#endif
}
int validateIntInput(string input) {
    for (int i=0;i<input.length();i++) {
        if (!isdigit(input[i])) return -1;
    }

    try {
        int number = std::stoi(input);
        return number;
    } catch (std::out_of_range&) {
        return -1;
    }

    return -1;
}

string toLowerCase(const string &str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
int getBooksLen() {
    int count = 0;
    while (books[count].bookId != -1) count++;
    return count;
}
int getMembersLen() {
    int count = 0;
    while (members[count].memberId != -1) count++;
    return count;
}
int getStaffLen() {
    int count = 0;
    while (staff[count].staffId != -1) count++;
    return count;
}
int getLoansLen() {
    int count = 0;
    while (loans[count].memberId != -1) count++;
    return count;
}
void setSentinelBook(int lastIndex) {
    books[lastIndex] = {-1, "Sentinel Value", "", "", 0, 0};
}
void setSentinelMember(int lastIndex) {
    members[lastIndex] = {-1, "Sentinel Value", "", "", "", 0 };
}
void setSentinelStaff(int lastIndex) {
    staff[lastIndex] = {-1, "Sentinel Value", "", ""};
}
void setSentinelLoan(int lastIndex) {
    loans[lastIndex] =  {-1, -1, -1, -1, "Sentinel Value", "Sentinel Value", "Sentinel Value"};
}
int findBookIndexById(int targetId) {
    int i = 0;
    while (books[i].bookId != -1) {
        if (books[i].bookId == targetId) return i;
        i++;
    }
    return -1;
}

int getMainChoice() {
    string input;
    clearScreen();
    cout << "=====================\n";
    cout << "Welcome\n";
    cout << "1. Book\n";
    cout << "2. Member\n";
    cout << "3. Staff\n";
    cout << "4. Loans\n";
    cout << "5. Add admin\n";
    cout << "0. Exit\n";
    cout << "=====================\n";
    cout << "Select menu : ";
    cin >> input;
    cin.ignore();
    return validateIntInput(input);
}

int getBookChoice() {
    string input;
    clearScreen();
    cout << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    cout << "Books Menu\n";
    cout << "1. Search Books\n";
    cout << "2. Show Books\n";
    cout << "3. Add Books\n";
    cout << "4. Update Books\n";
    cout << "5. Delete Books\n";
    cout << "0. Back to main menu\n";
    cout << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    cout << "Select menu : ";
    cin >> input;
    cin.ignore();
    return validateIntInput(input);
}

int getSearchBookChoice() {
    string input;
    clearScreen();
    cout << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    cout << "Search Book Menu\n";
    cout << "1. Search by ID\n";
    cout << "2. Search by Title\n";
    cout << "0. Back to book menu\n";
    cout << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    cout << "Select menu : ";
    cin >> input;
    cin.ignore();
    return validateIntInput(input);
}

int getMemberChoice() {
    string input;
    clearScreen();
    cout << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    cout << "Member Menu\n";
    cout << "1. Search Member\n";
    cout << "2. Show All Member\n";
    cout << "3. Add Member\n";
    cout << "4. Update Member\n";
    cout << "5. Delete Member\n";
    cout << "0. Back to main menu\n";
    cout << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    cout << "Select menu : ";
    cin >> input;
    cin.ignore();
    return validateIntInput(input);
}

int getStaffChoice() {
    string input;
    clearScreen();
    cout << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    cout << "Staff Menu\n";
    cout << "1. Show All Staff\n";
    cout << "2. Add Staff\n";
    cout << "3. Update Staff\n";
    cout << "4. Delete Staff\n";
    cout << "0. Back to main menu\n";
    cout << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    cout << "Select menu : ";
    cin >> input;
    cin.ignore();
    return validateIntInput(input);
}

int getLoansChoice(){
    string input;
    clearScreen();
    cout << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    cout << "Loans Menu\n";
    cout << "1. Show All Loans\n";
    cout << "2. Add Loan\n";
    cout << "3. Return Loan\n";
    cout << "4. Delete Loan\n";
    cout << "0. Back to main menu\n";
    cout << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    cout << "Select menu : ";
    cin >> input;
    cin.ignore();
    return validateIntInput(input);
}


string searchBookById(int index, int key){
    if (books[index].bookId == -1)
        return "Book not found";
    else if(books[index].bookId == key) 
        return books[index].title;
    else 
        return searchBookById(index + 1,key);
}

void searchBookByTitle() {
    string key;
   
    char repeat;
    do{ 
        int resultCount = 0;
        cout << "Enter book name : ";
        getline(cin, key); 
        if (key == "0") break;

        key = toLowerCase(key);
        cout << "Result :\n";
        for (int i=0; books[i].bookId != -1; i++) {
            if (toLowerCase(books[i].title).find(key) != string::npos) {
                resultCount++;
                cout << resultCount << ") "
                    << books[i].title
                    << ", by " << books[i].author
                    << " (" << books[i].publishedYear << ")\n";
            }
        }
        
        if (resultCount == 0) {
            cout << "No book found\n";
        } 
        cout << "\nSearch again? (y/n): ";
        cin >> repeat;
        cin.ignore();
        repeat = tolower(repeat);
    }while (repeat == 'y'|| repeat == 'Y');
    
}

/**
 * Show all element on books array including sentinel value
 */
void showBooks() {
    int i = 0;
    while (books[i].bookId != -1) {
        cout << books[i].bookId << ") "
            << books[i].title
            << ", by " << books[i].author
            << " (" << books[i].publishedYear << "), "
            << "Stock " << books[i].stock << endl;
        i++;
    }
    
}

void sortBooks(int criteria, int order){
    int i=0;
    int size = getBooksLen();//kooojoj
    Book duplicate[size];
    while (books[i].bookId != -1) {
        duplicate[i] = books[i];
        i++;
    }
    int validSize=i;
    for (int i=1; i < validSize; i++) {
        Book temp = duplicate[i];
        int j = i-1;
        while (j>=0) {
            bool swap = false;
            switch (criteria) {
                case 1:
                    if (order == 1) swap = (duplicate[j].bookId > temp.bookId);
                    else swap = (duplicate[j].bookId < temp.bookId);
                    break;
                case 2:
                    if (order == 1) swap = (duplicate[j].title > temp.title);
                    else swap = (duplicate[j].title < temp.title);
                    break;
                case 3:
                    if (order == 1) swap = (duplicate[j].author > temp.author);
                    else swap = (duplicate[j].author < temp.author);
                    break;
                case 4:
                    if (order == 1) swap = (duplicate[j].type > temp.type);
                    else swap = (duplicate[j].type < temp.type);
                    break;
                case 5:
                    if (order == 1) swap = (duplicate[j].stock > temp.stock);
                    else swap = (duplicate[j].stock < temp.stock);
                    break;
                case 6:
                    if (order == 1) swap = (duplicate[j].publishedYear > temp.publishedYear);
                    else swap = (duplicate[j].publishedYear < temp.publishedYear);
                    break;
                default:
                    cout << "Sort valued error" << endl;
                    getchar();
                    return;
            }

            if(!swap) break;
            duplicate[j+1] = duplicate[j];
            j-=1;
        }
        duplicate[j+1] = temp;
    }
    cout << setw(4) << left << "ID" 
            << setw(25) << left << "Title"
            << setw(25) << left << "Author"
            << setw(12) << left << "Type"
            << setw(8) << left << "Year"
            << setw(13) << left << "Stock" << endl
            << setfill('=') << setw(85) << "" << setfill(' ') << endl;
    for (int i=0; i<validSize; i++) {
        cout << setw(4) << left << duplicate[i].bookId
                << setw(25) << left << duplicate[i].title
                << setw(25) << left << duplicate[i].author
                << setw(12) << left << duplicate[i].type
                << setw(8) << left << duplicate[i].publishedYear
                << setw(5) << left << duplicate[i].stock << endl;  
    }
    cout  << setfill('=') << setw(85) << "" << setfill(' ') << endl;
}

void showBooksOrder() {
    int showChoice, orderChoice;
    clearScreen();
    cout << "Show Books Menu\n";
    cout << "1. Order by ID\n";
    cout << "2. Order by title\n";
    cout << "3. Order by author\n";
    cout << "4. Order by type\n";
    cout << "5. Order by stock\n";
    cout << "6. Order by published year\n";
    cout << "Select menu : ";
    cin >> showChoice;
    cin.ignore();
    
    cout << "Order by\n";
    cout << "1. Ascending\n";
    cout << "2. Descending\n";
    cout << "Select order : ";
    cin >> orderChoice;
    cin.ignore();
    
    sortBooks(showChoice,orderChoice);
}

// load data from file to books array
void loadBooks() {
    FILE* file = fopen("./data/books.txt", "r");
    if (file == nullptr) {
        cout << "No books data available\n";

    } else {
        int count = 0;
        char line[256];
        char tempTitle[100], tempAuthor[100], tempType[100];
        int tempId, tempStock, tempPublishedYear;
        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%d \"%[^\"]\" \"%[^\"]\" %s %d %d",
                &tempId, tempTitle, tempAuthor, tempType, &tempStock, &tempPublishedYear
            );
            books[count].bookId = tempId;
            books[count].title = tempTitle;
            books[count].author = tempAuthor;
            books[count].type = tempType;
            books[count].stock = tempStock;
            books[count].publishedYear = tempPublishedYear;
            count++;
        }
        setSentinelBook(count);
    }
    fclose(file);
}

// store current books array to file, for change (update and delete)
void storeBooks() {
    FILE* file = fopen("./data/books.txt", "w");
    if (file != nullptr) {
        for (int i = 0; i < getBooksLen(); i++) {
            string writeFormat = i < getBooksLen() - 1 
                ? "%d \"%s\" \"%s\" %s %d %d\n"
                : "%d \"%s\" \"%s\" %s %d %d";
            fprintf(file, writeFormat.c_str(),
                books[i].bookId,
                books[i].title.c_str(),
                books[i].author.c_str(),
                books[i].type.c_str(),
                books[i].stock,
                books[i].publishedYear
            );
        }
        fclose(file);
    } else {
        cout << "Failed to open file for writing.\n";
    }
}

void addBooks() {
    int currentCount = getBooksLen(), inputCount;
    string inputCountStr;

    clearScreen();
    cout << "How many books to add: ";
    cin >> inputCountStr;
    cin.ignore();

    inputCount = validateIntInput(inputCountStr);
    if (inputCount == -1) {
        cout << "Invalid input. Must be a number.\n";
        return;
    }

    if (currentCount + inputCount > GlobalSize::book) {
        cout << "Too many books. Max allowed is " << GlobalSize::book << endl;
        inputCount = GlobalSize::book - currentCount;
        cout << "Adding only " << inputCount << " books.\n";
    }

    for (int i = 0; i < inputCount; i++) {
        Book b;
        string temp;

        cout << "Book #" << (currentCount + i + 1) << endl;

        cout << "Book ID: ";
        getline(cin, temp);
        b.bookId = validateIntInput(temp);

        cout << "Title: ";
        getline(cin, b.title);
        cout << "Author: ";
        getline(cin, b.author);
        cout << "Type: ";
        getline(cin, b.type);

        cout << "Stock: ";
        getline(cin, temp);
        b.stock = validateIntInput(temp);

        cout << "Published Year: ";
        getline(cin, temp);
        b.publishedYear = validateIntInput(temp);

        books[currentCount + i] = b;
    }

    setSentinelBook(currentCount + inputCount);
    storeBooks();

    cout << "\nBooks added successfully.\n";
}


void updateBook() {
    string updateIdStr;
    int updateId;
    
    clearScreen();
    sortBooks(1, 1);
    cout << endl;
    cout << "Enter Book ID to be updated : ";
    getline(cin, updateIdStr);

    updateId = validateIntInput(updateIdStr);
    if (updateId == -1) {
        cout << "Invalid input, input must be a number." << endl;
        return;
    }

    // convert id to index
    updateId = findBookIndexById(updateId);
    if (updateId == -1) {
        cout << "Book could not be found\n";
        return;
    }

    Book updated;
    cout << "Enter new value, leave it blank to keep previous value\n";
    cout << "Book Title\t: "; getline(cin, updated.title);
    cout << "Author Name\t: "; getline(cin, updated.author);
    cout << "Book Type\t: "; getline(cin, updated.type);

    string temp;
    cout << "Pub. Year\t: "; getline(cin, temp);
    updated.publishedYear = temp.empty() ? books[updateId].publishedYear : stoi(temp);
    cout << "Book Stock\t: "; getline(cin, temp);
    updated.stock = temp.empty() ? books[updateId].stock : stoi(temp);

    if (!updated.title.empty() && updated.title != books[updateId].title) books[updateId].title = updated.title;
    if (!updated.author.empty() && updated.author != books[updateId].author) books[updateId].author = updated.author;
    if (!updated.type.empty() && updated.type != books[updateId].type) books[updateId].type = updated.type;
    if (updated.publishedYear != books[updateId].publishedYear) books[updateId].publishedYear = updated.publishedYear;
    if (updated.stock != books[updateId].stock) books[updateId].stock = updated.stock;

    storeBooks();
}

/**
 * Sequential search implementation
 * Search Member by ID
 */
void searchMemberById() {
    int key;
    cout << "Enter member ID : ";
    cin >> key;
    cin.ignore();

    int index = -1;
    for (int i = 0; members[i].memberId != -1; i++) {
        if (members[i].memberId == key){
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Member not found" << endl;
    } else {

        cout << "Nama Member : " << members[index].name << endl;
        string dob = members[index].dateOfBirth;
        size_t pos = dob.find(',');
        if (pos != string::npos)
            dob = dob.substr(0, pos);
        cout << "Tanggal dan Tempat Kelahiran : " << dob << endl;
        cout << "Alamat : " << members[index].address << endl;
        cout << "Email : " << members[index].email << endl;
        cout << "Nomor Telepon : " << members[index].phone << endl;
    }
}

/**
 * Pointer implementation with pointer arithmetic
 * Show members
 * 
 * @param mbr is a pointer to the first element of 'struct Member' array
 */
void showMembers(struct Member *mbr) {
    cout
        << setfill('=') << setw(65) << "" << setfill(' ') << endl
        << setw(5) << left << "ID" 
        << setw(30) << left << "Name"
        << setw(30) << left << "Email" << endl
        << setfill('=') << setw(65) << "" << setfill(' ') << endl;

    for (int i=0; (mbr + i)->memberId != -1; i++) {
        cout
            << setw(5) << left << (mbr + i)->memberId
            << setw(30) << left << (mbr + i)->name
            << setw(30) << left << (mbr + i)->email << endl;
    }

    cout << setfill('=') << setw(65) << "" << setfill(' ') << endl;
}

void showAllStaff() {
    cout << setfill('=') << setw(65) << "" << setfill(' ') << endl
         << setw(5) << left << "ID"
         << setw(30) << left << "Name"
         << setw(25) << left << "Role" << endl
         << setfill('=') << setw(65) << "" << setfill(' ') << endl;

    for (int i = 0; staff[i].staffId != -1; i++) {
        cout << setw(5) << left << staff[i].staffId
             << setw(30) << left << staff[i].name
             << setw(25) << left << staff[i].role << endl;
    }
    cout << setfill('=') << setw(65) << "" << setfill(' ') << endl;
}

void storeMembers() {
    FILE* file = fopen("./data/members.txt", "w");
    if (file != nullptr) {
        for (int i = 0; i < getMembersLen(); i++) {
            fprintf(file, "%d|%s|%s|%s|%s|%lld\n",
                members[i].memberId,
                members[i].name.c_str(),
                members[i].dateOfBirth.c_str(),
                members[i].address.c_str(),
                members[i].email.c_str(),
                members[i].phone
            );
        }
        fclose(file);
    } else {
        cout << "Failed to open members file for writing.\n";
    }
}

void loadMembers() {
    FILE* file = fopen("./data/members.txt", "r");
    if (file == nullptr) {
        cout << "No members data available.\n";
        return;
    }

    int count = 0;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        Member m;
        char name[100], dob[20], addr[200], email[100];
        sscanf(line, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%lld",
            &m.memberId, name, dob, addr, email, &m.phone);
        m.name = name;
        m.dateOfBirth = dob;
        m.address = addr;
        m.email = email;

        members[count++] = m;
    }
    setSentinelMember(count);
    fclose(file);
}

void addMember() {
    int currentCount = getMembersLen();
    if (currentCount >= GlobalSize::member - 1) {
        cout << "Member list is full.\n";
        return;
    }

    Member m;
    string temp;

    cout << "Enter Member ID: ";
    getline(cin, temp);
    m.memberId = validateIntInput(temp);
    if (m.memberId == -1) {
        cout << "Invalid ID input.\n";
        return;
    }

    // Cek duplikat ID
    for (int i = 0; members[i].memberId != -1; i++) {
        if (members[i].memberId == m.memberId) {
            cout << "A member with that ID already exists.\n";
            return;
        }
    }

    cout << "Name: ";
    getline(cin, m.name);

    cout << "Date of Birth (YYYY-MM-DD): ";
    getline(cin, m.dateOfBirth);

    cout << "Address: ";
    getline(cin, m.address);

    cout << "Email: ";
    getline(cin, m.email);

    cout << "Phone number: ";
    getline(cin, temp);
    try {
        m.phone = stoll(temp);
    } catch (...) {
        cout << "Invalid phone number.\n";
        return;
    }

    // Simpan ke array
    members[currentCount] = m;
    setSentinelMember(currentCount + 1);

    // Simpan ke file
    storeMembers();

    cout << "\nMember added successfully.\n";
}

void updateMember() {
    string input;
    cout << "Enter Member ID to update: ";
    getline(cin, input);
    int updateId = validateIntInput(input);

    if (updateId == -1) {
        cout << "Invalid ID input.\n";
        return;
    }

    int index = -1;
    for (int i = 0; members[i].memberId != -1; i++) {
        if (members[i].memberId == updateId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Member not found.\n";
        return;
    }

    Member updated;
    string temp;

    cout << "Enter new values (leave blank to keep current):\n";
    cout << "Name [" << members[index].name << "]: ";
    getline(cin, updated.name);
    cout << "Date of Birth [" << members[index].dateOfBirth << "]: ";
    getline(cin, updated.dateOfBirth);
    cout << "Address [" << members[index].address << "]: ";
    getline(cin, updated.address);
    cout << "Email [" << members[index].email << "]: ";
    getline(cin, updated.email);
    cout << "Phone [" << members[index].phone << "]: ";
    getline(cin, temp);

    // Update jika tidak kosong
    if (!updated.name.empty()) members[index].name = updated.name;
    if (!updated.dateOfBirth.empty()) members[index].dateOfBirth = updated.dateOfBirth;
    if (!updated.address.empty()) members[index].address = updated.address;
    if (!updated.email.empty()) members[index].email = updated.email;
    if (!temp.empty()) {
        try {
            members[index].phone = stoll(temp);
        } catch (...) {
            cout << "Invalid phone number input. Keeping old value.\n";
        }
    }

    storeMembers();
    cout << "Member updated successfully.\n";
}

void deleteMember() {
    string input;
    cout << "Enter Member ID to delete: ";
    getline(cin, input);
    int deleteId = validateIntInput(input);

    if (deleteId == -1) {
        cout << "Invalid ID.\n";
        return;
    }

    int index = -1;
    for (int i = 0; members[i].memberId != -1; i++) {
        if (members[i].memberId == deleteId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Member not found.\n";
        return;
    }

    // Geser array ke kiri
    for (int i = index; i < getMembersLen(); i++) {
        members[i] = members[i + 1];
    }

    setSentinelMember(getMembersLen() - 1);
    storeMembers();

    cout << "Member deleted.\n";
}

void deleteBook() {
    string deleteIdStr;
    int deleteId;

    clearScreen();
    sortBooks(1, 1);
    cout << "Enter Book ID to delete: ";
    getline(cin, deleteIdStr);

    deleteId = validateIntInput(deleteIdStr);
    if (deleteId == -1) {
        cout << "Invalid ID.\n";
        return;
    }

    int index = findBookIndexById(deleteId);
    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }

    // Geser elemen array ke kiri
    for (int i = index; i < getBooksLen(); i++) {
        books[i] = books[i + 1];
    }

    setSentinelBook(getBooksLen() - 1);
    storeBooks();
    cout << "Book deleted.\n";
}

void storeStaff() {
    FILE* file = fopen("./data/staff.txt", "w");
    if (file != nullptr) {
        for (int i = 0; i < getStaffLen(); i++) {
            fprintf(file, "%d|%s|%s|%s\n",
                staff[i].staffId,
                staff[i].name.c_str(),
                staff[i].role.c_str(),
                staff[i].email.c_str());
        }
        fclose(file);
    } else {
        cout << "Failed to open staff file for writing.\n";
    }
}

void loadStaff() {
    FILE* file = fopen("./data/staff.txt", "r");
    if (file == nullptr) {
        cout << "No staff data available.\n";
        return;
    }

    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Staff s;
        char name[100], role[50], email[100];
        sscanf(line, "%d|%[^|]|%[^|]|%[^\n]",
               &s.staffId, name, role, email);
        s.name = name;
        s.role = role;
        s.email = email;
        staff[count++] = s;
    }
    setSentinelStaff(count);
    fclose(file);
}

void addStaff() {
    int currentCount = getStaffLen();
    if (currentCount >= GlobalSize::staff - 1) {
        cout << "Staff list is full.\n";
        return;
    }

    Staff s;
    string temp;

    cout << "Enter Staff ID: ";
    getline(cin, temp);
    s.staffId = validateIntInput(temp);
    if (s.staffId == -1) {
        cout << "Invalid ID input.\n";
        return;
    }

    // Cek duplikat ID
    for (int i = 0; staff[i].staffId != -1; i++) {
        if (staff[i].staffId == s.staffId) {
            cout << "Staff with that ID already exists.\n";
            return;
        }
    }

    cout << "Name: ";
    getline(cin, s.name);
    cout << "Role: ";
    getline(cin, s.role);
    cout << "Email: ";
    getline(cin, s.email);

    staff[currentCount] = s;
    setSentinelStaff(currentCount + 1);
    storeStaff();
    cout << "Staff added successfully.\n";
}

void updateStaff() {
    string updateIdStr;
    int updateId;

    clearScreen();
    showAllStaff();  // tampilkan semua data terlebih dulu
    cout << "Enter Staff ID to update: ";
    getline(cin, updateIdStr);
    updateId = validateIntInput(updateIdStr);

    if (updateId == -1) {
        cout << "Invalid ID input.\n";
        return;
    }

    // cari index staff berdasarkan ID
    int index = -1;
    for (int i = 0; staff[i].staffId != -1; i++) {
        if (staff[i].staffId == updateId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Staff not found.\n";
        return;
    }

    Staff updated;
    cout << "Enter new values (leave blank to keep current):\n";

    cout << "Name [" << staff[index].name << "]: ";
    getline(cin, updated.name);
    cout << "Role [" << staff[index].role << "]: ";
    getline(cin, updated.role);
    cout << "Email [" << staff[index].email << "]: ";
    getline(cin, updated.email);

    if (!updated.name.empty()) staff[index].name = updated.name;
    if (!updated.role.empty()) staff[index].role = updated.role;
    if (!updated.email.empty()) staff[index].email = updated.email;

    storeStaff();
    cout << "Staff updated successfully.\n";
}

void deleteStaff() {
    string deleteIdStr;
    int deleteId;

    clearScreen();
    showAllStaff();
    cout << "Enter Staff ID to delete: ";
    getline(cin, deleteIdStr);

    deleteId = validateIntInput(deleteIdStr);
    if (deleteId == -1) {
        cout << "Invalid ID.\n";
        return;
    }

    int index = -1;
    for (int i = 0; staff[i].staffId != -1; i++) {
        if (staff[i].staffId == deleteId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Staff not found.\n";
        return;
    }

    // geser ke kiri
    for (int i = index; i < getStaffLen(); i++) {
        staff[i] = staff[i + 1];
    }

    setSentinelStaff(getStaffLen() - 1);
    storeStaff();
    cout << "Staff deleted.\n";
}

void showAllLoans() {
    cout << setfill('=') << setw(80) << "" << setfill(' ') << endl
         << setw(5) << left << "ID"
         << setw(10) << left << "MemberID"
         << setw(10) << left << "BookID"
         << setw(10) << left << "StaffID"
         << setw(15) << left << "Loan Date"
         << setw(15) << left << "Return Date"
         << setw(10) << left << "Status" << endl
         << setfill('=') << setw(80) << "" << setfill(' ') << endl;

    for (int i = 0; loans[i].id != -1; i++) {
        cout << setw(5) << left << loans[i].id
             << setw(10) << left << loans[i].memberId
             << setw(10) << left << loans[i].bookId
             << setw(10) << left << loans[i].staffId
             << setw(15) << left << loans[i].loanDate
             << setw(15) << left << loans[i].returnDate
             << setw(10) << left << loans[i].status << endl;
    }

    cout << setfill('=') << setw(80) << "" << setfill(' ') << endl;
}

void storeLoans() {
    FILE* file = fopen("./data/loans.txt", "w");
    if (file != nullptr) {
        for (int i = 0; i < getLoansLen(); i++) {
            fprintf(file, "%d|%d|%d|%d|%s|%s|%s\n",
                loans[i].id,
                loans[i].memberId,
                loans[i].bookId,
                loans[i].staffId,
                loans[i].loanDate.c_str(),
                loans[i].returnDate.c_str(),
                loans[i].status.c_str()
            );
        }
        fclose(file);
    } else {
        cout << "Failed to open loans file for writing.\n";
    }
}

void addLoan() {
    int currentCount = getLoansLen();
    if (currentCount >= GlobalSize::loan - 1) {
        cout << "Loan list is full.\n";
        return;
    }

    Loan l;
    string temp;

    cout << "Enter Loan ID: ";
    getline(cin, temp);
    l.id = validateIntInput(temp);
    if (l.id == -1) {
        cout << "Invalid ID.\n";
        return;
    }

    // Cek duplikat ID
    for (int i = 0; loans[i].id != -1; i++) {
        if (loans[i].id == l.id) {
            cout << "Loan ID already exists.\n";
            return;
        }
    }

    // Member ID
    cout << "Enter Member ID: ";
    getline(cin, temp);
    l.memberId = validateIntInput(temp);
    if (find_if(begin(members), end(members), [&](const Member& m){ return m.memberId == l.memberId; }) == end(members)) {
        cout << "Member not found.\n";
        return;
    }

    // Book ID
    cout << "Enter Book ID: ";
    getline(cin, temp);
    l.bookId = validateIntInput(temp);
    int bookIndex = findBookIndexById(l.bookId);
    if (bookIndex == -1) {
        cout << "Book not found.\n";
        return;
    }
    if (books[bookIndex].stock <= 0) {
        cout << "Book is out of stock.\n";
        return;
    }

    // Staff ID
    cout << "Enter Staff ID: ";
    getline(cin, temp);
    l.staffId = validateIntInput(temp);
    if (find_if(begin(staff), end(staff), [&](const Staff& s){ return s.staffId == l.staffId; }) == end(staff)) {
        cout << "Staff not found.\n";
        return;
    }

    // Tanggal pinjam dan kembali
    cout << "Enter Loan Date (YYYY-MM-DD): ";
    getline(cin, l.loanDate);
    cout << "Enter Expected Return Date (YYYY-MM-DD): ";
    getline(cin, l.returnDate);

    l.status = "Loaned";

    // Tambahkan ke array
    loans[currentCount] = l;
    setSentinelLoan(currentCount + 1);

    // Kurangi stok buku
    books[bookIndex].stock--;

    storeBooks();
    storeLoans();
    cout << "Loan successfully added.\n";
}

void returnLoan() {
    string temp;
    cout << "Enter Loan ID to return: ";
    getline(cin, temp);
    int loanId = validateIntInput(temp);

    if (loanId == -1) {
        cout << "Invalid ID.\n";
        return;
    }

    int index = -1;
    for (int i = 0; loans[i].id != -1; i++) {
        if (loans[i].id == loanId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Loan not found.\n";
        return;
    }

    if (toLowerCase(loans[index].status) == "returned") {
        cout << "Book already returned.\n";
        return;
    }

    // Cari buku dan tambahkan stok
    int bookIndex = findBookIndexById(loans[index].bookId);
    if (bookIndex != -1) {
        books[bookIndex].stock++;
    }

    loans[index].status = "Returned";
    cout << "Book returned successfully.\n";

    storeBooks();
    storeLoans();
    cout << "Loan status updated to 'Returned'.\n";
}



void loadLoans() {
    FILE* file = fopen("./data/loans.txt", "r");
    if (file == nullptr) {
        cout << "No loan data available.\n";
        return;
    }

    int count = 0;
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        Loan l;
        char loanDate[20], returnDate[20], status[20];

        sscanf(line, "%d|%d|%d|%d|%[^|]|%[^|]|%[^\n]",
            &l.id, &l.memberId, &l.bookId, &l.staffId,
            loanDate, returnDate, status
        );

        l.loanDate = loanDate;
        l.returnDate = returnDate;
        l.status = status;

        loans[count++] = l;
    }

    setSentinelLoan(count);
    fclose(file);
}

void deleteLoan() {
    string input;
    cout << "Enter Loan ID to delete: ";
    getline(cin, input);
    int deleteId = validateIntInput(input);

    if (deleteId == -1) {
        cout << "Invalid ID.\n";
        return;
    }

    int index = -1;
    for (int i = 0; loans[i].id != -1; i++) {
        if (loans[i].id == deleteId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Loan not found.\n";
        return;
    }

    // Tambahkan stok kembali jika status masih "Loaned"
    if (toLowerCase(loans[index].status) == "loaned") {
        int bookIndex = findBookIndexById(loans[index].bookId);
        if (bookIndex != -1) {
            books[bookIndex].stock++;
            storeBooks();
        }
    }

    // Geser array ke kiri
    for (int i = index; i < getLoansLen(); i++) {
        loans[i] = loans[i + 1];
    }

    setSentinelLoan(getLoansLen() - 1);
    storeLoans();

    cout << "Loan deleted.\n";
}

void mainPage(){
    cout << "Welcome to the Library Management System\n";
    loadBooks();
    loadMembers();
    loadStaff();
    loadLoans();
    char repeatMainMenu;
    int mainChoice;
    do {
        mainChoice = getMainChoice();
        switch (mainChoice) {
            case 1: { // Sub menu 'Book'
                int bookChoice;
                do {
                    bookChoice = getBookChoice();
                    switch (bookChoice) {
                        case 1: {
                            int searchBookChoice;
                            do {
                                searchBookChoice = getSearchBookChoice();
                                switch (searchBookChoice) {
                                    case 1: { //search book by id
                                        int bookId;
                                        cin.ignore();
                                        cout << "Enter Book ID : "; cin >> bookId;
                                        cin.ignore();
                                        if (bookId==0) break;
                                        cout<< "Result  :" << searchBookById(0,bookId) << endl;
                                        enterToContinue();
                                        break;
                                    }
                                    case 2://search book by title
                                        searchBookByTitle();
                                        enterToContinue();
                                        break;
                                    case 0:
                                        cout << "Back to book menu\n";
                                        break;
                                    default:
                                        invalidChoice();
                                        break;
                                }

                            } while (searchBookChoice != 0);
                            break;
                        }
                        case 2:
                            showBooksOrder();
                            enterToContinue();
                            break;
                        case 3:
                            addBooks();
                            enterToContinue();
                            break;
                        case 4:
                            updateBook();
                            enterToContinue();
                            break;
                        case 5:
                            deleteBook();
                            enterToContinue();
                            break;
                        case 0:
                        cout << "Back to main menu\n";
                            enterToContinue();
                            break;
                        default: {
                            invalidChoice();
                            break;
                        }
                    }
                } while(bookChoice != 0);
                break;
            }
            case 2: { // Sub menu 'Member'
                int memberChoice;
                do {
                    memberChoice = getMemberChoice();
                    switch (memberChoice) {
                        case 1:
                            searchMemberById();
                            enterToContinue();
                            break;
                        case 2:
                            showMembers(members);
                            enterToContinue();
                            break;
                        case 3:
                            addMember();
                            enterToContinue();
                            break;
                        case 4:
                            updateMember();
                            enterToContinue();
                            break;
                        case 5:
                            deleteMember();
                            enterToContinue();
                            break;
                        case 0:
                            cout << "Back to main menu\n";
                            break;
                        default:
                            invalidChoice();
                            break;
                    }
                } while (memberChoice != 0);
                break;
            }
            case 3: { // Sub menu 'Staff'
                int staffChoice;
                do {
                    staffChoice = getStaffChoice();
                    switch (staffChoice) {
                        case 1:
                            showAllStaff();
                            enterToContinue();
                            break;
                            case 2:
                            addStaff();
                            enterToContinue();
                            break;
                        case 3:
                            updateStaff();
                            enterToContinue();
                            break;
                        case 4:
                            deleteStaff();
                            enterToContinue();
                            break;
                        case 0:
                            cout << "Back to main menu";
                            enterToContinue();
                            break;
                        default:
                            invalidChoice();
                            break;
                    }
                } while (staffChoice != 0);
                break;
            } 
            case 4: {// Sub menu "Loans"
                int LoanChoice;
                do {
                    LoanChoice = getLoansChoice();
                    switch (LoanChoice) {
                        case 1:
                            showAllLoans();
                            enterToContinue();
                            break;
                        case 2: {
                            addLoan();
                            enterToContinue();
                            break;
                        }
                        case 3: {
                            returnLoan();
                            enterToContinue();
                            break;
                        }
                        case 4: {
                            deleteLoan();
                            enterToContinue();
                            break;
                        }
                        case 0:
                            cout << "Back to main menu\n";
                            break;
                        default:
                            invalidChoice();
                            break;
                    }
                } while (LoanChoice != 0);
                break;
            }
            case 5: { //Register user
                registerUser();
                enterToContinue();
                break;
            }
            case 0:
                cout << "Exit\n";
                break;
            default: {
                invalidChoice();
                break;
            }
        }
    } while (mainChoice != 0);
}

void menu() {
    system("cls");
    char pilihan;
    cout << "============================\n";
    cout << "1. LOGIN                    |\n";
    cout << "2. KELUAR                   |\n";
    cout << "============================\n";
    cout << "Masukkan pilihan : ";
    cin >> pilihan;
    switch (pilihan) {
        case '1': login(3); break;
        case '2': exit(0); break;
        default:
            cout << "Input salah\n. Mohon masukkan INPUT sesuai ketentuan!!\n";
            system("pause");
            menu();
            break;
    }
}

int main(){
    menu();
}