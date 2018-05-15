/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wyrazenia;

/**
 *
 * @author Kamil
 */
/** Abstrakcyjna klasa wyrażenie */
public abstract class Wyrazenie 
{
    /** Abstrakcyjna metoda oblicz */
    public abstract double oblicz();
    public abstract String toString();
    public abstract boolean equals(Object obj);
    public Wyrazenie(){}
    
    /** Sumuje dowolną ilość wyrażeń */
    public static double sumuj(Wyrazenie... wyr)
    {
        int wynik = 0;
        for(int i=0; i<wyr.length; i++)
            wynik += wyr[i].oblicz();
        
        return wynik;
    }
    
    /** Mnoży dowolną ilość wyrażeń */
    public static double pomnoz(Wyrazenie... wyr)
    {
        int wynik = 1;
        for(int i=0; i<wyr.length; i++)
            wynik *= wyr[i].oblicz();
        
        return wynik;
    }

}

/* class Stala extends Wyrazenie
{
    protected double val;
    
    public Stala(double v)
    {
        val = v;
    }
    
    @Override
    public double oblicz()
    {
        return val;
    }
    
    public String toString()
    {
        return "" + val;
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        double tmp = (double)obj;
        
        return val == tmp;
        
    }
            
}

class Zmienna extends Wyrazenie
{
    protected static Zbior val;
    private String zmienne = "";
    private int licz_oblicz = 0;
    private int licz_tostring = 0;
    
    static {
        val = new Zbior();
    }
    
    public Zmienna(String key)
    {
        val.wstaw(new Para(key, -1.618));
        zmienne += key;
    }
    
    public double oblicz()
    {
        String x = zmienne.substring(licz_oblicz, licz_oblicz+1);
        licz_oblicz++;
        return val.czytaj(x);
        //return -1.618; // do zrobienia!!!!!!!!
    }  
    
    public String toString()
    {
        licz_tostring++;
        return zmienne.substring(licz_tostring-1, licz_tostring);
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        double tmp = (double)obj;
        
        //return val == tmp;
        return true; // DO ZROBIENIA!!!!!!!!!
        
    }
}


abstract class Operator1Arg extends Wyrazenie
{
    protected final Wyrazenie arg1;

    public Operator1Arg (Wyrazenie a1) 
    {
        if (a1==null) throw new IllegalArgumentException();
        arg1 = a1;
    }
    
    public abstract double oblicz(); 
    public abstract String toString();
    public abstract boolean equals(Object obj);
}

class Przeciwny extends Operator1Arg
{

    public Przeciwny(Wyrazenie a1) 
    {
        super(a1);
    }
    
    public double oblicz()
    {
        return -1 * arg1.oblicz();
    }
    
    public String toString()
    {
        if(arg1.oblicz() < 0)
            return "" + arg1.oblicz();
        
        return "-" + arg1.toString();
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return -1 * arg1.oblicz() == tmp.oblicz();
        
    }
}

class Bezwgledna extends Operator1Arg
{

    public Bezwgledna(Wyrazenie a1) 
    {
        super(a1);
    }
    
    public double oblicz()
    {
        if(arg1.oblicz() < 0)
            return -1 * arg1.oblicz();
        
        return arg1.oblicz();
    }
    
    public String toString()
    {
        return "-" + arg1.toString();
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        if(arg1.oblicz() < 0)
            return -1 * arg1.oblicz() == tmp.oblicz();
        
        return arg1.oblicz() == tmp.oblicz();
        
    }
}

class Odwrot extends Operator1Arg
{

    public Odwrot(Wyrazenie a1) 
    {
        super(a1);
    }
    
    public double oblicz()
    {
        return 1 / arg1.oblicz();
    }
    
    public String toString()
    {
        return "1/" + arg1.toString();
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return  1 / arg1.oblicz() == tmp.oblicz();
        
    }
}

class Sin extends Operator1Arg
{

    public Sin(Wyrazenie a1) 
    {
        super(a1);
    }
    
    public double oblicz()
    {
        return Math.sin(arg1.oblicz());
    }
    
    public String toString()
    {
        return "sin(" + arg1.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return Math.sin(arg1.oblicz()) == tmp.oblicz();
        
    }
}

class Cos extends Operator1Arg
{

    public Cos(Wyrazenie a1) 
    {
        super(a1);
    }
    
    public double oblicz()
    {
        return Math.cos(arg1.oblicz());
    }
    
    public String toString()
    {
        return "cos(" + arg1.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return Math.cos(arg1.oblicz()) == tmp.oblicz();
        
    }
}

class Arctan extends Operator1Arg
{

    public Arctan(Wyrazenie a1) 
    {
        super(a1);
    }
    
    public double oblicz()
    {
        return Math.atan(arg1.oblicz());
    }
    
    public String toString()
    {
        return "arct(" + arg1.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return Math.atan(arg1.oblicz()) == tmp.oblicz();
        
    }
}

abstract class Operator2Arg extends Operator1Arg
{
    protected final Wyrazenie arg2;

    public Operator2Arg(Wyrazenie a1, Wyrazenie a2)
    {
        super(a1);
        if (a2==null) throw new IllegalArgumentException();
        arg2 = a2;
    }
    
    public abstract double oblicz();
    public abstract String toString();
    public abstract boolean equals(Object obj);
}

class Dodaj extends Operator2Arg
{

    public Dodaj(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    public double oblicz()
    {
        return arg1.oblicz() + arg2.oblicz();
    }
    
    public String toString()
    {
        return arg1.toString() + " + " + arg2.toString();
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return arg1.oblicz() + arg2.oblicz() == tmp.oblicz();
        
    }
}

class Odejmij extends Operator2Arg
{

    public Odejmij(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    public double oblicz()
    {
        return arg1.oblicz() - arg2.oblicz();
    }
    
    public String toString()
    {
        return arg1.toString() + " - " + arg2.toString();
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return arg1.oblicz() - arg2.oblicz() == tmp.oblicz();
        
    }
}

class Mnoz extends Operator2Arg
{

    public Mnoz(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    public double oblicz()
    {
        return arg1.oblicz() * arg2.oblicz();
    }
    
    public String toString()
    {
        return arg1.toString() + " * " + arg2.toString();
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return arg1.oblicz() * arg2.oblicz() == tmp.oblicz();
        
    }
}

class Dziel extends Operator2Arg
{

    public Dziel(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    public double oblicz()
    {
        return arg1.oblicz() / arg2.oblicz();
    }
    
    public String toString()
    {
        return arg1.toString() + " / " + arg2.toString();
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return arg1.oblicz() / arg2.oblicz() == tmp.oblicz();
        
    }
}

class Modulo extends Operator2Arg
{

    public Modulo(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    public double oblicz()
    {
        return arg1.oblicz() % arg2.oblicz();
    }
    
    public String toString()
    {
        return arg1.toString() + " % " + arg2.toString();
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return arg1.oblicz() % arg2.oblicz() == tmp.oblicz();
        
    }
}

class Maksimum extends Operator2Arg
{

    public Maksimum(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    public double oblicz()
    {
        if(arg1.oblicz() > arg2.oblicz())
            return arg1.oblicz();
        return arg2.oblicz();
    }
    
    public String toString()
    {
        return "Max(" + arg1.toString() + ", " + arg2.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;        
        
        if(arg1.oblicz() > arg2.oblicz())
            return arg1.oblicz() == tmp.oblicz();
        return arg2.oblicz() == tmp.oblicz();        
    }
}

class Minimum extends Operator2Arg
{

    public Minimum(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    public double oblicz()
    {
        if(arg1.oblicz() < arg2.oblicz())
            return arg1.oblicz();
        return arg2.oblicz();
    }
    
    public String toString()
    {
        return "Min(" + arg1.toString() + ", " + arg2.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;        
        
        if(arg1.oblicz() < arg2.oblicz())
            return arg1.oblicz() == tmp.oblicz();
        return arg2.oblicz() == tmp.oblicz();        
    }
}

class Logarytm extends Operator2Arg
{

    public Logarytm(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    public double oblicz()
    {
        return Math.log(arg2.oblicz()) / Math.log(arg1.oblicz());
    }
    
    public String toString()
    {
        return "log(" + arg1.toString() + ", " + arg2.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return Math.log(arg1.oblicz()) / Math.log(arg2.oblicz()) == tmp.oblicz();
        
    }
}

class Potega extends Operator2Arg
{

    public Potega(Wyrazenie a1, Wyrazenie a2) 
    {
        super(a1, a2);
    }
    
    public double oblicz()
    {
        return Math.pow(arg2.oblicz(),arg1.oblicz());
    }
    
    public String toString()
    {
        return "pow(" + arg1.toString() + ", " + arg2.toString() + ")";
    }
    
    public boolean equals(Object obj)
    {
        if (getClass() != obj.getClass())
            return false;
        
        Wyrazenie tmp = (Wyrazenie)obj;
        
        return Math.pow(arg1.oblicz(), arg2.oblicz()) == tmp.oblicz();
        
    }
}

*/