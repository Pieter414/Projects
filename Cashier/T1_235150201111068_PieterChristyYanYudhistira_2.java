/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package t1_235150201111068_pieterchristyyanyudhistira_2;

import java.util.Scanner;
import java.time.LocalDate;
import java.util.Locale;
import java.text.NumberFormat;

/**
 Nama 1 : Pieter Christy Yan Yudhistira 1 (235150201111068) 
 Nama 2 : Kaneysha Nadetta Julief       2 (235150200111067)
 Nama 3 : Christopher Robin Tanugroho   3 (235150201111067)

Tanggung jawab 1: mengerjakan soal nomor 1, membuat program Java yang tertera di source code, mendebug kesalahan argumen substring untuk mendapatkan jam dan menitnya, membuat substring function tersendiri di flowgorithm, mengecek kembali format pseudocode nomor 1, dan membuat pembahasan source code bersama tanggung jawab 2.
Tanggung jawab 2: mengerjakan soal nomor 1, membuat flowchart di flowgorithm, membuat pseudocode mengikuti flowchart, dan membuat pembahasan source code bersama tanggung jawab 1.
Tanggung jawab 3:mengerjakan soal nomor 2, membuat program Java yang tertera di source code, mengimplementasikan format output dengan NumberFormat dan LocalDate untuk output program dan membuat pembahasan source code nomor 2..

**/
public class T1_235150201111068_PieterChristyYanYudhistira_2 {
    public static void main(String[] args) {
        // TODO code application logic here
        Scanner input = new Scanner (System.in);
        String ID, name;
        char x = '|';
        double meal, beverage, dessert, payment, qty, qty1, qty2, sub, sub1, sub2;
        double total, change;
        System.out.print("Customer ID \t: ");
        ID = input.nextLine();
        System.out.print("Customer Name \t: ");
        name = input.nextLine();
        System.out.println("Order Price: ");
        System.out.print("Meal, Qty \t: ");
        meal = input.nextDouble();
        qty = input.nextDouble();
        System.out.print("Beverage, Qty \t: ");
        beverage = input.nextDouble();
        qty1 = input.nextDouble();
        System.out.print("Dessert, Qty \t: ");
        dessert = input.nextDouble();
        qty2 = input.nextDouble();
        System.out.print("Payment Money \t: ");
        payment = input.nextDouble();
        System.out.println("");
        
        sub = meal * qty;
        sub1 = beverage * qty1;
        sub2 = dessert * qty2;
        total = sub + sub1 + sub2;
        change = payment - total;
        
        NumberFormat a = NumberFormat.getNumberInstance (Locale.GERMANY);
        NumberFormat b = NumberFormat.getNumberInstance (Locale.GERMANY);
        NumberFormat c = NumberFormat.getNumberInstance (Locale.GERMANY);
        NumberFormat d = NumberFormat.getNumberInstance (Locale.GERMANY);
        NumberFormat e = NumberFormat.getNumberInstance (Locale.GERMANY);
        NumberFormat f = NumberFormat.getNumberInstance (Locale.GERMANY);
        NumberFormat g = NumberFormat.getNumberInstance (Locale.GERMANY);
        NumberFormat h = NumberFormat.getNumberInstance (Locale.GERMANY);
        NumberFormat i = NumberFormat.getNumberInstance (Locale.GERMANY);
        
        String aa = a.format(meal);
        String bb = b.format(beverage);
        String cc = c.format(dessert);
        String dd = d.format (payment);
        String ee = e.format(sub);
        String ff = f.format(sub1);
        String gg = g.format(sub2);
        String hh = h.format(total);
        String ii = i.format(change);
        
        LocalDate today = LocalDate.now();
        System.out.println("<<Printing Invoice>>\n");
        System.out.println("Customer ID \t: " + ID);
        System.out.println("Customer Name \t: " + name);   
        System.out.println("Date \t\t: " + today );
        System.out.println("");
        System.out.printf("%-9s %c %-12s %c %-8s %c %s\n","Menu", x,"Price", x, "Qty", x, "SubTotal");
        System.out.println("===============================================");
        System.out.printf("%-9s %c %13s %c %7.0f %c %9s\n", "Meal", x ,  aa, x, qty, x, ee);
        System.out.printf("%-9s %c %13s %c %7.0f %c %9s\n", "Beverage", x, bb, x, qty1, x,  ff);
        System.out.printf("%-9s %c %13s %c %7.0f %c %9s\n", "Dessert", x,  cc, x,qty2, x, gg);
           
        System.out.println("===============================================");
        System.out.printf("%32s %4c %9s\n", "Total", x, hh);
        System.out.printf("%34s %2c %9s\n", "Payment", x, dd);
        System.out.println("===============================================");
        System.out.printf("%33s %3c %9s\n", "Change", x, ii);
        input.close();
    }
}
