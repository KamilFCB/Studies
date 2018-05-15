/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad5;

import narzedzia.ONP_NieznanySymbol;
import narzedzia.WyjatekONP;
import narzedzia.Stos;
import narzedzia.Kolejka;
import narzedzia.Lista;
import narzedzia.Para;

/**
 *
 * @author Kamil
 */
public class Wyrazenie
{
    private Kolejka kolejka; // kolejka symboli (elementy typu Symbol)
    private Stos stos; // stos z wynikami pośrednimi (elementy typu double)
    private Lista zmienne; // lista zmiennych (pary String-double)
    public Wyrazenie (String onp, Lista zm) throws WyjatekONP
    {
        System.out.println(onp);
        zmienne = zm;
        kolejka = new Kolejka();
        stos = new Stos();
        Funkcja f;
        String tmp = "";
        boolean liczba = false;
        char[] wyr = onp.toCharArray();
        for(int i=0; i<wyr.length; i++)
        {
            if(wyr[i] != ' ')
            {
                
                if(wyr[i] >= '0' && wyr[i] <= '9')
                {
                    liczba = true;
                    tmp += "" + wyr[i];
                }
                else
                    tmp += "" + wyr[i];
            }
            else
            {
                if(liczba)
                {
                    double v = Double.parseDouble(tmp);
                    stos.wstaw(v);
                }
                else
                {
                    switch (tmp) 
                    {
                        case "+":
                            kolejka.wstaw(new Dodaj());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "-":
                            kolejka.wstaw(new Odejmij());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "/":
                            kolejka.wstaw(new Dziel());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "*":
                            kolejka.wstaw(new Mnoz());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "abs":
                            kolejka.wstaw(new Abs());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "acos":
                            kolejka.wstaw(new Acos());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "atan":
                            kolejka.wstaw(new Atan());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "ceil":
                            kolejka.wstaw(new Ceil());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "cos":
                            kolejka.wstaw(new Cos());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "e":
                            kolejka.wstaw(new E());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "floor":
                            kolejka.wstaw(new Floor());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "ln":
                            kolejka.wstaw(new Ln());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "log":
                            kolejka.wstaw(new Log());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "max":
                            kolejka.wstaw(new Max());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "min":
                            kolejka.wstaw(new Min());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "pi":
                            kolejka.wstaw(new Pi());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "pow":
                            kolejka.wstaw(new Pow());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "sgn":
                            kolejka.wstaw(new Sgn());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        case "sin":
                            kolejka.wstaw(new Sin());
                            f = (Funkcja)kolejka.pobierz();
                            while(f.brakujaceArgumenty() > 0)
                                f.dodajArgument(stos.pobierz());
                            stos.wstaw(f.obliczWartosc());
                            break;
                        default:
                            throw new ONP_NieznanySymbol("Nieznany symbol");
                    }
                    
                }           
                liczba = false;
                tmp = "";
            }
            if(i+1==wyr.length && wyr[i] != ' ')
            {
                wyr[i] = ' ';
                i--;
            }
        }
    }
    
    public void wypisz()
    {
        stos.wypisz();
    }
    
    public double wynik()
    {
        return (double)stos.poczatek.getWartosc();
    }
}