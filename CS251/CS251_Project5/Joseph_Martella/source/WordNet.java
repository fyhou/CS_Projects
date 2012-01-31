/**
 * CS 251 - Project 5 - WordNet
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date April 9, 2011
 *
 * @compile with javac -classpath .:algs4.jar WordNet.java
 * @execute with java  -classpath .:algs4.jar WordNet "synset_file" "hypernyms_file" "input_test"
 */

import java.util.*;
import java.io.*;

public class WordNet {
    private Hashtable<String, String> nounTable  = new Hashtable<String, String>();
    private Hashtable<Integer, String>   idTable = new Hashtable<Integer, String>();
    public SAP sap;
    
    /**
     * constructor takes the name of the two input files
     */
    public WordNet(String synsets, String hypernyms) {
        File syn_f  = new File (synsets);
        File hyp_f  = new File (hypernyms); 
        
        In scan_syn = new In (syn_f);
        In scan_hyp = new In (hyp_f);
        
        int count = 1;
        
        // reads the synset file, splits up each line into 
        // id, synset, and glossary. glossary is ignored because
        // it is not needed. id is parsed to an int. synset are again
        // split to get each noun, then each noun is placed 
        while (!scan_syn.isEmpty()) {
            count++;
            
            String line = scan_syn.readLine();
            String[] idANDsynset = line.split(",");
           
            Integer id = Integer.parseInt(idANDsynset[0]);
            String[] nouns = idANDsynset[1].split(" ");
            
            // puts nouns into hash table so word look up 
            // is easy later
            int length = nouns.length; 
            for (int i = 0; i < length; i++) {
                if (nounTable.get(nouns[i]) == null) 
                    nounTable.put(nouns[i], id.toString()); 
                else 
                    nounTable.put(nouns[i], nounTable.get(nouns[i]) + "," + id.toString());
            }     
            
            // puts synsets into hash table to determine
            // ancestors later
            idTable.put(id, idANDsynset[1]);
        }
        
        // reads the hypernyms file, and creates
        // a Digraph
        Digraph G = new Digraph (count);
        while (!scan_hyp.isEmpty()) {
            String line = scan_hyp.readLine();
            String[] ids = line.split(",");
            
            int v = Integer.parseInt(ids[0]);
            
            for (int i = 1; i < ids.length; i++) {
                int w = Integer.parseInt(ids[i]);
                G.addEdge(v,w);
            }  
        }    
        
        sap = new SAP (G);     
    }
    
    /**
     * is the word a WordNet noun? This can be used to search for existing
     * nouns at the beginning of the printSap method
     * 
     * @param word word to check
     * @return boolean true if word, false if not
     */
    public boolean isNoun(String word) {
        String id = (String) nounTable.get(word);         // searches for word in nounTable, if it 
                                                          // is in there, there'll be a non-null String returned
        if  (id != null)
            return true;
        else 
            return false;
    }
    
   /** 
    * print the synset (second field of synsets.txt) that is the common ancestor
    * of nounA and nounB in a shortest ancestral path as well as the length of the path,
    * following this format: "sap<space>=<space><number>,<space>ancestor<space>=<space><synsettext>"
    * If no such path exists the sap should contain -1 and ancestor should say "null"
    * This method should use the previously defined SAP datatype
    * 
    * @param String nounA first word 
    * @param String nounB second word
    */
    public void printSap(String nounA, String nounB) {
        String v = (String) nounTable.get(nounA);
        String w = (String) nounTable.get(nounB);
        
        // if word is not in WordNet, then exit
        if (v == null || w == null) {
            StdOut.println("sap = -1, ancestor = null");
            return;
        }
        
        // partitions possible synset IDs
        String[] vs = v.split(",");
        String[] ws = w.split(",");
        
        int v_int = 0, w_int = 0, length = 0, ancestorID = 0;
        boolean first = false;
        
        // goes through each combination of synset
        // IDs for both nouns, trying to find SAP
        for (int i = 0; i < vs.length; i++) {
            v_int = Integer.parseInt(vs[i]);
            for (int j = 0; j < ws.length; j++) {       
                w_int = Integer.parseInt(ws[j]);
                
                int _length     = sap.length(v_int,w_int);        // length using current v and w
                
                if(!first) {                                      // if it's the first one, it's our path and by 
                    length = _length;                             // default, the SAP ancestor of them is the 
                    first = true;                                 // ancestor
                    ancestorID = sap.ancestor(v_int,w_int);
                }
                else {                                            // if not the first one, i check if the new length
                    if (_length < length) {                       // is shorter than the shortest; if it is, i set the 
                        length = _length;                         // shortest length to the current one and get the ID
                        ancestorID = sap.ancestor(v_int,w_int);   // of the ancestor between the two IDs
                    }
                }        
            }
        }
        
        String ancestor = (String) idTable.get(ancestorID);               // gets the synset of the ancestor ID
        
        StdOut.println("sap = " + length + ", ancestor = " + ancestor);
        
    }
    
    /**
     * main method to test functionality
     * 
     * @command line args[0] synset file
     * @command line args[1] hypernyms file
     * @command line args[2] input test file
     */
    public static void main (String[] args) {
        WordNet net  = new WordNet (args[0], args[1]);
        File input   = new File (args[2]);
        In   scan_in = new In (input);
        
        while (!scan_in.isEmpty()) {
            String line = scan_in.readLine();
            String[] nouns = line.split(" ");
            net.printSap(nouns[0], nouns[1]);
        }       
    }
}