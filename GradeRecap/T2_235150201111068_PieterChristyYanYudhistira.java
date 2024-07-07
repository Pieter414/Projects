/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package t2_235150201111068_pieterchristyyanyudhistira;

import java.util.Scanner;

public class T2_235150201111068_PieterChristyYanYudhistira {
    final static int MAX_SISWA = 10;
    final static int MAX_MATPEL = 10;
    final static int MAX_SEMESTER = 2;
    /* menyimpan nama siswa */
    static String[] siswa = new String[MAX_SISWA];
    /* menyimpan nama matpel per siswa tiap semester, semester ganjil=0, genap=1 */ 
    static String[][][] siswaMatpel = new String[MAX_SISWA][MAX_SEMESTER][MAX_MATPEL];
    /* menyimpan nilai matpel per siswa tiap semester, semester ganjil=0, genap=1 */
    static double[][][] siswaMatpelNilai = new double[MAX_SISWA][MAX_SEMESTER][MAX_MATPEL]; 
    /* menyimpan banyak siswa */
    static int banyakSiswa = 0;
    /* menyimpan banyak matpel */
    static int banyakSiswaMatpel = 0;
    
    public static String konversiNilai(double nilai){
        /* Konversi nilai sesuai tabel */
        if (nilai <= 100 && nilai > 80) return "A";
        else if (nilai <= 80 && nilai > 75) return "B+";
        else if (nilai <= 75 && nilai > 69) return "B";
        else if (nilai <= 69 && nilai > 65) return "C+";
        else if (nilai <= 65 && nilai > 59) return "C";
        else if (nilai <= 59 && nilai > 55) return "D+";
        else if (nilai <= 55 && nilai > 40) return "D";
        else return "E";
    }
    
    public static void tambahSiswa(String nama){
        // Pieter
        /* Mengecek apakah nama siswa yang diinput sudah terdapat dalam array siswa */
        for (int i = 0; i < MAX_SISWA; i++){
            /* Jika ada yang sama, maka return tanpa menyimpan */
            if (nama.equalsIgnoreCase(siswa[i])) return;
        }
        // Menyimpan nama siswa kedalam array siswa
        siswa[banyakSiswa] = nama;
        banyakSiswa++;
    }

    public static void tambahMatpel(String matpel){
        // bin
        // Mengecek apakah matpel yang diinput sudah terdapat dalam array matpel
        for (int i = 0; i < MAX_SISWA; i++){
            for (int j = 0; j < MAX_SEMESTER; j++){
                for (int k = 0; k < MAX_MATPEL; k++){
                    // Jika ada yang sama, maka return tanpa menyimpan
                    if (matpel.equalsIgnoreCase(siswaMatpel[i][j][k])) return;
                }
            }
        }
        // Menyimpan semua mata kuliah di data semua siswa
        for (int i = 0; i < MAX_SISWA; i++){
            for (int j = 0; j < MAX_SEMESTER; j++){
                siswaMatpel[i][j][banyakSiswaMatpel] = matpel;
            }
        }
        banyakSiswaMatpel++;
    }
    
    public static int cariSiswa(String nama){
        // Jika nama siswa ditemukan dalam array siswa, return indeksnya
        for (int i = 0; i < banyakSiswa; i++){
            if (nama.equalsIgnoreCase(siswa[i])) return i;
        }
        // Jika tidak ditemukan, return -1 menandakan invalid
        return -1;
    }

    public static int cariMatpel(String matpel){
        // bin
        // Jika nama matpel ditemukan dalam array siswaMatpel, return indeksnya
        for (int i = 0; i < banyakSiswaMatpel; i++){
            if (matpel.equalsIgnoreCase(siswaMatpel[0][0][i]) && matpel.equalsIgnoreCase(siswaMatpel[0][1][i])) return i;
        }
        // Jika tidak ditemukan, return -1 menandakan invalid
        return -1;
    }
    
    /*
    nama: nama siswa
    semester: semester, 0 untuk ganjil, 1 untuk genap
    matpel: nama matpel
    nilai: nilai matpel tiap semester
    */
    public static void isiDataSiswa(String nama, int semester, String matpel, int nilai){
        int cariDataSiswa, cariDataMatpel;
        // Mencari data siswa dan matpel
        cariDataSiswa = cariSiswa(nama);
        cariDataMatpel = cariMatpel(matpel);
        // Jika hasil method cari siswa atau matpel invalid, maka program keluar
        if (cariDataSiswa == -1 || cariDataMatpel == -1) return;
        siswaMatpelNilai[cariDataSiswa][semester][cariDataMatpel] = nilai;
    }
    
    public static void printSiswa(){
        System.out.print("SISWA:");
        for (int i = 0; i < banyakSiswa; i++) System.out.print(" "+siswa[i]);
        System.out.println();
    }
    
    public static void printMatpel(){
        System.out.print("MATA PELAJARAN:");
        for (int i = 0; i < banyakSiswaMatpel; i++)System.out.print(" "+siswaMatpel[0][0][i]);
        System.out.println();
    }
    
    public static void printRaportSiswa(String nama){
        int indeksSiswa = cariSiswa(nama);
        if (indeksSiswa == -1) return;
        
        System.out.println(">> BEGIN RAPORT <<\n");
        System.out.println("Nama: "+siswa[indeksSiswa]);
        for (int i = 0; i < MAX_SEMESTER; i++){
            if (i == 0) System.out.println("Semester: Ganjil");
            else System.out.println("Semester: Genap");
            
            System.out.printf("%-20s|%10s|%14s\n", "Mata Pelajaran", "Nilai", "Nilai Huruf");
            System.out.println("-----------------------------------------------");
            for (int j = 0; j < banyakSiswaMatpel; j++){
                double nilaiSiswa = siswaMatpelNilai[indeksSiswa][i][j];
                System.out.printf("%-20s|%10.1f|%15s\n", siswaMatpel[indeksSiswa][i][j], nilaiSiswa, konversiNilai(nilaiSiswa));
            }
            System.out.println();
        }
        System.out.println(">> END RAPORT <<");
    }
    
    public static int cariJuara(int semester){
        double nilaiJuara = Integer.MIN_VALUE, average;
        int indeksJuara = -1;
        for (int i = 0; i < banyakSiswa; i++){
            double sum = 0;
            for (int j = 0; j < banyakSiswaMatpel; j++){
                sum += siswaMatpelNilai[i][semester][j];
            }
            average = sum / banyakSiswaMatpel;
            nilaiJuara = Math.max(nilaiJuara, average);
            if (nilaiJuara == average) indeksJuara = i;
        }
        return indeksJuara;
    }
    
    public static void hitungNilai(int semester){
        String nilaiHuruf;
        String[] huruf = {"A", "B+", "B", "C+", "C", "D+", "D", "E"};
        int[] totalNilai = new int[8];
        for (int i = 0; i < banyakSiswa; i++){
            for (int j = 0; j < banyakSiswaMatpel; j++){
                nilaiHuruf = konversiNilai(siswaMatpelNilai[i][semester][j]);
                switch(nilaiHuruf){
                    case "A":
                        totalNilai[0]++;
                        break;
                    case "B+":
                        totalNilai[1]++;
                        break;
                    case "B":
                        totalNilai[2]++;
                        break;
                    case "C+":
                        totalNilai[3]++;
                        break;
                    case "C":
                        totalNilai[4]++;
                        break;
                    case "D+":
                        totalNilai[5]++;
                        break;
                    case "D":
                        totalNilai[6]++;
                        break;
                    case "E":
                        totalNilai[7]++;
                        break;
                }
            }
            System.out.print(siswa[i]);
            for (int k = 0; k < totalNilai.length; k++){
                if (totalNilai[k] != 0) System.out.printf(" %s:%d", huruf[k], totalNilai[k]);
                totalNilai[k] = 0;
            }
            System.out.println();
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String perintah, dataSiswa, dataMatpel, dataSemester;
        int semester, dataNilai;
        
        while(sc.hasNext()){
            perintah = sc.next().toUpperCase();
            if (perintah.equals("SISWA")){
                dataSiswa = sc.next();
                // Mengecek apakah data siswa sudah penuH
                if (banyakSiswaMatpel >= MAX_MATPEL) System.out.println("Maaf, data siswa sudah penuh");
                else tambahSiswa(dataSiswa);
            }
            else if (perintah.equals("PRINT_SISWA")){
                printSiswa();
            }
            else if (perintah.equals("MATPEL")){
                // Mengecek apakah data siswa sudah penuh
                dataMatpel = sc.next();
                if (banyakSiswaMatpel >= MAX_MATPEL){
                    System.out.println("Maaf, data matpel siswa sudah penuh");
                }
                else{
                    
                    tambahMatpel(dataMatpel);
                }
            }
            else if (perintah.equals("PRINT_MATPEL")){
                printMatpel();
            }
            else if (perintah.equals("NILAI")){
                dataSiswa = sc.next();
                dataSemester = sc.next();
                dataMatpel = sc.next();
                dataNilai = sc.nextInt();
                // Mengkonversi data semester menjadi semester ganjil = 0, genap = 1, tidak valid = -1
                semester = (dataSemester.equalsIgnoreCase("GANJIL")) ? 0 : (dataSemester.equalsIgnoreCase("GENAP")) ? 1 : -1;
                // Jika data semester tidak valid, maka program akan keluar
                if (semester == -1) continue;
                isiDataSiswa(dataSiswa, semester, dataMatpel, dataNilai);
            }
            else if (perintah.equals("PRINT_RAPORT")){
                dataSiswa = sc.next();
                printRaportSiswa(dataSiswa);
            }
            else if (perintah.equals("CARI_JUARA")){
                dataSemester = sc.next();
                semester = (dataSemester.equalsIgnoreCase("GANJIL")) ? 0 : (dataSemester.equalsIgnoreCase("GENAP")) ? 1 : -1;
                if (semester == -1) continue;
                int indeksJuara = cariJuara(semester);
                System.out.println("JUARA_1 "+dataSemester.toUpperCase()+" "+siswa[indeksJuara]);
            }
            else if (perintah.equals("HITUNG_NILAI")){
                dataSemester = sc.next();
                semester = (dataSemester.equalsIgnoreCase("GANJIL")) ? 0 : (dataSemester.equalsIgnoreCase("GENAP")) ? 1 : -1;
                if (semester == -1) continue;
                hitungNilai(semester);
            } 
            else{
                System.exit(0);
            }
        }
    }
}
