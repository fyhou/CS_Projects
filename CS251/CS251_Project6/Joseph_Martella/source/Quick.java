/*************************************************************************
 *  Compilation:  javac Quick.java
 *  Execution:    java Quick N
 *  Dependencies: StdRandom.java
 *  
 *  Generate N random real numbers between 0 and 1 and quicksort them.
 *
 *************************************************************************/

public class Quick {

    // quicksort the array
    public static void sort(int[] a, String s) {
        StdRandom.shuffle(a);
        sort(a, 0, a.length - 1, s);
    }

    // quicksort the subarray from a[lo] to a[hi]
    private static void sort(int[] a, int lo, int hi, String s) { 
        if (hi <= lo) return;
        int j = partition(a, lo, hi, s);
        sort(a, lo, j-1, s);
        sort(a, j+1, hi, s);
        assert isSorted(a, lo, hi, s);
    }

    // partition the subarray a[lo .. hi] by returning an index j
    // so that a[lo .. j-1] <= a[j] <= a[j+1 .. hi]
    private static int partition(int[] a, int lo, int hi, String s) {
        int i = lo;
        int j = hi + 1;
        int v = a[lo];
        while (true) { 

            // find item on lo to swap
            while (BurrowsWheeler.less(a[++i], v, s))
                if (i == hi) break;

            // find item on hi to swap
            while (BurrowsWheeler.less(v, a[--j], s))
                if (j == lo) break;      // redundant since a[lo] acts as sentinel

            // check if pointers cross
            if (i >= j) break;

            exch(a, i, j);
        }

        // put v = a[j] into position
        exch(a, lo, j);

        // with a[lo .. j-1] <= a[j] <= a[j+1 .. hi]
        return j;
    }

   /***********************************************************************
    *  Rearranges the elements in a so that a[k] is the kth smallest element,
    *  and a[0] through a[k-1] are less than or equal to a[k], and
    *  a[k+1] through a[n-1] are greater than or equal to a[k].
    ***********************************************************************/
    public static Comparable select(int[] a, int k, String s) {
        if (k < 0 || k >= a.length) {
            throw new RuntimeException("Selected element out of bounds");
        }
        StdRandom.shuffle(a);
        int lo = 0, hi = a.length - 1;
        while (hi > lo) {
            int i = partition(a, lo, hi, s);
            if      (i > k) hi = i - 1;
            else if (i < k) lo = i + 1;
            else return a[i];
        }
        return a[lo];
    }



   /***********************************************************************
    *  Helper sorting functions
    ***********************************************************************/
        
    // exchange a[i] and a[j]
    private static void exch(int[] a, int i, int j) {
        int swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }


   /***********************************************************************
    *  Check if array is sorted - useful for debugging
    ***********************************************************************/
    private static boolean isSorted(int[] a, String s) {
        return isSorted(a, 0, a.length - 1, s);
    }

    private static boolean isSorted(int[] a, int lo, int hi, String s) {
        for (int i = lo + 1; i <= hi; i++)
            if (BurrowsWheeler.less(a[i], a[i-1], s)) return false;
        return true;
    }



    // test client
    public static void main(String[] args) {
    }
}