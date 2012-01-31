import java.util.*;
import java.io.*;

public class WriteRecipeFile
{
    public static void main(String[] args)
    {
        File f = new File(args[0]);
        
        OutputStream o = null;
        PrintWriter p = null;
        
        try
        {
            o = new FileOutputStream(f);
            p = new PrintWriter(o);
        } catch (Exception e) {};
        
        Scanner s = new Scanner(System.in);
        int count = 0; 
        String temp = "";
        
        p.println("@recipe");
        
        while (!temp.equals("<cntrl-d>"))
        {
            temp = s.nextLine();
            
            if (temp.length() == 0)
            {  
                if (count == 0)
                {
                    p.println("@ingredients");
                    count++; 
                }
                
                else if (count == 1)
                {
                    p.println("@directions");
                }
            }
            else if (!temp.equals("<cntrl-d>"))
                p.println(temp);
        }
        
        try{
            p.close();
        } catch (Exception e) {};
    }
}