import java.util.*;

public class Scheduler extends Thread
{
    private Vector queue;
    private Vector queue1;
    private Vector queue2;
    private int timeSlice;
    private int TimeSlice;
    private static final int DEFAULT_TIME_SLICE = 1000;

    // New data added to p161 
    private boolean[] tids; // Indicate which ids have been used
    private static final int DEFAULT_MAX_THREADS = 10000;

    // A new feature added to p161 
    // Allocate an ID array, each element indicating if that id has been used
    private int nextId = 0;
    private void initTid( int maxThreads ) {
	tids = new boolean[maxThreads];
	for ( int i = 0; i < maxThreads; i++ )
	    tids[i] = false;
    }

    // A new feature added to p161 
    // Search an available thread ID and provide a new thread with this ID
    private int getNewTid( ) {
	for ( int i = 0; i < tids.length; i++ ) {
	    int tentative = ( nextId + i ) % tids.length;
	    if ( tids[tentative] == false ) {
		tids[tentative] = true;
		nextId = ( tentative + 1 ) % tids.length;
		return tentative;
	    }
	}
	return -1;
    }

    // A new feature added to p161 
    // Return the thread ID and set the corresponding tids element to be unused
    private boolean returnTid( int tid ) {
	if ( tid >= 0 && tid < tids.length && tids[tid] == true ) {
	    tids[tid] = false;
	    return true;
	}
	return false;
    }

    // A new feature added to p161 
    // Retrieve the current thread's TCB from the queue
    public TCB getMyTcb( ) {
	Thread myThread = Thread.currentThread( ); // Get my thread object
	synchronized( queue ) {
	    for ( int i = 0; i < queue.size( ); i++ ) {
		TCB tcb = ( TCB )queue.elementAt( i );
		Thread thread = tcb.getThread( );
		if ( thread == myThread ) // if this is my TCB, return it
		    return tcb;
	    }
	}
	return null;
    }
    
    //Get TCB given the queue and the Thread to look for
    public TCB getMyTcb( Vector Q, Thread T) {
	Thread myThread = T;
	synchronized( Q ) {
	    for ( int i = 0; i < Q.size( ); i++ ) {
		TCB tcb = ( TCB ) Q.elementAt( i );
		Thread thread = tcb.getThread( );
		if ( thread == myThread ) // if this is my TCB, return it
		    return tcb;
	    }
	}
	return null;
    }

    // A new feature added to p161 
    // Return the maximal number of threads to be spawned in the system
    public int getMaxThreads( ) {
	return tids.length;
    }

    public Scheduler( ) {
	timeSlice = DEFAULT_TIME_SLICE;
	TimeSlice = DEFAULT_TIME_SLICE;
	queue = new Vector( );
	queue1 = new Vector( );
	queue2 = new Vector( );
	initTid( DEFAULT_MAX_THREADS );
    }

    public Scheduler( int quantum ) {
	timeSlice = quantum;
	TimeSlice = quantum;
	queue = new Vector( );
	queue1 = new Vector( );
	queue2 = new Vector( );
	initTid( DEFAULT_MAX_THREADS );
    }

    // A new feature added to p161 
    // A constructor to receive the max number of threads to be spawned
    public Scheduler( int quantum, int maxThreads ) {
	timeSlice = quantum;
	TimeSlice = quantum;
	queue = new Vector( );
	queue1 = new Vector( );
	queue2 = new Vector( );
	initTid( maxThreads );
    }

    private void schedulerSleep( ) {
	try {
	    Thread.sleep( timeSlice );
	} catch ( InterruptedException e ) {
	}
    }

    // A modified addThread of p161 example
    public TCB addThread( Thread t ) {
	//t.setPriority( 2 );
	TCB parentTcb = getMyTcb( ); // get my TCB and find my TID
	int pid = ( parentTcb != null ) ? parentTcb.getTid( ) : -1;
	int tid = getNewTid( ); // get a new TID
	if ( tid == -1)
	    return null;
	TCB tcb = new TCB( t, tid, pid ); // create a new TCB
	queue.add( tcb );
	return tcb;
    }

    // A new feature added to p161
    // Removing the TCB of a terminating thread
    public boolean deleteThread( ) {
	TCB tcb = getMyTcb( ); 
	if ( tcb!= null )
	    return tcb.setTerminated( );
	else
	    return false;
    }

    public void sleepThread( int milliseconds ) {
	try {
	    sleep( milliseconds );
	} catch ( InterruptedException e ) { }
    }
    
    // A modified run of p161
    @SuppressWarnings("deprecation")
	public void run( ) {
	Thread current = null;
	Thread Q1 = null;
	Thread Q2 = null;
	timeSlice = TimeSlice/2;
	int quantumLeft = 0;
	//this.setPriority( 6 );
	
	while ( true ) {
	    try {
		// get the next TCB and its thread
		if ( queue.size( ) == 0 ) { //Queue0 is empty
			if(queue1.size() == 0) { //Queue1 is empty
				if(queue2.size() == 0) { //Queue2 is empty
				    continue;
				    
				}else { //Queue2 is Not empty but Queue0 and Queue1 are
					
					TCB currentTCB;
					//Was Queue2 interrupted last time?
					if(Q2 == null) { //NOT interrupted
						currentTCB = (TCB)queue2.firstElement( );
						if ( currentTCB.getTerminated( ) == true ) {
						    queue2.remove( currentTCB );
						    returnTid( currentTCB.getTid( ) );
						    continue;
						}
						
						current = currentTCB.getThread( );
						if ( current != null ) {
						    if ( current.isAlive( ) ) {
						    	current.resume();//current.setPriority( 4 );	
						    }else {
						    currentTCB.setTerminated();
						    }
						}
						
						schedulerSleep( ); //Run 1 timeSlice/2
						
						if ( queue.size( ) != 0 || queue1.size() != 0 ) { //Check if Queue0 or Queue1 have new threads
						    if ( current != null && current.isAlive( ) ) //If they do store current thread in Q2
							current.suspend();
						    Q2 = current;
						    quantumLeft = 3; //store how many more timeSlices this thread needs to run when it executes again
						    queue2.remove( currentTCB ); //rotate to end
						    queue2.add( currentTCB ); 
							continue;
						}
						
						schedulerSleep( ); //Repeat 2nd timeSlice/2
						if ( queue.size( ) != 0 || queue1.size() != 0 ) {
						    if ( current != null && current.isAlive( ) )
							current.suspend();
						    Q2 = current;
						    quantumLeft = 2;
						    queue2.remove( currentTCB ); // rotate this TCB to the end
						    queue2.add( currentTCB ); // rotate this TCB to the end
							continue;
						}
						
						schedulerSleep( );  //Repeat 3rd timeSlice/2
						if ( queue.size( ) != 0 || queue1.size() != 0 ) {
						    if ( current != null && current.isAlive( ) )
							current.suspend();
						    Q2 = current;
						    quantumLeft = 1;
						    queue2.remove( currentTCB ); // rotate this to end
						    queue2.add( currentTCB ); 
							continue;
						}
						
						schedulerSleep( ); //Repeat 4th timeSlice/2
						synchronized ( queue2 ) {
						    if ( current != null && current.isAlive( ) )
							current.suspend();
						    queue2.remove( currentTCB ); // rotate this to end
						    queue2.add( currentTCB );
						}
					}else { //Queue2 WAS Interrupted
						currentTCB = getMyTcb(queue2, Q2); //Load Thread that was interrupted 
						if ( currentTCB.getTerminated( ) == true ) {
						    queue2.remove( currentTCB );
						    returnTid( currentTCB.getTid( ) );
						    Q2 = null;
						    continue;
						}
						current = currentTCB.getThread( );
						if ( current != null ) {
						    if ( current.isAlive( ) ) {
						    	current.resume();
						    }else {
						    	currentTCB.setTerminated();
						    }
						}
						//How many timeSlices does it still have to run?
						if(quantumLeft == 3) { 
							schedulerSleep( );
							if ( queue.size( ) != 0 || queue1.size() != 0 ) {
							    if ( current != null && current.isAlive( ) )
								current.suspend();
							    Q2 = current;
							    quantumLeft = 2;
							    queue2.remove( currentTCB ); 
							    queue2.add( currentTCB ); 
								continue;
							}
							
							schedulerSleep( ); //Check if it is interrupted again
							if ( queue.size( ) != 0 || queue1.size() != 0 ) {
							    if ( current != null && current.isAlive( ) )
								current.suspend();
							    Q2 = current;
							    quantumLeft = 1;
							    queue2.remove( currentTCB ); // rotate this TCB to the end
							    queue2.add( currentTCB ); // rotate this TCB to the end
								continue;
							}
							
							schedulerSleep( );//Check if it is interrupted again
							synchronized ( queue2 ) {
							    if ( current != null && current.isAlive( ) )
								current.suspend();//current.setPriority( 2 );
							    queue2.remove( currentTCB ); // rotate this TCB to the end
							    queue2.add( currentTCB );
							    Q2 = null;
							}
						}else if(quantumLeft == 2) {
							schedulerSleep( );//Check if it is interrupted again
							if ( queue.size( ) != 0 || queue1.size() != 0 ) {
							    if ( current != null && current.isAlive( ) )
								current.suspend();
							    Q2 = current;
							    quantumLeft = 1;
							    queue2.remove( currentTCB ); // rotate this TCB to the end
							    queue2.add( currentTCB ); // rotate this TCB to the end
								continue;
							}
							
							schedulerSleep( );
							synchronized ( queue2 ) {
							    if ( current != null && current.isAlive( ) )
								current.suspend();
							    queue2.remove( currentTCB ); // rotate this TCB to the end
							    queue2.add( currentTCB );
							    Q2 = null;
							}
						}else if(quantumLeft == 1) { //Last Run
							
							schedulerSleep( );
							synchronized ( queue2 ) {
							    if ( current != null && current.isAlive( ) )
								current.suspend();
							    queue2.remove( currentTCB ); // rotate this TCB to the end
							    queue2.add( currentTCB );
							    Q2 = null; //The Thread that was interrupted has finished its remaining timeSlices
							}
						}	
					}
				}
				
			}else { //Queue1 is NOT empty but Queue0 is	
		    	TCB currentTCB;
		    	//Check if the last time Queue1 was being run if it was interrupted
		    	if (Q1 == null) { //NOT interrupted
					currentTCB = (TCB)queue1.firstElement( );
					if ( currentTCB.getTerminated( ) == true ) {
					    queue1.remove( currentTCB );
					    returnTid( currentTCB.getTid( ) );
					    continue;
					}
					current = currentTCB.getThread( );
					if ( current != null ) {
					    if ( current.isAlive( ) ) {
					    	current.resume();//current.setPriority( 4 );	
					    }else {
					    	currentTCB.setTerminated();
					    }
					}
					
					 schedulerSleep( ); // Run one timeSlice /2
					 if ( queue.size( ) != 0 ) { //Check if there is a thread in Queue0 
					    if ( current != null && current.isAlive( ) ) //if there is, store current thread in Q1 to resume later
						current.suspend();
					    Q1 = current;
					    queue1.remove( currentTCB ); //rotate current thread to end
					    queue1.add( currentTCB ); 
						continue; //go to Queue0
					}//Nothing in Queue0
					schedulerSleep( ); //run for another timeSlide/2
					
					synchronized ( queue1 ) {
					    if ( current != null && current.isAlive( ) ) //if not complete send to queue2
						current.suspend();
					    queue1.remove( currentTCB ); 
					    queue2.add( currentTCB );
					}
		    	}else {  //Queue1 was interrupted
		    		currentTCB = getMyTcb(queue1, Q1); //get last thread that was running
					if ( currentTCB.getTerminated( ) == true ) {
					    queue1.remove( currentTCB );
					    returnTid( currentTCB.getTid( ) );
					    Q1 = null;
					    continue;
					}
					current = currentTCB.getThread( );
					if ( current != null ) {
					    if ( current.isAlive( ) ) {
					    	current.resume();
					    }else {
					    	currentTCB.setTerminated();
					    }
					}
					schedulerSleep( ); //run it one more timeSlice/2
					
					synchronized ( queue1 ) { 
					    if ( current != null && current.isAlive( ) ) //if not complete send to queue2
						current.suspend();
					    queue1.remove( currentTCB );
					    queue2.add( currentTCB );
					    Q1 = null; //interrupt was dealt with
					}
		    	}
			}
			
	    }else { //Queue0 is NOT empty
	    	
			TCB currentTCB = (TCB)queue.firstElement( );
			if ( currentTCB.getTerminated( ) == true ) {
			    queue.remove( currentTCB );
			    returnTid( currentTCB.getTid( ) );
			    continue;
			}
			current = currentTCB.getThread( );

			if ( current != null ) {
			    if ( current.isAlive( ) )
			    	current.resume();
			    else {
				current.start( ); 
			    }
			}
			
			schedulerSleep( ); // Run for timeSlice
	
			synchronized ( queue ) {
			    if ( current != null && current.isAlive( ) ) //If not complete suspend and send to Queue1
				current.suspend();
			    queue.remove( currentTCB );
			    queue1.add( currentTCB );
			}
	    }
	    } catch ( NullPointerException e3 ) { };
	}
    }
}
