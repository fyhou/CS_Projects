/**
 * CS 251 - Project 2 - Randomized Queue
 * A randomized queue is similar to a stack 
 * or queue, except that the item removed is 
 * chosen uniformly at random from items in 
 * the data structure.
 *
 * @author Joseph Martella
 *
 * @professor Neville
 *
 * @date February 11, 2011
 *
 * @compile with javac RandomizedQueue.java
 * @execute with java RandomizedQueue < otherinput.txt
 */

import java.util.Iterator;

public class RandomizedQueue<Item> implements Iterable<Item> {
    private int count = 0;      // how many objects are in the queue
    private Item[] items;       // array that holds items
    
    /**
     * constructor makes an 
     * empty queue with space
     * for one item
     */
    public RandomizedQueue () {
        items = (Item[]) new Object[1]; 
    }
    
    /** 
     * checks if the queue is empty
     * by checking if the item count 
     * is 0 or not
     * 
     * @return boolean true if empty, false if not
     */
    public boolean isEmpty() {
        if (count == 0) return true;
        else            return false;
    }
    
    /**
     * returns the size of the queue
     * 
     * @return int the number of items in the queue
     */
    public int size() {
        return count;
    }
    
    /**
     * enqueues an item 
     * 
     * @param item item to be enqueued
     */
    public void enqueue (Item item) {
        if (count == items.length) resize (2*items.length);
        
        for (int i = 0; i < items.length; i++) {
            if (items[i] == null) {
                items[i] = item;
                count++;
                break;
            }
        }
    }
    
    /**
     * dequeues a random item; throws a 
     * Runtime Exception if tried on an 
     * empty queue
     * 
     * @return Item item that is dequeued
     */
    public Item dequeue () {
        if (isEmpty()) throw new RuntimeException();
        
        int it = 0;
        StdRandom.shuffle(items);       
               
        while (1==1) {    
            Item returned = items[it++];
            if (returned != null) {
                items[--it] = null;
                count--;
                if (count > 0 && count == items.length/4) resize(items.length/2);
                return returned;
            }
        }   
    }
    
    /**
     * returns a random item from 
     * the queue, but does nothing
     * with it
     * 
     * @return Item item that is sampled 
     */
    public Item sample() {
        if (isEmpty()) throw new RuntimeException();
        
        StdRandom.shuffle(items);
        int it = 0;        
               
        while (1==1) {    
            Item returned = items[it++];
            if (returned != null) {
                return returned;
            }
        } 
    }
    
    /**
     * resizes the array by copying
     * and pointing the items array 
     * to the copy
     * 
     * @param capacity length of new array
     */
    private void resize (int capacity) {
        Item[] copy = (Item[]) new Object[capacity];
        int number = 0;
        for (int i = 0; i < items.length; i++) {
            if (items[i] != null) {
                copy[number++] = items[i];
            }
        }  
        
        items = copy;
    }
    
    /**
     * return an iterator that examines the 
     * items in order from front to back
     */
    public Iterator<Item> iterator() {
        StdRandom.shuffle(items);
        return new ArrayIterator(); 
    }
    
    private class ArrayIterator implements Iterator<Item> {
        private int i = items.length;
        
        public boolean hasNext() { return i > 0;                     }
        public void remove()     { /* not implemented, do not use */ }
        public Item next()       { return items[--i];                }
    }
    
    /**
     * prints the items in the queue
     * in a random order
     * 
     * @param i an iterator 
     */
    public void print (Iterator<Item> i) {
        int found = 0;
        
        while (i.hasNext()) {
            Item s = i.next();
            if (s != null) {
                found++;
                
                if (found != count)
                    StdOut.print(s + ",");
                else 
                    StdOut.println(s);
            }
        } 
    }
    
    /**
     * instantiates a RandomizedQueue of Strings
     * to test the functionality of the methods
     */
    public static void main (String[] args) {
        RandomizedQueue<String> rq = new RandomizedQueue<String>();
        
        while (!StdIn.isEmpty()) {
            String command = StdIn.readString();       
         
            if (command.equals("enqueue")) {
                String item = StdIn.readString();
                rq.enqueue(item);
            }
            else if (command.equals("dequeue")) {
                StdOut.println(rq.dequeue());
            }
            else if (command.equals("sample")) {
                StdOut.println(rq.sample());
            }
            else if (command.equals("print")) {
                Iterator<String> i = rq.iterator();
                rq.print(i);
            }           
        }
    }
}