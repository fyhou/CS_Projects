/**
 * CS 251 - Project 2 - Deque
 * A double-ended queue or deque (pronounced "deck") 
 * is a generalization of a stack and a queue that 
 * supports inserting and removing items from either 
 * the front or the back of the data structure.
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date February 11, 2011
 *
 * @compile with javac Deque.java
 * @execute with java Deque < input.txt
 */

import java.util.Iterator;

public class Deque<Item> implements Iterable<Item> {
    public Node first = null;               // pointer to first item in deque
    private Node last = null;                // pointer to last item in deque
    private Iterator itr = iterator();       // iterator to go through deque
    private int count = 0;                    // keeps track of how items in deque 
    
    /**
     * class to make a Node in the doubly-linked list;
     * each Node has a pointer to the next Node, the previous
     * Node, and an Item representing what it is
     */
    public class Node {
        Node next;              // pointer to the next Node in list
        Node prev;              // pointer to the previous Node in list
        Item item;              // item the Node stores
    }
    
    /**
     * creates an empty deque
     */
    public Deque() {
        first = null;
        last = null;
    }
    
    /**
     * checks if the deque is empty
     * 
     * @return boolean true or false if the deque is empty
     */
    public boolean isEmpty() {
        if (count == 0)    return true;
        else               return false;
    }
    
    /**
     * returns the size of the deque
     * 
     * @return int the number of items in the deque
     */
    public int size() {
        return count;
    }
    
    /**
     * adds an item to the front of the deque
     * 
     * @param item item to be added to the deque
     */
    public void addFirst(Item item) {
        if (isEmpty()) {
            first = new Node();
            first.item = item;
            first.prev = null;
            first.next = null;
            last = first;
        }
        else {
            Node oldFirst = first;
            first = new Node();
            first.item = item;
            first.prev = null;
            first.next = oldFirst;
            oldFirst.prev = first;
        }
        count++;
    }
    
    /**
     * adds an item to the back of the queue
     * 
     * @param item item to be added to the queue
     */
    public void addLast(Item item) {
        if (isEmpty()) {
            first = new Node();
            first.item = item;
            first.prev = null;
            first.next = null;
            last = first;
        }
        else {
            Node oldLast = last;
            last = new Node();
            last.item = item;
            last.next = null;
            last.prev = oldLast;
            oldLast.next = last;
        }
        count++;
    }
    
    /**
     * deletes first item in queue and returns new first
     *
     * @return Item new first item
     */
    public Item removeFirst()  {
        if (isEmpty()) {
            throw new RuntimeException();
        }
        else {          
            Item deleted = first.item;
            count--;
            
            if (!isEmpty()) {
                first = first.next;
                first.prev = null;
            }           
            
            return deleted;
        }
    }
    
    /**
     * deletes last item in queue and returns it
     * 
     * @param Item deleted Item
     */
    public Item removeLast() {
        if (isEmpty()) {
            throw new RuntimeException();
        }
        else {
            Item deleted = last.item;
            count--;
            
            if (!isEmpty()) {
                last = last.prev;
                last.next = null;
            }
            
            return deleted;
        }
    }
    
    /**
     * return an iterator that examines the 
     * items in order from front to back
     */
    public Iterator<Item> iterator() {
        return new ListIterator(); 
    }
    
    private class ListIterator implements Iterator<Item> {
        private Node current = first;
        
        public boolean hasNext() { return (current.next != null); }
        public void remove() { /* not implemented, do not use */ }
        public Item next() {
            Item item = current.item;
            current   = current.next;
            return item;
        }       
    }
    
    /**
     * print the item in the deque
     * 
     * @param i an iterator 
     */
    public void print(Iterator<Item> i) {
        while (i.hasNext()) {
            Item s = i.next();
            StdOut.print(s + ",");
        } 
        Item s = (Item) i.next();
        StdOut.println(s);
    }
    
    
    /**
     * instantiates a Deque of Strings
     * to test the functionality of the methods
     */
    public static void main(String[] args){
        Deque<String> deque = new Deque<String>();
        
        while (!StdIn.isEmpty()) {
            String command = StdIn.readString();       
         
            if (command.equals("addFirst")) {
                String item = StdIn.readString();
                deque.addFirst(item);
            }
            else if (command.equals("addLast")) {
                String item = StdIn.readString();
                deque.addLast(item);
            }
            else if (command.equals("removeFirst")) {
                deque.removeFirst();
            }
            else if (command.equals("removeLast")) {
                deque.removeLast();
            }
            else if (command.equals("print")) {
                Iterator<String> i = deque.iterator();
                deque.print(i);
            }           
        }
    }
}