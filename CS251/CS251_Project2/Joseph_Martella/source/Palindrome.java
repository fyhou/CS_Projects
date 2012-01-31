/**
 * CS 251 - Project 2 - Palindrome
 * reads in a sequence of characters from standard 
 * input using StdIn.readChar() and determines whether 
 * that sequence represents a Watson-Crick complemented 
 * palindrome: the {A, C, T, G}-sequence equals its 
 * reverse when you replace each base with its complement: 
 * A-T, C-G).
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date February 11, 2011
 *
 * @compile with javac Palindrome.java
 * @execute with echo input | java Palindrome
 */

public class Palindrome {
    public static void main (String[] args) {
        Deque<Character> deque = new Deque<Character>();
        String original = ""; 
        String palindrome = "";
        
        // reads in all data and enqueues each one
        while (!StdIn.isEmpty()) {
            char input = StdIn.readChar();
            deque.addFirst(input);
            
            original = original + input;
        }
        
        // removes the data backwards and flips it
        while (!(deque.isEmpty())) {
            char output = deque.removeFirst();

            // flips the pairs
            if (output == 'A')
                output = 'T';
            else if (output == 'T')
                output = 'A';
            else if (output == 'C')
                output = 'G';
            else if (output == 'G')
                output = 'C';
            
            palindrome = palindrome + output;
        }
        
        // compares the original String and palindrome String
        if (original.equals(palindrome))
            StdOut.println("true");
        else
            StdOut.println("false");
    }
}