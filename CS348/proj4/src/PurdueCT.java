import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

import java.util.*;
import java.util.List;

public class PurdueCT implements ActionListener{
	int user = 0; // 0 = faculty, 1 = student
	int rowsToClear = 0;
	int rowsToClear2 = 0;
	int rowsToClear3 = 0;
	int rowsToClear4 = 0;
	int rowsToClear5 = 0;
	FacultyTools ft = new FacultyTools();
	StudentTools st = new StudentTools();
	
	// Login GUI Components
	JFrame login = new JFrame("Purdue CT");
	JPanel p1 = new JPanel();
	
	JLabel welcome = new JLabel("");
	JLabel lUserID = new JLabel("User ID:");
	JLabel lPassword = new JLabel("Password:");		
	
	JTextField tfUserID = new JTextField(100);
	JPasswordField pfPassword = new JPasswordField();
		
	JRadioButton fButton = new JRadioButton("Faculty");
	JRadioButton sButton = new JRadioButton("Student");
	
	ButtonGroup bg = new ButtonGroup();	
	JButton okButton = new JButton("OK");
	JButton cancelButton = new JButton("Cancel");

	
	// Faculty GUI Components
	JFrame fFrame = new JFrame("Purdue CT [Faculty View]");
	JPanel p2 = new JPanel();
	
	JButton createClass = new JButton("Create/Modify a class");
	JButton assignStudents = new JButton("Assign students to a class");
	JButton createEval = new JButton("Create/Modify an evaluation");
	JButton reportClasses = new JButton("Report of classes");
	JButton reportStudents = new JButton("Report of students and grades");
	
	
	// Tool 1 for Faculty Components
	JFrame ft1Frame = new JFrame("Create/Modify a class");
	JPanel p3 = new JPanel();
	
	JLabel lClassName = new JLabel("Class name: ");
	JLabel lSemester = new JLabel("Semester (F or S): ");
	JLabel lYear = new JLabel("Year (YYYY): ");
	JLabel lMeetsAt = new JLabel("Meets at (HH:MI): ");
	JLabel lRoom = new JLabel("Room: ");
	
	JTextField tfClassName = new JTextField(100);
	JTextField tfSemester = new JTextField(100);
	JTextField tfYear = new JTextField(100);
	JTextField tfMeetsAt = new JTextField(100);
	JTextField tfRoom = new JTextField(100);
	
	JButton bSubmitFT1 = new JButton("Submit");
	JButton bCancelFT1 = new JButton("Cancel");
	
	
	// Tool 2 for Faculty Components
	JFrame ft2Frame = new JFrame("Assign students to a class");
	JPanel p4 = new JPanel();
	
	JLabel lStudentName = new JLabel("Student number: ");
	JLabel lClassName2 = new JLabel("Class name: ");
	
	JTextField tfStudentName = new JTextField(100);
	JTextField tfClassName2 = new JTextField(100);
	
	JButton bSubmitFT2 = new JButton("Submit");
	JButton bCancelFT2 = new JButton("Cancel");
	
	
	// Tool 3 for Faculty Components 
	JFrame ft3Frame = new JFrame("Create/Modify an evaluation");
	JPanel p5 = new JPanel();
	
	JLabel lEvName = new JLabel("Evaluation name: ");
	JLabel lEvType = new JLabel("Type (HW, M, F, or P): ");
	JLabel lWeight = new JLabel("Weight (Percentage): ");
	JLabel lRoom2 = new JLabel("Room: ");
	JLabel lClassName3 = new JLabel("Class name: ");
	JLabel lDeadline = new JLabel("Due date (MM/DD/YY): ");
	
	JTextField tfClassName3 = new JTextField(100);
	JTextField tfEvName = new JTextField(100);
	JTextField tfEvType =  new JTextField(100);
	JTextField tfWeight = new JTextField(100);
	JTextField tfDeadline = new JTextField(100);
	JTextField tfRoom2 = new JTextField(100);
	
	JButton bSubmitFT3 = new JButton("Submit");
	JButton bCancelFT3 = new JButton("Cancel");
	
	
	// Tool 4 for Faculty Components
	JFrame ft4Frame = new JFrame("Report of classes");
	JPanel p6 = new JPanel();
	
	Object[][] _dummy = new Object[100][5];
	String[] colNames = {"Class Name", "Meets At", "Room", "# of Students", "# of Evaluations"};
	@SuppressWarnings("serial")
	JTable tClass = new JTable(_dummy, colNames) {
	    public boolean isCellEditable(int rowIndex, int vColIndex) {
	        return false;
	    }
	};
	
	// Tool 5 for Faculty Components
	JFrame ft5Frame = new JFrame("Report of students and grades");
	JPanel p7 = new JPanel();
		
	Object[][] _dummy2 = new Object[100][5];
	String[] colNames2 = {"Class Name", "Semester", "Year", "Student Name", "Current Grade"};
	@SuppressWarnings("serial")
	JTable tStudents = new JTable(_dummy2, colNames2) {

	    public boolean isCellEditable(int rowIndex, int vColIndex) {
	        return false;
	    }
	};
	
	
	// Student GUI
	
	
	// Student GUI Components
	JFrame sFrame = new JFrame("Purdue CT [Student View]");
	JPanel p8 = new JPanel();
	
	JLabel welcomeStudent = new JLabel("");
	JButton getCalendar = new JButton("Calendar of evaluations");
	JButton getClasses = new JButton("My classes");
	JButton getGrades = new JButton("My grades");
	
	
	// Tool 1 for Students
	JFrame st1Frame = new JFrame("Calendar of evaluations");
	JPanel p9 = new JPanel();
	
	Object[][] _dummy3 = new Object[100][6];
	String[] colNames3 = {"Name", "Type", "Weight", "Due Date", "Room", "Class"};
	
	@SuppressWarnings("serial")
	JTable tEvals = new JTable(_dummy3, colNames3) {

	    public boolean isCellEditable(int rowIndex, int vColIndex) {
	        return false;
	    }
	};
	
	
	// Tool 2 for Students
	JFrame st2Frame = new JFrame("My classes");
	JPanel p10 = new JPanel();
	
	Object[][] _dummy4 = new Object[100][5];
	String[] colNames4 = {"Semester", "Year", "Class", "Meets At", "Room"};
	
	@SuppressWarnings("serial")
	JTable tClasses = new JTable(_dummy4, colNames4) {

	    public boolean isCellEditable(int rowIndex, int vColIndex) {
	        return false;
	    }
	};
	
	
	// Tool 3 for Students
	JFrame st3Frame = new JFrame("My grades");
	JPanel p11 = new JPanel();
	
	Object[][] _dummy5 = new Object[100][4];
	String[] colNames5 = {"Class Name", "Evaluation", "Weight", "Mark"};
	
	@SuppressWarnings("serial")
	JTable tGrades = new JTable(_dummy5, colNames5) {

	    public boolean isCellEditable(int rowIndex, int vColIndex) {
	        return false;
	    }
	};
	
	/**
	 * Entry point
	 */
	public static void main(String[] args) {
		PurdueCT p = new PurdueCT();
		p.addActionListeners();
		p.loginGUI();
	}
	
	/**
	 * Login GUI.
	 */
	public void loginGUI() {
		fButton.setSelected(true);
		bg.add(fButton);
		bg.add(sButton);
		
		okButton.setActionCommand("OK");
		okButton.addActionListener(this);
		cancelButton.setActionCommand("Cancel");
		cancelButton.addActionListener(this);
		
		p1.setLayout(new GridLayout(0, 2, 10, 10));
		p1.add(lUserID);
		p1.add(tfUserID);
		p1.add(lPassword);
		p1.add(pfPassword);
		p1.add(fButton);
		p1.add(sButton);
		p1.add(okButton);
		p1.add(cancelButton);
		
		login.add(p1);
		
		login.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		login.setSize(250,175);
		login.setLocationRelativeTo(null);
		login.setVisible(true);
	}
	
	/**
	 * Faculty View GUI.
	 */
	public void facultyGUI() {
		String name = "";
		if (tfUserID.getText().equals(""))
			name = "Faculty";
		else 
			name = tfUserID.getText();
		
		fFrame.setLayout(new GridLayout(0, 1));
		welcome.setText("Welcome, " + name + "!");
		
		createClass.setActionCommand("createClass");
		assignStudents.setActionCommand("assignStudents");
		createEval.setActionCommand("createEval");
		reportClasses.setActionCommand("reportClasses");
		reportStudents.setActionCommand("reportStudents");
		
		p2.setLayout(new GridLayout(0, 1, 5, 5));
		p2.add(welcome);
		p2.add(createClass);
		p2.add(assignStudents);
		p2.add(createEval);
		p2.add(reportClasses);
		p2.add(reportStudents);
		
		fFrame.add(p2);
		
		fFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		fFrame.setSize(350,400);
		fFrame.setLocationRelativeTo(null);
		fFrame.setVisible(true);
	}
	
	/**
	 * Faculty Tool 1 GUI (Create/modify a class).
	 */
	public void ft1GUI() {
		ft1Frame.setLayout(new GridLayout(0,1, 10, 10));
		
		bSubmitFT1.setActionCommand("bSubmitFT1");
		bCancelFT1.setActionCommand("bCancelFT1");
		
		p3.setLayout(new GridLayout(0,2, 10, 10));
		p3.add(lClassName); p3.add(tfClassName);
		p3.add(lSemester); p3.add(tfSemester);
		p3.add(lYear); p3.add(tfYear);
		p3.add(lMeetsAt); p3.add(tfMeetsAt);
		p3.add(lRoom); p3.add(tfRoom);
		p3.add(bSubmitFT1); p3.add(bCancelFT1);
		
		ft1Frame.add(p3);
		
		ft1Frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		ft1Frame.setSize(250,215);
		ft1Frame.setLocationRelativeTo(null);
		ft1Frame.setVisible(true);
	}

	/**
	 * Faculty Tool 2 GUI (Assign students to class).
	 */
	public void ft2GUI() {
		ft2Frame.setLayout(new GridLayout(0,1, 10, 10));
		
		bSubmitFT2.setActionCommand("bSubmitFT2");
		bCancelFT2.setActionCommand("bCancelFT2");
		
		p4.setLayout(new GridLayout(0,2, 10, 10));
		p4.add(lStudentName); p4.add(tfStudentName);
		p4.add(lClassName2); p4.add(tfClassName2);
		p4.add(bSubmitFT2); p4.add(bCancelFT2);
		
		ft2Frame.add(p4);
		
		ft2Frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		ft2Frame.setSize(275,125);
		ft2Frame.setLocationRelativeTo(null);
		ft2Frame.setVisible(true);
	}
	
	/**
	 * Faculty Tool 3 GUI (Evaluations).
	 */
	public void ft3GUI() {
		ft3Frame.setLayout(new GridLayout(0,1, 10, 10));
		
		bSubmitFT3.setActionCommand("bSubmitFT3");
		bCancelFT3.setActionCommand("bCancelFT3");
		
		p5.setLayout(new GridLayout(0,2, 10, 10));
		p5.add(lEvName); p5.add(tfEvName);
		p5.add(lEvType); p5.add(tfEvType);
		p5.add(lWeight); p5.add(tfWeight);
		p5.add(lDeadline); p5.add(tfDeadline);
		p5.add(lRoom2); p5.add(tfRoom2);
		p5.add(lClassName3); p5.add(tfClassName3);
		p5.add(bSubmitFT3); p5.add(bCancelFT3);
		
		ft3Frame.add(p5);
		
		ft3Frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		ft3Frame.setSize(320,275);
		ft3Frame.setLocationRelativeTo(null);
		ft3Frame.setVisible(true);
	}
	
	/**
	 * Faculty Tool 4 GUI (Class Report).
	 */
	public void ft4GUI(List<TableRow> data) {
		Collections.sort(data); 
		tClass.setColumnSelectionAllowed(false);
		tClass.setRowSelectionAllowed(false);
		
		int i = 0;
		for (i = 0; i <= rowsToClear; i++) {
			tClass.getModel().setValueAt("", i, 0);
	    	tClass.getModel().setValueAt("", i, 1);
	    	tClass.getModel().setValueAt("", i, 2);
	    	tClass.getModel().setValueAt("", i, 3);
	    	tClass.getModel().setValueAt("", i, 4);
		}
		
		ft4Frame.setLayout(new GridLayout(0, 1, 10, 10)); 	
		p6.setLayout(new GridLayout(0, 1, 10, 10));
		
		i = 0;
	    for (TableRow t: data) {
	    	tClass.getModel().setValueAt(t.cname, i, 0);
	    	tClass.getModel().setValueAt(t.meetsAt, i, 1);
	    	tClass.getModel().setValueAt(t.room, i, 2);
	    	tClass.getModel().setValueAt(t.nStudents, i, 3);
	    	tClass.getModel().setValueAt(t.nEvals, i, 4);
	    	i++;
	    }
		
	    rowsToClear = i; // for next time
	    
		ft4Frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		ft4Frame.setSize(500,275);
		ft4Frame.setLocationRelativeTo(null);
		ft4Frame.setVisible(true);
	}
	
	/**
	 * Faculty Tool 5 GUI (Student Report).
	 */
	public void ft5GUI(List<TableRow2> data2) {
		Collections.sort(data2); 
		tStudents.setColumnSelectionAllowed(false);
		tStudents.setRowSelectionAllowed(false);
		
		int i = 0;
		for (i = 0; i <= rowsToClear2; i++) {
			tStudents.getModel().setValueAt("", i, 0);
			tStudents.getModel().setValueAt("", i, 1);
			tStudents.getModel().setValueAt("", i, 2);
			tStudents.getModel().setValueAt("", i, 3);
			tStudents.getModel().setValueAt("", i, 4);
		}
		
		ft5Frame.setLayout(new GridLayout(0, 1, 10, 10)); 	
		p7.setLayout(new GridLayout(0, 1, 10, 10));
		
		i = 0;
	    for (TableRow2 t: data2) {
	    	tStudents.getModel().setValueAt(t.cname, i, 0);
	    	tStudents.getModel().setValueAt(t.semester, i, 1);
	    	tStudents.getModel().setValueAt(t.year, i, 2);
	    	tStudents.getModel().setValueAt(t.sname, i, 3);
	    	tStudents.getModel().setValueAt(t.currGrade, i, 4);
	    	i++;
	    }
		
	    rowsToClear2 = i; // for next time
	    
		ft5Frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		ft5Frame.setSize(500,275);
		ft5Frame.setLocationRelativeTo(null);
		ft5Frame.setVisible(true);
	}
	
	/**
	 * Faculty View GUI.
	 */
	public void studentGUI() {
		String name = "";
		if (tfUserID.getText().equals(""))
			name = "Student";
		else 
			name = tfUserID.getText();
		
		sFrame.setLayout(new GridLayout(0, 1));
		welcomeStudent.setText("Welcome, " + name + "!");
		
		getCalendar.setActionCommand("getCalendar");
		getClasses.setActionCommand("getClasses");
		getGrades.setActionCommand("getGrades");
		
		p8.setLayout(new GridLayout(0, 1, 5, 5));
		p8.add(welcomeStudent);
		p8.add(getCalendar);
		p8.add(getClasses);
		p8.add(getGrades);
		
		sFrame.add(p8);
		
		sFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		sFrame.setSize(350,280);
		sFrame.setLocationRelativeTo(null);
		sFrame.setVisible(true);
	}
	
	/**
	 * Student Tool 1 GUI (Evaluation Calendar).
	 */
	public void st1GUI(List<Evaluation> data) {
		Collections.sort(data); 
		tEvals.setColumnSelectionAllowed(false);
		tEvals.setRowSelectionAllowed(false);
		
		int i = 0;
		for (i = 0; i <= rowsToClear3; i++) {
			tEvals.getModel().setValueAt("", i, 0);
			tEvals.getModel().setValueAt("", i, 1);
			tEvals.getModel().setValueAt("", i, 2);
			tEvals.getModel().setValueAt("", i, 3);
			tEvals.getModel().setValueAt("", i, 4);
			tEvals.getModel().setValueAt("", i, 5);
		}
		
		st1Frame.setLayout(new GridLayout(0, 1, 10, 10)); 	
		p9.setLayout(new GridLayout(0, 1, 10, 10));
		
		i = 0;
		String last = "";
		
	    for (Evaluation t: data) {
	    	if (last.equals("")) {
	    		last = t.cname;
	    	}
	    	
	    	if (last.equals(t.cname) == false) {
	    		tEvals.getModel().setValueAt("", i, 0);
	    		tEvals.getModel().setValueAt("", i, 1);
	    		tEvals.getModel().setValueAt("", i, 2);
	    		tEvals.getModel().setValueAt("", i, 3);
	    		tEvals.getModel().setValueAt("", i, 4);
	    		tEvals.getModel().setValueAt("", i, 5);
	    		i++;
	    	}
	    	
	    	tEvals.getModel().setValueAt(t.name, i, 0);
	    	tEvals.getModel().setValueAt(t.type, i, 1);
	    	tEvals.getModel().setValueAt(t.weight, i, 2);
	    	tEvals.getModel().setValueAt(t.deadline, i, 3);
	    	tEvals.getModel().setValueAt(t.room, i, 4);
	    	tEvals.getModel().setValueAt(t.cname, i, 5);
	    	i++;
	    	
	    	last = t.cname; 
	    }
		
	    rowsToClear3 = i; // for next time
	    
		st1Frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		st1Frame.setSize(520,275);
		st1Frame.setLocationRelativeTo(null);
		st1Frame.setVisible(true);
	}
	
	/**
	 * Student Tool 2 GUI (My Classes).
	 */
	public void st2GUI(List<ClassTable> data) {
		Collections.sort(data); 
		tClasses.setColumnSelectionAllowed(false);
		tClasses.setRowSelectionAllowed(false);
		
		int i = 0;
		for (i = 0; i <= rowsToClear4; i++) {
			tClasses.getModel().setValueAt("", i, 0);
			tClasses.getModel().setValueAt("", i, 1);
			tClasses.getModel().setValueAt("", i, 2);
			tClasses.getModel().setValueAt("", i, 3);
			tClasses.getModel().setValueAt("", i, 4);
		}
		
		st2Frame.setLayout(new GridLayout(0, 1, 10, 10)); 	
		p10.setLayout(new GridLayout(0, 1, 10, 10));
		
		i = 0;

	    for (ClassTable t: data) {
	    	tClasses.getModel().setValueAt(t.semester, i, 0);
	    	tClasses.getModel().setValueAt(t.year, i, 1);
	    	tClasses.getModel().setValueAt(t.cname, i, 2);
	    	tClasses.getModel().setValueAt(t.meetsAt, i, 3);
	    	tClasses.getModel().setValueAt(t.room, i, 4);
	    	i++;
	    }
		
	    rowsToClear4 = i; // for next time
	    
		st2Frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		st2Frame.setSize(520,275);
		st2Frame.setLocationRelativeTo(null);
		st2Frame.setVisible(true);
	}
	
	/**
	 * Student Tool 3 GUI (My Grades).
	 */
	public void st3GUI(List<Grade> data) {
		Collections.sort(data); 
		tGrades.setColumnSelectionAllowed(false);
		tGrades.setRowSelectionAllowed(false);
		
		int i = 0;
		for (i = 0; i <= rowsToClear5; i++) {
			tGrades.getModel().setValueAt("", i, 0);
			tGrades.getModel().setValueAt("", i, 1);
			tGrades.getModel().setValueAt("", i, 2);
			tGrades.getModel().setValueAt("", i, 3);
		}
		
		st3Frame.setLayout(new GridLayout(0, 1, 10, 10)); 	
		p11.setLayout(new GridLayout(0, 1, 10, 10));
		
		i = 0;
	    for (Grade t: data) {
	    	tGrades.getModel().setValueAt(t.cname, i, 0);
	    	tGrades.getModel().setValueAt(t.name, i, 1);
	    	tGrades.getModel().setValueAt(t.weight, i, 2);
	    	tGrades.getModel().setValueAt(t.mark, i, 3);
	    	i++;
	    	
	    	if (t.weight.equals("N/A")) {
	    		tGrades.getModel().setValueAt("", i, 0);
	    		tGrades.getModel().setValueAt("", i, 1);
	    		tGrades.getModel().setValueAt("", i, 2);
	    		tGrades.getModel().setValueAt("", i, 3);
	    		i++;
	    	}
	    }
		
	    rowsToClear5 = i; // for next time
	    
		st3Frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		st3Frame.setSize(520,275);
		st3Frame.setLocationRelativeTo(null);
		st3Frame.setVisible(true);
	}
	
	/**
	 * Add action listeners for all buttons.
	 */
	public void addActionListeners() {
		createClass.addActionListener(this);
		assignStudents.addActionListener(this);
		createEval.addActionListener(this);
		reportClasses.addActionListener(this);
		reportStudents.addActionListener(this);
		
		bSubmitFT1.addActionListener(this);
		bCancelFT1.addActionListener(this);
		
		bSubmitFT2.addActionListener(this);
		bCancelFT2.addActionListener(this);
		
		bSubmitFT3.addActionListener(this);
		bCancelFT3.addActionListener(this);
		
		p6.add(new JScrollPane(tClass));	
		ft4Frame.add(p6);
		
		p7.add(new JScrollPane(tStudents));
		ft5Frame.add(p7);
		
		getCalendar.addActionListener(this);
		getClasses.addActionListener(this);
		getGrades.addActionListener(this);
		
		p9.add(new JScrollPane(tEvals));
		st1Frame.add(p9);
		
		p10.add(new JScrollPane(tClasses));
		st2Frame.add(p10);
		
		p11.add(new JScrollPane(tGrades));
		st3Frame.add(p11);
	}
	
	/**
	 * Event handler for everything.
	 */
	@SuppressWarnings("deprecation")
	public void actionPerformed (ActionEvent e) {
		int err = 0;
		
		// LOGIN BUTTONS
		if ("OK".equals(e.getActionCommand())) {
			// determines if user is faculty or a student
			if (fButton.isSelected()) {
				if (ft.isValidUser(tfUserID.getText(), pfPassword.getText())) {
					facultyGUI();
					tfUserID.setText(null);
					pfPassword.setText(null);
					return;
				}
				else {
					JOptionPane.showMessageDialog(login, "Invalid credentials!", "Error", JOptionPane.WARNING_MESSAGE);
					tfUserID.setText(null);
					pfPassword.setText(null);
					return;
				}
			}
			else {
				if (st.isValidUser(tfUserID.getText(), pfPassword.getText())) {
					studentGUI();
					tfUserID.setText(null);
					pfPassword.setText(null);
					return;
				}
				else {
					JOptionPane.showMessageDialog(login, "Invalid credentials!", "Oops!", JOptionPane.WARNING_MESSAGE);
					tfUserID.setText(null);
					pfPassword.setText(null);
					return;
				}
			}
		}
		else if ("Cancel".equals(e.getActionCommand())) {
			login.setVisible(false);
			System.exit(0);
			return;
		}
		// FACULTY BUTTONS
		else if ("createClass".equals(e.getActionCommand())) {
			ft1GUI();
			return;
		}
		else if ("assignStudents".equals(e.getActionCommand())) {
			ft2GUI();
			return;
		}
		else if ("createEval".equals(e.getActionCommand())) {
			ft3GUI();
			return;
		}
		else if ("reportClasses".equals(e.getActionCommand())) {
			List<TableRow> data = new ArrayList<TableRow>();
			data = ft.ft4SQL();
			
			ft4GUI(data);
			
			return;
		}
		else if ("reportStudents".equals(e.getActionCommand())) {
			List<TableRow2> data = new ArrayList<TableRow2>();
			data = ft.ft5SQL(); 
			
			ft5GUI(data);
			return;
		}
		// STUDENT BUTTONS
		else if ("getCalendar".equals(e.getActionCommand())) {
			List<Evaluation> data = new ArrayList<Evaluation>();
			data = st.st1SQL();
			
			st1GUI(data);
			return;
		}
		else if ("getClasses".equals(e.getActionCommand())) {
			//st2GUI();
			List<ClassTable> data = new ArrayList<ClassTable>();
			data = st.st2SQL();
			
			st2GUI(data);
			return;
		}
		else if ("getGrades".equals(e.getActionCommand())) {
			//st3GUI();
			List<Grade> data = new ArrayList<Grade>();
			data = st.st3SQL();
			
			st3GUI(data);
			return;
		}
		// FACULTY TOOL 1 BUTTONS
		else if ("bSubmitFT1".equals(e.getActionCommand())) {
			err = ft.ft1SQL(tfClassName.getText(), tfSemester.getText(), tfYear.getText(), tfMeetsAt.getText(), tfRoom.getText());
			if (err > 0) {
				tfClassName.setText("");
				tfSemester.setText("");
				tfYear.setText("");
				tfMeetsAt.setText("");
				tfRoom.setText("");
				ft1Frame.dispose();
				return; 
			}
			else {
				System.out.println(err);
				if (err == -1) {
					JOptionPane.showMessageDialog(ft1Frame, "Make sure all fields are valid!", "Oops!", JOptionPane.WARNING_MESSAGE);
				}
				else if (err == -2) {
					JOptionPane.showMessageDialog(ft1Frame, "You don't teach that class!", "Oops!", JOptionPane.WARNING_MESSAGE);
				}
				
				tfClassName.setText("");
				tfSemester.setText("");
				tfYear.setText("");
				tfMeetsAt.setText("");
				tfRoom.setText("");			
			}
			return;
		}
		else if ("bCancelFT1".equals(e.getActionCommand())) {
			tfClassName.setText("");
			tfSemester.setText("");
			tfYear.setText("");
			tfMeetsAt.setText("");
			tfRoom.setText("");	
			
			ft1Frame.setVisible(false);
			return;
		}
		// FACULTY TOOL 2 BUTTONS
		else if ("bSubmitFT2".equals(e.getActionCommand())) {
			err = ft.ft2SQL(tfStudentName.getText(), tfClassName2.getText());
			if (err > 0) {
				tfStudentName.setText(null);
				tfClassName2.setText(null);
				ft2Frame.dispose();
			}
			else {
				if (err == -1) {
					JOptionPane.showMessageDialog(ft2Frame, "Make sure all fields are valid!", "Oops!", JOptionPane.WARNING_MESSAGE);	
				}
				else if (err == -2) {
					JOptionPane.showMessageDialog(ft2Frame, "You don't teach that class!", "Oops!", JOptionPane.WARNING_MESSAGE);
				}
				else if (err == -3) {
					JOptionPane.showMessageDialog(ft2Frame, "That student could not be added!", "Oops!", JOptionPane.WARNING_MESSAGE);
				}
				
				tfStudentName.setText(null);
				tfClassName2.setText(null);
			}
			return;
		}
		else if ("bCancelFT2".equals(e.getActionCommand())) {
			tfStudentName.setText(null);
			tfClassName2.setText(null);
			ft2Frame.setVisible(false);
			return;
		}
		// FACULTY TOOL 3 BUTTONS
		else if ("bSubmitFT3".equals(e.getActionCommand())) {
			err = ft.ft3SQL(tfEvName.getText(), tfEvType.getText(), tfWeight.getText(), tfDeadline.getText(), tfRoom2.getText(), tfClassName3.getText());
			if (err > 0) {
				tfEvName.setText(null);
				tfEvType.setText(null);
				tfWeight.setText(null);
				tfDeadline.setText(null);
				tfRoom2.setText(null);
				tfClassName3.setText(null);
				ft3Frame.dispose();
			}
			else {
				if (err == -1) {
					JOptionPane.showMessageDialog(ft3Frame, "Make sure all fields are valid!", "Oops!", JOptionPane.WARNING_MESSAGE);	
				}
				else if (err == -2) {
					JOptionPane.showMessageDialog(ft3Frame, "You don't teach that class!", "Oops!", JOptionPane.WARNING_MESSAGE);
				}
				else if (err == -3) {
					JOptionPane.showMessageDialog(ft3Frame, "That evaluation could not be added!", "Oops!", JOptionPane.WARNING_MESSAGE);
				}
				else if (err == -4) {
					JOptionPane.showMessageDialog(ft3Frame, "You can't modify evaluations from the past!", "Oops!", JOptionPane.WARNING_MESSAGE);
				}
				else if (err == -5) {
					JOptionPane.showMessageDialog(ft3Frame, "You can't modify evaluations that are due today!", "Oops!", JOptionPane.WARNING_MESSAGE);
				}
				
				tfEvName.setText(null);
				tfEvType.setText(null);
				tfWeight.setText(null);
				tfDeadline.setText(null);
				tfRoom2.setText(null);
				tfClassName3.setText(null);
			}
			return;
		}
		else if ("bCancelFT3".equals(e.getActionCommand())) {
			tfEvName.setText(null);
			tfEvType.setText(null);
			tfWeight.setText(null);
			tfDeadline.setText(null);
			tfRoom.setText(null);
			tfClassName3.setText(null);
			ft3Frame.setVisible(false);
			return;
		}
	}
}