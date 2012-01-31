import java.util.*;
import java.io.*;

public class ReadRecipeFile
{
    public static void main(String[] args)
    {
        File f = new File(args[0]);
        Scanner s = new Scanner(System.in);
        
        try
        {
            s = new Scanner(f);
        } catch (Exception e) {};
        
        read(s);
    }
    
    private static void read(Scanner s)
    {    
        String temp = "";
        
        while (s.hasNextLine())
        {
            temp = s.nextLine();
            
            if (temp.length() != 0)
            {
                if (temp.charAt(0) == '@')
                {
                    System.out.println();
                }
                else
                    System.out.println(temp);
            }
            else
                System.out.println();
        }
        
        System.out.println();       
    }   
}
