/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;

import grafika.Kreska;

/**
 *
 * @author Kamil
 */
public class Wezel 
{
    private Kreska wartosc;
        private Wezel poprzedni;
        private Wezel nastepny;

        /** Pusty wezel */
        public Wezel()
        {
            nastepny = null;
            poprzedni = null;
        }

        /** Wezel o podanej wartosci z pustymi wskaznikami */
        public Wezel(Kreska val, Wezel prev, Wezel next)
        {
            wartosc = val;
            nastepny = next;
            poprzedni = prev;
        }
        
        /** Zwraca wartosc wezla */
        public Kreska getWartosc()
        {
            return wartosc;
        }

        /** Zwraca wskaznik kolejnego wezla */
        public Wezel getNastepny()
        {
            return nastepny;
        }

        /** Zwraca wskaznik poprzedniego wezla */
        public Wezel getPoprzedni()
        {
            return poprzedni;
        }

        /** Ustawia wskaznik poprzedniego wezla */
        public void setPoprzedni(Wezel w)
        {
            poprzedni = w;
        }

        /** Ustawia wskaznik kolejnego wezla */
        public void setNastepny(Wezel w)
        {
            nastepny = w;
        }
}
