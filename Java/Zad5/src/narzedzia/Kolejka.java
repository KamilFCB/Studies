/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package narzedzia;

import zad5.Symbol;

/**
 *
 * @author Kamil
 */

/** Kolejka dwukierunkowa */
public class Kolejka extends Lista
{
    /* *Dodanie wartosci Symbol do kolejki */
    public void wstaw(Symbol val)
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
    
    /** Wypisanie kolejki */
    @Override
    public void wypisz()
    {
        Wezel tmp = poczatek;
        while(tmp!=null)
        {
            //Symbol s = tmp.getWartosc();
            
            //System.out.println(s.obliczWartosc());
            tmp = tmp.getNastepny();
        }
    }
    
    /** Pobiera i usuwa pierwszy element z kolejki */
    public Symbol pobierz()
    {
        if(poczatek != koniec)
        {
            (poczatek.getNastepny()).setPoprzedni(null);
            Wezel tmp = poczatek;
            poczatek = poczatek.getNastepny();
            return (Symbol)tmp.getWartosc();
        }
        else
        {
            Wezel tmp = poczatek;
            poczatek = null;
            koniec = null;
            return (Symbol)tmp.getWartosc();
        }
    }
}
