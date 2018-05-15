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

/** Stos dwukierunkowy */
public class Stos extends Lista
{
    /** Wstawienie elementu na gore stosu */
    public void wstaw(double val)
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
    
    /** Wypisanie stosu */
    @Override
    public void wypisz()
    {
        Wezel tmp = koniec;
        while(tmp!=null)
        {            
            System.out.println(tmp.getWartosc());
            tmp = tmp.getPoprzedni();
        }
    }
    
    /** Pobranie i usuniecie elemntu z gory stosu*/
    public double pobierz() throws WyjatekONP
    {
        
        if(poczatek == koniec)
        {
            if(poczatek == null)
                throw new ONP_PustyStos("Brak elementow na stosie");
            Wezel tmp = koniec;
            poczatek = null;
            koniec = null;
            return (double)tmp.getWartosc();
        }
        else
        {
            (koniec.getPoprzedni()).setNastepny(null);
            Wezel tmp = koniec;
            koniec = koniec.getPoprzedni();
            return (double)tmp.getWartosc();
        }
    }
}
