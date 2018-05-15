/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad4;


import wyrazenia.*;

/**
 *
 * @author Kamil
 */
public class Zad4 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Para p1 = new Para("jeden", 2);
        Para p2 = new Para("dwa", 3);
        Para p3 = new Para("trzy", 65);
        Para p4 = new Para("cztery", 79);
        
        Zbior z = new Zbior(5);
        z.wstaw(p1);
        z.ustal(p2);
        z.wstaw(p3);
        z.wstaw(p4);
        p2.set(4);
        z.ustal(p2);
        Para w = z.szukaj("trzy");
        
        Para x = z.szukaj("jeden");
        
        System.out.println(z.czytaj("dwa"));
        
        z.czysc();
        System.out.println(z.ile());
        
        Wyrazenie w1 = new Dodaj(
                new Stala(3),
                new Stala(5)
        );
        
        Wyrazenie w2 = new Dodaj(
                new Stala(2),
                new Mnoz(
                        new Zmienna("x"),
                        new Stala(7)
                )
        );
        
        Wyrazenie w3 = new Dziel(
                new Odejmij(
                        new Mnoz(
                                new Stala(3),
                                new Stala(11)
                        ),
                        new Stala(1)
                ),
                new Dodaj(
                        new Stala(7),
                        new Stala(5)
                )
        );
        
        Wyrazenie w4 = new Arctan(
                new Dziel(
                        new Mnoz(
                                new Dodaj(
                                        new Zmienna("x"),
                                        new Stala(13)
                                ),
                                new Zmienna("x")
                        ),
                        new Stala(2)
                )
        );
        
        Wyrazenie w5 = new Dodaj(
                new Potega(
                        new Stala(2),
                        new Stala(5)
                ),
                new Mnoz(
                        new Zmienna("x"),
                        new Logarytm(
                                new Stala(2),
                                new Zmienna("y")
                        )
                )
        );
        
        System.out.println(w1.toString() + "=" + w1.oblicz());
        System.out.println(w2.toString() + "=" + w2.oblicz());
        System.out.println(w3.toString() + "=" + w3.oblicz());
        System.out.println(w4.toString() + "=" + w4.oblicz());
        System.out.println(w5.toString() + "=" + w5.oblicz());
        
    }
    
}
