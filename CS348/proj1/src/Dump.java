import java.util.*;
import java.io.*;

public class Dump {
    public Dump () {
    }
    
    public boolean save (String fileName, Hashtable<String, Hashtable<String,Model>> database, Hashtable<String,String> countries) {
        try {
            File file = new File(fileName);
            FileWriter fstream = new FileWriter(file);
            BufferedWriter out = new BufferedWriter(fstream);
            
            /*****************************************
              * 
              * 
              *        SAVING THE DATABASE 
              * 
              * 
              ******************************************/
            Enumeration keys = database.keys(); 
            String saveLine = "";
            int flag = 1;
            
            // iterates through the Makes
            while (keys.hasMoreElements()) {
                Object key = keys.nextElement();
                Hashtable<String, Model> models = database.get(key); 
                Enumeration otherKeys = models.keys();
                
                saveLine = saveLine + key.toString(); 
                flag = 1;
                
                // iterates through the Models
                while (otherKeys.hasMoreElements()) {
                    Object otherKey = otherKeys.nextElement();
                    Model model = models.get(otherKey);
                    
                    if (flag == 1) {
                        saveLine = saveLine + ":" + model.saveState();
                        flag = 0; 
                    }
                    else {
                        saveLine = saveLine + "!" + model.saveState();
                    }
                }
                
                saveLine = saveLine + "\n";           
            }
            
            saveLine = saveLine + "---\n";
            
            /*****************************************
              * 
              * 
              *        SAVING THE COUNTRIES 
              * 
              * 
              ******************************************/
            
            Enumeration cKeys = countries.keys(); 
            
            // iterates through the Makes
            while (cKeys.hasMoreElements()) {
                String cKey = (String) cKeys.nextElement();
                String country = countries.get(cKey); 
                
                saveLine = saveLine + cKey + ":" + country + "\n";
            }
            
            saveLine = saveLine + "$$$";
            
            // writes finished product to file
            out.write(saveLine);
            out.close();
            
        } catch (Exception e) {
            return false; 
        }
                            
        return true;
    }
    
    public ArrayList load (String fileName) {
        ArrayList<String> data = new ArrayList<String>();
        
        try {
            Scanner scan = new Scanner(new File(fileName));           
            
            while (scan.hasNextLine()) {
                data.add(scan.nextLine());  
            }
            
            return data; 
        } catch (Exception e) {
            return data; 
        }
    }
}