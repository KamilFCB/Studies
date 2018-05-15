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

/** Para klucz-wartość */
public class Para 
{
    /**
     * Para klucz(public) string-wartość(private) double
     */
    public final String klucz;
    private double wartosc;
    
    public Para(String key, double val)
    {
        klucz = key;
        wartosc = val;
    }
    
    /** zwraca wartość przypisaną do klucza */
    public double get()
    {
        return wartosc;
        
    }
    
    /** ustala wartość klucza, jako argument podajemy wartość którą chcemy przypisać */
    public void set(double val)
    {
        wartosc = val;
    }
    
    
    @Override
    public String toString()
    {
        return klucz + " : " + wartosc;
    }
    
    @Override
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Para tmp = (Para)obj;
        
        return klucz.equals(tmp.klucz);
        
    }
}
