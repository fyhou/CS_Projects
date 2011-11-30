import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class StudentTools {
	private Connection c;
	String snum = "";
	
	/**
	 * Establishes a connection with the database
	 */
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
		String query = "select password, snum from student where sname='" + id + "'";
		String storedPassword = "";
		
		try {
			stmt = c.createStatement();
			boolean r = stmt.execute(query);
			
			if (r) {
				
				ResultSet rs = stmt.getResultSet();
				while (rs.next()) {
					storedPassword = rs.getString("password");
					snum = rs.getString("snum");
				}
			}
			else {
				// student not in database
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
	
	/**
	 * Get Calendar of evaluations
	 */
	public List<Evaluation> st1SQL() {
		List<Evaluation> cal = new ArrayList<Evaluation>();
		
		Statement stmt = null;
		String query = "select cname from enrolled where snum = '" + snum + "'";
		
		try {
			stmt = c.createStatement();
			boolean r = stmt.execute(query);
			
			if (r) {
				ResultSet rs = stmt.getResultSet();
				while (rs.next()) {
					String cname = rs.getString("cname");
					
					Statement _stmt = null;
					String _query = "select * from evaluation where cname = '" + cname + "'";
					
					_stmt = c.createStatement();
					boolean _r = _stmt.execute(_query);
					
					if (_r) {
						ResultSet _rs = _stmt.getResultSet();
						while (_rs.next()) {
							Evaluation e = new Evaluation();
							e.name = _rs.getString("name");
							e.type = _rs.getString("type");
							e.weight = _rs.getString("weight");
							e.deadline = _rs.getString("deadline");
							e.deadline = e.deadline.substring(0, 10);
							e.room = _rs.getString("room");
							e.cname = _rs.getString("cname");
							
							cal.add(e);
						}
					}
					else {
						;
					}
				}
			}
			else {
				;
			}
		} catch (Exception e) {
			System.out.println("Error: " + e.getMessage());
		}
		
		return cal;
	}
}