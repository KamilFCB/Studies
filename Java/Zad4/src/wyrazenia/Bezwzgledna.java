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

/** Wartość bezwzględna liczby */
public class Bezwzgledna extends Operator1Arg
{

    public Bezwzgledna(Wyrazenie a1) 
    {
        super(a1);
    }
    
    /** Oblicza wartość bezwzględną argumentu */
    public double oblicz()
    {
        if(arg1.oblicz() < 0)
            return -1 * arg1.oblicz();
        
        return arg1.oblicz();
    }
    
    public String toString()
    {
        return "-" + arg1.toString();
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        if(arg1.oblicz() < 0)
            return -1 * arg1.oblicz() == tmp.oblicz();
        
        return arg1.oblicz() == tmp.oblicz();
        
    }
}
