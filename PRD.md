# Product Requirements Document (PRD)

## Nama Produk

LexiBuild (Aplikasi Kamus dan Perangkai Kalimat Interaktif)

## Bahasa Pemrograman

C

## Mata Kuliah

Struktur Data dan Algoritma

## 1. Ringkasan Eksekutif

LexiBuild adalah aplikasi berbasis Command Line Interface (CLI) yang memiliki fungsi ganda: sebagai kamus pintar (pencari kosakata dan sinonim) serta sebagai ruang kerja interaktif untuk merangkai kalimat.

Aplikasi ini mendemonstrasikan integrasi dua struktur data utama:

- Binary Search Tree (BST): Digunakan sebagai pangkalan data utama di dalam memori untuk pencarian string yang efisien (secara lexicographic).
- Queue (Antrean): Berbasis Linked List, digunakan secara eksklusif pada fitur perangkai kalimat untuk menjaga urutan kata secara First-In First-Out (FIFO).

## 2. Tim Pengembang & Tanggung Jawab

Proyek ini dikembangkan oleh 2 orang menggunakan pendekatan Divide and Conquer untuk memastikan efisiensi dan mencegah conflict pada kode.

### 👨‍💻 Danang (Backend & Data Specialist)

Fokus: Mengelola struktur data di memori, file I/O, dan algoritma penelusuran (Tree).

- Tugas 1 (Modifikasi ADT): Mengubah tipe infotype pada ADT Tree dan Queue menjadi format string (char[50]). Menambahkan struktur array sinonim berkapasitas 5 elemen di dalam ElmtNode BST.
- Tugas 2 (File Parser): Membuat prosedur LoadKamus untuk membaca file eksternal kamus.txt (menggunakan fopen, fgets, strtok) dan menyisipkannya ke dalam BST.
- Tugas 3 (Algoritma Auto-complete): Membuat fungsi SearchPrefix dengan metode Tree Traversal (seperti Inorder) yang memanfaatkan strncmp untuk mencocokkan 3 huruf awalan.
- Tugas 4 (Algoritma Exact Match): Membuat fungsi CariSinonim menggunakan strcmp untuk menemukan alamat node spesifik pada BST agar data sinonimnya dapat ditarik.

### 👨‍🎨 Rafi (Logic Integrator & UI Specialist)

Fokus: Merancang antarmuka CLI, mengatur alur menu utama (main.c), dan manipulasi Queue.

- Tugas 1 (Kerangka UI Utama): Membangun kerangka main.c dengan do-while dan switch-case untuk menampilkan 3 menu utama.
- Tugas 2 (Integrasi Menu 1 & 2): Menyambungkan input pengguna ke modul pencarian buatan Danang untuk menampilkan hasil auto-complete dan sinonim murni (tanpa manipulasi Queue).
- Tugas 3 (Ruang Kerja / Menu 3): Membuat sub-menu interaktif di mana pengguna dapat mencari kata/sinonim, memilih kata menggunakan nomor urut, lalu memanggil fungsi Insert untuk menyimpannya ke antrean.
- Tugas 4 (Eksekusi Kalimat): Membangun logika penyelesaian di Menu 3: mengecek !IsEmpty(Q), lalu melakukan iterasi Delete sembari mencetak (print) data tersebut hingga antrean kosong dan membentuk kalimat utuh.

## 3. Spesifikasi Teknis & Batasan (Constraints)

- Sumber Data: File teks eksternal (kamus.txt).
- Format File: kata_utama,sinonim1,sinonim2 (dipisahkan oleh koma per baris).
- Batas Tampilan: Maksimal 10 kata yang ditampilkan per pencarian agar layar CLI tidak perlu di-scroll (One-Screen Rule).
- Pemicu Auto-complete: Pengguna diwajibkan mengetikkan minimal 3 huruf awalan agar saran kata muncul (mencegah output yang terlalu luas).

## 4. Arsitektur Menu Utama

Aplikasi dirancang dengan 3 menu independen yang saling melengkapi:

### [Menu 1] Kamus Pintar (Auto-complete)

Berfungsi sebagai sarana eksplorasi kata.

Alur: Pengguna input prefix -> Program memvalidasi jumlah karakter (>= 3) -> Program memanggil fungsi SearchPrefix -> Ditampilkan maksimal 10 saran kata alfabetis -> Kembali ke Menu Utama. (Tidak menyentuh Queue).

### [Menu 2] Thesaurus (Cari Sinonim)

Berfungsi untuk mencari persamaan kata spesifik.

Alur: Pengguna input kata utuh -> Program memanggil fungsi CariSinonim -> Jika node ditemukan, tampilkan isi array sinonim -> Kembali ke Menu Utama. (Tidak menyentuh Queue).

### [Menu 3] Ruang Kerja (Buat Kalimat)

Berfungsi sebagai alat bantu menyusun kata demi kata menggunakan fasilitas dari Menu 1 dan Menu 2.

Alur: Pengguna masuk ke Menu 3 -> Ditawarkan opsi "Cari Awalan Kata", "Cari Sinonim", atau "Selesai".

Jika memilih kata, program akan mengeksekusi Insert(&Q, kata_terpilih).

Jika pengguna menekan "Selesai", program akan melakukan perulangan pengosongan antrean melalui fungsi Delete dan merangkainya menjadi satu kalimat yang dicetak di layar.

## 5. Timeline & Milestones

- Fase Infrastruktur: Penyesuaian infotype pada seluruh file header (.h) dan pembuatan UI mockup sederhana di main.c.
- Fase Integrasi Data: Penyelesaian modul LoadKamus untuk memastikan file teks bisa membentuk Binary Search Tree yang utuh.
- Fase Mesin Pencari: Pembuatan dan pengujian fungsi pencarian prefix dan persamaan kata menggunakan string matching.
- Fase Integrasi Logika: Pemasangan mesin pencari ke dalam main.c serta penyempurnaan alur Insert dan Delete pada Menu 3.
- Fase Finalisasi & QA: Pengujian menyeluruh (stress test input) untuk memastikan program tidak crash
