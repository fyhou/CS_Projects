import java.util.Scanner;

/**
 * Driver -- provided code for Project 2
 * The Driver class handles printing menus and creating
 * the shapes that must be defined for Project 2.
 */
class Driver {
    //Scanner to read input
    private static Scanner sc = new Scanner(System.in);

    /**
     * main method- prints main menu, gets choices from the user and handles dispatching
     *
     * @param args String[] for command line arguments, not used here
     */
    public static void main(String[] args) {
        Shape s = null;  //to hold the shape we are currently working with
        int choice;      //int to hold the user's menu choice

        System.out.println("Welcome to the Shape tester!");
        do{
            //print the menu
            System.out.println("What would you like to do? (enter 9 to quit)");
            System.out.println("1) Create a shape");
            System.out.println("2) Get area");
            System.out.println("3) Get perimeter");
            System.out.println("4) Check equality against another shape");
            System.out.println("5) Check for shape containment");

            //read in the user choice
            choice = sc.nextInt();

            //handle the menu option
            switch(choice){
                case 1:
                    //create a shape and store it
                    s = createShape();
                    break;
                case 2:
                    //check that there is a shape to work with, then get its area
                    if(s == null){
                        System.out.println("You haven't created a shape yet");
                    }
                    else{
                        System.out.println("The area is " + s.getArea());
                    }
                    break;
                case 3:
                    //check that there is a shape to work with, then get its perimeter
                    if(s == null){
                        System.out.println("You haven't created a shape yet");
                    }
                    else{
                        System.out.println("The perimeter is " + s.getPerimeter());
                    }
                    break;
                case 4:
                    //check that there is a shape to work with
                    if(s == null){
                        System.out.println("You haven't created a shape yet");
                    }
                    else{
                        //create a new shape to compare to
                        System.out.println("Create a shape to compare:");
                        Shape newS = createShape();

                        //call the equals method to determine if they are the same
                        if(s.equals(newS)){
                            System.out.println("The shapes are equal");
                        }
                        else{
                            System.out.println("The shapes are not equal");
                        }
                    }
                    break;
                case 5:
                    //check that there is a shape to work with
                    if(s == null){
                        System.out.println("You haven't created a shape yet");
                    }
                    else{
                        //create a new shape to compare to
                        System.out.println("Create a shape to compare:");
                        Shape newS = createShape();

                        //call the fitsInside method to determine containment
                        int result = s.fitsInside(newS);
                        switch(result){
                         case Shape.YES:
                             System.out.println("Yes, this shape fits inside our current shape");
                             break;
                         case Shape.NO:
                             System.out.println("No, this shape doesn't fit inside our current shape");
                             break;
                         case Shape.NOTSURE:
                             System.out.println("We're not sure about this one...");
                             break;
                         default:
                             System.out.println("The fitsInside() method is returning something incorrectly");   
                        }
                    }
                    break;
                case 9:
                    //exit case
                    System.out.println("Goodbye!");
                    break;
                default:
                    //print an error message for improper input
                    System.out.println("Sorry, that's not a valid choice");
                    break;
            }
        } while(choice != 9); //continue until exit choice is entered
    }

    /**
     * prints the sub-menu for creating a Shape object and gets user input
     * to create the shape
     *
     * @return A Shape corresponding to the input the user has entered
     */

    public static Shape createShape() {
        int choice;  //variable to hold the user's menu choice
        do{
            //print the shape menu
            System.out.println("What kind of shape?");
            System.out.println("1) Circle");
            System.out.println("2) Triangle");
            System.out.println("3) Rectangle");
            System.out.println("4) Square");

            //read in the user's choice
            choice = sc.nextInt();

            //switch on the choice
            switch(choice){
                case 1:
                    //create a circle
                    System.out.println("What is the radius?");
                    double r = sc.nextDouble();  //user inputs for radius
                    return new Circle(r);
                case 2:
                    //create a triangle
                    System.out.println("What is the base?");
                    double b = sc.nextDouble();  //user inputs for base
                    System.out.println("What is the height?");
                    double h = sc.nextDouble();  //user inputs for height
                    return new Triangle(b,h);
                case 3:
                    //create a rectangle
                    System.out.println("What is the width?");
                    double w = sc.nextDouble();  //user inputs for width
                    System.out.println("What is the height?");
                    h = sc.nextDouble();  //user inputs for height
                    return new Rectangle(w,h);
                case 4:
                    //create a square
                    System.out.println("What is the width?");
                    w = sc.nextDouble();  //user inputs for width
                    return new Square(w);
                default:
                    //print an error message for bad menu choice
                    System.out.println("Sorry, that was not a valid choice");
            }
        } while (choice < 1 || choice > 4);  //continue until a valid choice is entered

        //this shouldn't happen
        return null;      
    }
}