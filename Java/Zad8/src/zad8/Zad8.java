/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package zad8;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.awt.image.RenderedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.event.*;
/**
 *
 * @author Kamil
 */



class Okno extends JFrame
{
    private JPanel panel = new JPanel(new BorderLayout());
    private JLabel kordy = new JLabel("0, 0");
    private JPanel kolory_panel = new JPanel(new GridLayout(2,1));
    private JPanel malarski = new JPanel()
    {
        @Override
        public void paintComponents(Graphics gr)
        {   if(img != null)
            {  
                super.paintComponent(gr);
                Graphics2D g2d = (Graphics2D)gr;
                g2d.scale(zoom, zoom);
                g2d.drawImage(img, 0, 0, null);  
                this.setPreferredSize(new Dimension(img.getWidth()*zoom, img.getHeight()*zoom));
                this.revalidate();
            }
        } 
        
        @Override
        protected void paintComponent(Graphics gr)
        {
            if(img != null)
            {
                super.paintComponent(gr);
                Graphics2D g2d = (Graphics2D)gr;
                g2d.scale(zoom, zoom);
                g2d.drawImage(img, 0, 0, null);   
                this.setPreferredSize(new Dimension(img.getWidth()*zoom, img.getHeight()*zoom));
                this.revalidate();
            }
        }
    };
    private JToolBar p_narzedzi = new JToolBar();
    DefaultListModel lista = new DefaultListModel();
    private JList l_kolory = new JList(lista);
    private JFileChooser fc = new JFileChooser();
    private ImageIcon icon_zoomin = createImageIcon("zoomin.png", "zoom_in");
    private ImageIcon icon_zoomout = createImageIcon("zoomout.png", "zoom_out");
    private ImageIcon icon_file = createImageIcon("folder_open.png", "file");
    private ImageIcon icon_color = createImageIcon("kolor.png", "kolor");
    private ImageIcon icon_left = createImageIcon("left.jpg", "left");
    private ImageIcon icon_right = createImageIcon("right.jpg", "right");
    private ImageIcon icon_up = createImageIcon("up.jpg", "up");
    private ImageIcon icon_down = createImageIcon("down.jpg", "down");
    private JButton zoom_in = new JButton(icon_zoomin);
    private JButton zoom_out = new JButton(icon_zoomout);
    private JButton file_open = new JButton(icon_file);
    private JButton color_pick = new JButton(icon_color);
    private JButton left = new JButton(icon_left);
    private JButton right = new JButton(icon_right);
    private JButton up = new JButton(icon_up);
    private JButton down = new JButton(icon_down);
    private JScrollPane scrollPane1 = new JScrollPane(kolory_panel);
    private JScrollPane scrollPane2 = new JScrollPane(malarski);
    private JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, scrollPane1, scrollPane2);
    private Graphics g;
    private Color c = Color.BLACK;
    private File file;
    private int zoom = 1;
    
    private String fileName;
    private BufferedImage img;
    
    protected ImageIcon createImageIcon(String path, String description) 
    {
        java.net.URL imgURL = getClass().getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL, description);
        } else {
            System.err.println("Couldn't find file: " + path);
            return null;
        }
    }
    
    private ActionListener fileListener = new ActionListener() 
    {
        @Override
        public void actionPerformed(ActionEvent ev) 
        {
            int returnVal = fc.showOpenDialog((Component)ev.getSource());
            if (returnVal == JFileChooser.APPROVE_OPTION) 
            {
                file = fc.getSelectedFile(); 
                try{
                    img = ImageIO.read(file);
                    int szer = img.getWidth();
                    int wys = img.getHeight();
                    zoom = 1;
                    Graphics g = malarski.getGraphics();
                    malarski.paintComponents(g);
                    
                }
                catch (IOException e) {
                    System.out.println(e.getMessage());
                }
                
            }   
        }
    };
    
    private ActionListener color = new ActionListener()
    {
        @Override
        public void actionPerformed(ActionEvent ev)
        {
            Color newColor = JColorChooser.showDialog(null, "Wybierz kolor", null);
            if (newColor != null) 
            {
                Graphics g = malarski.getGraphics();
                c = newColor;
                g.setColor(newColor);
            }
            

        }
    };
    
    private ActionListener zoomIn = new ActionListener()
    {
        @Override
        public void actionPerformed(ActionEvent ev)
        {
            if(zoom == 8)
                return;
            zoom += 1;
            Graphics g = malarski.getGraphics();
            malarski.paintComponents(g);
        }
    };
    
    private ActionListener zoomOut = new ActionListener()
    {
        @Override
        public void actionPerformed(ActionEvent ev)
        {
            if(zoom == 1)
                return;
            zoom -= 1;
            Graphics g = malarski.getGraphics();
            malarski.paintComponents(g);
        }
    };
    
    private ActionListener scrollLeft = new ActionListener()
    {
        @Override
        public void actionPerformed(ActionEvent ev) 
        {
            JViewport pozycja = scrollPane2.getViewport();
            Point p = pozycja.getViewPosition();
            if(p.x/zoom - 75 > 0)
                p.x -= 75;
            else
                p.x = 0;
            pozycja.setViewPosition(p);
        }        
    };
    
    private ActionListener scrollRight = new ActionListener()
    {
        @Override
        public void actionPerformed(ActionEvent ev) 
        {
            JViewport pozycja = scrollPane2.getViewport();
            Point p = pozycja.getViewPosition();
            if(p.x/zoom + 75 < img.getWidth())
                p.x += 75;
            else
                p.x = 0;
            pozycja.setViewPosition(p);
        }        
    };
    
    private ActionListener scrollDown = new ActionListener()
    {
        @Override
        public void actionPerformed(ActionEvent ev) 
        {
            JViewport pozycja = scrollPane2.getViewport();
            Point p = pozycja.getViewPosition();
            if(p.y/zoom + 75 < img.getHeight())
                p.y += 75;
            else
                p.y = 0;
            pozycja.setViewPosition(p);
        }        
    };
    
    private ActionListener scrollUp = new ActionListener()
    {
        @Override
        public void actionPerformed(ActionEvent ev) 
        {
            JViewport pozycja = scrollPane2.getViewport();
            Point p = pozycja.getViewPosition();
            if(p.y/zoom - 75 > 0)
                p.y -= 75;
            else
                p.y = 0;
            pozycja.setViewPosition(p);
        }        
    };
    
    private MouseListener mouse = new MouseListener()
    {
        @Override
        public void mouseClicked(MouseEvent ev)
        {
            if(file == null)
                return;
            
            Graphics g = img.createGraphics();
            g.setColor(c);
            g.drawLine(ev.getX()/zoom, ev.getY()/zoom, ev.getX()/zoom, ev.getY()/zoom);
            g.dispose();
            repaint();
//            try{
//                Container c = getContentPane();
//                BufferedImage im = new BufferedImage(325, 58, BufferedImage.TYPE_INT_ARGB);
//                c.paint(malarski.getGraphics());
//                ImageIO.write(im, "PNG", new File("saved.png"));
//            }
//            catch(IOException e)
//            {
//                System.out.println(e.getMessage());
//            }
        }

        @Override
        public void mousePressed(MouseEvent e) {
        }

        @Override
        public void mouseReleased(MouseEvent e) {
        }

        @Override
        public void mouseEntered(MouseEvent e) {
        }

        @Override
        public void mouseExited(MouseEvent e) {
            
        }

    };
    
    private MouseMotionListener mouseMotion = new MouseMotionListener()
    {
        @Override
        public void mouseDragged(MouseEvent e) {
        }

        @Override
        public void mouseMoved(MouseEvent ev) 
        {
            kordy.setText(ev.getX()/zoom + ", " + ev.getY()/zoom);
        }
        
    };
    
    private MouseListener colorMouse = new MouseListener()
    {
        @Override
        public void mouseClicked(MouseEvent e) 
        {
            int k = l_kolory.getSelectedIndex();
            
            switch(k)
            {
                case 0:
                    c = Color.RED;
                    break;
                case 1:
                    c = Color.GREEN;
                    break;
                case 2:
                    c = Color.BLUE;
                    break;
                case 3:
                    c = Color.BLACK;
                    break;
                case 4:
                    c = Color.WHITE;
                    break;
            }
        }

        @Override
        public void mousePressed(MouseEvent e) {
        }

        @Override
        public void mouseReleased(MouseEvent e) {
        }

        @Override
        public void mouseEntered(MouseEvent e) {
        }

        @Override
        public void mouseExited(MouseEvent e) {
        }
        
    };
    
    {
        l_kolory.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        l_kolory.setLayoutOrientation(JList.VERTICAL_WRAP);
        file_open.addActionListener(fileListener);
        color_pick.addActionListener(color);
        lista.addElement("czerwony");
        lista.addElement("zielony");
        lista.addElement("niebieski");
        lista.addElement("czarny");
        lista.addElement("bialy");
        kolory_panel.add(l_kolory);
        kolory_panel.add(color_pick);
        p_narzedzi.add(file_open);
        p_narzedzi.add(zoom_in);
        p_narzedzi.add(zoom_out);
        p_narzedzi.add(left);
        p_narzedzi.add(up);
        p_narzedzi.add(down);   
        p_narzedzi.add(right);
        panel.add(p_narzedzi, BorderLayout.PAGE_START);
        panel.add(splitPane, BorderLayout.CENTER);
        panel.add(kordy, BorderLayout.PAGE_END);
        splitPane.setDividerLocation(100);
        g = malarski.getGraphics();
        malarski.addMouseListener(mouse);
        malarski.addMouseMotionListener(mouseMotion);
        zoom_in.addActionListener(zoomIn);
        zoom_out.addActionListener(zoomOut);
        l_kolory.addMouseListener(colorMouse);
        left.addActionListener(scrollLeft);
        right.addActionListener(scrollRight);
        up.addActionListener(scrollUp);
        down.addActionListener(scrollDown);
    }
    
    
    
    public Okno()
    {
        super("Edytor obrazow");
        setSize(800, 600);
        setLocation(100,100);
        setResizable(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        add(panel);
        setVisible(true);
    }
}


public class Zad8 {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        new Okno();
    }
    
}
