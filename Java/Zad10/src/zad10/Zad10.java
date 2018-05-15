/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad10;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.TimerTask;
import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.event.*;
import java.util.Timer;

/**
 *
 * @author Kamil
 */

class Droga
{
    private boolean gora, dol, prawo, lewo;
}

class Samochod implements Runnable
{
    public static volatile boolean jazda = true;
    private int droga; // 0-lewo, 1-prawo, 2-gora, 3-dol
    private int kierunek; // 0-lewo, 1-prawo, 2-gora, 3-dol
    private int predkosc;
    public int x, y;
    
    
    public Samochod()
    {
        droga = (int)Math.floor(Math.random()*4);
        kierunek = (int)Math.floor(Math.random()*4);
        while(droga == kierunek)
            kierunek = (int)Math.floor(Math.random()*4);
        predkosc = (int)Math.floor(Math.random()*31) + 20;
        x=0;
        y=470;
    }
    
    
    @Override
    public void run()
    {
        while(jazda)
        {
            System.out.println(1);
            //x+=1;
        }
    }
}

class Okno extends JFrame
{
    private Samochod s = new Samochod();
    private JPanel panel = new JPanel(new BorderLayout());
    private JToolBar p_narzedzi = new JToolBar();
    private JButton start = new JButton("Start");
    private JPanel skrzyzowanie = new JPanel()
    {  
        @Override
        protected void paintComponent(Graphics gr)
        {
            if(img != null)
            {
                super.paintComponent(gr);
                gr.drawImage(img, 0, 0, null);   
                gr.drawImage(img2, s.x, s.y, null);  
            }
        }
    };
    private BufferedImage img, img2;
    
       
    {
        panel.add(skrzyzowanie, BorderLayout.CENTER);
        try
        {
            img = ImageIO.read(new File("D:\\Studia\\Java\\Zad10\\src\\zad10\\skrzyzowanie.png"));
            img2 = ImageIO.read(new File("D:\\Studia\\Java\\Zad10\\src\\zad10\\prosto.png"));
            System.out.println(img.getHeight());
        }
        catch (IOException ex) 
        {
            System.out.println(ex.getMessage());
        }
        
        p_narzedzi.add(start);
        //panel.add(p_narzedzi, BorderLayout.PAGE_START);
    }
    
    public Okno()
    {
        super("Symulator skrzyżowania");
        setSize(1507, 907);
        setLocation(100,100);
        setResizable(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        add(panel);
        Timer t = new Timer();
        new Thread(s).start();
        t.scheduleAtFixedRate(new TimerTask(){        
            @Override
            public void run()
            {
                if(s.x<650)
                    s.x += 2;
                else
                    s.y += 2;
                skrzyzowanie.repaint();
            }
        }, 40,40);
    }
}


public class Zad10 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        new Okno();
    }
    
}
