#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Struct untuk makanan
struct Food {
    string name;
    int quantity;
    int calories;
    char goal; // 'N' untuk naik berat badan, 'T' untuk turun berat badan
};

// Struct untuk review
struct Review {
    string username;
    string comment;
    int rating;
};

// Fungsi untuk mencetak beberapa makanan
void printSeveralFoods(Food foods[], int foodCount, char goal) {
    for (int i = 0; i < foodCount; i++) {
        if (foods[i].goal == goal) {
            cout << "Nama: " << foods[i].name << ", Kalori per porsi: " << foods[i].calories << endl;
        }
    }
}

// Fungsi rekursif untuk mencari makanan
bool searchFood(Food foods[], int foodCount, string target, int index = 0) {
    if (index == foodCount) {
        return false;
    }
    if (foods[index].name == target) {
        return true;
    }
    return searchFood(foods, foodCount, target, index + 1);
}

// Fungsi untuk mencari makanan berdasarkan tujuan berat badan
void searchWeightGoal(Food foods[], int foodCount, char goal) {
    bool found = false;
    string target;
    cout << "Masukkan nama makanan yang ingin Anda cari: ";
    cin.ignore();
    getline(cin, target);

    cout << "Makanan yang direkomendasikan untuk ";
    if (goal == 'N') {
        cout << "menaikkan berat badan:" << endl;
    } else if (goal == 'T') {
        cout << "menurunkan berat badan:" << endl;
    } else {
        cout << "Pilihan tidak valid." << endl;
        return;
    }

    for (int i = 0; i < foodCount; i++) {
        if (foods[i].goal == goal && foods[i].name == target) {
            cout << "Nama: " << foods[i].name << ", Kalori per porsi: " << foods[i].calories << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Makanan yang dicari tidak ditemukan." << endl;
    }
}

// Fungsi untuk menambahkan makanan
void addFood(Food foods[], int& foodCount, char weightGoal) {
    string name;
    int quantity, calories;
    cout << "Masukkan nama makanan: ";
    cin.ignore();
    getline(cin, name);
    cout << "Masukkan jumlah porsi: ";
    cin >> quantity;
    cout << "Masukkan kalori per porsi: ";
    cin >> calories;
    foods[foodCount++] = {name, quantity, calories, weightGoal};

    if (weightGoal == 'N' && calories > 300) {
        cout << "Makanan berhasil ditambahkan! Direkomendasikan untuk menaikkan berat badan." << endl;
    } else if (weightGoal == 'T' && calories < 100) {
        cout << "Makanan berhasil ditambahkan! Direkomendasikan untuk menurunkan berat badan." << endl;
    } else {
        cout << "Makanan berhasil ditambahkan!" << endl;
    }
}

// Fungsi untuk menambahkan review
void addReview(Review reviews[], int& reviewCount, const string& username) {
    if (reviewCount >= 100) {
        cout << "Jumlah review sudah mencapai batas maksimum." << endl;
        return;
    }
    
    cout << "Masukkan komentar Anda: ";
    cin.ignore();
    getline(cin, reviews[reviewCount].comment);

    cout << "Masukkan rating Anda (dari 1 hingga 5): ";
    cin >> reviews[reviewCount].rating;

    reviews[reviewCount].username = username;
    reviewCount++;
}

// Fungsi untuk menampilkan review
void printReviews(Review reviews[], int reviewCount) {
    if (reviewCount == 0) {
        cout << "Belum ada review untuk ditampilkan." << endl;
    } else {
        cout << "Review:" << endl;
        for (int i = 0; i < reviewCount; i++) {
            cout << "Nama Pengguna: " << reviews[i].username << ", Komentar: " << reviews[i].comment << ", Rating: " << reviews[i].rating << endl;
        }
    }
}

// Fungsi untuk mengurutkan review berdasarkan rating menggunakan Bubble Sort
void bubbleSortReviewsByRating(Review reviews[], int reviewCount) {
    for (int i = 0; i < reviewCount - 1; i++) {
        for (int j = 0; j < reviewCount - i - 1; j++) {
            if (reviews[j].rating < reviews[j + 1].rating) { // Mengurutkan dari rating tertinggi ke terendah
                // Tukar posisi review
                Review temp = reviews[j];
                reviews[j] = reviews[j + 1];
                reviews[j + 1] = temp;
            }
        }
    }
}

// Fungsi untuk mendaftarkan pengguna
void registerUser(string usernames[], string passwords[], int& userCount) {
    string username, password;
    bool usernameExists = false;

    cout << "Masukkan nama pengguna: ";
    cin.ignore();
    getline(cin, username);

    // Cek apakah nama pengguna sudah ada
    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == username) {
            usernameExists = true;
            break;
        }
    }

    if (usernameExists) {
        cout << "Nama pengguna sudah ada. Silakan pilih nama pengguna lain." << endl;
    } else {
        cout << "Masukkan kata sandi: ";
        getline(cin, password);
        usernames[userCount] = username;
        passwords[userCount] = password;
        userCount++;
        cout << "Registrasi berhasil!" << endl;
    }
}

// Fungsi untuk melakukan login pengguna
bool loginUser(string usernames[], string passwords[], int userCount, bool& isAdmin, string& loggedInUsername) {
    string username, password;
    cout << "Masukkan nama pengguna: ";
    cin.ignore();
    getline(cin, username);
    cout << "Masukkan kata sandi: ";
    getline(cin, password);

    if (username == "admin" && password == "admin123") {
        isAdmin = true;
        loggedInUsername = username;
        cout << "Login sebagai admin berhasil!" << endl;
        return true;
    }

    for (int i = 0; i < userCount; i++) {
        if (username == usernames[i] && password == passwords[i]) {
            loggedInUsername = username;
            cout << "Login berhasil!" << endl;
            return true;
        }
    }
    cout << "Nama pengguna atau kata sandi salah." << endl;
    return false;
}

// Fungsi untuk menghapus makanan
void deleteFood(Food foods[], int& foodCount) {
    string name;
    cout << "Masukkan nama makanan yang ingin dihapus: ";
    cin.ignore();
    getline(cin, name);
    bool found = false;
    for (int i = 0; i < foodCount; i++) {
        if (foods[i].name == name) {
            for (int j = i; j < foodCount - 1; j++) {
                foods[j] = foods[j + 1];
            }
            foodCount--;
            found = true;
            cout << "Makanan berhasil dihapus!" << endl;
            break;
        }
    }
    if (!found) {
        cout << "Makanan tidak ditemukan." << endl;
    }
}

// Fungsi untuk melihat semua review
void viewAllReviews(Review reviews[], int reviewCount) {
    if (reviewCount == 0) {
        cout << "Belum ada review untuk ditampilkan." << endl;
    } else {
        bubbleSortReviewsByRating(reviews, reviewCount); // Tambahkan ini untuk mengurutkan review
        cout << "Semua Review:" << endl;
        for (int i = 0; i < reviewCount; i++) {
            cout << "Nama Pengguna: " << reviews[i].username << ", Komentar: " << reviews[i].comment << ", Rating: " << reviews[i].rating << endl;
        }
    }
}

int main() {
    const int MAX_FOODS = 100;
    Food foods[MAX_FOODS];
    Review reviews[MAX_FOODS];
    int foodCount = 0;
    int reviewCount = 0;

    const int MAX_USERS = 100;
    string usernames[MAX_USERS];
    string passwords[MAX_USERS];
    int userCount = 0;

    foods[foodCount++] = {"Daging Sapi", 1, 600, 'N'};
    foods[foodCount++] = {"Alpukat", 1, 400, 'N'};
    foods[foodCount++] = {"Kacang Almond", 1, 350, 'N'};

    foods[foodCount++] = {"Brokoli", 1, 30, 'T'};
    foods[foodCount++] = {"Kentang Rebus", 1, 70, 'T'};
    foods[foodCount++] = {"Ikan Salmon", 1, 200, 'T'};

    char choice;
    char weightGoal;
    bool loggedIn = false;
    bool isAdmin = false;
    string loggedInUsername;
    int loginAttempts = 0;
    const int maxAttempts = 3;

    while (true) {
        while (!loggedIn) {
            if (loginAttempts >= maxAttempts) {
                cout << "Anda telah mencapai batas maksimum percobaan login. Program akan keluar." << endl;
                exit(0);
            }

            cout << "== Menu Login/Daftar ==" << endl;
            cout << "1. Daftar" << endl;
            cout << "2. Login" << endl;
            cout << "3. Keluar" << endl;
            cout << "Pilih: ";
            cin >> choice;

            switch (choice) {
                case '1':
                    registerUser(usernames, passwords, userCount);
                    break;
                case '2':
                    if (loginUser(usernames, passwords, userCount, isAdmin, loggedInUsername)) {
                        loggedIn = true;
                    } else {
                        loginAttempts++;
                    }
                    break;
                case '3':
                    cout << "Program berakhir." << endl;
                    exit(0);
                default:
                    cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
        }

        while (loggedIn) {
            if (isAdmin) {
                cout << "== Menu Admin ==" << endl;
                cout << "1. Tambah Makanan" << endl;
                cout << "2. Hapus Makanan" << endl;
                cout << "3. Lihat Semua Review" << endl;
                cout << "4. Cari Makanan" << endl;
                cout << "5. Logout" << endl;
                cout << "Pilih: ";
                cin >> choice;

                switch (choice) {
                    case '1':
                        cout << "Apakah makanan yang ditambahkan direkomendasikan untuk menaikkan atau menurunkan berat badan? (N/T): ";
                        cin >> weightGoal;
                        if (weightGoal != 'N' && weightGoal != 'T') {
                            cout << "Pilihan tidak valid. Silakan masukkan N untuk menaikkan berat badan atau T untuk menurunkan berat badan." << endl;
                            continue;
                        }
                        addFood(foods, foodCount, weightGoal);
                        break;
                    case '2':
                        deleteFood(foods, foodCount);
                        break;
                    case '3':
                        viewAllReviews(reviews, reviewCount);
                        break;
                    case '4':
                        cout << "Apakah Anda ingin menaikkan atau menurunkan berat badan? (N/T): ";
                        cin >> weightGoal;
                        cout << "Beberapa makanan yang direkomendasikan:" << endl;
                        if (weightGoal == 'N') {
                            printSeveralFoods(foods, foodCount, 'N');
                        } else if (weightGoal == 'T') {
                            printSeveralFoods(foods, foodCount, 'T');
                        } else {
                            cout << "Pilihan tidak valid." << endl;
                            continue;
                        }
                        searchWeightGoal(foods, foodCount, weightGoal);
                        break;
                    case '5':
                        loggedIn = false;
                        isAdmin = false;
                        loginAttempts = 0; // reset attempts on successful login and logout
                        cout << "Logout berhasil." << endl;
                        break;
                    default:
                        cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                }
            } else {
                cout << "== Menu Utama ==" << endl;
                cout << "1. Cari Makanan" << endl;
                cout << "2. Tambah Review" << endl;
                cout << "3. Tampilkan Review" << endl;
                cout << "4. Logout" << endl;
                cout << "Pilih: ";
                cin >> choice;

                switch (choice) {
                    case '1':
                        cout << "Apakah Anda ingin menaikkan atau menurunkan berat badan? (N/T): ";
                        cin >> weightGoal;
                        cout << "Beberapa makanan yang direkomendasikan:" << endl;
                        if (weightGoal == 'N') {
                            printSeveralFoods(foods, foodCount, 'N');
                        } else if (weightGoal == 'T') {
                            printSeveralFoods(foods, foodCount, 'T');
                        } else {
                            cout << "Pilihan tidak valid." << endl;
                            continue;
                        }
                        searchWeightGoal(foods, foodCount, weightGoal);
                        break;
                    case '2':
                        addReview(reviews, reviewCount, loggedInUsername);
                        break;
                    case '3':
                        printReviews(reviews, reviewCount);
                        break;
                    case '4':
                        loggedIn = false;
                        loginAttempts = 0; // reset attempts on successful login and logout
                        cout << "Logout berhasil." << endl;
                        break;
                    default:
                        cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                }
            }
        }
    }

    return 0;
}
