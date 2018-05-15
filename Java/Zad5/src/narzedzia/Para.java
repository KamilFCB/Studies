/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package narzedzia;

/**
 *
 * @author Kamil
 */

/** Klasa Para klucz(string)-wartosc(double) */
public class Para 
{
    /** Identyfikator pary */
    public final String klucz;
    private double wartosc;
    
    /** Utworzenie pary (klucz, wartosc) */
    public Para(String key, double val)
    {
        klucz = key;
        wartosc = val;
    }
    
    /** zwraca wartość przypisaną do klucza */
    public double get()
    {
        return wartosc;
        
    }
    
    /** ustala wartość klucza, jako argument podajemy wartość którą chcemy przypisać */
    public void set(double val)
    {
        wartosc = val;
    }
    
    
    @Override
    public String toString()
    {
        return klucz + " : " + wartosc;
    }
    
    @Override
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Para tmp = (Para)obj;
        
        return klucz.equals(tmp.klucz);
        
    }
}
