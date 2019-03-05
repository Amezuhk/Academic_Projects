import java.util.Vector;
/*
 * @author Khuzaima Mushtaq
 * This is the FileTable.java for the File System
 * The File table represents a vector array of all the fileTableEntries in our file system
 * based on the Directory and Inodes that we have
 * we use the FileTable to access the fileTableEntries that we use to view our files
 */

public class FileTable {
	private Vector<FileTableEntry> fileTable;
	private Directory directory;
	
	//inode flags
    public final static int UNUSED = 0;
    public final static int USED = 1;
    public final static int READ = 2;
    public final static int WRITE = 3;
	
	/*
	 * Constructor
	 * instantiate file table, receive reference to Directory
	 */
	public FileTable(Directory direc) {
		fileTable = new Vector<FileTableEntry>();
		directory = direc;
	}
	
	/*
	 * falloc
	 * return the FileTableEntry related to the filename and mode
	 * if the file already exists then simple point to it 
	 * otherwise create a new file with fileName and mode
	 */
    public synchronized FileTableEntry falloc( String fileName, String mode ) {
        short iNumber = -1;
        Inode inode = null;

        while (true) {
            if(fileName.equals("/")) {
            	iNumber = 0;
            }else {
            	iNumber = directory.namei(fileName);
            }
	        if(iNumber < 0) {
	        	iNumber = directory.ialloc(fileName);
	        }
	        inode = new Inode(iNumber);
	        inode.count++;  // Increase the number of users
	        inode.toDisk(iNumber);
	        // create new file table entry and add it to the file table
	        FileTableEntry entry = new FileTableEntry(inode, iNumber, mode);
	        fileTable.addElement(entry);
	        return entry;
	    }
   }

    /*
     * ffree
     * remove fd/ FileTableEntry from the fileTable
     * update the inode and write it to disk
     * return success or failure
     */
    public synchronized boolean ffree( FileTableEntry fd ) {
        Inode inode = new Inode(fd.iNumber);
        
        if (fileTable.remove(fd)) {
            notifyAll();
            inode.count--;
            inode.toDisk(fd.iNumber);
            return true;
        }
        return false;
    }
    
    /*
     * delete
     * find fileName in directory
     * use the iNumber to find the entry in the fileTable
     * delete/ free entry
     */
    public synchronized int delete( String fileName ) {
    	FileTableEntry check;
    	int iNumber = directory.namei(fileName);
    	for(int i = 0; i < fileTable.size(); i++) {
    		check = fileTable.get(i);
    		if(check.iNumber == iNumber) {
    			ffree(check);
    			return 0;
    		}
    	}
    	return -1;
    }

    /*
     * returns if fileTable is empty or not
     */
    public synchronized boolean fempty( ) {
        return fileTable.isEmpty( );
    } 

}
