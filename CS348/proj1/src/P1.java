import java.util.*;
import java.io.*;

public class P1 {
    private Hashtable<String, Hashtable<String, Model>> database;       // make name is key, Hashtable of (modelName, Model) is value
    private Hashtable<String, String> countries;                        // make name is key, country name is value
    
    private boolean exFlag = false;
    private String writeString = "";
    
    public P1() {
        database  = new Hashtable(); 
        countries = new Hashtable(); 
    }
    
    public void run() {
        CommandParser parser = new CommandParser();
        
        System.out.println("CS348 Project 1");
        System.out.println("Please enter a command.  Enter 'help' for a list of commands.");
        System.out.println();
        System.out.print("> "); 
        
        Command cmd = null;
        while ((cmd = parser.fetchCommand()) != null) {
            
            boolean result=false;
            exFlag=false;
            
            // look for the command
            if (cmd.getCommand().equals("help")) {
                result = doHelp();           
            } 
            else if (cmd.getCommand().equals("add_make")) {
                String[] params = cmd.getParameters();
                result = addMake(params);
            } 
            else if (cmd.getCommand().equals("add_model")) {
                String[] params = cmd.getParameters();
                result = addModel(params);
            }
            else if (cmd.getCommand().equals("makes")) {
                String[] params = cmd.getParameters();
                result = printMakes(params);
            }
            else if (cmd.getCommand().equals("models")) {
                String[] params = cmd.getParameters();
                result = printModels(params);
            }
            else if (cmd.getCommand().equals("models_by_price")) {
                String[] params = cmd.getParameters();
                result = printModelsByPrice(params);
            }
            else if (cmd.getCommand().equals("makes_by_origin")) {
                String[] params = cmd.getParameters();
                result = printMakesByOrigin(params);
            }
            else if (cmd.getCommand().equals("ordered_models_per_make")) {
                String[] params = cmd.getParameters();
                result = printModelsOrdered(params);
            }
            else if (cmd.getCommand().equals("execute")) {
                String[] params = cmd.getParameters();
                exFlag = true;
                result = execute(params);
            }
            else if (cmd.getCommand().equals("save")) {
                String[] params = cmd.getParameters();
                result = save(params);
            }
            else if (cmd.getCommand().equals("load")) {
                String[] params = cmd.getParameters();
                result = load(params);
            }
            else if (cmd.getCommand().equals("exit")) {
                String[] params = cmd.getParameters();
                result = exit(params);
            }
            
            // process the result
            if (result == true) {
                System.out.println("Command executed successfully.\n");
            }
            else if (result == false) {
                System.out.println("Error.\n");
            }
            else {
            }
            
            exFlag = false;
            
            System.out.print("> "); 
        }        
    }
    
    /**
     * function executes a batch of commands given
     * by a file
     * 
     * @param - params: the parameters of the execute Command
     * @return - boolean: true if sucessful, false if not
     */
    public boolean execute(String[] p) {
        if (p.length == 2) {
            try {
                File file = new File(p[1]);
                FileWriter fstream = new FileWriter(file);
                BufferedWriter out = new BufferedWriter(fstream);
                
                // get commands line by line from the input file
                InputParser inputParser = new InputParser (p[0]); 
                ArrayList<String> rawCommands = inputParser.getInput();
                
                // make raw commands into Commands
                CommandParser parser = new CommandParser();
                
                ArrayList<Command> commands = new ArrayList<Command>(); 
                
                for (int i = 0; i < rawCommands.size(); i++) {
                    commands.add(parser.commandFromRawText(rawCommands.get(i)));
                }
                
                // iterate through each command, executing each one
                for (int i = 0; i < commands.size(); i++) {
                    Command cmd = commands.get(i); 
                    
                    writeString = writeString + "> " + cmd.executeString() + "\n";
                    
                    boolean result=false;
                    
                    // look for the command
                    if (cmd.getCommand().equals("help")) {
                        result = doHelp();           
                    } 
                    else if (cmd.getCommand().equals("add_make")) {
                        String[] params = cmd.getParameters();
                        result = addMake(params);
                    } 
                    else if (cmd.getCommand().equals("add_model")) {
                        String[] params = cmd.getParameters();
                        result = addModel(params);
                    }
                    else if (cmd.getCommand().equals("makes")) {
                        String[] params = cmd.getParameters();
                        result = printMakes(params);
                    }
                    else if (cmd.getCommand().equals("models")) {
                        String[] params = cmd.getParameters();
                        result = printModels(params);
                    }
                    else if (cmd.getCommand().equals("models_by_price")) {
                        String[] params = cmd.getParameters();
                        result = printModelsByPrice(params);
                    }
                    else if (cmd.getCommand().equals("makes_by_origin")) {
                        String[] params = cmd.getParameters();
                        result = printMakesByOrigin(params);
                    }
                    else if (cmd.getCommand().equals("ordered_models_per_make")) {
                        String[] params = cmd.getParameters();
                        result = printModelsOrdered(params);
                    }
                    else if (cmd.getCommand().equals("save")) {
                        String[] params = cmd.getParameters();
                        result = save(params);
                    } 
                    else if (cmd.getCommand().equals("load")) {
                        String[] params = cmd.getParameters();
                        result = load(params);
                    }
                    else if (cmd.getCommand().equals("exit")) {
                        String[] params = cmd.getParameters();
                        result = exit(params);
                    }
                    
                    // process the result
                    if (result) {
                        writeString = writeString + "Command executed successfully.\n\n";
                    }
                    else {
                        writeString = writeString + "Error.\n\n";
                    }
                } 
                
                out.write(writeString);
                out.close();
                return true; 
            } catch (Exception e) {}
            
            return true;
        }
        else {
            return false;
        }           
    }
    
    private boolean doHelp() {
        System.out.println("add_make MAKE COUNTRY - add a car of MAKE made in COUNTRY");
        System.out.println("add_model NAME MAKE YEAR PRICE - add a model of a car named NAME by MAKE in YEAR valued at PRICE");
        System.out.println("makes - print a listing of all makes in the DB");
        System.out.println("models - print a listing of all models in the DB");
        System.out.println("models_by_price OP PRICE - print a listing of models in the DB, filtered by price");
        System.out.println("makes_by_origin COUNTRY - print a listing of makes in the DB, filtered by country");
        System.out.println("save FILENAME - save the contents of the DB to FILENAME");
        System.out.println("load FILENAME - load the contents of the DB from FILENAME");
        System.out.println("exit - goodbye!");        
        return true;
    }
    
    /**
     * function adds a new Make to the database
     * 
     * @param - params: the parameters of the Command
     * @return - boolean: true if sucessful, false if not
     */
    private boolean addMake(String[] params) {
        // checks to see if the number of parameters are appropriate 
        if (params.length == 2) {
            // checks both paramaters to see if they are alphanumeric
            if (params[0].matches("[a-zA-z0-9]*") && params[1].matches("[a-zA-z0-9]*")) {
                String make    = params[0];      // name of the Make
                String country = params[1];      // name of the country
                
                // checks if make is already in database
                if (countries.containsKey(make)) {
                    return false;
                }
                else { 
                    Hashtable models = new Hashtable();            // Hashtable of (modelName, Models)
                    
                    database.put(make, models);                    // adds key, value pair of the new make and a list of models
                    countries.put(make, country);                  // adds key, value pair of name of make and name of country
                    
                    return true;
                }
            }          
            else {
                return false;
            }
        }
        else { 
            return false;
        }
    }
    
    /**
     * function adds a new Model to the database
     * 
     * @param - params: the parameters of the Command
     * @return - boolean: true if sucessful, false if not
     */
    private boolean addModel(String[] params) {
        // checks to see if the number of parameters are appropriate 
        if (params.length == 4) {
            // checks both paramaters to see if they are alphanumeric
            if (params[0].matches("[a-zA-z0-9]*") && params[1].matches("[a-zA-z0-9]*") && isInteger(params[2]) && isInteger(params[3])) {
                String name = params[0];                     // name of the Model
                String makeString = params[1];               // Make of the Model
                int year    = Integer.parseInt(params[2]);   // year Model was made
                int price   = Integer.parseInt(params[3]);   // price of Model
                
                // checks if make is already in database
                if (countries.containsKey(makeString)) {
                    Hashtable models = (Hashtable) database.get(makeString);    // list of Models associated with Make
                    
                    // construct the Make of the Model, and construct the Model
                    Make theMake = new Make (makeString, (String) countries.get(makeString));
                    Model newModel = new Model(name, theMake, year, price);
                    
                    // if model name is already in list
                    if (models.containsKey(name)) {
                        return false; 
                    }
                    // if model name is not in list yet
                    else {
                        models.put(name, newModel);
                        database.put(makeString, models);
                        return true;
                    }
                }
                else {
                    return false; 
                }
            }          
            else {
                return false;
            }
        }
        else { 
            return false;
        }
    }
    
    /**
     * function prints all the Makes
     * 
     * @params - params: paramaters of the Command
     * @return - boolean: true if successful, false if not
     */
    public boolean printMakes(String[] params) {
        // checks to see if the number of parameters are appropriate
        if (params.length == 0) {
            Enumeration keys = countries.keys(); 
            
            // iterates through the Makes
            while (keys.hasMoreElements()) {
                String key = (String) keys.nextElement();
                String country = countries.get(key); 
                
                if (!exFlag) {
                    System.out.println(key + " " + country);
                }
                else {
                    writeString = writeString + key + " " + country + "\n";
                }
            }
            
            return true;
        }
        else {
            return false;
        }
    }
    
    /**
     * function prints all the Models
     * 
     * @params - params: paramaters of the Command
     * @return - boolean: true if successful, false if not
     */
    public boolean printModels(String[] params) {
        // checks to see if the number of parameters are appropriate
        if (params.length == 0) {
            Enumeration keys = database.keys(); 
            
            // iterates through the Makes
            while (keys.hasMoreElements()) {
                Object key = keys.nextElement();
                Hashtable<String, Model> models = database.get(key); 
                Enumeration otherKeys = models.keys();
                
                // iterates through the Models
                while (otherKeys.hasMoreElements()) {
                    Object otherKey = otherKeys.nextElement();
                    Model model = models.get(otherKey);
                    
                    if (!exFlag) {
                        System.out.println(model.toString());
                    }
                    else {
                        writeString = writeString + model.toString() + "\n";
                    }
                }
                
            }
            
            return true;
        }
        else {
            return false;
        }
    }
    
    /**
     * function prints the Models by price
     * 
     * @params - params: paramaters of the Command 
     * @return - boolean: true if successful, false if not
     */
    public boolean printModelsByPrice(String[] params) {
        // checks to see if the number of parameters are appropriate
        if (params.length == 2) {
            if ((params[0].equals("<") || params[0].equals(">") || params[0].equals("=")) && isInteger(params[1])) {
                int comparePrice = Integer.parseInt(params[1]);
                Enumeration keys = database.keys(); 
                
                // iterates through the Makes
                while (keys.hasMoreElements()) {
                    Object key = keys.nextElement();
                    Hashtable<String, Model> models = database.get(key); 
                    Enumeration otherKeys = models.keys();
                    
                    // iterates through the Models
                    while (otherKeys.hasMoreElements()) {
                        Object otherKey = otherKeys.nextElement();
                        Model model = models.get(otherKey);
                        
                        // prints the Model iff price falls under appropriate condition specified by user
                        if (params[0].equals("<")) {
                            if (model.getPrice() < comparePrice) {
                                if (!exFlag) {
                                    System.out.println(model.getName());
                                }
                                else {
                                    writeString = writeString + model.getName() + "\n";
                                }
                            }
                        }
                        else if (params[0].equals(">")) {
                            if (model.getPrice() > comparePrice) {
                                if (!exFlag) {
                                    System.out.println(model.getName());
                                }
                                else {
                                    writeString = writeString + model.getName() + "\n";
                                }
                            }
                        }
                        else {
                            if (model.getPrice() == comparePrice) {
                                if (!exFlag) {
                                    System.out.println(model.getName());
                                }
                                else {
                                    writeString = writeString + model.getName() + "\n";
                                }
                            }
                        }
                    }
                    
                }
                
                return true;
            }
            else {
                return false;    
            }
        }
        else {
            return false;
        }
    }
    
    /** 
     * function prints the Makes made by an origin
     * 
     * 
     * @params - params: paramaters of the Command
     * @return - boolean: true if successful, false if not
     */
    public boolean printMakesByOrigin(String[] params) {
        // checks to see if the number of parameters are appropriate
        if (params.length == 1) {
            if(params[0].matches("[a-zA-z0-9]*")) {
                Enumeration keys = countries.keys(); 
                
                // iterates through the Makes
                while (keys.hasMoreElements()) {
                    String key = (String) keys.nextElement();
                    String country = countries.get(key); 
                    
                    // if Make is from country specified by user, print it
                    if (country.equals(params[0])) {
                        if (!exFlag) {
                            System.out.println(key);
                        }
                        else {
                            writeString = writeString + key + "\n";
                        }
                    }
                }
                
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    
    /**
     * 
     * function prints all the Models in an ordered fashion
     * 
     * @params - params: paramaters of the Command
     * @return - boolean: true if successful, false if not
     */
    public boolean printModelsOrdered(String[] params) {
        // checks to see if the number of parameters are appropriate
        if (params.length == 1) {
            if(params[0].matches("[a-zA-z0-9]*")) {
                ArrayList<Model> allModels = new ArrayList(); 
                Enumeration keys = database.keys(); 
                
                // iterates through the Makes
                while (keys.hasMoreElements()) {
                    Object key = keys.nextElement();
                    
                    if (key.equals(params[0])) {
                        Hashtable<String, Model> models = database.get(key); 
                        Enumeration otherKeys = models.keys();
                        
                        // iterates through the Models of the Make specified by the user
                        while (otherKeys.hasMoreElements()) {
                            Object otherKey = otherKeys.nextElement();
                            Model model = models.get(otherKey);
                            allModels.add(model);
                        } 
                    } 
                    else {
                        continue;
                    }
                }
                
                // sorts the Models
                Collections.sort(allModels); 
                
                // iterates through the Models and prints them
                for (int i = 0; i < allModels.size(); i++) {
                    Model currentModel = allModels.get(i);
                    
                    if (!exFlag) {
                        System.out.println(currentModel.getName() + " " + currentModel.getPrice());
                    }
                    else {
                        writeString = writeString + currentModel.getName() + " " + currentModel.getPrice() + "\n"; 
                    }
                }
                
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    
    /**
     * 
     * function saves all the data to a file
     * 
     * @params - params: paramaters of the Command
     * @return - boolean: true if successful, false if not
     */
    public boolean save(String[] params) {
        if (params.length == 1) {
            Dump saver = new Dump();
            saver.save(params[0], database, countries);
            
            return true;
        }
        else {
            return false;
        }
    }
    
    /**
     * 
     * function loads data from a file
     * 
     * @params - params: paramaters of the Command
     * @return - boolean: true if successful, false if not
     */
    public boolean load(String[] params) {
        if (params.length == 1) {
            Dump loader = new Dump();
            
            ArrayList<String> data = loader.load(params[0]);
            
            database.clear();
            countries.clear();
            
            String curr = "";
            
            boolean tableFlag = true;   // true for database, false for countries
            
            for (int i = 0; i < data.size(); i++) {
                curr = data.get(i);
                
                if (curr.equals("---")) {
                    tableFlag = false;
                }
                else if (curr.equals("$$$")) {
                    break;
                }
                else if (tableFlag) {
                    String[] parts = curr.split(":");
                    
                    if (parts.length == 1) {
                        // no Models, so add Make and empty Model table
                        Hashtable<String, Model> modelTable = new Hashtable<String,Model>();
                        database.put(parts[0], modelTable);
                    }
                    else {
                        // splits Make and Model info
                        String[] models = parts[1].split("!");
                        Hashtable<String, Model> modelTable = new Hashtable<String,Model>(); 
                        
                        // builds each Model
                        for (int j = 0; j < models.length; j++) {
                            String[] modelParts = models[j].split(",");
                            Make modelMake = new Make(modelParts[1], modelParts[2]);
                            
                            Model model = new Model(modelParts[0], modelMake, Integer.parseInt(modelParts[3]), Integer.parseInt(modelParts[4]));
                            modelTable.put(modelParts[0], model);
                        }
                        
                        // adds the Make and the Models of that Make back into database
                        database.put(parts[0], modelTable);
                    }
                }
                else if (!tableFlag) {
                    String[] parts = curr.split(":");
                    
                    countries.put(parts[0], parts[1]);
                }
            }
            
            return true;
        }
        else {
            return false;
        }
    }
    
    /**
     * 
     * function closes the program
     * 
     * @params - params: paramaters of the Command
     * @return - boolean: true if successful, false if not
     */
    public boolean exit(String[] params) {
        if (params.length == 0) {
            System.exit(0);
            return true;
        }
        else {
            return false;
        }
    }
    
    /**
     * @param args
     */
    public static void main(String[] args) {
        new P1().run();
    }
    
    /**
     * function checks if String is an integer
     * 
     * @param - i: the String to check
     * @return - boolean: true if yes, false if no
     */
    private static boolean isInteger (String i) {
        try {
            Integer.parseInt(i);
            return true;
        } catch (NumberFormatException e) {
            return false; 
        }
        
    }
    
}
