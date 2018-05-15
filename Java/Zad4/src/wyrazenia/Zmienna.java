/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wyrazenia;

/**
 *
 * @author Kamil
 */

/** Zbiór zmiennych */
public class Zmienna extends Wyrazenie
{
    /** Zbiór zmiennych */
    protected static final Zbior val;
    private String zmienne = "";
    private int licz_oblicz = 0;
    private int licz_tostring = 0;
    
    static {
        val = new Zbior();
    }
    
    /** Dodaje nową zmienną do zbioru i przypisuje wartość -1.618 */
    public Zmienna(String key)
    {
        val.ustal(new Para(key, 1.618));
        zmienne += key;
    }
    
    /* Zwraca wartość zmiennej */
    public double oblicz()
    {
        String x = zmienne.substring(licz_oblicz, licz_oblicz+1);
        licz_oblicz++;
        return val.czytaj(x);
    }  
    
    public String toString()
    {
        licz_tostring++;
        return zmienne.substring(licz_tostring-1, licz_tostring);
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Zbior tmp = (Zbior)obj;
        
        if(val.ile() != tmp.ile())
            return false;
        
        return val.equals(tmp);
    }
}
