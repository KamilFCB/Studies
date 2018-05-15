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

/** Lista dwukierunkowa */
public class Lista<T> {
    /** Poczatek listy */
    public Wezel poczatek;
    /** Koniec listy*/
    public Wezel koniec;
    
    /** Utworzenie pustej listy */
    public Lista()
    {
        poczatek = null;
        koniec = null;
    }
    
    /** Wstawienie elemntu na koniec listy */
    public void wstaw(T val)
    {
        Wezel nowy = new Wezel(val, null, null);
        if(czyPusta())
        {
            poczatek = nowy;
            koniec = nowy;
        }
        else
        {
            nowy.setPoprzedni(koniec);
            koniec.setNastepny(nowy);
            koniec = nowy;
        }
    }
    
    /** Usuniecie elementu z listy */
    public void usun(String n)
    {
        Wezel tmp = poczatek;
        Para p = new Para(n, 0);
        while(tmp!=null)
        {
            if(tmp.getWartosc().equals(p))
            {
                if(tmp == poczatek)
                {
                    poczatek = tmp.getNastepny();
                    return;
                }
                if(tmp == koniec)
                {
                    koniec = koniec.getPoprzedni();
                    koniec.setNastepny(null);
                    return;
                }
                
                (tmp.getPoprzedni()).setNastepny(tmp.getNastepny());
                (tmp.getNastepny()).setPoprzedni(tmp.getPoprzedni());
                return;                
            }
            tmp = tmp.getNastepny();
        }
        if(tmp == null)
            System.out.println("Nie ma takiej zmiennej");
        // wyjatek?
    }
    
    /** Czyszczenie listy */
    public void wyczysc()
    {
        poczatek = null;
        koniec = null;
    }
    
    /** Wypisanie listy */
    public void wypisz()
    {
        Wezel tmp = poczatek;
        while(tmp!=null)
        {
            System.out.println(tmp.getWartosc().toString());
            tmp = tmp.getNastepny();
        }
    }
    
    /** Sprawdzenie czy lista jest pusta */
    public boolean czyPusta()
    {
        return poczatek == null;
    }
    
    /** Sprawdzenie rozmiaru listy */
    public int rozmiar()
    {
        Wezel tmp = poczatek;
        int i=0;
        for(; tmp != null; i++)
            tmp = tmp.getNastepny();
        
        return i;
    }
    
}
