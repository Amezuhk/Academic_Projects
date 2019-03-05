import java.util.Random;
public class Test4 extends Thread {
	String test; //enabled/disabled Cache
	int type; //test cases 1-4
	//Constructor
	public Test4(String[] args) {
		test = args[0];
		type = Integer.parseInt(args[1]);
	}
	
	//Where the magic happens O.O
    public void run( ) {
    	
    	long start; //time start
    	long end; //time end
    	long msec; //time total in microsecs
    	int n; //random holder
    	Random rand = new Random(); //for randoms
    	byte[][] x = new byte[1000][512]; //create 1000 blocks of 512 size
    	for(int i = 0; i < x.length; i++) {
    		for(int j = 0; j < x[0].length; j++) {
    			x[i][j] = (byte) i;
    		}
    	}
    	
    	//where the real magic begins
    	switch(test) {
    	case "enabled": //Cache Enabled
    		switch (type) {
    		case 1: //Random
    	    	SysLib.flush();
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) { //do 1000 random access writes
    	    		n = (int) (Math.random() * 999) + 0;
    	    		SysLib.cwrite(n, x[n]);
    	    	}
    	    	end = System.nanoTime(); //AND time!
    	    	msec = (end - start) / 1000; 
    	    	System.out.println("Time for 1000 Random Writes with Cache: " + msec + " Microsec");
    	    	
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) { //1000 random access reads
    	    		n = (int) (Math.random() * 999) + 0; 
    	    		SysLib.cread(n, x[n]);
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000 Random Reads with Cache: " + msec + " Microsec");
    			break;
    		case 2: //Localized
    	    	SysLib.flush();
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) { //1000 localized write accesses
    	    		SysLib.cwrite((i % 10), x[(i % 10)]); //blocks 1-10
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000; 
    	    	System.out.println("Time for 1000 Localized Writes with Cache: " + msec + " Microsec");
    	    	
    	    	
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {
    	    		SysLib.cread((i % 10), x[(i % 10)]); //1000 localized read accesses
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000 Localized Reads with Cache: " + msec + " Microsec");
    			break;
    		case 3: //Mixed
    	    	SysLib.flush();
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {
    	    		n = (int) (Math.random() * 10) + 1;
    	    		if(n == 1) { //10% of the time 1/10 
    	        		n = (int) (Math.random() * 999) + 0; //do random
    	        		SysLib.cwrite(n, x[n]);
    	    		}else { //else do local acceses on 1-10
    	    			SysLib.cwrite((i % 10), x[(i % 10)]);
    	    		}
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000  Mixed Writes with Cache: " + msec + " Microsec");
    	    	
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {
    	    		n = (int) (Math.random() * 10) + 1;
    	    		if(n == 1) { //10% of the time 1/10
    	        		n = (int) (Math.random() * 999) + 0;
    	        		SysLib.cread(n, x[n]);
    	    		}else {
    	    			SysLib.cread((i % 10), x[(i % 10)]);
    	    		}
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000  Mixed Reads with Cache: " + msec + " Microsec");
    			break;
    		case 4: //Adversary
    	    	SysLib.flush();
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) { //in order write acceses 1- 1000 makes sure no cache hits
    	    		SysLib.cwrite(i, x[i]);
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000 Adversary Writes with Cache: " + msec + " Microsec");
    	    	
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {//in order write acceses 1- 1000 makes sure no cache hits
    	    		SysLib.cread(i, x[i]);
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000 Adversary Reads with Cache: " + msec + " Microsec");
    			break;
			default:
				break;
    		}
    		break;
    	case "disabled": //Cache NOT enabled
    		/*
    		 * ALL tests are the same for EACH type
    		 * in disabled, uses rawread and rawwrite instead of
    		 * cread and cwrite!
    		 */
    		switch (type) {
    		
    		case 1: //Random
    	    	SysLib.flush();
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {
    	    		n = (int) (Math.random() * 999) + 0;
    	    		SysLib.rawwrite(n, x[n]); 
    	    	} 
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000 Random Writes: " + msec + " Microsec");
    	    	
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {
    	    		n = (int) (Math.random() * 999) + 0;
    	    		SysLib.rawread(n, x[n]);
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000 Random Reads: " + msec + " Microsec");
    			break;
    		case 2: //Localized rawwrite rawread
    	    	SysLib.flush();
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {
    	    		SysLib.rawwrite((i % 10), x[(i % 10)]);
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000 Localized Writes: " + msec + " Microsec");
    	    	
    	    	
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {
    	    		SysLib.rawread((i % 10), x[(i % 10)]);
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000 Localized Reads: " + msec + " Microsec");
    			break;
    		case 3: //Mixed
    	    	SysLib.flush();
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {
    	    		n = (int) (Math.random() * 10) + 1;
    	    		if(n == 1) { //10% of the time 1/10
    	        		n = (int) (Math.random() * 999) + 0;
    	        		SysLib.rawwrite(n, x[n]);
    	    		}else {
    	    			SysLib.rawwrite((i % 10), x[(i % 10)]);
    	    		}
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000  Mixed Writes: " + msec + " Microsec");
    	    	
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {
    	    		n = (int) (Math.random() * 10) + 1;
    	    		if(n == 1) { //10% of the time 1/10
    	        		n = (int) (Math.random() * 999) + 0;
    	        		SysLib.rawread(n, x[n]);
    	    		}else {
    	    			SysLib.rawread((i % 10), x[(i % 10)]);
    	    		}
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000  Mixed Reads: " + msec + " Microsec");
    			break;
    		case 4: //Adversary
    	    	SysLib.flush();
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {
    	    		SysLib.rawwrite(i, x[i]);
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000 Adversary Writes: " + msec + " Microsec");
    	    	
    	    	start = System.nanoTime();
    	    	for(int i = 0; i < x.length; i++) {
    	    		SysLib.rawread(i, x[i]);
    	    	}
    	    	end = System.nanoTime();
    	    	msec = (end - start) / 1000;
    	    	System.out.println("Time for 1000 Adversary Reads: " + msec + " Microsec");
    			break;
			default:
				break;
    		}
    		break;
    	default:
    		SysLib.cerr("ERRROR");
    	}
    	SysLib.exit();
    }
}
