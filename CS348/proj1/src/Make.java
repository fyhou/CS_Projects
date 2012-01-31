public class Make {
    private String _make;          // name for the make
    private String _country;       // name for the country
    
    public Make (String make, String country) {
        this._make    = make;
        this._country = country; 
    }
    
    public String getMake() {
        return _make;
    }
    
    public String getCountry() {
        return _country;
    }
    
    public String saveState() {
        return _make + "," + _country;
    }
}
