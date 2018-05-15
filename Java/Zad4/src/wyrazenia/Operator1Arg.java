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

/** Abstrakcyjna klasa Operator1Arg */
public abstract class Operator1Arg extends Wyrazenie
{
    /** Argument 1 */
    protected final Wyrazenie arg1;

    public Operator1Arg (Wyrazenie a1) 
    {
        if (a1==null) throw new IllegalArgumentException();
        arg1 = a1;
    }
    
    public abstract double oblicz(); 
    public abstract String toString();
    public abstract boolean equals(Object obj);
}