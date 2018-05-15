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
public class Sgn extends Funkcja
{
    protected static double[] arg;
    protected static int ile;
    static{
        arg = new double[1];
        ile=0;
    }
    
    public Sgn()
    {
        ile = 0;
    }
    
    @Override
    public double obliczWartosc()
    {
        return Math.signum(arg[0]);
    }
    
    @Override
    public int arnosc()
    {
        return 1;
    }
    
    @Override
    public int brakujaceArgumenty()
    {
        return arnosc()-ile;
    }
    
    @Override
    public void dodajArgument(double v) throws ONP_ZaDuzoArgumentow 
    { 
        if(brakujaceArgumenty()==0) 
            throw new ONP_ZaDuzoArgumentow();
        arg[ile] = v;       
        ile++;
    }
}
