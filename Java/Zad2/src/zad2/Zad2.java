/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad2;

/**
 *
 * @author Kamil
 */

public class Zad2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        if(args.length == 0)
            System.err.println("Brak parametrów");
        else
        {
            for(int i=0; i<args.length; i++)
            {
                long liczba = new Long(args[i]);       
                long test[] = LiczbyPierwsze.naCzynnikiPierwsze(liczba);

                System.out.print(liczba + " = ");
                for(int j=0; j < test.length-1; j++)
                    System.out.print(test[j] + " * ");

                System.out.print(test[test.length-1]);

                System.out.println("");
            }
        }
    }
    
}
