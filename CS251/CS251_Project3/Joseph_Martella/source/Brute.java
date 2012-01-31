/**
 * CS 251 - Project 3 - Brute
 * Examines 4 points at a time and checks
 * if they all lie on the same line segment, 
 * printing out any such line segments to 
 * standard output and plotting them using 
 * standard draw.
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date February 25, 2011
 *
 * @compile with javac Brute.java < input.txt
 * @execute with java Brute
 */
import java.util.*;

public class Brute {
    public static void main (String[] args) {
        Point points[] = PointPlotter.main(null);         // returns input points
        int N = points.length;                            // number of points 
        
        /**
         * code below gets every combination
         * of four of the input points given; if they are found
         * to be collinear, they are sorted and printed using the
         * print function at the bottom.
         */        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) { 
                    break; 
                }
                for (int k = 0; k < N; k++) {
                    if (j == k || i == k) {
                        break;
                    }
                    for (int m = 0; m < N; m++) {
                        if (m == i || m == j || m == k) 
                            break;
                        else {
                            if(Point.areCollinear(points[i],points[j],points[k], points[m])) {
                                print(points[i],points[j],points[k], points[m]);
                            }
                        }
                    }
                }
            }
        }
    }
    
    /**
     * sorts and prints Points that are
     * found to be collinear
     * 
     * @param p,q,r,s Points to be compared
     * @return void
     */
    private static void print (Point p, Point q, Point r, Point s) {
        Point[] points = {p,q,r,s};
        Arrays.sort(points, new MyPointComparator());
        
        // prints out the points in the order they appear on the screen
        StdOut.println ("4: " + points[0].toString() + " -> " + points[1].toString() + " -> " + 
                        points[2].toString() + " -> " + points[3].toString());
        
        // draws the line segment
        points[0].drawTo(points[3]);
        StdDraw.show(0);
    }
}