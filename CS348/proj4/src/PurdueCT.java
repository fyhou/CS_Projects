import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;

public class PurdueCT implements ActionListener{
	int user = 0; // 0 = faculty, 1 = student
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
		
		createClass.addActionListener(this);
		assignStudents.addActionListener(this);
		createEval.addActionListener(this);
		reportClasses.addActionListener(this);
		reportStudents.addActionListener(this);
		
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
	 * Add action listeners for all buttons.
	 */
	public void addActionListeners() {
		bSubmitFT1.addActionListener(this);
		bCancelFT1.addActionListener(this);
		
		bSubmitFT2.addActionListener(this);
		bCancelFT2.addActionListener(this);
		
		bSubmitFT3.addActionListener(this);
		bCancelFT3.addActionListener(this);
	}
	
	/**
	 * Event handler for everything.
	 */
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
					//studentGUI();
					System.out.println("Valid user!");
				}
				else {
					JOptionPane.showMessageDialog(login, "Invalid credentials!", "Oops!", JOptionPane.WARNING_MESSAGE);
					return;
				}
			}

			login.setVisible(false);
			
			return;
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
			fFrame.setVisible(false);
			return;
		}
		else if ("reportStudents".equals(e.getActionCommand())) {
			fFrame.setVisible(false);
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