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

/** Potęga dwóch argumentów */
public class Potega extends Operator2Arg
{

    public Potega(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    /** Oblicza argument1 do potęgi argument2 */
    public double oblicz()
    {
        return Math.pow(arg2.oblicz(),arg1.oblicz());
    }
    
    public String toString()
    {
        return "pow(" + arg1.toString() + ", " + arg2.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return Math.pow(arg1.oblicz(), arg2.oblicz()) == tmp.oblicz();
        
    }
}

