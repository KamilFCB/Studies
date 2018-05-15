/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package algorithms;

/**
 *
 * @author Kamil
 */
public interface Dict <T extends Comparable<T>>
{
    public boolean search(T v);
    public void insert(T v);
    public void remove(T v);
    public T min();
    public T max();
}
