import java.sql.*;
import java.text.*;
import java.util.*;

public class FacultyTools {
	private Connection c;
	public String fid = "-1";
	
	/**
	 * Establish connection with the database.
	 */
	FacultyTools() {
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
		String query = "select * from faculty where fname='" + id + "'";
		String storedPassword = "";
		
		try {
			stmt = c.createStatement();
			boolean r = stmt.execute(query);
			
			if (r) {
				
				ResultSet rs = stmt.getResultSet();
				while (rs.next()) {
					storedPassword = rs.getString("password");
					fid = rs.getString("fid");
				}
			}
			else {
				// faculty not in db
			}
		} catch (Exception e) {
			// handle exception
		}

		if (storedPassword.equals(password)) {
			return true;
		}
		else 
			return false;
	}
	
	/**
	 * Creates/Modify a class.
	 */
	public int ft1SQL(String cname, String semester, String year, String meetsAt, String room) {
		if (cname.equals("") || year.equals("") || meetsAt.equals("") || room.equals(""))
			return -1;
		
		Statement stmt = null;
		String query = "select * from class where cname='" + cname + "'";
		String storedFID = "";
		
		boolean update = false;
		
		try {
			stmt = c.createStatement();
			boolean r = stmt.execute(query);
			
			// check if class is in db
			if (r) {
				ResultSet rs = stmt.getResultSet();
				while (rs.next()) {
					storedFID = rs.getString("fid");	
					
					// if class is already in database, check if faculty teaches it
					if (fid.equals(storedFID)) {
						update = true;
						break;
					}
					else {
						return -2; 
					}
				}
			}
			
			// format data
			int dYear = Integer.parseInt(year);
			String hour = meetsAt.substring(0, 2);
			String minutes = meetsAt.substring(3,5);			
			
			// insert a class
			if (update == false) {
				String insert = "insert into class values('" + cname + "', '" + semester + "', " + dYear + ", to_date('" + hour + ":" + minutes + "', 'HH:MI'), " + "'" + room + "', " + fid + ")";
				stmt.executeUpdate(insert);
				stmt.close();
			}
			else {
				String insert = "update class set cname = '" + cname + "', semester = '" + semester + "', year = " + dYear + ", meets_at = to_date('" + hour + ":" + minutes + "', 'HH:MI'), " + "room = '" + room + "' where cname='" + cname + "'";
				stmt.executeUpdate(insert);
				stmt.close();
			}
			
		} catch (Exception e) {
			System.out.println("Error: " + e.getMessage());
		}
		
		return 1;
	}
	
	/**
	 * Assign students to a class.
	 */
	public int ft2SQL(String snum, String cname) {
		if (snum.equals("") || cname.equals(""))
			return -1;
		
		Statement stmt = null;
		String query = "select * from class where cname='" + cname + "'";
		String storedFID = "";

		try {
			stmt = c.createStatement();
			boolean r = stmt.execute(query);
			
			// check if class is in db
			if (r) {
				ResultSet rs = stmt.getResultSet();
				while (rs.next()) {
					storedFID = rs.getString("fid");	
					
					// if class is already in database, check if faculty teaches it
					if (fid.equals(storedFID)) {
						break;
					}
					else {
						return -2; 
					}
				}
			}
			
			String insert = "insert into enrolled values(" + snum + ", '" + cname + "')";
			stmt.executeUpdate(insert);
			stmt.close();	
		} catch (Exception e) {
			return -3;
		}
		
		return 1;
	}

	/**
	 * Creates/Modify an evaluation.
	 */
	@SuppressWarnings("unused")
	public int ft3SQL(String name, String type, String weight, String deadline, String room, String cname) {
		if (name.equals("") || type.equals("") || weight.equals("") || deadline.equals("") || cname.equals(""))
			return -1;
		
		Statement stmt = null;
		String query = "select * from class where cname='" + cname + "'";
		String storedFID = "";

		try {
			stmt = c.createStatement();
			boolean r = stmt.execute(query);
			
			// check if class is in db
			if (r) {
				ResultSet rs = stmt.getResultSet();
				while (rs.next()) {
					storedFID = rs.getString("fid");	
					
					// if class is already in database, check if faculty teaches it
					if (fid.equals(storedFID)) {
						break;
					}
					else {
						return -2; 
					}
				}
			}
			
			// format data
			int month = Integer.parseInt(deadline.substring(0, 2));
			int day = Integer.parseInt(deadline.substring(3,5));
			int year = Integer.parseInt(deadline.substring(6, 8));

			String evalCheck = "select * from evaluation where cname = '" + cname + "' and name = '" + name + "'";
			boolean r2 = stmt.execute(evalCheck);
			boolean update = false;
			
			String n = ""; String cn = "";
			DateFormat df = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
			Calendar currentDate = Calendar.getInstance();
			String d = df.format(currentDate.getTime());
			//System.out.println(d);
			
			if (r2) {
				ResultSet rs2 = stmt.getResultSet();
				while (rs2.next()) {
					n = rs2.getString("name");
					cn = rs2.getString("cname");
					
					if (n.equals(name) && cn.equals(cname)) {
						update = true;
						break;
					}
				}
				
				if (1 == 0) {
				}
				else {
					int _y = Integer.parseInt(d.substring(2,4));
					int _m = Integer.parseInt(d.substring(5,7));
					int _d = Integer.parseInt(d.substring(8,10));
					
					if (year < _y) {
						return -4;
					}
					else if (year == _y && month < _m) {
						return -4;
					}
					else if (year == _y && month == _m && day < _d) {
						return -4;
					}
					else if (year == _y && month == _m && day == _d) {
						return -5;
					}
				}
				
				if (update == true) {
					String insert = "update evaluation set weight = " + weight + ", room = '" + room + "', deadline = to_date('" + month + "/" + day + "/" + year + "', 'MM/DD/YY') where cname='" + cname + "'";
					stmt.executeUpdate(insert);
					stmt.close();
				}
				else {
					String insert = "insert into evaluation values('" + name + "', '" + type + "', " + weight + ", to_date('" + month + "/" + day + "/" + year + "', 'MM/DD/YY'), " + "'" + room + "', '" + cname + "')";
					stmt.executeUpdate(insert);
					stmt.close();
				}
			}
		} catch (Exception e) {
			System.out.println("Error: " + e.getMessage());
			return -3;
		}
		
		return 1;
	}
}