/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad5;

import narzedzia.ONP_ZaDuzoArgumentow;
import narzedzia.ONP_DzieleniePrzez0;

/**
 *
 * @author Kamil
 */
public class Dziel extends Funkcja
{
    protected static double[] arg;
    protected static int ile;
    static{
        arg = new double[2];
        ile=0;
    }
    
    public Dziel()
    {
        ile = 0;
    }
    
    @Override
    public double obliczWartosc() throws ONP_DzieleniePrzez0
    {
        if(arg[1]==0)
            throw new ONP_DzieleniePrzez0();
        return arg[1] / arg[0];
    }
    
    @Override
    public int arnosc()
    {
        return 2;
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
