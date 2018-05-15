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

/** Maksimum dwóch argumentów */
public class Maksimum extends Operator2Arg
{

    public Maksimum(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    /** Oblicza maksimum dwóch argumentów */
    public double oblicz()
    {
        if(arg1.oblicz() > arg2.oblicz())
            return arg1.oblicz();
        return arg2.oblicz();
    }
    
    public String toString()
    {
        return "Max(" + arg1.toString() + ", " + arg2.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;        
        
        if(arg1.oblicz() > arg2.oblicz())
            return arg1.oblicz() == tmp.oblicz();
        return arg2.oblicz() == tmp.oblicz();        
    }
}