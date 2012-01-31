/*************************************************************************
 * Compilation:  javac Point.java
 *
 * Description: An immutable data type for points in the plane.
 *
 *************************************************************************/
import java.util.*;

public class Point {
    private int x;                        // x coordinate
    private int y;                        // y coordinate
    private double angle = -20000000;     // angle it makes with an 'origin'

    // constructor
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * determines if the 3 given points
     * are collinear
     * 
     * @param p,q,r Points to be compared
     * @return true if they are, false if not
     */
    public static boolean areCollinear(Point p, Point q, Point r) {
        double qxRatio = q.x - p.x;
        double rxRatio = r.x - p.x;
        double qyRatio = q.y - p.y;
        double ryRatio = r.y - p.y;
        
        if (qxRatio == 0 && rxRatio == 0) return true;
        
        if (qyRatio/qxRatio == ryRatio/rxRatio) {
            return true;
        }
        
        return false;
    }

    /**
     * determines if the 4 given points
     * are collinear
     * 
     * @param p,q,r,s Points to be compared
     * @return true if they are, false if not
     */
    public static boolean areCollinear(Point p, Point q, Point r, Point s) {
        if (areCollinear(p,q,r)) {
            double qxRatio = q.x - p.x;
            double rxRatio = r.x - p.x;
            double sxRatio = s.x - p.x; 
            double qyRatio = q.y - p.y;
            double ryRatio = r.y - p.y;      
            double syRatio = s.y - p.y; 
            
            if (qxRatio == 0 && rxRatio == 0 && sxRatio == 0) return true;
            
            if (syRatio/sxRatio == ryRatio/rxRatio) {  
                return true;
            }
        }
        
        return false;
    }

    // plot this point using StdDraw
    public void draw() {
        StdDraw.point(x, y);
    }

    // draw line from this point to that point using standard draw
    public void drawTo(Point that) {
        StdDraw.line(this.x, this.y, that.x, that.y);
    }

    // return string representation of this point
    public String toString() {
        return "(" + x + ", " + y + ")";
    }
    
    /**
     * gets the x value of a point
     * 
     * @return x value
     */
    public int getX() {
        return x;
    }
    
    /**
     * gets the y value of a point
     * 
     * @return y value
     */
    public int getY() {
        return y;
    }
    
    /**
     * gets the angle 
     * 
     * @return angle
     */
    public double getAngle() {
        return angle;
    }
    
    /**
     * sets the angle
     * 
     * @param angle
     */
    public void setAngle(double angle) {
        this.angle = angle;
    }
}