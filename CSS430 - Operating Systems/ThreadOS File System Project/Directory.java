/*
 * @Author Khuzaima Mushtaq
 * This is the Directory.java for the File System.
 * The directory is a single level directory which defines files names and file
 * sizes for the files that we have in our file system. The size of the directory is
 * equal to the number of inodes that our file system has, since one inode represents one
 * file
 */
public class Directory {
    private static int maxChars = 30; // max characters of each file name
    private static int CHAR_SIZE = 60;//
    private static int ENTRY_SIZE = 64; //each file entry is 64 bytes, 60 for chars
    									//4 for size
    private final static int iSize = 4; // int size, int = 4 Bytes

    // Directory entries
    private int fsize[];        // each element stores a different file size.
    private int directorySize;  // size of directory
    private char fnames[][];    // each element stores a different file name.

    /*
     * Constructor
     */
    public Directory( int maxInumber ) {
        fsize = new int[maxInumber];     // maxInumber = max files
        for ( int i = 0; i < maxInumber; i++ )
            fsize[i] = 0;                 // all file size initialized to 0
        directorySize = maxInumber;
        fnames = new char[maxInumber][maxChars];
        String root = "/";                // entry(inode) 0 is "/"
        fsize[0] = root.length( );        // fsize[0] is the size of "/".
        root.getChars( 0, fsize[0], fnames[0], 0 ); // fnames[0] includes "/"
    }
    
    
    /*
     * Bytes to Directory
     * Given byte array data, use the data to populate the directory
     */
    public void bytes2directory(byte data[]) {
    	int offset = 0;
    	
    	//populate the fsize array
    	for(int i = 0; i < directorySize; i++) {
    		fsize[i] = SysLib.bytes2int(data, offset);
    		offset += iSize;
    	}
    	
    	//populate fnames
    	for(int i = 0; i < directorySize; i++) {
    		String temp = new String(data, offset, CHAR_SIZE);
    		temp.getChars(0,  fsize[i], fnames[i], 0);
    	}	
    }
    
    /*
     * Bytes to Directory
     * Given byte array data, use the data to populate the directory
     */
    public byte[] directory2bytes() {
    	int offset = 0;
    	byte[] data = new byte[ENTRY_SIZE * directorySize]; //toReturn
    	byte[] names;
    	
    	//add fsizes to data
    	for(int i = 0; i < directorySize; i++) {
    		SysLib.int2bytes(fsize[i], data, offset);
    		offset += iSize;
    	}
    	
    	//add fnames to data
    	for(int i = 0; i < directorySize; i++) {
    		String temp = new String(fnames[i], 0, fsize[i]);
    		names = temp.getBytes();
    		System.arraycopy(names, 0, data, offset, names.length);
    		offset += CHAR_SIZE;
    	}
    	return data;
    }
    
    
    /*
     * ialloc
     * allocate an inode to filename
     */
    public short ialloc(String filename) {
    	//allocates a new inode to filename
    	if(filename.length() > maxChars) {
    		return -1;
    	}
    	for(short i = 0; i < directorySize; i++) {
    		if(fsize[i] ==0) { //this inode has no file currently
    			int file = filename.length();
    			fsize[i] = file;
    			filename.getChars(0, fsize[i], fnames[i], 0);
    			return i;
    		}
    	}
    	
    	return -1;
    }

    
    /*
     * namei
     * return iNumber of filename if in directory
     */
    public short namei(String filename) {
    	for (short i = 0; i < directorySize; i++) {
    		if(fsize[i] == filename.length()) {
    			String temp = new String(fnames[i], 0, fsize[i]);
    			if(filename.equals(temp))
    				return i;
    		}
    	}
    	return -1;
    }
}
