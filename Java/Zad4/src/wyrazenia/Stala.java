/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wyrazenia;

/**
 *
 * @author Kamil
 */

/** Wartość stała */
public class Stala extends Wyrazenie
{
    /** Wartość stałej */
    protected double val;
    
    /** Przypisuje wartość do stałej */
    public Stala(double v)
    {
        val = v;
    }
    
    /** Zwraca wartość stałej */
    public double oblicz()
    {
        return val;
    }
    
    public String toString()
    {
        return "" + val;
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        double tmp = (double)obj;
        
        return val == tmp;
        
    }
            
}
