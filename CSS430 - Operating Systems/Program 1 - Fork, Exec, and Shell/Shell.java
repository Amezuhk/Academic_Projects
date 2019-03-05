/**
 * @author Khuzaima Mushtaq
 */


public class Shell extends Thread {
	private StringBuffer s;   //Buffer to read in user input
	private int shellCount = 0; //Shell command line number tracker
	
    public Shell()  {
    }

    /*
     * Thread run method
     * Assumes that makeStrings works properly
     * simulates a linux Shell as described by the Assignment
     */
    public void run() {
    	String[] arg; //single argument array
    	String[] args; //all the commands/delimiters array
	   	int index = 0; //args index
	   	int tid;       //threadId
	   	
	    while (true) {  //Shell Start
	    	SysLib.cout("\n");
	    	SysLib.cout("Shell [" + shellCount + "]: " );
		   	s = new StringBuffer();
		   	SysLib.cin(s);
		   	args = makeStrings(s);
		   	index = 0;
		   	
		   	
		   	while(args[index] != null) {
		   		String str = args[index];
				String deli = args[index + 1];
				if(args[index].isEmpty() || args[index].equals(" ")) { 
														//takes care of syntax errors
														//like ;;; or & &
					index += 2;
					
				}else if(deli == null) {               //no delimiters (assumes ;)
					if(str.equals("exit")) {
						SysLib.exit();
					}else {
						arg = SysLib.stringToArgs(str);	
						tid = SysLib.exec(arg);
						index++;
						int check = SysLib.join();
				    	while(check != tid) {    //wait for thread end
				    		check = SysLib.join();
				    		}
					}
					
				}else if(deli.equals(";")) {            //; delimiters
					arg = SysLib.stringToArgs(str);
					tid = SysLib.exec(arg);
					int check = SysLib.join();
			    	while(check != tid) {  		//Wait for thread end
			    		check = SysLib.join();
			    		}
					index += 2;
				}else {                                 //& delimiters 
					arg = SysLib.stringToArgs(str);
					tid = SysLib.exec(arg);		
					index += 2;
				}
	    	
	    	}
		   	shellCount++;
	    }
    }
    
    /*
     * Helped method to run()
     * @param buf: Takes used input from keyboard and parses it into a
     * String array so that the commands/ calls are separated from their delimiters
     * such that even elements of the array are commands and odd elements after them 
     * are their delimiters
     */
	public static String[] makeStrings(StringBuffer buf) {
		String string;
		String delimeter;
		String[] cmds = new String[200]; //arbitrary size of array
										//can be changed to accommodate more commands
		
		for(int i = 0; i < cmds.length; i++) { //nullify the array
			cmds[i] = null;
		}
		
		int cmdIndex = 0;//sudo array index
		
	    while(buf != null) {
			int indexA = buf.indexOf("&");   //get index of delimiters
		    int indexC = buf.indexOf(";");
		    
		    if(indexA > -1 && indexC > -1 ) { //has both delimiters
		    	if(indexA < indexC) {  //first delimiters is &
		    		string = buf.substring(0, indexA); //get command string
		    		cmds[cmdIndex] = string; 		   //save command
		    		cmdIndex++;						   //index up
		    		buf.delete(0,indexA); 			   //delete command from buf
		    		
		    		delimeter = buf.substring(0, 1);   //get delimiter
		    		cmds[cmdIndex] = delimeter;        //save delimiter
		    		cmdIndex++; 					   //index up
		    		buf.delete(0, 1); 				   //delete delimiter from buf
		    		
		    		
		    	}else {  // first delimiters is ;
		    		string = buf.substring(0, indexC);
		    		cmds[cmdIndex] = string;
		    		cmdIndex++;
		    		buf.delete(0,indexC);
		    		
		    		delimeter = buf.substring(0, 1);
		    		cmds[cmdIndex] = delimeter;
		    		cmdIndex++;
		    		buf.delete(0, 1);
		    		
		    		
		    	}
		    	
		    }else if(indexA > -1) { //only has & delimeters
	    		string = buf.substring(0, indexA);
	    		cmds[cmdIndex] = string;
	    		cmdIndex++;
	    		buf.delete(0,indexA);
	    		
	    		delimeter = buf.substring(0, 1);
	    		cmds[cmdIndex] = delimeter;
	    		cmdIndex++;
	    		buf.delete(0, 1);
	
		    	
		    }else if(indexC > -1) { //only has ; delimiters
	    		string = buf.substring(0, indexC);
	    		cmds[cmdIndex] = string;
	    		cmdIndex++;
	    		buf.delete(0,indexC);
	    		
	    		delimeter = buf.substring(0, 1);
	    		cmds[cmdIndex] = delimeter;
	    		cmdIndex++;
	    		buf.delete(0, 1);
		    }else {  //no delimiter 
	    		cmds[cmdIndex] = buf.toString();
	    		cmdIndex++;
	    		buf = null;
		    }
	    }
	    
	    
		return cmds;
		
	}
    
}