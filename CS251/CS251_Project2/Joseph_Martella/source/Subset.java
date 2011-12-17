/**
 * CS 251 - Project 2 - Subset
 * Takes a command-line argument k, reads in
 * a sequence of strings from standard input,
 * and prints out exactly k of them, uniformly
 * at random.
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date February 11, 2011
 *
 * @compile with javac Subset.java
 * @execute with echo input | java Subset k
 */

public class Subset {
    public static void main (String[] args) {
        RandomizedQueue<String> rq = new RandomizedQueue<String>();  // RandomizedQueue to hold input
        int k = Integer.parseInt(args[0]);                           // number of inputs to be printed
        int count = 0;                                               // number of input strings
        // reads in all data and enqueues each one
        while (!StdIn.isEmpty()) {
            String input = StdIn.readString();
            rq.enqueue(input);
            count++;
        }
        
        // checks if there are enough elements in queue to perform 
        if (k > count) {
            StdOut.println("Error: size of subset can't be larger than number of elements");
            System.exit(1);
        }
        
        // loops k amount of times, dequeues a random
        // item and prints
        for (int i = 0; i < k; i++) {
            StdOut.println(rq.dequeue());
        }
    }
}