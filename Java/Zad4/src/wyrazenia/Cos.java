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

/** Cos liczby */
public class Cos extends Operator1Arg
{

    public Cos(Wyrazenie a1) 
    {
        super(a1);
    }
    
    /** Oblicza Cos argumentu */
    public double oblicz()
    {
        return Math.cos(arg1.oblicz());
    }
    
    public String toString()
    {
        return "cos(" + arg1.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return Math.cos(arg1.oblicz()) == tmp.oblicz();
        
    }
}
