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
public class Zmienna extends Operand
{
    double val;
    String id;
    
    public Zmienna(String name, double v)
    {
        String wzor = "\\p{Alpha}\\p{Alnum}*";
        if(name.matches(wzor) && !name.equals("Pi") && !name.equals("E"))
            System.out.println("elo");
        val = v;
        id = name;
    }
    
    @Override
    public double obliczWartosc()
    {
        return val;
    }
}
