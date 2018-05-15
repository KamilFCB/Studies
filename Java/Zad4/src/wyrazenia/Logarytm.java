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

/** Logarytm dwóch argumentów */
public class Logarytm extends Operator2Arg
{

    public Logarytm(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    /** Oblicza logarytm dwóch argumentów */
    public double oblicz()
    {
        return Math.log(arg2.oblicz()) / Math.log(arg1.oblicz());
    }
    
    public String toString()
    {
        return "log(" + arg1.toString() + ", " + arg2.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return Math.log(arg1.oblicz()) / Math.log(arg2.oblicz()) == tmp.oblicz();
        
    }
}