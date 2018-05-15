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

/** Wartość przeciwna liczby */
public class Przeciwny extends Operator1Arg
{

    public Przeciwny(Wyrazenie a1) 
    {
        super(a1);
    }
    
    /** Oblicza wartość przeciwną argumentu */
    public double oblicz()
    {
        return -1 * arg1.oblicz();
    }
    
    public String toString()
    {
        if(arg1.oblicz() < 0)
            return "" + arg1.oblicz();
        
        return "-" + arg1.toString();
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return -1 * arg1.oblicz() == tmp.oblicz();
        
    }
}
