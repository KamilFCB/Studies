/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad3;

import geometria.*;

/**
 *
 * @author Kamil
 */
public class Zad3 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Punkt p1 = new Punkt(0, 0);
        Wektor w1 = new Wektor(2, 4);
        Punkt p2 = new Punkt(3, -2);
        Prosta pr1 = new Prosta(-1, 1, 0);
        
        System.out.println("Przesunięcie punktu " + p1.toString() + " o wektor " + w1.toString());
        p1.przesun(w1);
        System.out.println(p1.toString());
        System.out.println();
        System.out.println("Obrót punktu " + p1.toString() + " o kat 23 stopnie i punkt " + p2.toString());
        p1.obroc(p2, 23);
        System.out.println(p1.toString());
        System.out.println();
        System.out.println("Symetria punktu " + p1.toString() + " względem prostej " + pr1.toString());
        p1.odbij(pr1);
        System.out.println(p1.toString());
        System.out.println();
        
        Punkt p3 = new Punkt(0, 0);
        Punkt p4 = new Punkt(3, 2);
        Odcinek o1 = new Odcinek(p3,p4);
        System.out.println("Przesunięcie odcinka " + o1.toString() + " o wektor " + w1.toString());
        o1.przesun(w1);
        System.out.println(o1.toString());
        System.out.println();
        System.out.println("Obrót Odcinka " + o1.toString() + " o kat 23 stopnie i punkt " + p2.toString());
        o1.obroc(p2, 23);
        System.out.println(o1.toString());
        System.out.println();
        System.out.println("Symetria odcinka " + o1.toString() + " względem prostej " + pr1.toString());
        o1.odbij(pr1);
        System.out.println(o1.toString());
        System.out.println();
        
        Punkt p5 = new Punkt(0, 0);
        Punkt p6 = new Punkt(3, 2);
        Punkt p7 = new Punkt(2, 5);
        Trojkat t1 = new Trojkat(p5, p6, p7);
        System.out.println("Przesunięcie trójkąta " + t1.toString() + " o wektor " + w1.toString());
        t1.przesun(w1);
        System.out.println(t1.toString());
        System.out.println();
        System.out.println("Obrót trójkąta " + t1.toString() + " o kat 23 stopnie i punkt " + p2.toString());
        t1.obroc(p2, 23);
        System.out.println(t1.toString());
        System.out.println();
        System.out.println("Symetria trójkąta " + t1.toString() + " względem prostej " + pr1.toString());
        t1.odbij(pr1);
        System.out.println(t1.toString());
        System.out.println();
        
        Wektor w2 = new Wektor(-1, -5);
        System.out.println("Złożenie wektora " + w1.toString() + " z wektorem " + w2.toString());
        Wektor w3 = Wektor.zloz(w1, w2);
        System.out.println(w3.toString());
        System.out.println();
        
        System.out.println("Przesunięcie prostej " + pr1.toString() + " o wektor " + w1.toString());
        Prosta pr2 = Prosta.przesun(pr1, w1);
        System.out.println(pr2.toString());
        System.out.println();
        
        System.out.println("Czy prosta " + pr1.toString() + " i " + pr2.toString() + "są równoległe?");
        System.out.println(Prosta.czy_rownolegle(pr1, pr2));
        System.out.println();
        
        System.out.println("Czy prosta " + pr1.toString() + " i " + pr2.toString() + "są prostopadłe?");
        System.out.println(Prosta.czy_prostopadle(pr1, pr2));
        System.out.println();
        
        Prosta pr3 = new Prosta(-2, 1, 3);
        System.out.println("Punkt przecięcia prostej " + pr1.toString() + " z prostą " + pr3.toString());
        System.out.println(Prosta.pkt_przeciecia(pr1, pr3));
        System.out.println();
        
        Punkt a1= new Punkt(1,0);
        Punkt a2= new Punkt(0,0);
        a1.obroc(a2, 180);
        System.out.println(a1.toString());
    }
    
}
