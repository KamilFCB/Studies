/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad5;

import narzedzia.ONP_ZaDuzoArgumentow;

/**
 *
 * @author Kamil
 */
public class E extends Funkcja
{
    protected static double arg;
    
    public E(){}
    
    @Override
    public double obliczWartosc()
    {
        return Math.E;
    }
    
    @Override
    public int arnosc()
    {
        return 0;
    }
    
    @Override
    public int brakujaceArgumenty()
    {
        return 0;
    }
    
    @Override
    public void dodajArgument(double v) throws ONP_ZaDuzoArgumentow
    {
            throw new ONP_ZaDuzoArgumentow();
    }
}
