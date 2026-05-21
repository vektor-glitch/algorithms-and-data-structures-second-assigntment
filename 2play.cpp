#include <iostream>
#include <iomanip>
using namespace std;

// struct bes
struct lagu
{
    string judul;
    string penyanyi;
    float durasi;
    int tahunterbit;

    lagu *kiri;
    lagu *kanan;
};

lagu *root = NULL;
lagu *headplaylist = NULL;
lagu *tailplaylist = NULL;
lagu *topriwayat = NULL;

// fungsi ini buat bikin node baru pada memori setiap kita menambah lagu bes
lagu *buatnode(string judul, string penyanyi, float durasi, int tahun)
{
    lagu *nodebaru = new lagu();
    nodebaru->judul = judul;
    nodebaru->penyanyi = penyanyi;
    nodebaru->tahunterbit = tahun;
    nodebaru->durasi = durasi;
    nodebaru->kiri = NULL;
    nodebaru->kanan = NULL;
    return nodebaru;
}

// yes or no
bool yesorno(string yort)
{
    cout << endl;
    while (true)
    {
        cout << "Kembali ke menu utama? (Y/T) : ";
        cin >> yort;

        if (yort == "ya" || yort == "Ya" || yort == "YA" || yort == "yA" || yort == "y" || yort == "Y")
        {
            system("cls");
            return false;
        }
        else if (yort == "tidak" || yort == "Tidak" || yort == "TIDAK" || yort == "t" || yort == "T")
        {
            system("cls");
            return true;
        }
        else
        {
            cout << "Opsi tidak tersedia! Input hanya (ya/tidak atau y/t). Silahkan coba lagi." << endl;
        }
    }
}

// fuction buat nambah lagu ya bes
lagu *tambah(lagu *node, string judul, string penyanyi, float durasi, int tahun)
{
    // error handling bes
    if (node == NULL)
    {
        return buatnode(judul, penyanyi, durasi, tahun);
    }

    // ini untuk membandingkan judul untuk disisipkan ke kiri atau ke kanan bes
    if (judul < node->judul)
    {
        node->kiri = tambah(node->kiri, judul, penyanyi, durasi, tahun);
    }
    else if (judul > node->judul)
    {
        node->kanan = tambah(node->kanan, judul, penyanyi, durasi, tahun);
    }
    else
    {
        cout << "Lagu dengan judul yang sama sudah ada!" << endl;
    }
    return node;
}

void tambahlagu()
{
    string jdl;
    string pnyny;
    int thn;
    float drs;

    cout << "==== TAMBAH LAGU 2PLAY ====" << endl;
    cout << "Judul Lagu    : ";
    cin >> ws;
    getline(cin, jdl);
    cout << "Penyanyi      : ";
    getline(cin, pnyny);
    cout << "tahun Terbit  : ";
    while (!(cin >> thn) || thn < 0)
    {
        cout << "Tahun tidak valid! Silahkan input angka yang benar: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << "Durasi Lagu   : ";
    while (!(cin >> drs) || drs <= 0)
    {
        cout << "Durasi tidak valid! Silahkan input angka lebih dari 0: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    root = tambah(root, jdl, pnyny, drs, thn);
    cout << "Lagu berhasil ditambahkan!" << endl;
}

// function tampilkan lagu bes

void preorder(lagu *node)
{
    // error handling bes
    if (node != NULL)
    {
        cout << left << setw(30) << node->judul << " | "
             << left << setw(25) << node->penyanyi << " | "
             << left << setw(10) << node->durasi << " | "
             << left << setw(14) << node->tahunterbit << endl;
        preorder(node->kiri);
        preorder(node->kanan);
    }
}

void inorder(lagu *node)
{
    if (node != NULL)
    {
        inorder(node->kiri);
        cout << left << setw(30) << node->judul << " | "
             << left << setw(25) << node->penyanyi << " | "
             << left << setw(10) << node->durasi << " | "
             << left << setw(14) << node->tahunterbit << endl;
        inorder(node->kanan);
    }
}

void postorder(lagu *node)
{
    if (node != NULL)
    {
        postorder(node->kiri);
        postorder(node->kanan);
        cout << left << setw(30) << node->judul << " | "
             << left << setw(25) << node->penyanyi << " | "
             << left << setw(10) << node->durasi << " | "
             << left << setw(14) << node->tahunterbit << endl;
    }
}

void tampilkanlagu()
{
    if (root == NULL)
    {
        cout << "==== TAMPILKAN LAGU 2PLAY ====" << endl;
        cout << "Belum ada lagu! Silahkan tambahkan lagu terlebih dahulu." << endl;
        return;
    }

    int pilihan;

    // error handling bes
    while (true)
    {
        cout << "==== TAMPILKAN LAGU 2PLAY ====" << endl;
        cout << "Pilih metode penampilan" << endl;
        cout << "1. Preorder" << endl;
        cout << "2. Inorder" << endl;
        cout << "3. Postorder" << endl;
        cout << "Metode: ";

        if (!(cin >> pilihan))
        {
            cout << "Input harus angka! Silahkan coba lagi.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            system("pause");
            system("cls");
            continue;
        }

        if (pilihan >= 1 && pilihan <= 3)
        {
            break;
        }
        else
        {
            cout << "Opsi tidak tersedia! Silahkan coba lagi.\n";
            system("pause");
            system("cls");
        }
    }

    cout << left << setw(30) << "Judul" << " | "
         << left << setw(25) << "Penyanyi" << " | "
         << left << setw(10) << "Durasi" << " | "
         << left << setw(10) << "Tahun Terbit" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    switch (pilihan)
    {
    case 1:
        preorder(root);
        break;

    case 2:
        inorder(root);
        break;

    case 3:
        postorder(root);
        break;
    }
    cout << "-----------------------------------------------------------------------------------------" << endl;
}

// function cari lagu bes
lagu *search(lagu *node, string target)
{
    // error handling bila gaada
    if (node == NULL)
    {
        return NULL;
    }

    // ini kalo target sesuai dengan node saat ini
    if (target == node->judul)
    {
        return node;
    }

    // ini kalo target lebih kecil, cari ke kiri
    if (target < node->judul)
    {
        return search(node->kiri, target);
    }

    // ini kalo target lebih besar, cari ke kanan
    return search(node->kanan, target);
}

void carilagu()
{
    // error handling
    if (root == NULL)
    {
        cout << "Belum ada lagu! Silahkan tambahkan lagu terlebih dahulu.";
        return;
    }

    string targetjudul;
    cout << "==== CARI LAGU 2PLAY ====" << endl;
    cout << "Masukkan judul lagu: ";
    cin >> ws;
    getline(cin, targetjudul);

    lagu *hasil = search(root, targetjudul);

    if (hasil != NULL)
    {
        cout << "Lagu Ditemukan!" << endl;
        cout << endl;
        cout << "==== DATA LAGU ====" << endl;
        cout << "Judul      : " << hasil->judul << endl;
        cout << "Penyanyi   : " << hasil->penyanyi << endl;
        cout << "Tahun      : " << hasil->tahunterbit << endl;
        cout << "Durasi     : " << hasil->durasi << endl;
    }
    else
    {
        cout << "Lagu " << targetjudul << " tidak ditemukan!" << endl;
    }
}

void tambahkeplaylist()
{
    // error handling
    if (root == NULL)
    {
        cout << "Belum ada lagu! Silahkan tambahkan lagu terlebih dahulu.";
        return;
    }

    string trgtjdl;
    cout << "=== TAMBAH LAGU KE PLAYLIST ===" << endl;
    cout << "Masukkan judul lagu: ";
    cin >> ws;
    getline(cin, trgtjdl);

    lagu *hasil = search(root, trgtjdl);

    if (hasil == NULL)
    {
        cout << "Lagu tidak ditemukan!" << endl;
        return;
    }

    lagu *buatnodelagubaru = buatnode(hasil->judul, hasil->penyanyi, hasil->durasi, hasil->tahunterbit);

    if (headplaylist == NULL)
    {
        headplaylist = buatnodelagubaru;
        tailplaylist = buatnodelagubaru;
    }
    else
    {
        tailplaylist->kanan = buatnodelagubaru;
        tailplaylist = buatnodelagubaru;
    }
    cout << "Lagu berhasil ditambahkan ke playlist!" << endl;
}

void lihatplaylist()
{
    if (headplaylist == NULL)
    {
        cout << "Belum ada lagu yang ditambahkan pada playlist! Silahkan tambah lagu terlebih dahulu." << endl;
        return;
    }

    lagu *bantu = headplaylist;

    cout << "==== PLAYLIST AKTIF 2PLAY ====" << endl;
    cout << endl;
    cout << left << setw(30) << "Judul" << " | "
         << left << setw(25) << "Penyanyi" << " | "
         << left << setw(10) << "Durasi" << " | "
         << left << setw(10) << "Tahun Terbit" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    while (bantu != NULL)
    {
        cout << left << setw(30) << bantu->judul << " | "
             << left << setw(25) << bantu->penyanyi << " | "
             << left << setw(10) << bantu->durasi << " | "
             << left << setw(14) << bantu->tahunterbit << endl;

        bantu = bantu->kanan;
    }
    cout << "-----------------------------------------------------------------------------------------" << endl;
}

void putarplaylist()
{
    if (headplaylist == NULL)
    {
        cout << "==== PUTAR PLAYLIST 2PLAY ====" << endl;
        cout << endl;
        cout << "Belum ada lagu yang ditambahkan pada playlist! Silahkan tambah lagu terlebih dahulu." << endl;
        return;
    }

    int pilihan;
    bool dihentikan = false;

    while (headplaylist != NULL)
    {
        system("cls");
        while (true)
        {
            cout << "==== PUTAR PLAYLIST 2PLAY ====" << endl;
            cout << "=====================================================================================" << endl;
            cout << "Sedang memutar:" << endl;
            cout << headplaylist->judul << " - " << headplaylist->penyanyi << endl;
            cout << "=====================================================================================" << endl;
            cout << endl;
            cout << "1. Lagu Berikutnya" << endl;
            cout << "2. Stop Playlist" << endl;
            cout << "Pilih: ";

            if (!(cin >> pilihan))
            {
                cout << "Input harus angka! Silahkan coba lagi.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                system("pause");
                system("cls");
                continue;
            }

            if (pilihan >= 1 && pilihan <= 2)
            {
                break;
            }
            else
            {
                cout << "Opsi tidak tersedia! Silahkan coba lagi.\n";
                system("pause");
                system("cls");
            }
        }
        if (pilihan == 1)
        {
            lagu *nodeout = headplaylist;
            headplaylist = headplaylist->kanan;
            if (headplaylist == NULL)
            {
                tailplaylist = NULL;
            }

            // ini untuk dimasukkan ke riwayat ygy
            nodeout->kanan = topriwayat;
            topriwayat = nodeout;
        }
        else
        {
            dihentikan = true;
            break;
        }
    }

    if (dihentikan)
    {
        cout << "Memutar playlist dihentikan!" << endl;
    }
    else
    {
        cout << "Semua lagu sudah diputar!" << endl;
    }
}

void replaylagu()
{
    // error handling
    if (root == NULL)
    {
        cout << "Belum ada lagu! Silahkan tambahkan lagu terlebih dahulu.";
        return;
    }

    string trgtjdl;
    cout << "=== REPLAY LAGU 2PLAY ===" << endl;
    cout << "Masukkan judul lagu: ";
    cin >> ws;
    getline(cin, trgtjdl);

    lagu *hasil = search(root, trgtjdl);

    if (hasil == NULL)
    {
        cout << "Lagu tidak ditemukan!" << endl;
        return;
    }

    int pilihan;
    while (true)
    {
        cout << "==== MODE REPLAY 2PLAY ====" << endl;
        cout << "1. Replay berdasarkan jumlah" << endl;
        cout << "2. Replay berdasarkan menit" << endl;
        cout << "Pilihan: ";

        if (!(cin >> pilihan))
        {
            cout << "Input harus angka! Silahkan coba lagi.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            system("pause");
            system("cls");
            continue;
        }

        if (pilihan >= 1 && pilihan <= 2)
        {
            break;
        }
        else
        {
            cout << "Opsi tidak tersedia! Silahkan coba lagi.\n";
            system("pause");
            system("cls");
        }
    }
    int jumlahputar = 0;
    if (pilihan == 1)
    {
        while (true)
        {
            cout << "Berapa kali replay?";
            if (!(cin >> jumlahputar))
            {
                cout << "Input harus angka! Silahkan coba lagi.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                system("pause");
                system("cls");
                continue;
            }

            if (jumlahputar > 0)
            {
                break;
            }
            else
            {
                cout << "Tidak bisa input kurang dari 0!.\n";
                system("pause");
                system("cls");
            }
        }
        cout << "Memutar lagu...." << endl;
    }
    else
    {
        float targetmenit;
        while (true)
        {
            cout << "Putar selama berapa menit? ";
            if (!(cin >> targetmenit))
            {
                cout << "Input harus angka! Silahkan coba lagi.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                system("pause");
                system("cls");
                continue;
            }
            if (targetmenit > 0)
            {
                break;
            }
            else
            {
                cout << "Tidak bisa input kurang atau sama dengan 0!\n";
                system("pause");
                system("cls");
            }
        }
        jumlahputar = targetmenit / hasil->durasi;
        cout << "Lagu diputar sebanyak " << jumlahputar << " kali" << endl;
    }

    for (int i = 1; i <= jumlahputar; i++)
    {
        cout << i << " " << hasil->judul << " - " << hasil->penyanyi << endl;
        lagu *nodebaru = buatnode(hasil->judul, hasil->penyanyi, hasil->durasi, hasil->tahunterbit);
        nodebaru->kanan = topriwayat;
        topriwayat = nodebaru;
    }
}

void riwayatlagu()
{
    // error handling
    if (topriwayat == NULL)
    {
        cout << "Belum riwayat pemutaran lagu!";
        return;
    }

    lagu *bantu = topriwayat;
    cout << "==== RIWAYAT LAGU 2PLAY ====" << endl;
    cout << endl;
    cout << left << setw(30) << "Judul" << " | "
         << left << setw(25) << "Penyanyi" << " | "
         << left << setw(10) << "Durasi" << " | "
         << left << setw(10) << "Tahun Terbit" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    while (bantu != NULL)
    {
        cout << left << setw(30) << bantu->judul << " | "
             << left << setw(25) << bantu->penyanyi << " | "
             << left << setw(10) << bantu->durasi << " | "
             << left << setw(14) << bantu->tahunterbit << endl;

        bantu = bantu->kanan;
    }
    cout << "-----------------------------------------------------------------------------------------" << endl;
}

lagu *cariahliwaris(lagu *node)
{
    while (node->kiri != NULL)
    {
        node = node->kiri;
    }
    return node;
}

lagu *hapusnode(lagu *node, string targetjudul)
{
    if (node == NULL)
    {
        return node;
    }

    if (targetjudul < node->judul)
    {
        node->kiri = hapusnode(node->kiri, targetjudul);
    }
    else if (targetjudul > node->judul)
    {
        node->kanan = hapusnode(node->kanan, targetjudul);
    }
    else
    {
        if (node->kiri == NULL)
        {
            lagu *temp = node->kanan;
            delete node;
            return temp;
        }
        else if (node->kanan == NULL)
        {
            lagu *temp = node->kiri;
            delete node;
            return temp;
        }
        else
        {
            lagu *temp = cariahliwaris(node->kanan);
            node->judul = temp->judul;
            node->penyanyi = temp->penyanyi;
            node->durasi = temp->durasi;
            node->tahunterbit = temp->tahunterbit;
            node->kanan = hapusnode(node->kanan, temp->judul);
        }
    }
    return node;
}

void hapuslagu()
{
    if (root == NULL)
    {
        cout << "Belum ada lagu! Silahkan tambahkan lagu terlebih dahulu." << endl;
        return;
    }

    string targetjudul;
    cout << "==== HAPUS LAGU 2PLAY ====" << endl;
    cout << "Masukkan judul lagu yang ingin dihapus: " << endl;
    cin >> ws;
    getline(cin, targetjudul);

    lagu *hasil = search(root, targetjudul);

    if (hasil == NULL)
    {
        cout << "Lagu tidak ditemukan!" << endl;
    }
    else
    {
        root = hapusnode(root, targetjudul);
        cout << "Lagu Berhasil dihapus!" << endl;
    }
}

int main()
{
    // variable lokal bes
    int pilihan;

    // menu utama
    do
    {
        while (true)
        {
            cout << "==== 2PLAY =====" << endl;
            cout << "1. Tambah Lagu" << endl;
            cout << "2. Tampilkan Lagu" << endl;
            cout << "3. Cari Lagu" << endl;
            cout << "4. Tambah Lagu ke Playlist" << endl;
            cout << "5. Lihat Playlist" << endl;
            cout << "6. Putar Playlist" << endl;
            cout << "7. Replay Lagu" << endl;
            cout << "8. Riwayat Lagu" << endl;
            cout << "9. Hapus Lagu" << endl;
            cout << "10. Keluar" << endl;
            cout << "Pilihan menu: ";

            if (!(cin >> pilihan))
            {
                cout << "Input harus angka! Silahkan coba lagi.\n";
                cin.clear();
                cin.ignore(1000, '\n');
                system("pause");
                system("cls");
                continue;
            }

            if (pilihan >= 1 && pilihan <= 10)
            {
                break;
            }
            else
            {
                cout << "Opsi tidak tersedia! Silahkan coba lagi.\n";
                system("pause");
                system("cls");
            }
        }

        switch (pilihan)
        {
        case 1:
            do
            {
                tambahlagu();
            } while (yesorno(""));
            break;
        case 2:
            do
            {
                tampilkanlagu();
            } while (yesorno(""));
            break;
        case 3:
            do
            {
                carilagu();
            } while (yesorno(""));
            break;
        case 4:
            do
            {
                tambahkeplaylist();
            } while (yesorno(""));
            break;
        case 5:
            do
            {
                lihatplaylist();
            } while (yesorno(""));
            break;
        case 6:
            do
            {
                putarplaylist();
            } while (yesorno(""));
            break;
        case 7:
            do
            {
                replaylagu();
            } while (yesorno(""));
            break;
        case 8:
            do
            {
                riwayatlagu();
            } while (yesorno(""));
            break;
        case 9:
            do
            {
                hapuslagu();
            } while (yesorno(""));
            break;
        }
    } while (pilihan != 10);
    cout << "Terima kasih telah menggunakan program" << endl;
    system("pause");
    system("cls");
    return 0;
}