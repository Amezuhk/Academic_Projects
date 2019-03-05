/*
 * @author Khuzaima Mushtaq
 * This is the Superblock.java for the File System
 * The Superblock describes to the file system the total number of blocks,
 * the total number of files/inodes and all the free blocks available to the OS to use
 * 
 */

class Superblock {
   public int totalBlocks; // the number of disk blocks
   public int totalInodes; // the number of inodes
   public int freeList;    // the block number of the free list's head
   
   //super block is ALWAYS block 0 in the disk
   
   private final int defaultInodeBlocks = 64;
   private final int blockSize = Disk.blockSize; //block size, 512
   private final int diskSize = 1000; //num of blocks our disk has, 1000
   private final int tbOffset = 0;     //totalBlocks offset
   private final int tiOffset = 4;     // totalInodes offset
   private final int flOffset = 8;     // freeList offset
   
   /*
    * Constructor
    * implemented as recommended in project notes
    */
   public Superblock( int numBlocks) {
	   byte[] superBlock = new byte[blockSize];
	   SysLib.rawread(0, superBlock);
	   
		totalBlocks = SysLib.bytes2int(superBlock, tbOffset);
		totalInodes = SysLib.bytes2int(superBlock, tiOffset);
		freeList = SysLib.bytes2int(superBlock, flOffset);

		//inodeBlocks = totalInodes;
		//disk contents validation
		if (totalBlocks == numBlocks && totalInodes > 0 && freeList >= 2){
			return;     // valid
		}
		else {
			totalBlocks = numBlocks;
			format(defaultInodeBlocks);
		}
   }
   
   /*
    * Format
    * Formats the disk and sets all variables to the proper values
    * Set up the FreeList
    * Write default Inodes to disk
    */
   public void format (int numInodes){
	   //param error check
	   if(numInodes < 0) {
		   numInodes = defaultInodeBlocks;
	   }
	   
	   //set Superblock variables
	   totalBlocks = diskSize;
	   totalInodes = numInodes;
	   freeList = (totalInodes / 16) + 2;
	   
	   //Write default Inodes to disk
	   Inode def = new Inode(); //default Inode
	   def.flag = 0;
	   
	   for(int i = 0; i < totalInodes; i++) {
		   def.toDisk((short) i);
	   }
	   
	   //Set up FreeList
	   byte[] data = new byte[blockSize];
	   
	   for(int i = freeList; i <= totalBlocks - 1; i++) {
		   //zero out data
		   for(int j = 0; j < blockSize; j++) {
			   data[j] = 0;
		   }
		   
		   //set first int (4 bytes) to point to next freeBlock
		   if(i < totalBlocks - 1) { //all freeBlocks
			   SysLib.int2bytes(i+1,  data, 0);
			   SysLib.rawwrite(i, data);
		   }else { //lastBlock end of list
			   SysLib.int2bytes(-1,  data, 0);
			   SysLib.rawwrite(i, data);
		   }

	   }
	   
	   //Write SuperBlock to disk
	   sync();
   }
   
	/*
	 * Sync
	 * This method writes the Superblock to disk
	 */
	public void sync () {
		byte[] data = new byte[blockSize];
		
		SysLib.int2bytes(totalBlocks, data, tbOffset);
		SysLib.int2bytes(totalInodes, data, tiOffset);
		SysLib.int2bytes(freeList, data, flOffset);

		SysLib.rawwrite(0, data);
	}
	
	/*
	 * Add blockNum to freeList
	 */
	public int addToFreeList(int blockNum) {
		//check if block is valid
		if(blockNum < 0 || blockNum > totalBlocks) { //invalid blockNum
			return -1;
			
		}else {
			int nextFree = freeList;
			int temp = 0;
			
			byte[] data = new byte[blockSize];
			for(int j = 0; j < blockSize; j++) { //zero out data
			   data[j] = 0;
		    }
			
			//Find end of FreeList
			while(nextFree != -1) {
				SysLib.rawread(nextFree, data);
				temp = SysLib.bytes2int(data, 0);
				
				if(temp == -1) { //is last block
					//point last block to BlockNum
					SysLib.int2bytes(blockNum, data, 0);
					SysLib.rawwrite(nextFree, data);
					SysLib.int2bytes(-1, data, 0);
					SysLib.rawwrite(blockNum, data);
					return 1;
				}
				
				nextFree = temp;
			}
		   
		}
		
		return -1;
	}
	
	
	/*
	 * Retrieve a Free Block
	 */
	public int getFreeBlock() {
		//check if freeList is valid
		if(freeList < 0 || freeList > totalBlocks) { //freeList is not valid
			return -1;
			
		}else { //freeList is valid
			byte[] data = new byte[blockSize];
			SysLib.rawread(freeList, data);
			
			int toReturn = freeList;
			int nextB = SysLib.bytes2int(data, 0); //next Block
			
			freeList = nextB;
			
			return toReturn;
		}
	}
	
	
 }