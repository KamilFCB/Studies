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

/** Arctan liczby */
public class Arctan extends Operator1Arg
{

    public Arctan(Wyrazenie a1) 
    {
        super(a1);
    }
    
    /** Oblicza Arctan argumentu */
    public double oblicz()
    {
        return Math.atan(arg1.oblicz());
    }
    
    public String toString()
    {
        return "arct(" + arg1.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return Math.atan(arg1.oblicz()) == tmp.oblicz();
        
    }
}