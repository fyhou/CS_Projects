/**
 * Circle -- a class that has methods that can find
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
public class Circle implements Shape 
{
    public double radius = 0; // the cirlce's radius
    
    public Circle (double radius)
    {
        this.radius = radius;
    }
    
    /**
     * computes the area of a circle: pi*r^2
     * 
     * @return area the area of the cirlce
     */
    public double getArea()
    {
        double area = (Math.PI * Math.pow(radius, 2));
        return area; 
    }
    
    /**
     * computes the circumfrence of a circle: 2*pi*r
     * 
     * @return perimeter the circumfrence of the circle
     */
    public double getPerimeter()
    {
        double perimeter = (2 * Math.PI * radius);
        return perimeter; 
    }
    
    /**
     * checks equality of circles
     * 
     * @param s a shape that'll be set equal to
     * @return a boolean illustrating equality
     */
    public boolean equals(Shape s)
    {
        if (s == null)
            return false;
        if(! (s.getClass().equals(getClass())))
            return false;
        Circle c = (Circle) s; 
        if (c.radius == radius)
            return true;
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
        Rectangle circleRec = new Rectangle((2*radius),(2*radius));       
        String typeShape = s.toString();
        
        // Circle
        if (typeShape.startsWith("Circ"))
        {
            Circle c = (Circle) s; 
            
            if (c.radius <= radius)
            {
                return YES;
            }
            else
                return NO;
        }
        
        // Rectangles
        if (typeShape.startsWith("Rect"))
        {
            Rectangle r = (Rectangle) s;
            double possible = Math.sqrt((r.height/2.00)*(r.height/2.00) + radius*radius);
            
            if (r.height <= possible)
            {
                return YES; 
            }
            else 
                return NO;
        }
        
        // Squares
        if (typeShape.startsWith("Squa"))
        {
            Square r = (Square) s;
            double possible = Math.sqrt((r.width/2.00)*(r.width/2.00) + radius*radius);
            
            if (r.width <= possible)
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
            
            if (Math.sqrt(t.height*t.height + t.base*t.base) <= radius)
            {
                return YES; 
            }
            else 
                return NO;
        }
        
        return NOTSURE;
    }
}


