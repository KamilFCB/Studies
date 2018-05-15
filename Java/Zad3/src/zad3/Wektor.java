/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad3;

/**
 *
 * @author Kamil
 */
public class Wektor 
{
    public final double dx, dy;
    
    public Wektor(double x, double y)
    {
        dx = x;
        dy= y;
    }
    
    public static Wektor zloz(Wektor w1, Wektor w2)
    {
        double x = w1.dx + w2.dx;
        double y = w1.dy + w2.dy;        
        Wektor res = new Wektor(x, y);
        
        return res;
    }
    
    public String toString()
    {
        return "[" + dx + ", " + dy + "]";
    }
}
