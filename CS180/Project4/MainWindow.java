/**
 * Project 4 - Recipe Book
 * 
 * @description Can write and read recipes from a file.
 * 
 * @author Joe Martella (jmartel)
 * 
 * @recitation f7
 * 
 * @date April 1, 2010
 *
 */


import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

public class ProjectFour implements ActionListener
{
    String [] measurements = {"cup(s)", "tsp.", "gallon(s)", "tub(s)"};
    JButton exit, search, newButton, cancel, done, more;
    JTextField textField, ingredientsAmount, ingredientsItem;
    JComboBox measure;
    JTextArea instructions;
    JFrame recipe;
    JPanel panel2;
    JLabel ingredients;
    JTextField[] ingredAmount = new JTextField[50];
    JTextField[] ingredItem = new JTextField[50];
    JComboBox[] measures = new JComboBox[50];
    String [] ingredientsX = new String[50];
    String [] directions = new String[50];
    File f;
    static String recipeFile;
    boolean found = false;
    static int count = 0;
    String [] measureString = new String[50];
    
    
    
    
    public static void main(String[] args)
    {
        recipeFile = args[0];
        MainWindow window = new MainWindow();
    }
    
    public MainWindow()
    {
        JFrame frame = new JFrame("Recipe File");
        frame.setSize(260,100);
        frame.setLocation(500,315);
        
        // panel1
        JPanel panel1 = new JPanel();
        panel1.setLayout(new FlowLayout());
        
        // buttons
        exit = new JButton("Exit");
        exit.addActionListener(this);
        search = new JButton("Search");
        search.addActionListener(this);
        newButton = new JButton("Create New");
        newButton.addActionListener(this);
        
        
        // text field
        JLabel name = new JLabel("Name");
        textField = new JTextField("Recipe name here");
        textField.addActionListener(this);
        
        // adding to panel1
        panel1.add(name);
        panel1.add(textField);
        panel1.add(search);
        panel1.add(newButton);
        panel1.add(exit);
        
        // add panel to window and display
        frame.add(panel1);
        frame.setVisible(true);
    }
    
    public void RecipeWindow()
    {
        recipe = new JFrame("Recipe for " + textField.getText());
        recipe.setSize(850,950);
        
        // panel2
        panel2 = new JPanel();
        panel2.setLayout(new FlowLayout());
        
        // label
        ingredients = new JLabel("Ingredients: ");
        
        // text fields
        ingredAmount[0] = new JTextField(5);
        ingredItem[0] = new JTextField(15);
        
        // combo box
        measures[0] = new JComboBox(measurements);
        
        // text area
        instructions = new JTextArea(8,50);
        
        // buttons
        cancel = new JButton("Cancel");
        cancel.addActionListener(this);
        done = new JButton("Done");
        done.addActionListener(this);
        more = new JButton("                   More Ingredients                   ");
        more.addActionListener(this);
        
        
        // add to panel2
        panel2.add(ingredients);
        panel2.add(ingredAmount[0]);
        panel2.add(measures[0]);
        panel2.add(ingredItem[0]);
        panel2.add(more);
        panel2.add(instructions);
        panel2.add(cancel);
        panel2.add(done);
        
        // add panel to window and display
        recipe.add(panel2);
        recipe.setVisible(true);
    }
    
    // action listener
    public void actionPerformed(ActionEvent e){
        Object source = e.getSource();
        if (source instanceof JButton){
            handleButtonAction(e);
        }
    }
    
    // handles button actions **from lecture
    private void handleButtonAction(ActionEvent e)
    {
        JButton button = (JButton) e.getSource();
        if(button == exit)
        {
            System.exit(0);
        }
        else if (button == search)
        {
            String temp2 = "";
            JOptionPane pane = new JOptionPane();
            Scanner scan = null; 
            found = false;
            f = new File(recipeFile);
            
            try {
                scan = new Scanner(f);
               
            } catch (Exception ohno) {};
            
            
            String recipeSearch = textField.getText().toLowerCase();
            try{
            while (scan.hasNextLine())
            {
                
                String temp = scan.nextLine();               
                
                if (temp.equals("@recipe"))
                {     
                    temp2 = scan.nextLine().toLowerCase();
                    
                    if (recipeSearch.equals(temp2))
                    {
                        found = true;
                        break;
                    }
                }
            }
            
            
            if (found)
            {
                String name = temp2;
                String ingredientsPrint = "";
                String directionsPrint = "";
                String temp3 = scan.nextLine();
                String temp4 = "";
                String temp5 = "";
                
                //////////// INGREDIENTS ///////////////
                if (temp3.equals("@ingredients"))
                {
                    int i = 0;
                    
                    
                    while (!(temp4.equals("@directions")))
                    {
                        temp4 = scan.nextLine();
                        if (!(temp4.equals("@directions")))    
                        {
                            ingredientsX[i] = temp4;
                            i++;
                        }
                    }
                    
                    for (int x = 0; x < i; x++)
                    {
                        ingredientsPrint = ingredientsPrint + "\n" + ingredientsX[x]; 
                    }
                    
                    i = 0;
                }
                ////////////// INGREDIENTS ///////////////
               
                
                //////////// DIRECTIONS ///////////////
                if (temp4.equals("@directions"))
                {
                    int i = 0;
                    
                    
                    while (!(temp5.equals("@end")))
                    {
                        
                        temp5 = scan.nextLine();
                        if (!(temp5.equals("@end")))    
                        {
                            directions[i] = temp5;
                            i++;
                        }
                    }
                    
                    for (int x = 0; x < i; x++)
                    {
                        directionsPrint = directionsPrint + "\n" + directions[x]; 
                    }
                    
                    i = 0;
                }
                ////////////// INGREDIENTS ///////////////
                
                pane.showMessageDialog(new JFrame(), "Ingredients: " + ingredientsPrint + "\n\nPreparation Instructions: " + directionsPrint, "Recipe for " + name, 3);
            }
            else 
                pane.showMessageDialog(new JFrame(), "Sorry, that recipe was not found.", "Oops!", 0);
            } catch (Exception ohmygod) { pane.showMessageDialog(new JFrame(), "Sorry, that file was not found. \n Write a recipe to create it!", "Oops!", 0);}
        }
        else if (button == newButton)
        {
            RecipeWindow();
        }
        else if (button == cancel)
        {
            recipe.setVisible(false);
        }
        else if (button == done)
        {            
            
            
            OutputStream o = null;
            PrintWriter p = null;
            
            try
            {
                o = new FileOutputStream(recipeFile, true);
                p = new PrintWriter(o);
            } catch (Exception booga) {};
            
            p.println("@recipe");
            p.println(textField.getText());
            p.println("@ingredients");
            for (int i = 0; i <= count; i++)
            {     
                p.print(ingredAmount[i].getText() + " ");
                measureString[i] = measurements[measures[i].getSelectedIndex()];
                p.print(measureString[i] + " ");
                p.println(" of " + ingredItem[i].getText());
            }
            p.println("@directions");
            p.println(instructions.getText());
            p.println("@end");
            p.close();
            ///////////////
            
            recipe.setVisible(false);
        }
        else if (button == more)
        {
            count++;
            
            // text fields
            ingredAmount[count] = new JTextField(5);
            ingredAmount[count].addActionListener(this);
            ingredItem[count] = new JTextField(15);
            ingredItem[count].addActionListener(this);
            
            // combo box
            measures[count] = new JComboBox(measurements);
            measures[count].addActionListener(this);
            
            // add to panel2
            for (int i = 0; i < count; i++)
            {
                panel2.add(ingredAmount[count]);
                panel2.add(measures[count]);
                panel2.add(ingredItem[count]);            
            }
            
            //panel2.add(more);
            panel2.add(instructions);
            panel2.add(cancel);
            panel2.add(done);
            
            recipe.add(panel2);
            recipe.setVisible(true);
        }
    }
}