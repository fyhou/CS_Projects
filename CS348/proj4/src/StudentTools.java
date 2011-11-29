import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class StudentTools {
	private Connection c;
	
	StudentTools() {
		c = null;
		String driverName = "oracle.jdbc.driver.OracleDriver";
		
		String serverName = "claros.cs.purdue.edu";
		String port = "1524";
		String sid = "strep";
		
		String url = "jdbc:oracle:thin:@" + serverName + ":" + port + ":" + sid;
		
		String username = "jmartel";
		String password = "s0cc3r";
		
		try {
			Class.forName(driverName);
			c = DriverManager.getConnection(url, username, password);
		} catch (ClassNotFoundException e) {
			System.out.println("ClassNotFoundException: " + e.getMessage());
		} catch (SQLException e) {
			System.out.println("SQLException: " + e.getMessage());
		}
	}
	
	/**
	 * Checks if login information is valid.
	 */
	public boolean isValidUser(String id, String password) {
		if (id.equals("") || password.equals(""))
			return false;

		Statement stmt = null;
		String query = "select password from student where sname='" + id + "'";
		String storedPassword = "";
		
		try {
			stmt = c.createStatement();
			boolean r = stmt.execute(query);
			
			if (r) {
				
				ResultSet rs = stmt.getResultSet();
				while (rs.next()) {
					storedPassword = rs.getString(1);
				}
			}
			else {
				// student not in db
			}
		} catch (Exception e) {
			System.out.println("Error: " + e.getMessage());
		}

		if (storedPassword.equals(password)) {
			return true;
		}
		else 
			return false;
	}
}