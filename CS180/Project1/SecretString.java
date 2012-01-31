/**
 * Project 1: A Different String Class
 * This program takes in a set of integers or bytes, as 
 * designated by the user and converts such values into
 * a textual message that is outputted to the screen. 
 *
 * @author Joseph Martella
 *
 * @recitation f7 (Jacqueline Soenneker)
 *
 * @date February 4, 2010
 *
 */

public class SecretString
{
    private boolean[] bits; // boolean array that represents a binary string
    
    /**
     * SecretString constructor 
     * 
     * @param data data represented as an integer array
     */
    public SecretString(int[] data)
    {  
        bits = convertToBits(data);
    }
    
    /**
     * SecretString constructor 
     * 
     * @param data data represented as a byte array
     */
    public SecretString(byte[] data)
    {
        bits = convertToBits(data);
    }
    
    /** 
     * converts an array of integers into an array of booleans
     * 
     * @param array an integer array
     * @return a boolean array
     */    
    private static boolean[] convertToBits(int[] array)
    {
        int length = array.length; // length of the input array
        boolean [] booleanArray = new boolean[32*length]; // boolean array that stores binary representation
        String binaryString = ""; // string that holds all binary representation
        String tempBinary = ""; // temporary string that holds binary representatin of array element
        
        // converts integer array into a binary String array
        for (int index = 0; index < length; index++)
        {
            tempBinary = Integer.toBinaryString(array[index]);

            // pads the string wit 0s to get 32 values
            while (tempBinary.length() != 32)
            {
                tempBinary = "0" + tempBinary;
            }
            
            // concates each binary representation to for one String
            binaryString = binaryString + tempBinary;
        }
        
        // converts each value in the string to true or false
        for (int index = 0; index < 32*length; index++)
        {
            if (binaryString.charAt(index) == '1')
                booleanArray[index] = true;
            else
                booleanArray[index] = false;
        }
        
        return booleanArray;
    }    
    
    /** 
     * converts an array of bytes into an array of booleans
     * 
     * @param array an array of bytes
     * @return a boolean array
     */    
    private static boolean[] convertToBits(byte[] array)
    {
        int length = array.length; // length of the input array
        int convertedByte = 0; // byte converted
        boolean [] booleanArray = new boolean[8*length];  // boolean array that stores binary representation
        String binaryString = ""; // string that holds all binary representation
        String tempBinary = ""; // temporary string that holds binary representatin of array element
        
        // converts integer array into a binary String array
        for (int index = 0; index < length; index++)
        {
            convertedByte = (int) array[index];          
            tempBinary = Integer.toBinaryString(convertedByte);

            // pads the string wit 0s to get 8 values
            while (tempBinary.length() != 8)
            {
                tempBinary = "0" + tempBinary;
            }
            
            // concates each binary representation to for one String
            binaryString = binaryString + tempBinary;
        }
        
        // converts each value in the string to true or false
        for (int index = 0; index < 8*length; index++)
        {
            if (binaryString.charAt(index) == '1')
                booleanArray[index] = true;
            else
                booleanArray[index] = false;
        }
        
        return booleanArray;
    }
    
    /**
     * finds character at place specified by index and
     * returns its plain text representation
     * 
     * @param index integer value that represents spot in array
     * @return plain text character
     */
    public char getCharAt(int index)
    {
        String booleanString = "";
        
        for (int i = (index*8); i < ((index*8) + 8) ; i++)
        {
            if (bits[i])
                booleanString += "1";
            else
                booleanString += "0";
        }        
        
        int number = Integer.parseInt(booleanString, 2);
        char character = ((char)number);
        
        return character;     
    }
    
    /**
     * returns the length of the array
     * 
     * @return the length of the array
     */
    public int getLength()
    {
        int length = bits.length / 8;
        return length;
    }
}