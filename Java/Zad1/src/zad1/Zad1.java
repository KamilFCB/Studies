/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad1;

/**
 *
 * @author Kamil
 */
public class Zad1 {
    
    private static String[] rzymskie = {
    "M", "CM", "D", "CD", "C","XC", "L", "XL", "X", "IX", "V", "IV", "I"
    };
    private static int[] arabskie = {
    1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
    };
    
    /**
     * @param args the command line arguments
     */
    
    public static void main(String[] args)
    {
        for(int i=0; i<args.length; i++)
        {
            int liczba = new Integer(args[i]);
            if(liczba <= 0 || liczba >= 5000)
                throw new IllegalArgumentException("liczba " + liczba + " spoza zakresu 1-4999");
            System.out.println(args[i] + " " + naRzymskie(liczba));
        }
        
    }
    
    private static String naRzymskie(int liczba)
    {
        String wynik = new String();
        int j=0;
        while(liczba > 0)
        {
            if(liczba - arabskie[j] >= 0)
            {
                wynik += rzymskie[j];
                liczba -= arabskie[j];
                j=0;
            }
            else
                j++;
        }
        
        return wynik;
    }
    
}