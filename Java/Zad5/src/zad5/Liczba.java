/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad5;

/**
 *
 * @author Kamil
 */
public class Liczba extends Operand
{
    double val;
    
    public Liczba(double v)
    {
        val = v;
    }
    
    @Override
    public double obliczWartosc()
    {
        return val;
    }
}
