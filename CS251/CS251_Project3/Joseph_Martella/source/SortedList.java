/**
 * CS 251 - Project 3 - SortedList
 * Keeps a list of the 'tails' of all line
 * segments to deter the printing of 
 * subsegments in Fast.java.
 *
 * @author Joseph Martella (adapted from online code)
 * http://www.java-forums.org/java-lang/7610-how-create-sorted-list-java.html
 * It was code we talked about in lecture pretty much, and found 
 * a nice implementation of it online. I tailored it to hold Point instead of 
 * double and I also tailored it to have two values instead of one.
 *
 * @professor Neville
 *
 * @date February 25, 2011
 *
 * @compile with javac SortedList.java
 * @execute with not applicable 
 */
public class SortedList {
  public Link first;          // first element in the list

  public SortedList() {
    first = null;
  }

  /**
   * inserts a new 'tail' into the list;
   * sorts using the x values of the xPoint.
   * 
   * @param xKey the first Point in tail
   * @param yKey the second Point in tail
   */
  public void insert(Point xKey, Point yKey){
    Link newLink = new Link(xKey, yKey);   // Link to be added
    Link previous = null;                  // sets previous to null
    Link current = first;                  // sets current to first to traverse the array

    // traveres until the new xPoint's x value is less than or equal
    // to the current's x value
    while (current != null && xKey.getX() > current.xPoint.getX()) {
      previous = current;
      current = current.next;
    }
    
    // adds the new Link to the list
    if (previous == null)
      first = newLink; 
    else
      previous.next = newLink; 
    newLink.next = current; 
  }
  
  public class Link {
    public Point xPoint;     // first Point in the tail
    public Point yPoint;     // second Point in the tail
    public Link next;        // connecting Link 
    
    public Link(Point one, Point two) {
      xPoint = one;
      yPoint = two;
    }
  }
}