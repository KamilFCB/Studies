/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;
import java.awt.*;
/**
 *
 * @author Kamil
 */
public class Kreska 
{
    protected Point poczatek, koniec;
    public Color kolor;
    
    public Kreska(Point pocz, Point kon, Color kol)
    {
        poczatek = pocz;
        koniec = kon;
        kolor = kol;
    }
    
    public Kreska()
    {
        poczatek = null;
        koniec = null;
        kolor = null;
    }
    
    public void setPoczatek(Point p)
    {
        poczatek = p;
    }
    
    public void setKoniec(Point p)
    {
        koniec = p;
    }
    
    public void setKolor(Color k)
    {
        kolor = k;
    }
    
    public Point getPoczatek()
    {
        return poczatek;
    }
    
    public Point getKoniec()
    {
        return koniec;
    }
    
    public Color getKolor()
    {
        return kolor;
    }
    
}
