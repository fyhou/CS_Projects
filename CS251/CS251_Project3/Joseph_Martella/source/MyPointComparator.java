/**
 * CS 251 - Project 3 - MyPointComparator
 * Compares two points' x coordinate values
 * and determines which one is less.
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date February 25, 2011
 *
 * @compile with javac MyPointComparator.java
 * @execute with not applicable 
 */
import java.util.*;

public class MyPointComparator implements Comparator<Point> {
    /**
     * Given two partially ordered sets A and B, the lexicographical 
     * order on the Cartesian product A ? B is defined as
     * (a,b) ² (a?,b?) if and only if a < a? or (a = a? and b ² b?).
     * 
     * @param that point being compared
     * @return -1 if one comes before two
     * @return 1  if one comes after two
     * @return 0  if the x coordinates are equal
     */
    public int compare(Point one, Point two) {
        if (one.getX() < two.getX()) return -1;
        if (one.getX() > two.getX()) return 1;
        if (one.getY() < two.getY()) return -1;
        if (one.getY() > two.getY()) return 1;
        return 0;
    }
}