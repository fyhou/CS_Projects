/**
 * CS 251 - Project 6 - Burrows Wheeler
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date April 18, 2011
 *
 * @compile with javac -classpath .:stdlib.jar:algs4.jar BurrowsWheeler.java
 * @execute with java  -classpath .:stdlib.jar:algs4.jar BurrowsWheeler - < input.txt (compress)
 * @execute with java  -classpath .:stdlib.jar:algs4.jar BurrowsWheeler + < input.txt (expand)
 * 
 */

import java.util.*;

public class BurrowsWheeler {
    public static String s;
    /**
     * apply Burrows-Wheeler encoding, reading from 
     * standard input and writing to standard output
     */
    public static void encode () {
        // read the input
        s = BinaryStdIn.readString();
        char[] input = s.toCharArray();

        int[] indices = new int[input.length];
        for (int i = 0; i < indices.length; i++) {
            indices[i] = i;
        }
        
        Quick.sort(indices, s);
        
        // create t[] and find where original ended up
        char[] t     = new char[input.length];      // last column in suffix sorted list
        int inputPos = 0;                           // row number where original String ended up
        
        for (int i = 0; i < indices.length; i++) {
            int index = indices[i];
            
            // finds row number where original String ended up
            if (index == 0)
                inputPos = i;
            
            if (index > 0)
                t[i] = s.charAt(index-1);
            else
                t[i] = s.charAt(indices.length-1);
        }
        
        
        // write t[] preceded by the row number where orginal String ended up
        BinaryStdOut.write(inputPos);
        for (int i = 0; i < t.length; i++) {
            BinaryStdOut.write(t[i]);
            BinaryStdOut.flush();
        }       
    }
    
    /**
     * less() method used in Quick.java to sort
     * array of indices
     */
    public static boolean less (int a, int b, String s) {
        int N = s.length();
        String v;
        String w;
        
        // construct suffix to compare
        if (a > 0) 
            v = s.substring(a,N) + s.substring(0, a);
        else
            v = s.substring(a,N);
        
        // construct suffix to compare
        if (b > 0) 
            w = s.substring(b,N) + s.substring(0, b);
        else
            w = s.substring(b,N);
        
        // is v less than v?
        if (v.compareTo(w) < 0)
            return true;
        else 
            return false;
    }
    
    /**
     * apply Burrows-Wheeler decoding, reading from 
     * standard input and writing to standard output
     */
    public static void decode () {
        // read the input
        int firstThing = BinaryStdIn.readInt();
        s = BinaryStdIn.readString();
        char[] t           = s.toCharArray();
        char[] firstColumn = new char[t.length];
        int [] next        = new  int[t.length];
        
        // copy array and sort
        for (int i = 0; i < t.length; i++) {
            firstColumn[i] = t[i];
        }
        Arrays.sort(firstColumn);
            
        // decode
        int N = t.length;
        int [] count = new int[256];
        
        // counts frequency of each letter
        for (int i = 0; i < N; i++) {
            count[t[i]]++;
        }
         
        int m = 0, j = 0;
        
        // fills the next[] array with appropriate values
        while (m < N) {
            int _count = count[firstColumn[m]];
            while (_count > 0) {
                if (t[j] == firstColumn[m]) {
                    next[m++] = j;
                    _count--;
                }
                j++;
            }
            j = 0;
        }
        
        // decode the String
        int _next = next.length;
        int    _i = firstThing;
        for (int i = 0; i < _next; i++) {
            _i = next[_i];
            System.out.print(t[_i]);
        }  
        System.out.println();
    }
    
    /**
     * if args[0] is '-', apply Burrows-Wheeler encoding
     * if args[0] is '+', apply Burrows-Wheeler decoding
     */
    public static void main (String[] args) {
        if      (args[0].equals("-"))
            encode();
        if (args[0].equals("+"))
            decode();
    }
}