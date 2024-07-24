import java.applet.*;
import java.awt.*;
import java.awt.event.*;

/*
 * <applet code="FourFuncApplet" width=500 height=500></applet>
 */

//public class FourFuncCalcApplet extends Applet{
public class FourFuncCalcApplet extends Applet implements Runnable, TextListener, ActionListener {
//	public class FourFuncCalcApplet extends Applet implements ActionListener {

	public TextField operand1String = new TextField(15);
	public TextField operand2String = new TextField(15);
	public Label calcResult = new Label("0.000                          ", Label.LEFT);
	public Button[] fourButtons = new Button[4];
	public String buttonLabels[] = {"+", "-", "x", "/"}; 
	Thread t2 = null;
	boolean stopFlag2;

	public void init(){
		setBackground(Color.YELLOW);
		setForeground(Color.BLACK);
		setLayout(new FlowLayout(FlowLayout.CENTER));
		//setLayout(new GridLayout(2,2));

		//showStatus("In FourFuncCalcApplet init routine.");

		add(operand1String);
		add(operand2String);
		add(calcResult);

		for(int i = 0; i < 4; i++)
		{
			fourButtons[i] = new Button(buttonLabels[i]);
			add(fourButtons[i]);
			fourButtons[i].addActionListener(this);
		}

		operand1String.addTextListener(this);
		operand2String.addTextListener(this);
	}

	// Entry point for the thread that runs the calculator.
	public void run() {
		for( ; ; ) {
			try {
				//repaint();
				if(stopFlag2)
					break;
//			} catch(InterruptedException e) {}
		} catch(Exception e) {}
	}
}

// Pause the calculator.
public void stop() {
	stopFlag2 = true;
	t2 = null;
}

public void actionPerformed(ActionEvent e){
	int currButton = 0;
	String emptyString = "", resultString;
	double operand1 = 0.0, operand2 = 0.0, intermediate=0.0;


	for(int i = 0; i < 4; i++)	
		if (e.getSource() == fourButtons[i]){
			currButton = i;
		}
	//		showStatus("Pushed button " + i);}

	//showStatus("Button " + currButton);	

	//check if operands have been entered
	if ((operand1String.getText().equals(emptyString) != true) & (operand2String.getText().equals(emptyString) != true)) {
		//showStatus("Both operand fields populated.");
		operand1 = Double.parseDouble(operand1String.getText());
		operand2 = Double.parseDouble(operand2String.getText());

		switch(currButton) {

		case 0:
			intermediate = operand1 + operand2;
			break;
		case 1: 
			intermediate = operand1 - operand2;
			break;
		case 2:
			intermediate = operand1 * operand2;
			break;
		case 3:
			if (operand2 == 0.0) {
				showStatus("Attempt to divide by zero.");
				return;
			}
			intermediate = operand1 / operand2;

		}

		resultString = String.valueOf(intermediate);
		calcResult.setText(resultString);
	}

}

public void textValueChanged(TextEvent te){
	//	showStatus(te.toString());
}

}
