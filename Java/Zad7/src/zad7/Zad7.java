/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad7;

import grafika.Wezel;
import grafika.Lista;
import grafika.Kreska;
import java.awt.*;
import java.awt.event.*;

/**
 *
 * @author Kamil
 */


class MojeOkno extends Frame
{
    private WindowListener frameList = new WindowAdapter()
    {
        @Override
        public void windowClosing (WindowEvent ev)
        {
            MojeOkno.this.dispose();
        }
    };
    private MouseListener mouseList = new MouseAdapter()
    {
        @Override
        public void mouseClicked(MouseEvent ev)
        {
            Graphics gr = plotno.getGraphics();
            gr.clearRect(0, 0, 600, 500);
            Wezel tmp = kreski.poczatek;
            while(tmp!=null)
            {
                Kreska kr_tmp = tmp.getWartosc();
                Point p1_tmp = kr_tmp.getPoczatek();
                Point p2_tmp = kr_tmp.getKoniec();
                gr.setColor(kr_tmp.kolor);
                gr.drawLine(p1_tmp.x, p1_tmp.y, p2_tmp.x, p2_tmp.y);
                tmp = tmp.getNastepny();
            }
        }
        
        @Override
        public void mousePressed(MouseEvent ev)
        {
            p1 = new Point(ev.getX(), ev.getY());
        }
        
        @Override
        public void mouseReleased(MouseEvent ev)
        {
            p2 = new Point(ev.getX(), ev.getY());
            if(p1.x != p2.x && p1.y != p2.y)
            {
                int index = kolory.getSelectedIndex();
                Graphics gr = plotno.getGraphics();
                switch(index)
                {
                    case 0:
                        gr.setColor(Color.RED);
                        k = Color.RED;
                        break;
                    case 1:
                        gr.setColor(Color.GREEN);
                        k = Color.GREEN;
                        break;
                    case 2:
                        gr.setColor(Color.BLUE);
                        k = Color.BLUE;
                        break;
                    default:
                        gr.setColor(Color.BLACK);
                        k = Color.BLACK;
                }

                if(!exit)
                {
                    kr = new Kreska(p1, p2, k);
                    gr.drawLine(p1.x, p1.y, p2.x, p2.y);
                    kreski.wstaw(kr);
                }
            }
            exit = false;
            
        }
        
        public void mouseExited(MouseEvent ev)
        {
            exit = true;
        }        
    };
    
    private MouseMotionListener mouseMotionList = new MouseAdapter()
    {
        public void mouseDragged(MouseEvent ev) 
        {
            Graphics gr = plotno.getGraphics();
            gr.clearRect(0, 0, 600, 500);
            Wezel tmp = kreski.poczatek;
            while(tmp!=null)
            {
                Kreska kr_tmp = tmp.getWartosc();
                Point p1_tmp = kr_tmp.getPoczatek();
                Point p2_tmp = kr_tmp.getKoniec();
                gr.setColor(kr_tmp.kolor);
                gr.drawLine(p1_tmp.x, p1_tmp.y, p2_tmp.x, p2_tmp.y);
                tmp = tmp.getNastepny();
            }
            gr.setColor(Color.GRAY);
            gr.drawLine(p1.x, p1.y, ev.getX(), ev.getY());
        }      
    };    
    
    private MouseListener mouseLister = new MouseAdapter()
    {
        public void mouseClicked(MouseEvent ev)
        {
            int index = kolory.getSelectedIndex();
            Graphics gr = plotno.getGraphics();
            switch(index)
            {
                case 0:
                    gr.setColor(Color.RED);
                    break;
                case 1:
                    gr.setColor(Color.GREEN);
                    break;
                case 2:
                    gr.setColor(Color.BLUE);
                    break;
                default:
                    gr.setColor(Color.BLACK);
            }            
        }
    };
            
            
    private KeyListener keyList = new KeyAdapter()
    {
        @Override
        public void keyPressed (KeyEvent ev)
        {           
            switch (ev.getKeyCode())
            {
            case KeyEvent.VK_F:
                kreski.usun_pierwszy();
                Wezel tmp = kreski.poczatek;
                Graphics gr = plotno.getGraphics();
                gr.clearRect(0, 0, 600, 500);
                while(tmp!=null)
                {
                    Kreska kr_tmp = tmp.getWartosc();
                    Point p1_tmp = kr_tmp.getPoczatek();
                    Point p2_tmp = kr_tmp.getKoniec();
                    gr.setColor(kr_tmp.kolor);
                    gr.drawLine(p1_tmp.x, p1_tmp.y, p2_tmp.x, p2_tmp.y);
                    tmp = tmp.getNastepny();
                }
                break;
            case KeyEvent.VK_L: 
                kreski.usun_ostatni();   
                gr = plotno.getGraphics();
                gr.clearRect(0, 0, 600, 500);
                tmp = kreski.poczatek;
                while(tmp!=null)
                {
                    Kreska kr_tmp = tmp.getWartosc();
                    Point p1_tmp = kr_tmp.getPoczatek();
                    Point p2_tmp = kr_tmp.getKoniec();
                    gr.setColor(kr_tmp.kolor);
                    gr.drawLine(p1_tmp.x, p1_tmp.y, p2_tmp.x, p2_tmp.y);
                    tmp = tmp.getNastepny();
                }
                break;
            case KeyEvent.VK_B:
                kreski.usun_ostatni();
                gr = plotno.getGraphics();
                gr.clearRect(0, 0, 600, 500);
                tmp = kreski.poczatek;
                while(tmp!=null)
                {
                    Kreska kr_tmp = tmp.getWartosc();
                    Point p1_tmp = kr_tmp.getPoczatek();
                    Point p2_tmp = kr_tmp.getKoniec();
                    gr.setColor(kr_tmp.kolor);
                    gr.drawLine(p1_tmp.x, p1_tmp.y, p2_tmp.x, p2_tmp.y);
                    tmp = tmp.getNastepny();
                }
                break;
            case KeyEvent.VK_BACK_SPACE:
                kreski.wyczysc();
                gr = plotno.getGraphics();
                gr.clearRect(0, 0, 600, 500);
                tmp = kreski.poczatek;
                while(tmp!=null)
                {
                    Kreska kr_tmp = tmp.getWartosc();
                    Point p1_tmp = kr_tmp.getPoczatek();
                    Point p2_tmp = kr_tmp.getKoniec();
                    gr.setColor(kr_tmp.kolor);
                    gr.drawLine(p1_tmp.x, p1_tmp.y, p2_tmp.x, p2_tmp.y);
                    tmp = tmp.getNastepny();
                }
            }
        }
    };
    
    private Canvas plotno = new Canvas();    
    
    private List kolory = new List(3, false);    
    
    private Kreska kr = new Kreska();
    private Point p1 = new Point();
    private Point p2 = new Point();
    private Color k = Color.RED;
    
    private boolean exit = false;
    
    private Lista kreski = new Lista();    

    public MojeOkno()
    {
        super("kreski");
        setSize(600, 500);
        setLocation(100, 100);
        add(plotno, BorderLayout.CENTER);
        add(kolory, BorderLayout.WEST);
        kolory.add("czerwony");
        kolory.add("zielony");
        kolory.add("niebieski");
        kolory.addMouseListener(mouseLister);
        kolory.select(0);
        plotno.addKeyListener(keyList);
        plotno.addMouseListener(mouseList);
        plotno.addMouseMotionListener(mouseMotionList);
        plotno.setFocusable(true);
        plotno.requestFocus();
        addWindowListener(frameList);
        setResizable(false);
        setVisible(true);
    }
}

public class Zad7 
{
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        new MojeOkno();
    }
}
