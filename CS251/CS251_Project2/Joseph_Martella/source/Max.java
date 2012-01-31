public class Max {
    public static int max (Deque<Integer>.Node current) {
        if (current == null) return 0;
        
        int currentItem = current.item;
        int nextItem;
         
        if (current.next == null) return currentItem;
        else nextItem = max(current.next);
        
        if (currentItem > nextItem) return currentItem;
        else                        return nextItem;
    }
    
    public static void main (String[] args) {
        Deque<Integer> d = new Deque<Integer>();
        
        for (int i = 0; i < 10; i++) {
            d.addFirst(i);
        }
        
        int max = max(d.first);
        
        System.out.println(max);
    }
}