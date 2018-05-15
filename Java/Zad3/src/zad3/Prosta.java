/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad3;

import geometria.*;

/**
 *
 * @author Kamil
 */
public class Prosta 
{
    public final double a, b, c;
    
    public Prosta(double x, double y, double z)
    {
        a=x;
        b=y;
        c=z;
    }
    
    public static Prosta przesun(Prosta p, Wektor w)
    {
        double a = p.a;
        double b = p.b;
        double c = (p.c + a * (-1 * w.dx) + b * (-1 * w.dy));
        
        Prosta res = new Prosta(a, b, c);
        return res;
    }
    
    public static boolean czy_rownolegle(Prosta p1, Prosta p2)
    {
        double a1 = (-1 * p1.a) / p1.b;
        double a2 = (-1 * p2.a) / p2.b;
        
        return a1 == a2;
    }
    
    public static boolean czy_prostopadle(Prosta p1, Prosta p2)
    {
        double a1 = (-1 * p1.a) / p1.b;
        double a2 = (-1 * p2.a) / p2.b;
        
        Math.pow(a2, -1);
        a2 *= -1;
        
        return a1 == a2;
    }
    
    public static Punkt pkt_przeciecia(Prosta p1, Prosta p2)
    {
        if(czy_rownolegle(p1, p2))
            throw new IllegalArgumentException("Proste nie przecinają się");
        else
        {
            double a1 = (-1 * p1.a) / p1.b;
            double b1 = (-1 * p1.c) / p1.b;
            double a2 = (-1 * p2.a) / p2.b;
            double b2 = (-1 * p2.c) / p2.b;
            
            double x = (b1 - b2) / (a2 - a1);
            double y = a2 * x + b2;
            
            Punkt wynik = new Punkt(x, y);
            
            return wynik;
        }
    }
    
    public String toString()
    {
        return a + "x + " + b + "y + " + c + " = 0";
    }
}
