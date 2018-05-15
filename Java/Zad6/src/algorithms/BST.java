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
public class BST <T extends Comparable<T>> implements Dict<T>
{
    private Node<T> root;
    
    private class Node <T extends Comparable<T>>
    {
        T val;
        Node<T> left, right, parent;
        
        public Node(T v, Node p)
        {
            val = v;
            left = null;
            right = null;
            parent = null;
        }
        
        public Node(T v, Node l, Node r)
        {
            val = v;
            left = l;
            right = r;
        }
    }
    
    public BST()
    {
        root = null;
    }
    
    public BST(T v)
    {
        root = new Node(v, null);
    }
    
    @Override
    public boolean search(T v)
    {
        return search(v, root);        
    }
    
    private boolean search(T v, Node n)
    {
        if(n == null)
            return false;
        
        int porownaj = n.val.compareTo(v);
        if(porownaj < 0)
            return search(v, n.right);
        else if(porownaj > 0)
            return search(v, n.left);
        
        return true;
    }
    
    @Override
    public void insert(T v)
    {        
        if(v == null)
            throw new NullPointerException();
        if(root == null)
        {
            root = new Node(v, null);
            return;
        }
        
        insert(v, root);            
    }
    
    private void insert(T v, Node n)
    {
        int porownaj = n.val.compareTo(v);
        
        if(porownaj < 0)
        {
            if(n.right==null)
                n.right = new Node(v, n);
            else
                insert(v, n.right);
        }
        else if(porownaj > 0)
        {
            if(n.left==null)
                n.left = new Node(v, n);
            else
                insert(v, n.left);
        }
        
        // duplikat gdy rowny
    }
    
    @Override
    public void remove(T v)
    {
        root = remove(v, root);
    }
    
    private Node remove(T v, Node n)
    {
        if(n == null)
            return null;
        int porownaj = n.val.compareTo(v);
        
        if(porownaj < 0)
            n.right = remove(v, n.right);
        else if(porownaj > 0)
            n.left = remove(v, n.left);
        else
        {
            if(n.left == null )
                return n.right;
            else if(n.right == null)
                return n.left;
            
            else 
            {
                n.val = min(n.right);
                n.right = remove((T)n.val, n.right);
            }
        }
        return n;
    }
    
    @Override
    public T min()
    {
        return min(root);
    }
    
    private T min(Node n)
    {
        T min = (T) n.val;
        while(n.left != null)
        {
            min = (T) n.left.val;
            n = n.left;
        }
        return min;
    }
    
    @Override
    public T max()
    {
        return max(root);
    }
    
    private T max(Node n)
    {
        T max = (T) n.val;
        while(n.right != null)
        {
            max = (T) n.right.val;
            n = n.right;
        }
        return max;
    }
    
    public void clear()
    {
        clear(root);
        root = null;
    }
    
    private void clear(Node n)
    {
        if(n.left != null)
            clear(n.left);
        
        n.left = null;

        if(n.right != null)
            clear(n.right);
        
        n.right = null;
        n.parent = null;
        n.val = null;
    }
    
    public int size()
    {        
        if(root==null)
            return 0;
        return size(root);
    }
    
    private int size(Node n)
    {
        int l=1, r=1;
        
        if(n.left != null)
            l=size(n.left) + 1;
        else if(n.right != null)
            r = size(n.right) + 1;
        
        return Math.max(l, r);
    }
    
    @Override
    public String toString()
    {
        return print(root);
    }
    
    private String print(Node n)
    {
        if(n == null)
            return "";
        return print(n.left) + " " + n.val.toString() + " " + print(n.right);
    }
    
}
