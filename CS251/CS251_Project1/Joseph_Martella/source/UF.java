/**
 * CS 251 - Project 1 - Union-Find
 * This class stores the data structure
 * of union find used for percolation. Has both
 * quick-find and weighted-union implementations.
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date January 24, 2011
 */

public class UF {
    private int[] id;     // access to component id (site indexed)
    private int[] sz;     // size of component for roots (site indexed)
    private int count;    // number of components
   
    public UF (int N) {
        // initialize component id array
        count = N;
        id = new int[N];
        
        for (int i = 0; i < N; i++)
            id[i] = i;
        
        sz = new int[N];
        for (int i = 0; i < N; i++)
            sz[i] = 1;
    }
    
    public int count() {
        return count;
    }
    
    // checks if p and q are in the same component
    public boolean connected (int p, int q) {
        return (find(p) == find(q));
    }
    
    // weight union connected method
    public boolean weightedConnected (int p, int q) {
        return (findIt(p) == findIt(q));
    }
    
    // quick find
    public int find (int p) {
        return id[p];
    }
    
    // weight quick union
    private int findIt (int p) {
        // follow links to find a root
        while (p != id[p]) 
            p = id[p];
        return p;
    }
    
    public void union (int p, int q) {
        // put p and q into the same component
        int pID = find(p);
        int qID = find(q);
        
        // nothing to do if p and q are already in the same component
        if (pID == qID) return;
        
        // rename p's component to q's name
        for (int i = 0; i < id.length; i++)
            if (id[i] == pID) id[i] = qID;
        count--;
    }
    
    // union for the weightedUnion
    public void weightedUnion (int p, int q) {
        int i = findIt(p);
        int j = findIt(q);
        if (i == j) return;
        
        // Make smaller root point to larger one.
        if (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i];}
        else               { id[j] = i; sz[i] += sz[j];}
        count--;
    }
    
}