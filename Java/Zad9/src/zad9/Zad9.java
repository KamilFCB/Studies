/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad9;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Calendar;
import java.util.GregorianCalendar;

/**
 *
 * @author Kamil
 */

class KreslarzElementowListy extends JLabel implements ListCellRenderer
{
    public KreslarzElementowListy()
    {
    }

    @Override
    public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected, boolean cellHasFocus) 
    {
        String napis = value.toString();
        setText(napis);
        setForeground(Color.RED);
        return this;
    }
    
}

class ModelDanych extends AbstractListModel
{
    static Calendar kalendarz;
    public static int rok;
    public static int miesiac;
    
    {
        kalendarz = new GregorianCalendar();
        rok = kalendarz.get(Calendar.YEAR);
        miesiac = kalendarz.get(Calendar.MONTH);
    }
    
    public ModelDanych(int r, int mies)
    {
        rok = r;
        miesiac = mies;
    }    
    
    @Override
    public int getSize() 
    {
        return kalendarz.getActualMaximum(Calendar.DAY_OF_MONTH);
    }

    @Override
    public Object getElementAt(int dzien) 
    {
        kalendarz.set(rok, miesiac, dzien);
        int dzienTygodnia = kalendarz.get(Calendar.DAY_OF_WEEK);
        int dzienMiesiaca = kalendarz.get(Calendar.DAY_OF_MONTH);
        String nazwaDnia = "", nazwaMiesiaca = "";
        
        switch(dzienTygodnia)
        {
            case 1:
                nazwaDnia = "Niedziela";
                break;
            case 2:
                nazwaDnia = "Poniedziałek";
                break;
            case 3:
                nazwaDnia = "Wtorek";
                break;
            case 4:
                nazwaDnia = "Środa";
                break;
            case 5:
                nazwaDnia = "Czwartek";
                break;
            case 6:
                nazwaDnia = "Piątek";
                break;
            case 7:
                nazwaDnia = "Sobota";
                break;
        }
        
        switch(miesiac)
        {
            case 0:
                nazwaMiesiaca = "Styczeń";
                break;
            case 1:
                nazwaMiesiaca = "Luty";
                break;
            case 2:
                nazwaMiesiaca = "Marzec";
                break;
            case 3:
                nazwaMiesiaca = "Kwiecień";
                break;
            case 4:
                nazwaMiesiaca = "Maj";
                break;
            case 5:
                nazwaMiesiaca = "Czerwiec";
                break;
            case 6:
                nazwaMiesiaca = "Lipiec";
                break;
            case 7:
                nazwaMiesiaca = "Sierpień";
                break;
            case 8:
                nazwaMiesiaca = "Wrzesień";
                break;
            case 9:
                nazwaMiesiaca = "Październik";
                break;
            case 10:
                nazwaMiesiaca = "Listopad";
                break;
            case 11:
                nazwaMiesiaca = "Grudzień";
                break;
        }
        
        return nazwaDnia + ", " + dzienMiesiaca + ". " + nazwaMiesiaca;
        
    }
    
}

class Okno extends JFrame
{
    String[] mies = {"Styczeń", "Luty", "Marzec", "Kwiecień", "Maj", "Czerwiec", "Lipiec", "Sierpień", "Wrzesień", "Październik", "Listopad", "Grudzień"};
    private JPanel panel = new JPanel(new BorderLayout());
    JTabbedPane tabbedPane = new JTabbedPane();
    JPanel panel1 = new JPanel(new GridLayout(3,4));  
    JPanel[] miesiace = new JPanel[12];
    ModelDanych model = new ModelDanych(2017, 0);
    String data = (String)model.getElementAt(2);
    JLabel panel2 = new JLabel(data);   
    
    {
        panel.add(tabbedPane);
        tabbedPane.addTab("Rok", panel1);
        tabbedPane.addTab("Miesiąc", panel2);
        for(int i=0; i<12; i++)
        {
            miesiace[i] = new JPanel(new BorderLayout());
            miesiace[i].add(new JButton(mies[i]), BorderLayout.NORTH);
            miesiace[i].add(new JList(model));
            model.miesiac = i;
            panel1.add(miesiace[i]);
        }
    }
    
    public Okno()
    {
        super("Kalendarz");
        setSize(800, 600);
        setLocation(100,100);
        setResizable(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        getContentPane().add(panel, BorderLayout.CENTER);
        setVisible(true);
    }
}


public class Zad9 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        new Okno();
    }
    
}
