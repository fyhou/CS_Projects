/**
 * CS 251 - Project 6 - Move to Front 
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date April 18, 2011
 *
 * @compile with javac -classpath .:stdlib.jar:algs4.jar MoveToFront.java
 * @execute with java  -classpath .:stdlib.jar:algs4.jar MoveToFront - < input.txt (compress)
 * @execute with java  -classpath .:stdlib.jar:algs4.jar MoveToFront + < input.txt (expand)
 * 
 */

import java.util.*;

public class MoveToFront {
    /**
     * apply move-to-front encoding, 
     * reading from standard input and 
     * writing to standard output
     */
    public static void encode() {
        // makes list of ascii values
        LinkedList<Integer> list = new LinkedList<Integer>();
        for (int i = 0; i < 256; i++) {
            list.add(i, new Integer(i));
        }
        
        // reads input 
        String s = BinaryStdIn.readString();
        char[] input = s.toCharArray();
        
        // does the MTF
        for (int i = 0; i < input.length; i++) {
            char ch = s.charAt(i);                   // character to search for
            Integer c = (Integer) ((int) ch);        // char to Integer value
            byte index = (byte) list.indexOf(c);     // index where Integer occurs      
            int superIndex = (int) list.indexOf(c);
            
            BinaryStdOut.write(index);
            BinaryStdOut.flush();
            
            Integer toMove = list.remove(superIndex);      // remove element and then
            list.addFirst(toMove);                         // add element to front of list
        }
    }
    
    /**
     * apply move-to-front decoding, 
     * reading from standard input and 
     * writing to standard output
     */
    public static void decode() {
        // makes list of ascii values
        LinkedList<Integer> list = new LinkedList<Integer>();
        for (int i = 0; i < 256; i++) {
            list.add(i, new Integer(i));
        }
        
        // reads input 
        String s = BinaryStdIn.readString();
        char[] input = s.toCharArray();
        
        // decode this message
        for (int i = 0; i < input.length; i++) {
            int index = input[i];
            Integer in = list.remove(index);
            list.addFirst(in);
            
            // write character
            int value = in.intValue();
            char c = (char) value;
            System.out.print(c);
        }
        System.out.println();
    }
    
    /**
     * if args[0] is '-', apply move-to-front encoding
     * if args[0] is '+', apply move-to-front decoding
     */
    public static void main(String[] args) {
        if      (args[0].equals("-"))
            encode();
        if (args[0].equals("+"))
            decode();
    }
}