/* A simple banner applet.

	   This applet creates a thread that scrolls
	   the message contained in msg right to left
	   across the applet's window.
 */
import java.awt.*;
import java.applet.*;
/*
	<applet code="SimpleBanner" width=300 height=50>
	</applet>
 */

public class SimpleBanner extends Applet implements Runnable {
	String msg = " Say YES to Multi-threading!";
	Thread t = null, t2 = null;
	int state;
	boolean stopFlag, stopFlag2;
	FourFuncCalcApplet enclosedCalc = new FourFuncCalcApplet();
	Font f;

	// Set colors and initialize thread.
	public void init() {
//		setLayout(new GridLayout(2,1));
		setBackground(Color.cyan);
		add(enclosedCalc);
	}

	// Start thread
	public void start() {
		t = new Thread(this);
		stopFlag = false;
		t.start();
		enclosedCalc.init();
	//	stopFlag2 = false;
		t2 = new Thread(enclosedCalc);
		t2.start();
	}

	// Entry point for the thread that runs the banner.
	public void run() {
		char ch;

		// Display banner 
		for( ; ; ) {
			try {
				repaint();
				Thread.sleep(250);
				ch = msg.charAt(0);
				msg = msg.substring(1, msg.length());
				msg += ch;
				if(stopFlag)
					break;
			} catch(InterruptedException e) {}
		}
	}

	// Pause the banner.
	public void stop() {
		stopFlag = true;
		t = null;
	}

	// Display the banner.
	public void paint(Graphics g) {
		f = new Font(msg, Font.TRUETYPE_FONT,24);
		Color saveColor = g.getColor();
		g.setColor(Color.YELLOW);
		g.fillRect(90,60,400,50);
		g.setPaintMode();

		Font saveFont = g.getFont();
		g.setFont(f);
		g.setColor(Color.BLACK);
		g.drawString(msg, 100, 100);
		g.setFont(saveFont);
		g.setColor(saveColor);
	}
}
