/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad5;

import narzedzia.WyjatekONP;

/**
 *
 * @author Kamil
 */
public interface Funkcyjny extends Obliczalny
{
    int arnosc();
    int brakujaceArgumenty();
    void dodajArgument(double arg) throws WyjatekONP;
}
