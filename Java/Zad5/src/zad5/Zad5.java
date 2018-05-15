/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad5;

import narzedzia.WyjatekONP;
import narzedzia.Para;
import narzedzia.Lista;
import java.io.*;
import java.util.logging.*;

/**
 *
 * @author Kamil
 */
public class Zad5 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws WyjatekONP, IOException
    {
        /*
        Symbol s = new Zmienna("as", 2);
        Funkcja a = new Abs();
        
        
        
        
        Symbol m = new Pi();
        
        Funkcja f = (Funkcja) a;
        
        System.out.println(a.brakujaceArgumenty());
        a.dodajArgument(2);
        System.out.println(a.brakujaceArgumenty());
        System.out.println(a.obliczWartosc());
        
        Lista<Para> l = new Lista();
        Para p1 = new Para("x", 1);
        Para p2 = new Para("y", 3);
        l.wstaw(p1);
        l.wstaw(p2);
        l.usun("x");
        l.wypisz();
        
        Stos st = new Stos();
        st.wstaw(1);
        st.wstaw(3);
        st.wypisz();
        
        String k = "kamil";
        
        char[] tab = k.toCharArray();
        for(int i=0; i<tab.length; i++)
            System.out.println(tab[i]);
        */
        Lista<Para> l = new Lista();
        /* Para p1 = new Para("x", 1);
        Para p2 = new Para("y", 3);
        l.wstaw(p1);
        l.wstaw(p2); */
        Wyrazenie w1 = new Wyrazenie("2 2 +", l);
        w1.wypisz();
        
        BufferedReader we = new BufferedReader(new InputStreamReader(System.in));
        Logger logger = Logger.getLogger(Wyrazenie.class.getName());
        Handler handler = new FileHandler("calc.log", true);
        handler.setFormatter(new SimpleFormatter());
        logger.addHandler(handler);
        logger.entering(Wyrazenie.class.getName(), "main");
        
        for (String ln = we.readLine(); ln != null; ln = we.readLine())
        {
            String[] slowa = ln.split(" ");
            assert (slowa[0].equals("calc")) || (slowa[0].equals("clear")) || (slowa[0].equals("exit")) : "Bledne polecenie";
            if(slowa[0].equals("exit"))
                break;
            if(slowa[0].equals("clear"))
            {
                if(slowa.length==1)
                    l.wyczysc();
                for(int i=1; i<slowa.length; i++)
                {
                    l.usun(slowa[i]);
                }
            }
            if(slowa[0].equals("calc"))
            {
                String onp = "";
                for(int i=1; i<slowa.length; i++)
                    onp += slowa[i] + " ";
                
                try
                {
                    w1 = new Wyrazenie(onp, l);
                }
                catch(WyjatekONP e)
                {
                    logger.log(Level.WARNING, e.getMessage());
                }
                String info = onp + "= " + w1.wynik();
                logger.log(Level.INFO, info);
                w1.wypisz();
            }
        }
    }
    
}
