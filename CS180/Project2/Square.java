/**
 * Square -- a class that has methods that can find
 * the area and perimeter of the shape; it also checks
 * equality against other shapes and check containment 
 * of other shapes.
 *
 * @author Joseph Martella
 *
 * @recitation f7
 *
 * @date February 18, 2010
 *
 */
public class Square extends Rectangle
{  
    public Square (double width)
    {
        super(width, 0);
    }
    
    /**
     * checks equality of squares
     * 
     * @param s a shape that'll be set equal to the instance
     * @return a boolean illustrating equality
     */
    public boolean equals(Shape s)
    {
        if (s == null)
            return false;
        
        Rectangle r = (Rectangle) s;
        
        if (r.width == width)
        {
            if ((r.width == height))
            {
                return true;
            }
            else
            {
                return false; 
            }                
        }
        else 
            return false;
    }
    
    /**
     * tests if a shape fits inside the instance
     * 
     * @param s a shape that'll be fitting into the other
     * @return yes, no, or not sure
     */
    public int fitsInside(Shape s)
    {       
        String typeShape = s.toString();
        
        // Rectangles
        if (typeShape.startsWith("Rect"))
        {
            Rectangle r = (Rectangle) s;
            
            if (r.height <= width && r.width <= width)
            {
                return YES; 
            }
            else 
                return NO;
        }
        
        // Square 
        if (typeShape.startsWith("Squa"))
        {
            Square r = (Square) s;
            
            if (r.width <= width)
            {
                return YES;
            }
            else
                return NO;
        }
        
        // Circle
        if (typeShape.startsWith("Circ"))
        {
            Circle c = (Circle) s; 
            
            if ((c.radius*2) <= width && (c.radius*2) <= width)
            {
                return YES;
            }
            else
                return NO;
        }
        
        // Triangle
        if (typeShape.startsWith("Tri"))
        {
            Triangle t = (Triangle) s; 
            
            if (t.base <= width && t.height <= width)
            {
                return YES;
            }
            else
                return NO;
        }
        
        return NOTSURE; 
    }
}


