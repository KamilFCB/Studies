/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package geometria;

import zad3.Wektor;
import zad3.Prosta;

/**
 *
 * @author Kamil
 */
public class Punkt 
{
    protected double x, y;
    
    public Punkt(double a, double b)
    {
        x = a;
        y = b;
    }
    
    public void przesun(Wektor v)
    {
        x += v.dx;
        y += v.dy;
    }
    
    public void obroc(Punkt p, double kat)
    {
        x = (x - p.x)*Math.cos(Math.toRadians(kat)) - (y - p.y)*Math.sin(Math.toRadians(kat)) + p.x;
        y = (x - p.x)*Math.sin(Math.toRadians(kat)) - (y - p.y)*Math.cos(Math.toRadians(kat)) + p.x;
    }
    
    public void odbij(Prosta p)
    {
        double a = Math.pow(p.a, -1);
        a *= -1;
        
        double c = a * x  + p.b * y;
        c *= -1;
        
        Prosta p1 = new Prosta(a, p.b, c);
        Punkt pkt = Prosta.pkt_przeciecia(p1, p);
        
        double px = pkt.x - x;
        double py = pkt.y - y;
        
        x = pkt.x + px;
        y = pkt.y + py;       
    }
    
    public String toString()
    {
        return "(" + x + ", " + y + ")";
    }
}
