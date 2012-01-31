/**
 * Triangle -- a class that has methods that can find
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
public class Triangle implements Shape
{
    public double base = 0;    // the triangle's base
    public double height = 0;  // the triangle's height
    
    public Triangle (double base, double height)
    {
        this.base = base;
        this.height = height;
    }
    
    /**
     * computes the area of a triangle: 1/2*base*height
     * 
     * @return area the area of the triangle
     */
    public double getArea()
    {
        double area = ((1.00/2.00) * base * height);
        return area; 
    }
    
    /**
     * computes the hypotenuse of the triangle by using
     * the Pythagorean theorem
     * 
     * @return hypotenuse the hypotenuse of the triangle
     */
    private double getHypotenuse()
    {
        double hypotenuse = Math.sqrt(Math.pow(base,2) + Math.pow(height,2));  
        return hypotenuse; 
    }
    
    /**
     * computer the perimeter of the trianlge by adding up
     * all the sides
     * 
     * @return perimeter the perimeter of the triangle
     */
    public double getPerimeter()
    {
        double hypotenuse = getHypotenuse();
        double perimeter = base + height + hypotenuse;
        return perimeter; 
    }
    
    /**
     * checks equality of triangles
     * 
     * @param s a shape that'll equality will be judged against
     * @return a boolean illustrating equality
     */
    public boolean equals(Shape s)
    {
        if (s == null)
            return false;
        if(! (s.getClass().equals(getClass())))
            return false;
        Triangle t = (Triangle) s; 
        if ((t.base == base) && (t.height == height))
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
        
        // Triangles
        if (typeShape.startsWith("Tri"))
        {
            Triangle t = (Triangle) s;
            
            if (t.base <= base && t.height <= height)
            {
                return YES;
            }
            else
                return NO;
        }
        
        return NOTSURE;
    }
}


