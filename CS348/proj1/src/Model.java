public class Model implements Comparable{
    private String _name;   // name of the model
    private Make _make;     // car manufacturer 
    private int _year;      // year when it was made
    private int _price;     // price that it is valued at
    
    public Model (String name, Make make, int year, int price) {
        this._name  = name;
        this._make  = make;
        this._year  = year;
        this._price = price; 
    }
    
    public String toString () {
        String modelString = _name + " " + _year + " @ " + _price + ", " + _make.getMake() + " in " + _make.getCountry();
        return modelString; 
    }
    
    public int getPrice() {
        return _price; 
    }
    
    public String getName() {
        return _name;
    }
    
    public int compareTo (Object anotherModel) throws ClassCastException {
        if (!(anotherModel instanceof Model))
            throw new ClassCastException ("A Model object expected.");
        
        int anotherModelPrice = ((Model) anotherModel).getPrice();
        return anotherModelPrice - this._price;
    }
    
    public String saveState() {
        return _name + "," + _make.saveState() + "," + _year + "," + _price; 
    }
}
