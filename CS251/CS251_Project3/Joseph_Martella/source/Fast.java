/**
 * CS 251 - Project 3 - Fast
 * Remarkably, it is possible to solve 
 * the problem much faster than the 
 * brute-force solution described above. 
 * Given a point p, the following method 
 * determines whether p participates 
 * in a set of 4 or more collinear points.
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date February 25, 2011
 *
 * @compile with javac Fast.java < input.txt
 * @execute with java Fast
 */
import java.util.*;

public class Fast {
    
    /**
     * An equality method I made to help determine 
     * if the tails of segments are identical to 
     * help deter the printing of sub segments.
     * 
     * @param a first comparison Point
     * @param b second comparison Point
     * @return boolean true if equal, false if not
     */
    private static boolean equal (Point a, Point b) {
        if (a.getX() == b.getX()) {
            if (a.getY() == b.getY()) {
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    
    public static void main (String[] args) {
        Point points[] = PointPlotter.main(null);         // returns input points
        int N = points.length;                            // number of points 
        SortedList list = new SortedList();               // SortedList to hold 'tails' of segments

        /**
         * This huge for loop's purpose is to determine
         * how many different line segments I have, how many
         * points are in each one, and the origin used to
         * obtain the line.
         */
        for (int j = 0; j < N; j++) {
            // sorts the array of points in order according to
            // the x axis first, then y axis; essentially sorts
            // in order from left to right as they'd appear on 
            // a graph. 
            Arrays.sort(points, new MyPointComparator());
            
            Point start = points[j];   // holds the origin value we are using for drawing

            /**
             * determines the angle each point makes with 
             * the origin simply using slope and the arctan
             * function supplied by Math
             */
            for (int i = j; i < N; i++) {
                if (i == j) continue;
                double xDiff = (double)(points[i].getX() - points[j].getX());
                
                // if xDiff is equal to 0, that means it is directly below
                // or above the origin with no defined slope; i gave this an
                // arbitrary value of -1000000 because that slope is impossible
                // with the 32k by 32k grid, yet still groups these points together
                if ( xDiff == 0.00)
                    points[i].setAngle(-1000000);
                else {
                    // slope formula
                    double tan = ((double)(points[i].getY() - points[j].getY())/xDiff);
                    double angleVal = Math.atan(tan);
                    
                    // pretty sure -0.00 is equal to 0.00 anyway,
                    // but couldn't hurt just to make sure
                    if (angleVal == -0.00) points[i].setAngle(0);
                    else points[i].setAngle(angleVal);
                }
            }
            
            // sorts the points so points with equal angle values
            // are together 
            Arrays.sort(points, new AnglePointComparator());            
            
            for (int i = j; i < N; i++) {
                int coPoints = 1;                     // number of points with the same angle
                double angle = points[i].getAngle();  // the angle i am looking for in the array of Points
                
                if (angle == -20000000) continue;  // used to ignore origin point
                
                /**
                 * traverses through array of Points, compares the key angle
                 * with the angle of each Point, if they are equal, we increment
                 * coPoints, which is essentially the number of points with
                 * equal angles; if there are 4 or more, we have a line segment
                 */
                for (int k = 1; k < N; k++) {
                    if (angle == points[k].getAngle()) {
                        coPoints++;
                    }
                }
                
                Point x = null;          // second last Point in segment
                Point y = null;          // last Point in segment
                int counter = 1;         // how many I hit so far
                
                /**
                 * if the number of points constitutes a line segment (>3),
                 * I then traverse through the array again and store the last
                 * two Points of the segment by comparing a counter to the 
                 * number of Points in the segment.
                 */
                if (coPoints > 3) {
                    for (int q = j; q < N; q++) {
                        
                        if (points[q].getAngle() == angle) {
                            counter++;
                            if (counter+1 == coPoints) {
                                x = points[q];
                            }
                            if (counter == coPoints) {
                                y = points[q];
                            }
                        }
                    }  
                    
                    SortedList.Link e = list.first;    // sets an arbitary Point e to first Link
                    boolean sub = false;               // true = sub segment, false = not sub segment
                    
                    /**
                     * traverses through the SortedList comparing the pairs of tails
                     * to determine if a longer segment with the same tail has already
                     * been printed; if so, we are currently dealing with a sub segment
                     * of that line and sub is set to true.
                     */
                    while (e != null) {
                        if (equal(x, e.xPoint) && equal(y,e.yPoint)) {
                            sub = true;
                        }
                        e = e.next;
                    }                  
                    
                    /**
                     * if it is a sub segment, skip to the next
                     * iteration of the loop
                     */
                    if (sub)
                        continue;
                    
                    /**
                     * if we are dealing with a new line segment,
                     * add its tail to the SortedList of tails to
                     * use as a comparison later
                     */
                    list.insert(x,y);
                    
                    /**
                     * This block is for printing and drawing purposes.
                     * A counter is used to determine when to print an 
                     * arrow and when we have hit the end of the segment
                     * since they can be of different sizes.
                     */
                    int count = 1;
                    StdOut.print(coPoints + ": " + points[0].toString() + " -> ");
                    for (int l = j; l < N; l++) {
                        if (points[l].getAngle() == angle) {
                            StdOut.print(points[l].toString());
                            count++;
                            
                            if (count < coPoints) 
                                StdOut.print(" -> ");
                            else {
                                StdOut.print("\n");
                                start.drawTo(points[l]);
                                StdDraw.show(0);
                            }
                        }
                    }
                }
            }
            
            // sets all angle values back to trivial value
            for (int i = 0; i < N; i++) {
                points[i].setAngle(-20000000);
            } 
        }
    }
}