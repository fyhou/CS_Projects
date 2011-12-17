import java.util.*;
import java.io.*;

public class InputParser {
    Scanner scan; 
    
    
    public InputParser (String fileName) {
        try {
            scan = new Scanner(new File(fileName));
        } catch (Exception e) {};
    } 
    
    public ArrayList<String> getInput () {
        ArrayList<String> input = new ArrayList<String>();
        int i = 0; 
        
        while (scan.hasNextLine()) {
            input.add(scan.nextLine());  
        }
        
        return input;
    }
    
}
