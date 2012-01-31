/**
 * CS 251 - Project 1 - Percolation
 * Program reads in data from a file
 * to create a matrix of open/closed 
 * cells. Determines whether or not the
 * system percolates.
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date January 31, 2011
 *
 * @compile with javac -classpath .:stdlib.jar Percolation.java
 * @execute with java -classpath .:stdlib.jar Percolation < inputfile.txt
 */

public class Percolation {
    private int n;                  // n x n matrix
    private boolean[][] matrix;     // the matrix
    private UF uf;                  // union find data structure
    private String speed;           // fast = weight union find; slow = quick find
    
    /**
     * creates a new n by n grid where all cells are initially blocked
     * 
     * @param n determines the size of the grid
     */
    public Percolation (int n, String speed) {
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
        
        this.speed = speed; 
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
    public void open (int x, int y) {
        // opens a spot in the matrix (true = open)
        matrix[x][y] = true;
        
        // checks cells to the left, right, above, and under
        // the newly opened cell; if checked cells are opened,
        // they are unioned      
        if (speed.equals("slow")) {
            if (isOpen(x+1,y))
                uf.union((y*n+x),(y*n+(x+1)));
            if (isOpen(x-1,y))
                uf.union((y*n+x),(y*n+(x-1)));
            if (isOpen(x,y+1))
                uf.union((y*n+x),((y+1)*n+x));
            if (isOpen(x,y-1))
                uf.union((y*n+x),((y-1)*n+x)); 
        }
        if (speed.equals("fast")) {
            if (isOpen(x+1,y))
                uf.weightedUnion((y*n+x),(y*n+(x+1)));
            if (isOpen(x-1,y))
                uf.weightedUnion((y*n+x),(y*n+(x-1)));
            if (isOpen(x,y+1))
                uf.weightedUnion((y*n+x),((y+1)*n+x));
            if (isOpen(x,y-1))
                uf.weightedUnion((y*n+x),((y-1)*n+x)); 
        }
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
        for (int row = 0; row < n; row++) {
            if (speed.equals("slow")) {
                if (uf.connected(((y*n)+x), (((n-1)*n)+(row))))
                    return true;
            }
            if (speed.equals("fast")) {
                if (uf.weightedConnected(((y*n)+x), (((n-1)*n)+(row))))
                    return true;
            }
        }
        return false;
    }
    
    /**
     * Analyzes the entire grid and returns true if the whole 
     * system percolates
     * 
     * @return boolean true or false
     */
    public boolean percolates() {
        // checks each cell in the first row to see if there is
        // a path to the surface, aka if the whole thing percolates
        for (int i = 0; i < n; i++) {
            if (isFull(i, 0)) {
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * Analyzes the entire grid and returns true if the whole 
     * system percolates
     * 
     * @return boolean true or false
     */
    public boolean percolatesX() {
        // checks each cell in the first row to see if there is
        // a path to the surface, aka if the whole thing percolates
        if (isFull(0,0))
            return true;

        return false;
    }
    
    /**
     * Reads a description of a grid 
     * from standard input (using StdIn.java) and validates if 
     * the system described percolates or not, printing to 
     * standard output a simple "Yes" or "No" answer 
     * (using StdOut.java).
     */
    public static void main (String[] args) {
        // hard coded to use weighted union find
        String speed = "fast";
        int size = StdIn.readInt();  
        Percolation percolater = new Percolation (size, speed);   
        
        // reads values until file is empty
        while (!StdIn.isEmpty()) {
            int x = StdIn.readInt();       
            int y = StdIn.readInt();
            percolater.open(x,y);
        }
        
        if (percolater.percolates())
            System.out.println("Yes");
        else 
            System.out.println("No");
           
    }    
}