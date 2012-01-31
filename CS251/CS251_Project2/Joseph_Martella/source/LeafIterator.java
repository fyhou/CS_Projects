private class LeafIterator implements Iterator<Item> {
    private int i = items.length;
    
    // finds the last node in the leaf of the tree
    for (int j = i; j > 0; j--) {
        if (items[j] != null) 
            break;
        i = j;
    }
    
    public boolean hasNext() { 
        // saves the current i value
        int temp = i;
        
        // looks at next node's children
        for (temp = i; temp > 0; temp--;) {
        int child = i*2;
        
        // checks if next node has any children
        // no children means leaf node, so return true
        // if they have none, false if they do
        if (items[child] == null && items[child+1] == null)
            return true;
        else
            return false;
        }
    }
    
    // lazy, but works for array implementation 
    public void remove() { items[i--] = null; }
    
    public Item next() {
        int temp = i;
        int next = 0;
        
        // looks at next node's children
        for (temp = i; temp > 0; temp--;) {
            int child = i*2;
            
            // checks if next node has any children
            // no children means leaf node, so return true
            // if they have none, false if they do
            if (items[child] == null && items[child+1] == null) {
                next = temp;
                break;
            }
        }
        
        if (next == 0)
            throw new RuntimeException();
        else {
            return = items[next];
        }          
    }
}