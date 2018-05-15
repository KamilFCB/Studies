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
public class Trojkat 
{
    private Punkt p1, p2, p3;
    
    public Trojkat(Punkt a, Punkt b, Punkt c)
    {
        if((a.x == b.x && a.y == b.y) || (a.x == c.x && a.y == c.y) || (c.x == b.x && c.y == b.y))
            System.err.println("To nie jest trójkąt");
        else if((a.x == b.x && b.x == c.x) || (a.y == b.y && b.y == c.y))
            System.err.println("To nie jest trójkąt");
        else
        {
            p1 = new Punkt(a.x, a.y);
            p2 = new Punkt(b.x, b.y);
            p3 = new Punkt(c.x, c.y);
        }
    }
    
    public Trojkat(double x1, double x2, double x3, double y1, double y2, double y3)
    {
        if((x1 == x2 && y1 == y2) || (x1 == x3 && y1 == y3) || (x3 == x2 && y3 == y2))
            System.err.println("To nie jest trójkąt");
        else if((x1 == x2 && x2 == x3) || (y1 == y2 && y2 == y3))
            System.err.println("To nie jest trójkąt");
        else
        {
            p1 = new Punkt(x1, y1);
            p2 = new Punkt(x2, y2);
            p3 = new Punkt(x3, y3);
        }
    }
    
    public void przesun(Wektor v)
    {
        p1.x += v.dx;
        p1.y += v.dy;
        p2.x += v.dx;
        p2.y += v.dy;
        p3.x += v.dx;
        p3.y += v.dy;
    }   
    
    public void obroc(Punkt p, double kat)
    {
        p1.x = (p1.x - p.x)*Math.cos(Math.toRadians(kat)) - (p1.y - p.y)*Math.sin(Math.toRadians(kat)) + p.x;
	p1.y = (p1.x - p.x)*Math.sin(Math.toRadians(kat)) + (p1.y - p.y)*Math.cos(Math.toRadians(kat)) + p.x;
	p2.x = (p2.x - p.x)*Math.cos(Math.toRadians(kat)) - (p2.y - p.y)*Math.sin(Math.toRadians(kat)) + p.x;
	p2.y = (p2.x - p.x)*Math.sin(Math.toRadians(kat)) + (p2.y - p.y)*Math.cos(Math.toRadians(kat)) + p.x;
        p3.x = (p3.x - p.x)*Math.cos(Math.toRadians(kat)) - (p3.y - p.y)*Math.sin(Math.toRadians(kat)) + p.x;
	p3.y = (p3.x - p.x)*Math.sin(Math.toRadians(kat)) + (p3.y - p.y)*Math.cos(Math.toRadians(kat)) + p.x;
    }
    
    public void odbij(Prosta p)
    {
        // p1
        double a = Math.pow(p.a, -1);
        a *= -1;
        
        double c = a * p1.x  + p.b * p1.y;
        c *= -1;
        
        Prosta pr1 = new Prosta(a, p.b, c);
        Punkt pkt1 = Prosta.pkt_przeciecia(pr1, p);
        
        double px = pkt1.x - p1.x;
        double py = pkt1.y - p1.y;
        
        p1.x = pkt1.x + px;
        p1.y = pkt1.y + py;   
        
        //p2
        a = Math.pow(p.a, -1);
        a *= -1;
        
        c = a * p2.x  + p.b * p2.y;
        c *= -1;
        
        Prosta pr2 = new Prosta(a, p.b, c);
        Punkt pkt2 = Prosta.pkt_przeciecia(pr2, p);
        
        px = pkt2.x - p2.x;
        py = pkt2.y - p2.y;
        
        p2.x = pkt2.x + px;
        p2.y = pkt2.y + py; 
        
        //p3
        a = Math.pow(p.a, -1);
        a *= -1;
        
        c = a * p3.x  + p.b * p3.y;
        c *= -1;
        
        Prosta pr3 = new Prosta(a, p.b, c);
        Punkt pkt3 = Prosta.pkt_przeciecia(pr3, p);
        
        px = pkt3.x - p3.x;
        py = pkt3.y - p3.y;
        
        p3.x = pkt3.x + px;
        p3.y = pkt3.y + py; 
    }
    
    public String toString()
    {
        return "A(" + p1.x + ", " + p1.y + "), B(" + p2.x + ", " + p2.y + "), C(" + p3.x + ", " + p3.y + ")";
    }
    
}
