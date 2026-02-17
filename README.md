# Tucil 1 - Queens Game Solver

## Penjelasan Singkat
Program ini adalah aplikasi GUI untuk menyelesaikan permainan **Queens**. Program ini dibangun menggunakan bahasa C++ dan library grafis **Raylib**.

Program memiliki kemampuan untuk mencari solusi penempatan bidak Ratu menggunakan dua algoritma:
1.  **Brute Force:** Mencoba semua kemungkinan kombinasi penempatan (Exhaustive Search).
2.  **Backtracking:** Mencoba penempatan secara rekursif dengan pemangkasan (pruning) ketika solusi tidak valid ditemukan.

## Requirements
Untuk mengkompilasi dan menjalankan program ini, dibutuhkan:
* **Compiler C++:** MinGW-w64 (mendukung C++17) atau GCC.
* **Build Tool:** CMake (Minimal versi 3.10).
* **Library:** Raylib (sudah disertakan dalam folder `lib/` dan `include/`, tidak perlu instalasi global).
* **OS:** Windows atau Linux.

## Cara Mengkompilasi (Build)
Pastikan Anda berada di direktori utama (root) proyek, lalu jalankan perintah berikut di terminal:

```bash
# 1. Buat direktori build
mkdir build
cd build

# 2. Konfigurasi CMake
cmake -G "MinGW Makefiles" ..

# 3. Compile Project
cmake --build .
```

## Cara Menjalankan Program
Dari folder root proyek, jalankan:
```bash
./bin/solver.exe
```

## Panduan Penggunaan
1. Load input file: klik tombol "Load Input File" dan pilih file .txt berisi persoalan.
2. Pilih algoritma:
    * Klik "Solve (Backtrack)" untuk penyelesaian menggunakan algoritma backtrack.
    * Klik "Solve (BruteForce)" untuk penyelesaian menggunakan algoritma naif.
3. Simpan Proses: Centang "Save Process?" sebelum menekan tombol solve jika ingin menyimpan log langkah-langkah pencarian solusi ke dalam file teks.
4. Simpan solusi: Jika solusi ditemukan, klik "Save Final Result" untuk menyimpan grid jawaban ke file teks.

## Author
* Nama: An-Dafa Anza Avansyah
* NIM: 13524038