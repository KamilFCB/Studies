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

/** Abstrakcyjna klasa Operator2Arg */
public abstract class Operator2Arg extends Operator1Arg
{
    /** Argument 2 */
    protected final Wyrazenie arg2;

    public Operator2Arg(Wyrazenie a1, Wyrazenie a2)
    {
        super(a1);
        if (a2==null) throw new IllegalArgumentException();
        arg2 = a2;
    }
    
    public abstract double oblicz();
    public abstract String toString();
    public abstract boolean equals(Object obj);
}
