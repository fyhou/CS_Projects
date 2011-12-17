/**
 * Project 1: A Different String Class
 * This program takes in a set of integers or bytes, as 
 * designated by the user and converts such values into
 * a textual message that is outputted to the screen. 
 *
 * @author Joseph Martella
 *
 * @recitation f7 (Jacqueline Soenneker)
 *
 * @date February 4, 2010
 *
 */

import java.util.*;
public class Driver
{
    public static void main(String[] args)
    {
        Scanner scan = new Scanner (System.in); 
        String choice = "";
        
        // menu
        while (!choice.equals("3"))
        {
            choice = "";
            System.out.println("\n1. Enter Integers \n2. Enter Bytes \n3. Exit");          
            System.out.print("What do you want to do? ");
            choice = scan.next();            
            
            while (!choice.equals("1") && !choice.equals("2") && !choice.equals("3"))
            {
                System.out.println("\n1. Enter Integers \n2. Enter Bytes \n3. Exit");
                System.out.print("Please enter a valid menu choice: ");
                choice = scan.next();
            }            
            
            if (choice.equals("1"))
            {
                System.out.print("How many numbers will you enter? ");
                int numberOfIntegers = scan.nextInt();
                int [] integers = new int[numberOfIntegers];
                System.out.println("Enter integers separated by spaces or newlines:");
                
                /**
                 * stores user's integers in an array of integers
                 */
                for (int count = 0; count < numberOfIntegers; count++)
                {
                    integers[count] = scan.nextInt();
                }
                
                SecretString secret = new SecretString(integers);
                
                System.out.print("Your message is: \"");
                
                for (int i = 0; i < secret.getLength(); i++)
                {
                    System.out.print(secret.getCharAt(i));
                }
                
                System.out.println("\"");
            }
            
            if (choice.equals("2"))
            {
                System.out.print("How many numbers will you enter? ");
                int numberOfBytes = scan.nextInt();
                byte [] bytes = new byte[numberOfBytes];
                System.out.println("Enter bytes separated by spaces or newlines:");
                
                
                //stores user's integers in an array of integers
                for (int count = 0; count < numberOfBytes; count++)
                {
                    bytes[count] = scan.nextByte();
                }
                
                SecretString secret = new SecretString(bytes);
                
                System.out.print("Your message is: \"");
                
                for (int i = 0; i < secret.getLength(); i++)
                {
                    System.out.print(secret.getCharAt(i));
                }                
                
                System.out.println("\"");
            }
        }
    }
}