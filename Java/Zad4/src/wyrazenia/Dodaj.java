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

/** Dodawanie dwóch argumentów */
public class Dodaj extends Operator2Arg
{

    public Dodaj(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    /** Oblicza sumę dwóch argumentów */
    public double oblicz()
    {
        return arg1.oblicz() + arg2.oblicz();
    }
    
    public String toString()
    {
        return arg1.toString() + " + " + arg2.toString();
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return arg1.oblicz() + arg2.oblicz() == tmp.oblicz();
        
    }
}