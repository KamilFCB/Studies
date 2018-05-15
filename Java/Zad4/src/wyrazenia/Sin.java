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

/** Sin liczby */
public class Sin extends Operator1Arg
{

    public Sin(Wyrazenie a1) 
    {
        super(a1);
    }
    
    /** Oblicza Sin argumentu */
    public double oblicz()
    {
        return Math.sin(arg1.oblicz());
    }
    
    public String toString()
    {
        return "sin(" + arg1.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return Math.sin(arg1.oblicz()) == tmp.oblicz();
        
    }
}
