/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;

import grafika.Kreska;

/**
 *
 * @author Kamil
 */
public class Lista 
{
    public Wezel poczatek, koniec;
    
    public Lista()
    {
        poczatek = null;
        koniec = null;
    }
    
    public void wstaw(Kreska val)
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
    
    public void usun_pierwszy()
    {
        if(poczatek == koniec)
        {
            poczatek = null;
            koniec = null;
            return;
        }
        Wezel tmp = poczatek.getNastepny();
        tmp.setPoprzedni(null);
        poczatek = tmp;
    }
    
    public void usun_ostatni()
    {
        if(poczatek == koniec)
        {
            poczatek = null;
            koniec = null;
            return;
        }
        Wezel tmp = koniec.getPoprzedni();
        tmp.setNastepny(null);
        koniec = tmp;
    }
    
    public boolean czyPusta()
    {
        return poczatek == null;
    }
    
    public void wyczysc()
    {
        poczatek = null;
        koniec = null;
    }
}
