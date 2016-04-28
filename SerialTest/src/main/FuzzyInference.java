package main;
import net.sourceforge.jFuzzyLogic.FIS;

public class FuzzyInference {
	private String FileName;
	private FIS fis;
	public FuzzyInference(String FileName) {
		this.FileName = FileName;
        fis = FIS.load(this.FileName,true);
        // Error while loading?
        if( fis == null ) { 
            System.err.println("Can't load file: '" + FileName + "'");
            return;
        }
	}
	
	public double getEnvironmentStatus(double temperature, int light) {
		updateVar(temperature, light);
		// Evaluate
        fis.evaluate();
        return fis.getVariable("environment_status").defuzzify();
	}

	public void updateVar(double temperature, int light) {
		fis.setVariable("temperature", temperature);
        fis.setVariable("light", light);
	}
	
}
