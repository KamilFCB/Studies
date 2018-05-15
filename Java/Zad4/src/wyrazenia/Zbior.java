/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wyrazenia;

import static wyrazenia.Zmienna.val;

/**
 *
 * @author Kamil
 */

/** Zbiór par klucz-wartość */
public class Zbior 
{
    /**
     * Tablica przechowująca obiekty klasy Para
     */
    private Para[] zbior;
    
    /** Tworzy tablice 20 obiektów klasy Para */
    public Zbior()
    {
        zbior = new Para[20];
    }
    /** Tworzy tablice obiektów klasy Para o podanej wielkości */
    public Zbior(int size)
    {
        zbior = new Para[size];
    }
    
    
    /** metoda szuka pary z określonym kluczem */
    public Para szukaj (String kl) throws IllegalArgumentException
    {
        for(int i=0; zbior[i] != null; i++)
        {
            if(zbior[i].klucz.equals(kl))
                return zbior[i];
        }
        
        throw new IllegalArgumentException("Nie ma takiego klucza");  
    }
    
    /** metoda wstawia do zbioru nową parę */
    public void wstaw (Para p) throws IllegalArgumentException
    {
        int i=0;
        for(; zbior[i] != null; i++)
        {}
        
        zbior[i] = new Para(p.klucz, p.get());
    }
    
    /** metoda odszukuje parę i zwraca wartość związaną z kluczem */
    public double czytaj (String kl) throws IllegalArgumentException
    {
        Para tmp;
        try
        {
            tmp = this.szukaj(kl);
        }
        catch(IllegalArgumentException e)
        {
            throw new IllegalArgumentException("Brak klucza o podanej wartości");
        }
            return tmp.get();
    }
    
    /** metoda wstawia do zbioru nową albo aktualizuje istniejącą parę */
    public void ustal (Para p) throws IllegalArgumentException
    {
        int i=0;
        for(; zbior[i] != null; i++)
        {
            if(zbior[i].klucz.equals(p.klucz))
            {
                zbior[i].set(p.get());
                return;
            }
        }
        
        zbior[i] = new Para(p.klucz, p.get());
    }
    
    /** metoda podaje ile par jest przechowywanych w zbiorze */
    public int ile ()
    {
        int ile=0;
        
        for(int i=0; i<zbior.length; i++)
        {
            if(zbior[i] != null)
                ile++;
        }
        
        return ile;
    }
    
    /** metoda usuwa wszystkie pary ze zbioru */
    public void czysc ()
    {
        for(int i=0; i<zbior.length; i++)
            zbior[i] = null;       
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Zbior tmp = (Zbior)obj;
        
        if(zbior.length != tmp.ile())
            return false;
        
        for(int i=0; i<val.ile(); i++)
        {
            if(!(zbior[i].klucz.equals(tmp.zbior[i].klucz)))
                return false;
        }
        
        return true;
    }
}
