/**
 * Rectangle -- a class that has methods that can find
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
public class Rectangle implements Shape
{
    public double width;   // the rectangle's width
    public double height;  // the rectangle's height
    
    public Rectangle (double width, double height)
    {
        this.width = width;
        this.height = height;
    }
    
    /**
     * computes the area of a rectangle: width * height
     * 
     * @return area the area of the rectangle
     */
    public double getArea()
    {
        double area = 0;
        
        if (height == 0)
        {
            area = width * width;
        }
        else
        {
            area = width * height;
        }
        
        return area; 
    }
    
    /**
     * computer the perimeter of a rectangle
     * 
     * @return perimter the perimeter of the rectangle
     */
    public double getPerimeter()
    {
        double perimeter = 0;
        
        if (height == 0)
        {
            perimeter = 4 * width;
        }
        else 
        {
            perimeter = ((2 * width) + (2 * height));
        }
        
        return perimeter;
    }
    
    /**
     * checks equality of rectangles
     * 
     * @param s a shape 
     * @return a boolean illustrating equality
     */
    public boolean equals(Shape s)
    {
        if (s == null)
            return false;
        Rectangle r = (Rectangle) s; 
        if ((r.height == height || r.height == 0) && (r.width == width))
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
        String typeShape = s.toString();
        
        // Rectangles
        if (typeShape.startsWith("Rect"))
        {
            Rectangle r = (Rectangle) s;
            
            if (r.height <= height && r.width <= width)
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
            
            if (r.width <= height && r.width <= width)
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
            
            if ((c.radius*2) <= height && (c.radius*2) <= width)
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
            
            if (t.base <= width && t.height <= height)
            {
                return YES;
            }
            else
                return NO;
        }
        
        return NOTSURE; 
    }
}


