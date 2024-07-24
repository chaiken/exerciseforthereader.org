import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class WindChill extends Applet implements AdjustmentListener, ItemListener {
	public Panel windPanel = new Panel();
	public CheckboxGroup windUnits = new CheckboxGroup();
	public Checkbox mphUnits = new Checkbox("MPH                                ", true, windUnits);
	public Checkbox kphUnits = new Checkbox("KPH                                ", false, windUnits);
	public Label windLabel = new Label("Wind Speed is 6 MPH\n", Label.LEFT);
	public int WINDSCROLLERWIDTH = 5;
	public Scrollbar windSpeedScroller = new Scrollbar(Scrollbar.HORIZONTAL, 6, 1, 5, 50+WINDSCROLLERWIDTH);
	public Panel tempPanel = new Panel();
	public CheckboxGroup tempUnits = new CheckboxGroup();
	public Checkbox fUnits = new Checkbox("F                         ", true, tempUnits);
	public Checkbox cUnits = new Checkbox("C                         ", false, tempUnits);
	public Label tempLabel = new Label("Temperature is 32 F", Label.LEFT);
	public int TEMPSCROLLERWIDTH = 10;
	public Scrollbar tempScroller = new Scrollbar(Scrollbar.HORIZONTAL, 32, 1, -50, 90+TEMPSCROLLERWIDTH);
	public Panel outPanel = new Panel();
	public Label outLabel = new Label("Windchill index is 26", Label.LEFT);
	public double windSpeedVal = 25, tempVal = 20;
	public Rectangle frameDims = this.getBounds();
	public Panel blankPanel = new Panel();
	public Panel blankPanel1 = new Panel();

	public void init(){

		//this.setSize(600,600);
		//frameDims = this.getBounds();
		this.setLayout(new GridLayout(3,1));
		windPanel.setBackground(Color.MAGENTA);
		windPanel.setLayout(new GridLayout(4,1));
		this.add(windPanel);
		tempPanel.setBackground(Color.YELLOW);
		tempPanel.setLayout(new GridLayout(4,1));
		this.add(tempPanel);
		outPanel.setBackground(Color.GREEN);
		outPanel.setLayout(new GridLayout(3,1));
		this.add(outPanel);
		windSpeedScroller.setVisibleAmount(WINDSCROLLERWIDTH);
		windPanel.add(windSpeedScroller);
		windPanel.add(windLabel);
		windPanel.add(mphUnits);
		windPanel.add(kphUnits);
		tempScroller.setVisibleAmount(TEMPSCROLLERWIDTH);
		tempPanel.add(tempScroller);
		tempPanel.add(tempLabel);
		tempPanel.add(fUnits);
		tempPanel.add(cUnits);
		outPanel.add(blankPanel);
		outPanel.add(outLabel);
		outPanel.add(blankPanel1);
		outLabel.setAlignment(Label.LEFT);
		mphUnits.addItemListener(this);
		kphUnits.addItemListener(this);
		fUnits.addItemListener(this);
		cUnits.addItemListener(this);
		windSpeedScroller.addAdjustmentListener(this);
		tempScroller.addAdjustmentListener(this);
	}

	public void paint(Graphics g){
		frameDims = this.getBounds();
		//showStatus("Dimensions are " + frameDims);
		windPanel.setSize((int)frameDims.getWidth(),(int)frameDims.getHeight()/3);
		tempPanel.setSize((int)frameDims.getWidth(),(int)frameDims.getHeight()/3);
		outPanel.setSize((int)frameDims.getWidth(),(int)frameDims.getHeight()/3);

	}


	public void adjustmentValueChanged(AdjustmentEvent ae){

		if (ae.getSource() == windSpeedScroller) {
			windSpeedVal = (double) windSpeedScroller.getValue();
			if (mphUnits.getState() == true) 
				windLabel.setText("Wind Speed is " + windSpeedVal +  " MPH");
			else windLabel.setText("Wind Speed is " + windSpeedVal +  " KPH");
		}
		else if (ae.getSource() == tempScroller){
			tempVal = (double) tempScroller.getValue();
			if (fUnits.getState() == true)
				tempLabel.setText("Temperature is " + tempVal + " F");
			else tempLabel.setText("Temperature is " + tempVal + " C");
		}
		outLabel.setText("Windchill index is " + Math.round(calcWindChill()));
	}

	public void itemStateChanged(ItemEvent ie){
		double windMax = windSpeedScroller.getMaximum();
		double windMin = windSpeedScroller.getMinimum();
		double windVal = windSpeedScroller.getValue();
		double tempMax = tempScroller.getMaximum();
		double tempMin = tempScroller.getMinimum();
		double tempVal = tempScroller.getValue();

		if (ie.getSource() == mphUnits){
			windMax = kToM(windMax);
			windMin = kToM(windMin);
			windVal = kToM(windVal);
			windSpeedScroller.setMaximum((int) Math.round(windMax));
			windSpeedScroller.setMinimum((int) Math.round(windMin));
			windSpeedScroller.setValue((int) Math.round(windVal));
			windLabel.setText("WindSpeed is " + Math.round(windVal) + " MPH");
		}

		if (ie.getSource() == kphUnits){
			windMax = mToK(windMax);
			windMin = mToK(windMin);
			windVal = mToK(windVal);
			windSpeedScroller.setMaximum((int) Math.round(windMax));
			windSpeedScroller.setMinimum((int) Math.round(windMin));
			windSpeedScroller.setValue((int) Math.round(windVal));
			windLabel.setText("Wind Speed is " + Math.round(windVal) + " KPH");
		}
		if (ie.getSource() == fUnits)
		{
			tempMax = cToF(tempMax);
			tempMin = cToF(tempMin);
			tempVal = cToF(tempVal);
			tempScroller.setMaximum((int) Math.round(tempMax));
			tempScroller.setMinimum((int) Math.round(tempMin));
			tempScroller.setValue((int) Math.round(tempVal));
			tempLabel.setText("Temperature is " + tempVal + " F");
		}

		if (ie.getSource() == cUnits){
			tempMax = fToC(tempMax);
			tempMin = fToC(tempMin);
			tempVal = fToC(tempVal);
			tempScroller.setMaximum((int) Math.round(tempMax));
			tempScroller.setMinimum((int) Math.round(tempMin));
			tempScroller.setValue((int) Math.round(tempVal));
			tempLabel.setText("Temperature is " + tempVal + " C");
		}
		outLabel.setText("Windchill index is " + Math.round(calcWindChill()));
	}

	public double fToC(double currTemp){
		return (5.0/9.0)*(currTemp - 32.0);
	}

	public double cToF(double currTemp){
		return ((9.0/5.0)*currTemp) + 32.0;
	}

	public double mToK(double currSpeed){
		return currSpeed/0.62137119;
	}

	public double kToM(double currSpeed){
		return currSpeed*0.62137119;
	}

	public double calcWindChill(){
		double wcIndex = 0.0, temperature = 0.0, windSpeed = 0.0, x;

		temperature = tempScroller.getValue();
		windSpeed = windSpeedScroller.getValue();

		if (cUnits.getState() == true) temperature = cToF(temperature);
		if (kphUnits.getState()== true) windSpeed = kToM(windSpeed);
		x =  0.303439* Math.sqrt(windSpeed) - 0.0202886*windSpeed;
		wcIndex = 91.9 - (91.4 - temperature)*(x+0.474266);
		if (cUnits.getState() == true) wcIndex = fToC(wcIndex);
		return wcIndex;
	}


}
