package zad2;

import java.util.ArrayList;
import java.util.List;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Kamil
 */
public final class LiczbyPierwsze 
{
    private LiczbyPierwsze() { }
    
    private final static int POTEGA2 = 21;
    private final static int[] SITO = new int[1<<POTEGA2];
    
    static 
    {
        long rozmiar = 1<<POTEGA2;
        
        for(int i = 2; i < rozmiar; i++) 
            SITO[i] = i; 
        
        for(int i = 2; i*i < rozmiar; i++)
        {
            if(SITO[i] == i)
            {
                for(int j = i; i * j < rozmiar; j++)
                {
                    if(SITO[i*j] > i) 
                        SITO[i*j] = i;
                }
             }
        }
        
    }
    
    public static boolean czyPierwsza(long x)
    {            
        if(x%2==0)
            return false;
        
        for(long i=3; i <= Math.sqrt(x); i+=2)
        {
            if(x%i==0)
                return false;
        }
        
        return true;
    }
    
    public static long[] naCzynnikiPierwsze(long x)
    {
        List<Long> czynniki = new ArrayList<Long>();
        long rozmiar = 1<<POTEGA2;
        int i=2;
               
        if(x == 0 || x == 1 || x==-1)
            czynniki.add(x);
        else
        {
            if(x<0)
            {
                czynniki.add((long)-1);
                x *= -1;
            }
            
            if(czyPierwsza(x))
                czynniki.add(x);
            else
            {
                while(x != 1 && i < rozmiar)
                {
                    if(i == SITO[i] && x % i == 0)
                    {
                        czynniki.add((long)SITO[i]);
                        x /= SITO[i];
                        if(czyPierwsza(x) && x!=1 && x!=-1)
                        {
                            czynniki.add(x);
                            break;
                        }
                    }
                    else
                        i++;
                }
            }
        }
        
        long[] wynik = new long[czynniki.size()];
        
        for(int j=0; j<czynniki.size(); j++)
        {
            wynik[j]=czynniki.get(j);
        }
        
        return wynik;
    }
}
