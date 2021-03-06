/**
 * CS 251 - Project 1 - PercolationVisualizer
 * Program reads data in from input file,
 * and visually displays everything that the
 * Percolation class does.
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date January 31, 2011
 *
 * @compile with javac -classpath .:stdlib.jar PercolationVisualizer.java
 * @execute with java -classpath .:stdlib.jar PercolationVisualizer < inputfile.txt
 */

public class PercolationVisualizer {
    private int n;                  // n x n matrix
    private boolean[][] matrix;     // the matrix
    private UF uf;                  // union find data structure
    private int squares = 0;        // number of spots opened
    
    /**
     * creates a new n by n grid where all cells are initially blocked
     * 
     * @param n determines the size of the grid
     */
    public PercolationVisualizer (int n) {
        // creates boolean 2d array
        this.n = n;
        matrix = new boolean[n][n];
        uf = new UF (n*n);
        
        // initializes 2d array by filling all spots (false = blocked)
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                matrix[x][y] = false;
            }
        }   
    }
    
    /**
     * Open the site at coordinate (x,y), where x represents the horizontal
     * axis and y the vertical one. For consistency purposes, (0,0) will be 
     * the bottom-left cell of the grid and (n-1,n-1) will be on the 
     * top-right.
     * 
     * @param x horizontal axis
     * @param y vertical axis
     * @return void
     */
    public void open (int x, int y, double scale) {
        // opens a spot in the matrix (true = open)
        matrix[x][y] = true;
        int row = x;
        int col = y;
        
        // checks cells to the left, right, above, and under
        // the newly opened cell; if checked cells are opened,
        // they are unioned       
        if (isOpen(x+1,y))
            uf.weightedUnion((y*n+x),(y*n+(x+1)));
        if (isOpen(x-1,y))
            uf.weightedUnion((y*n+x),(y*n+(x-1)));
        if (isOpen(x,y+1))
            uf.weightedUnion((y*n+x),((y+1)*n+x));
        if (isOpen(x,y-1))
            uf.weightedUnion((y*n+x),((y-1)*n+x));
        
        // if it percolates to point (x,y), represent that
        // component in light blue
        if (isFull(x,y)) {
            StdDraw.setPenColor(StdDraw.BOOK_LIGHT_BLUE);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (uf.weightedConnected((y*n+x), (j*n+i)))
                        StdDraw.filledSquare(scale + (2*scale*i),scale + (2*scale*j), scale);
                }
            }
        }
        // if doesn't percolate to point (x,y), just draw
        // a white square
        else {
            StdDraw.setPenColor(StdDraw.WHITE);
            StdDraw.filledSquare(scale + (2*scale*row),scale + (2*scale*col), scale);
        }
        
        
        // clears the previous text, and writes new text
        // displaying how many open sites are currently
        // open on the board
        StdDraw.setPenColor(StdDraw.BLACK);
        StdDraw.filledRectangle(.47, -.03, .2, .024);
        squares++;
        StdDraw.setPenColor(StdDraw.GREEN);
        StdDraw.text(.47, -.03, squares + " open sites");
    }
    
    /**
     * Returns true if cell (x,y) is open due to a previous call to 
     * open(int x, int y)
     * 
     * @param x horizontal axis
     * @param y vertical axis
     * @return boolean if it's open
     */
    public boolean isOpen (int x, int y) {
        // checks for out of range values
        if (x < 0 || x >= n) return false;
        if (y < 0 || y >= n) return false;
        
        // true is open, false is closed
        return matrix[x][y];
    }
    
    /**
     * Returns true if there is a path from cell (x,y) to the surface
     * (i.e. there is percolation up to this cell)
     * 
     * @param x horizontal axis
     * @param y vertical axis
     * @return boolean if it percolates
     */
    public boolean isFull (int x, int y) {
        // n == column
        for (int row = 0; row < n; row++) {
            if (uf.weightedConnected((((n-1)*n)+(row)), ((y*n)+x)))
                return true;
        }
        return false;
    }
    
    /**
     * Analyzes the entire grid and returns true if the whole 
     * system percolates
     * 
     * @boolean true or false
     */
    public boolean percolates() {
        // checks each cell in the first row to see if there is
        // a path to the surface, aka if the whole thing percolates
        for (int i = 0; i < n-1; i++) {
            if (isFull(i, 0)) {
                System.out.println("Yes");
                return true;
            }
        }
        System.out.println("No");
        return false;
    }
    
    /**
     * Waits in seconds
     * 
     * @param n time in seconds to wait
     */
    public static void waiting (double n){
        
        long t0, t1;
        
        t0 =  System.currentTimeMillis();
        
        do{
            t1 = System.currentTimeMillis();
        }
        while ((t1 - t0) < (n * 1000));
    }
    
    /**
     * Reads a description of a grid from standard input 
     * (using StdIn.java) and draws it
     */
    public static void main (String[] args) {
        int size = StdIn.readInt();  
        PercolationVisualizer percolater = new PercolationVisualizer (size);
        
        double scale = ((1.00 / size) / 2.00);
        
        // sets the background as white, with a black square on top
        StdDraw.setCanvasSize(600,600);
        // StdDraw.frame.setTitle("Percolation Visualizer");
        StdDraw.clear(StdDraw.BLACK);
        
        // prototype: first parameter is for column, second parameter is for row
        // int row = 3;
        // int column = 1;
        // StdDraw.filledSquare(scale + (2*scale*column),scale + (2*scale*row), scale);
        
        
        while (!StdIn.isEmpty()) {
            int x = StdIn.readInt();
            int y = StdIn.readInt();
            percolater.open(x,y,scale);
            //waiting(.3);
        }
    }
}