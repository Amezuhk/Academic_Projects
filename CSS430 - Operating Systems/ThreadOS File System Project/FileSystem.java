/*
 * @author Khuzaima Mushtaq
 * This is the FileSystem.java file for the FileSystem
 * This class combines all the other classes to create a file System, and provides a FileSystem
 * Interface to the user thread so they can open close read write delete seek files etc.
 * The file system uses the Superblock Directory and FileTable classes to maintain the file system
 */
public class FileSystem {
	private static final int SEEK_SET = 0; //for seek
    private static final int SEEK_CUR = 1;
    private static final int SEEK_END = 2;

    private Superblock superblock;         
    private Directory directory;
    private FileTable fileTable;
	
	/*
	 * Constructor
	 * Initializes the file System: SuperBlock, Directory and FileTable
	 */
    public FileSystem (int blocks) {
    	superblock = new Superblock(blocks);
    	directory = new Directory(superblock.totalInodes);
    	fileTable = new FileTable(directory);
    	
    	// read the "/" file from disk
    	FileTableEntry directoryEntry = open( "/", "r");
    	int directorySize = directoryEntry.inode.length;
    	
    	if ( directorySize > 0 ) { //there is already data in directory, copy it to this object
    		byte[] directoryData = new byte[directorySize];
    		read( directoryEntry, directoryData );
    		directory.bytes2directory(directoryData);
    	}
    	close( directoryEntry );
    }
    
    /*
     * Sync
     * Synchronize the FileSystem and all its components to the Disk
     */
    public void sync() {
    	byte[] tempData = directory.directory2bytes();
    	//open root directory with write access
    	FileTableEntry root = open("/", "w");
        //write directory to root
    	write(root, tempData);
        //close root directory
    	close(root);
        //sync superblock
    	superblock.sync();
    }


    /*
     * Format
     * Format the Disk and the FileSystem and create a clean new FileSystem
     */
    public int format( int files) {
    	superblock.format(files);
    
        //create directory
    	directory = new Directory(superblock.totalInodes);
    	
        //file table is created and store directory in the file table
    	fileTable = new FileTable(directory);
    	
        //return true on completion
        return 0;
    }

    /*
     * Open
     * This method opens a file called filename with the permissions of mode
     * It returns a fileTableEntry which acts as a file descriptor that the users can use
     * to interact with the file. 
     * Creates a new file if filename doesnt exist, if it already exists just returns the 
     * FileTableEntry for it
     */
    public FileTableEntry open(String filename, String mode){
    	FileTableEntry ftEntry = fileTable.falloc(filename, mode);
    	return ftEntry;
    }


    /*
     * close fd
     */
    public boolean close(FileTableEntry fd){
    	//cast the entry as synchronized
    	synchronized(fd) {
			// decrease the number of users
			fd.count--;

			if (fd.count == 0) {
				return fileTable.ffree(fd);
			}
			return true;
		}
    }


    /*
     * read
     * Read from fd, into buffer
     * return value is the number of bytes read or -1 on fail
     * reads as many bytes as it can from fd into buffer
     */
    public int read(FileTableEntry fd, byte[] buffer) {
    	
		if ((fd.mode == "w") || (fd.mode == "a")) //make sure mode is right
			return -1;

        int len  = buffer.length;   //set total size of data to read
        int bytesRead = 0; 
        int blockSize = 512;        //set block size
        int toRead = 0;             //Num bytes to read from a block
        
        synchronized(fd) {
        	while (fd.seekPtr < fd.inode.length && (len > 0)) {
        		int currentBlock = fd.inode.findBlock(fd.seekPtr);
        		
        		if (currentBlock == -1) { //invalid block
        			break;
        		}
        		
        		//read block data
				byte[] data = new byte[blockSize];
        		SysLib.rawread(currentBlock, data);
        		
        		//go to exact seek pointer
        		int offset = fd.seekPtr % blockSize;
        		int bytesLeft = blockSize - offset;
        		int fileLeft = fd.inode.length - fd.seekPtr;
        		
        		//check how many bytes to read from this block
        		if (bytesLeft < fileLeft) //read num of bytesleft
					toRead = bytesLeft;
				else                      //read amount of fileLeft
				    toRead = fileLeft;

				if (toRead > len)        //if buffer cant hold all, read len
					toRead = len;

        		System.arraycopy(data, offset, buffer, bytesRead, toRead);
        		bytesRead += toRead;
        		fd.seekPtr += toRead;
        		len -= toRead;
        	}
        	return bytesRead;
        }
    }

    /*
     * write
     * Write buffer to fd
     * Check mode to make sure writing is legal
     * returns num of bytes writter or -1 on fail
     * can write over data or append to file based on seek pointer
     */
    public int write(FileTableEntry fd, byte[] buffer){
    	int bytesWritten = 0;
		int len = buffer.length;
		int blockSize = 512;

		if (fd == null || fd.mode == "r") { //check mode
			return -1;
		}
		
		synchronized (fd) {
			while (len > 0) {
				int block = fd.inode.findBlock(fd.seekPtr);

				//block found is invalid
				if (block == -1) { 
					short newBlock = (short) superblock.getFreeBlock();
					
					//add free block to inode direct or indirect
					int check = fd.inode.addFreeBlock(fd.seekPtr, newBlock); 
					if (check == -2) { //indirect pointer is empty
						short freeBlock = (short) this.superblock.getFreeBlock();
						//create indirect Block
						if (fd.inode.createIndirectBlock(freeBlock) < 0) {
							return -1;
						}
						if (fd.inode.addFreeBlock(fd.seekPtr, newBlock) != 0) {
							return -1;
						}
					}else if (check == -1) {
						return -1;
					}
					block = newBlock;
				}
				
				//read block
				byte [] buf = new byte[blockSize];
				SysLib.rawread(block, buf);
				
				//go to exact seek pointer
				int offset = fd.seekPtr % blockSize;
				int bytesLeft = blockSize - offset;

				if (bytesLeft > len) { //can only write bytes left on this block
					System.arraycopy(buffer, bytesWritten, buf, offset, len);
					SysLib.rawwrite(block, buf);

					fd.seekPtr += len;
					bytesWritten += len;
					len = 0;
				}
				else { 
					System.arraycopy(buffer, bytesWritten, buf, offset, bytesLeft);
					SysLib.rawwrite(block, buf);

					fd.seekPtr += bytesLeft;
					bytesWritten += bytesLeft;
					len -= bytesLeft;
				}
			}

			//update
			if (fd.seekPtr > fd.inode.length) {
				fd.inode.length = fd.seekPtr;
			}
			fd.inode.toDisk(fd.iNumber);
			return bytesWritten;
		}
    }


    /*
     * seek
     * seek the location in file based on whence + offset
     * adjust the file size accordingly and increment attributes as needed
     */
    public int seek(FileTableEntry fd, int offset, int whence){
    	synchronized (fd) {
			if(whence == SEEK_SET) {
				fd.seekPtr = offset;
			}else if(whence == SEEK_CUR) {
				fd.seekPtr += offset;
			}else if(whence == SEEK_END) {
				fd.seekPtr = fd.inode.length + offset;
			}else {
				return -1;
			}

			if (fd.seekPtr < 0) {
				fd.seekPtr = 0;
			}
			if (fd.seekPtr > fd.inode.length) {
				fd.seekPtr = fd.inode.length;
			}

			return fd.seekPtr;
		}
    }

    /*
     * delete
     * delete filename from FileTable
     */
	int delete(String filename) {
		return fileTable.delete(filename);
	}
	
	/*
	 * return file size of fd
	 */
    public synchronized int fsize(FileTableEntry fd){
    	synchronized(fd) {
    		return fd.inode.length;
    	}
    }

}
