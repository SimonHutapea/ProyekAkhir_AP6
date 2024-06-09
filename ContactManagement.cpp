#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Tambahan untuk std::transform
using namespace std;

struct Contact {
    string nama;
    string nomorKontak;
};

class manajemenKontak {
private:
    vector<Contact> contacts;

    // Fungsi untuk mengubah string menjadi huruf kecil
    string toLowerCase(const string& str) const {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

public:
    void tambahkanKontak(const string& nama, const string& nomorKontak) {
        Contact kontakBaru{nama, nomorKontak};
        contacts.push_back(kontakBaru);
        cout << "Kontak ditambahkan: " << nama << " - " << nomorKontak << endl;
    }

    void daftarKontak() const {
        if (contacts.empty()) {
            cout << "Tidak ada kontak yang tersedia." << endl;
            return;
        }

        cout << "Daftar Kontak:" << endl;
        for (const auto& contact : contacts) {
            cout << "Nama: " << contact.nama << ", Nomor Kontak: " << contact.nomorKontak << endl;
        }
    }

    vector<Contact*> cariKontak(const string& substring) {
        vector<Contact*> hasil;
        // Mengubah substring menjadi huruf kecil
        string lowerSubString = toLowerCase(substring);
        for (auto& contact : contacts) {
            // Mengubah nama kontak menjadi huruf kecil saat melakukan pencarian
            if (toLowerCase(contact.nama).find(lowerSubString) != string::npos) {
                hasil.push_back(&contact);
            }
        }
        return hasil;
    }

    void hapusKontak(const string& nama) {
        auto it = contacts.begin();
        while (it != contacts.end()) {
            if (it->nama == nama) {
                cout << "Kontak dihapus: " << it->nama << endl;
                contacts.erase(it);
                return;
            }
            ++it;
        }
        cout << "Kontak tidak ditemukan: " << nama << endl;
    }
};

void menu(manajemenKontak& manager) {
    int pilih;
    do {
        cout << "\nMenu Manajemen Kontak\n";
        cout << "1. Tambahkan Kontak Baru\n";
        cout << "2. Munculkan Daftar Kontak\n";
        cout << "3. Cari Kontak\n";
        cout << "4. Hapus Kontak\n";
        cout << "5. Keluar\n";
        cout << "Masukkan pilihan anda: ";
        cin >> pilih;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Pilihan tidak valid. Tolong masukkan pilihan dengan benar." << endl;
            continue;
        }

        switch (pilih) {
        case 1: {
            string nama, nomorKontak;
            cout << "Masukkan nama: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan Nomor Kontak: ";
            cin >> nomorKontak;
            manager.tambahkanKontak(nama, nomorKontak);
            break;
        }
        case 2:
            manager.daftarKontak();
            break;
        case 3: {
            string subString;
            cout << "Masukkan Nama Kontak: ";
            cin.ignore();
            getline(cin, subString);
            vector<Contact*> hasil = manager.cariKontak(subString);
            if (!hasil.empty()) {
                cout << "Kontak ditemukan:\n";
                for (auto contact : hasil) {
                    cout << "Nama: " << contact->nama << " - " << contact->nomorKontak << endl;
                }
            } else {
                cout << "Kontak tidak ditemukan: " << subString << endl;
            }
            break;
        }
        case 4: {
            string nama;
            cout << "Masukkan Nama Kontak: ";
            cin.ignore();
            getline(cin, nama);
            manager.hapusKontak(nama);
            break;
        }
        case 5:
            cout << "Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilih != 5);
}

int main() {
    manajemenKontak manager;
    menu(manager);
    return 0;
}