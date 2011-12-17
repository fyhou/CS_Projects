/**
 * CS 251 - Project 1 - PercolationStats
 * Program uses PercolationVisualizer to 
 * randomly create systems until they 
 * Percolate and estimate the p* value.
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date January 31, 2011
 *
 * @compile with javac -classpath .:stdlib.jar PercolationStats.java
 * @execute with java -classpath .:stdlib.jar PercolationStats N T (fast or slow)
 */

public class PercolationStats {
    
    /**
     * Main method takes three arguments, n,t, and speed;
     * n is the size of the matrix; t is the repetitions,
     * speed determines which implementation of union-find
     * to use.
     */
    public static void main (String[] args) {
        int n = Integer.parseInt(args[0]);          // the size of the square grid
        int t = Integer.parseInt(args[1]);          // repetitions of process
        String speed = args[2];                     // slow = quick find; fast = weighted union find
        double[] sitesOpen = new double[t];         // how many open sites
        double[] thresholds = new double[t];        // stores threshold values (p* = sitesOpen / n^2)
        double[] time = new double[t];              // stores time of each repition
        
        // stats to calculate
        double avgThreshold = 0;                    // average threshold value
        double standardDev = 0;                     // standard deviation of threshold values   
        double totalTime = 0;                       // total time
        double averageTime = 0;                     // average time
        double standardDevTime = 0;                 // standard deviation of time
        
        int extra = n+2;                            // to use ghost rows
        
        Percolation percolater = new Percolation (extra, speed);
        
        int[] xA = new int[n*n];

        // performs test t amount of times, each
        // time with a new system and a different 
        // set of open spaces.        
        for (int reps = 0; reps < t; reps++) {
            // System.out.println(reps);
            // creates new, blocked grid to test
            percolater = new Percolation (extra, speed);
            boolean go = false;   
            
            for (int i = 0; i < n*n; i++) {
                xA[i] = i;
            }
            
            StdRandom.shuffle(xA);
            
            for (int i = 0; i < n; i++) {
                percolater.open(i,0);
                percolater.open(i,extra-1);
            }
            
            // y*n + x
            // 4x4
            // 12 13 14 15
            // 8  9  10 11
            // 4  5  6  7
            // 0  1  2  3
            
            // modNum = 6 mod 4 = 2
            // divNum = 6 div 4 = 1
            // (x,y) = (modNum, divNum)
            
            // 15 mod 4 = 3
            // 15 div 4 = 3
            
            int modNum = 0;
            int divNum = 0;
            int x = 0;
            int y = 0;
            int i = 0;
                      
            Stopwatch timer = new Stopwatch();
            // keeps opening random boxes until system percolates
            while (!go) {
                // generates random row and column to open             
                modNum = xA[i] % n;
                divNum = xA[i] / n;
                i++;
                
                x = modNum+1;
                y = divNum+1;
                
                // makes sure random spot is closed before
                // trying to open and increment value
                percolater.open(x,y);
                sitesOpen[reps]++;   
                
                time[reps] = timer.elapsedTime();
                
                // if system percolates, calculates p* value
                //if (sitesOpen[reps] > n) {
                    if (percolater.percolatesX()) {
                        thresholds[reps] = (sitesOpen[reps] / (double)(n*n));
                        go = true;
                    }
                //}
            }
        }
        
        //////////////////////////////
        //// Calculation of Stats ////
        //////////////////////////////
      
        // calculates the average threshold 
        avgThreshold = StdStats.mean(thresholds);
        
        // calculates the standard deviation
        standardDev = StdStats.stddev(thresholds);
        
        // calculates total time
        for (int i = 0; i < t; i++) {
            totalTime += time[i];
        }
        
        // calculates average time of experiment
        averageTime = StdStats.mean(time);
        
        // calculates standard deviation of time
        standardDevTime = StdStats.stddev(time);
        
         
        //////////////////////
        //// Prints Stats ////
        //////////////////////
        
        System.out.println("mean threshold = " + avgThreshold);
        System.out.println("std dev = " + standardDev);
        System.out.println("time = " + totalTime);
        System.out.println("mean time = " + averageTime);
        System.out.println("stddev time = " + standardDevTime);
        
    }
}