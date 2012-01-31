/*************************************************************************
 *  Compilation:  javac PointPlotter.java
 *  Execution:    java PointPlotter < input.txt
 *  Dependencies: Point.java, StdIn.java, StdDraw.java
 *
 *  Reads in an integer N from standard input, and then N pairs of
 *  points (x, y), and plots them using standard draw.
 *
 *************************************************************************/

public class PointPlotter {
    public static Point[] points;
    public static int N = 0;
    
    public static Point[] main(String[] args) {

        // rescale coordinates and turn on animation mode
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        StdDraw.show(0);

        // read in the input
        N = StdIn.readInt();
        
        Point[] points = new Point[N];
        int index = 0;
        
        for (int i = 0; i < N; i++) {
            int x = StdIn.readInt();
            int y = StdIn.readInt();
            Point p = new Point(x, y);
            points[index++] = p;
            p.draw();
        }

        // display to screen
        StdDraw.show(0);
        
        return points;
    }
}