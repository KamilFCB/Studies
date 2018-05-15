/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad6;

import algorithms.*;

/**
 *
 * @author Kamil
 */
public class Zad6 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        BST<Integer> b = new BST(5);
        b.insert(3);
        b.insert(10);
        b.insert(4);
        b.insert(1);
        b.insert(20);
        b.insert(-10);
        b.insert(8);
        b.insert(2);
        System.out.println(b.toString());
        System.out.println("Czy wystepuje 10?" + b.search(10));
        System.out.println("Czy wystepuje 11?" + b.search(11));
        b.remove(3);
        System.out.println("Po usunieciu 3");
        System.out.println(b.toString());
        System.out.println("Max: " + b.max());
        System.out.println("Min: " + b.min());
        System.out.println("Rozmiar: " + b.size());
        
        b.clear();
        System.out.println("Po wyczyszczeniu: " + b.toString());
        System.out.println("Rozmiar: " + b.size());
        
        
        System.out.println("------------------------------");
        
        BST<String> s = new BST("kamil");
        s.insert("basia");
        s.insert("kasia");
        s.insert("andrzej");
        s.insert("ania");
        s.insert("zaneta");
        s.insert("tymoteusz");
        s.insert("weronika");
        s.insert("kornelia");
        System.out.println(s.toString());
        System.out.println("Czy wystepuje andrzej?" + s.search("andrzej"));
        System.out.println("Czy wystepuje beata?" + s.search("beata"));
        System.out.println("Rozmiar: " + s.size());
        System.out.println("Max: " + s.max());
        System.out.println("Min: " + s.min());
        s.remove("tymoteusz");
        System.out.println("Po usunieciu tymoteusza");
        System.out.println(s.toString());
    }
    
}
