/**
 * CS 251 - Project 5 - SAP (Shortest Ancestral Path)
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date April 9, 2011
 *
 * @compile with javac -classpath .:algs4.jar SAP.java
 * @execute with java -classpath .:algs4.jar SAP "file_to_make_Digraph" "test_file"
 */

import java.io.*;

public class SAP {
    Digraph DAG;  // the digraph
    BreadthFirstDirectedPaths vBFS;  // BFS for vertex v
    BreadthFirstDirectedPaths wBFS;  // BFS for vertex w
    
    int last_v = -1;                 // last v used to find length
    int last_w = -1;                 // last w used to find length
    int oldAncestor = -1;            // ancestor between last used v and w
    int oldDistance = -1;            // distance of SAP between last used v and w
    
    /**
     * constructor for SAP using
     * a Digraph 
     * 
     * @param Digraph the digraph we're using
     */
    public SAP (Digraph G) {
        DAG = G; 
    }
    
    /**
     * finds length of SAP between v and w
     * 
     * @param int v the first vertex
     * @param int w the second vertex
     * @return int the length of the SAP between v and w (-1 if none)
     */
    public int length (int v, int w) {
        if (v < 0 || v > DAG.V()-1 || w < 0 || w >DAG.V()-1)
            return -1;
        
        if (v == last_v && w == last_w)
            return oldDistance;
        else {
            BreadthFirstDirectedPaths vBFS = new BreadthFirstDirectedPaths (DAG, v);
            BreadthFirstDirectedPaths wBFS = new BreadthFirstDirectedPaths (DAG, w);
            
            last_v = v;
            last_w = w;
            
            boolean hasAncestralPath = false;
            int min = -1;
            
            for (int i = 0; i < DAG.V(); i++) {                      // checks each vertex possible in the DAG
                if (vBFS.hasPathTo(i) && wBFS.hasPathTo(i)) {            // if both sources have path to vertex, check distance
                    if (!hasAncestralPath) {                         // if no path has been established yet, it is the min
                        hasAncestralPath = true;                        // distance and we set hasAncestralPath to true
                        min = vBFS.distTo(i) + wBFS.distTo(i);          // and set the length to the distance
                        oldAncestor = i;
                    }
                    else {                                           // if a path already exists, we determine if the new 
                        int dist = vBFS.distTo(i) + wBFS.distTo(i);      // found path is shorter, and if it is, we set that 
                        if (dist < min) {                                // distance to the new found one
                            min = dist;
                            oldAncestor = i;
                        }
                    }
                }
            }
            
            if (hasAncestralPath)         // if there is a SAP, return the distance of it
                return min;
            else {                        // if there isn't a SAP, return -1
                oldAncestor = -1;
                return -1;
            }
        }
    }
    
    /**
     * returns the common ancestor of v and w that participates in SAP
     * 
     * @param int v the first vertex
     * @param int w the second vertex
     * @return int the ancenstor (-1 if none)
     */
    public int ancestor (int v, int w) {
        if (v < 0 || v > DAG.V()-1 || w < 0 || w > DAG.V()-1)
            return -1;
        
        if (v == last_v && w == last_w)
            return oldAncestor;
        else {
            BreadthFirstDirectedPaths vBFS = new BreadthFirstDirectedPaths (DAG, v);
            BreadthFirstDirectedPaths wBFS = new BreadthFirstDirectedPaths (DAG, w);
            
            last_v = v;
            last_w = w;
            
            boolean hasAncestralPath = false;
            int min = -1;
            int ancestor = -1;
            
            for (int i = 0; i < DAG.V(); i++) {                      // checks each vertex possible in the DAG
                if (vBFS.hasPathTo(i) && wBFS.hasPathTo(i)) {            // if both sources have path to vertex, check distance
                    if (!hasAncestralPath) {                         // if no path has been established yet, it is the min
                        hasAncestralPath = true;                        // distance and we set hasAncestralPath to true
                        min = vBFS.distTo(i) + wBFS.distTo(i);          // and set the length to the distance
                        ancestor = i;
                    }
                    else {                                           // if a path already exists, we determine if the new 
                        int dist = vBFS.distTo(i) + wBFS.distTo(i);      // found path is shorter, and if it is, we set that 
                        if (dist < min) {                                // distance to the new found one
                            min = dist;
                            ancestor = i;  
                        }
                    }
                }
            }
            
            if (hasAncestralPath) {       // if there is a SAP, return the ancestor
                oldDistance = min;
                return ancestor;
            }
            else                          // if there isn't a SAP, return -1
                return -1;
        }
    }
    
    /**
     * main method to test functionality; constructs a Digraph using
     * an input file; then tests pairs of vertices from a different file;
     * main prints the SAP and ancestor of the pair of vertices if they exist
     * and prints -1 for both if they do not exist.
     * 
     * @command line args[0] file to make Digraph
     * @command line args[1] test input file
     */
    public static void main (String[] args) {
        File file = new File (args[0]);
        In     in = new In   (file);
        Digraph G = new Digraph (in);  
        SAP   sap = new SAP (G);
        
        File input = new File (args[1]);
        In    scan = new In   (input);
               
        while (!scan.isEmpty()) {
            int v = scan.readInt();
            int w = scan.readInt();
            
            StdOut.println("sap = " + sap.length(v,w) + ", ancestor = " + sap.ancestor(v,w));
        }
    }
}
