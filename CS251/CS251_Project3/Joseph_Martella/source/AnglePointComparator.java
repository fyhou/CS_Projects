/**
 * CS 251 - Project 3 - AnglePointComparator
 * Compares the angles points make with
 * a designated origin.
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date February 25, 2011
 *
 * @compile with javac AnglePointComparator.java
 * @execute with not applicable 
 */
import java.util.*;

public class AnglePointComparator implements Comparator<Point> {
    /**
     * Orders angles from least to greatest.
     * 
     * @param that point being compared
     * @return -1 if one's angle is less than two's
     * @return 1  if one's angle is greater than two's
     * @return 0  if the angles are equal 
     */
    public int compare(Point one, Point two) {
        if (one.getAngle() < two.getAngle()) return -1;
        if (one.getAngle() > two.getAngle()) return 1;
        return 0;
    }
}