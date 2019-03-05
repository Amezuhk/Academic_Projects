/*
 * @author Khuzaima Mushtaq
 * This is the Inode.java for the file system. 
 * It is based on the linux inode and follows the sample given in the
 * Project description.
 * 
 * The Inode defines a file as described in the project. 
 */

public class Inode {
   private final static int iNodeSize = 32;       // fix to 32 bytes
   public final static int directSize = 11;      // # direct pointers
   private final static int blockSize = 512;      // Size of each block 512 bytes
   private final static int iNperBlock = 16;      // Number of inodes per block 512/32 = 16
   private final static int iSize = 4;            // int size, int = 4 Bytes
   private final static int sSize = 2;            // short size, short = 2 bytes
   
   public int length;                             // file size in bytes
   public short count;                            // # file-table entries pointing to this
   public short flag;                             // 0 = unused, 1 = used, ...
   public short direct[] = new short[directSize]; // direct pointers
   public short indirect;                         // a indirect pointer

   Inode( ) {                                     // a default constructor
      length = 0;
      count = 0;
      flag = 1;
      for ( int i = 0; i < directSize; i++ )
         direct[i] = -1;
      indirect = -1;
   }
   
   
   Inode( short iNumber ) {                       // retrieving inode from disk
       //find which block the iNumber iNode is in
	   int block = (iNumber / iNperBlock) + 1;    //+1 because block 0 is super block
	   
	   //find the offset in the block that the iNode is in
	   int offset = (iNumber % iNperBlock) * iNodeSize; 
	   
	   //Read block data to get inode info from
	   byte[] data = new byte[blockSize];
	   SysLib.rawread(block, data);
	   
	   //Read from data into inode fields
       length = SysLib.bytes2int(data, offset);
       offset += iSize; 
       count = SysLib.bytes2short(data, offset);
       offset += sSize;
       flag = SysLib.bytes2short(data, offset);
       offset += sSize;

       for (int i = 0; i < directSize; i++){
           direct[i] = SysLib.bytes2short(data, offset);
           offset += sSize;
       }
       indirect = SysLib.bytes2short(data, offset);
       offset += sSize;
   }
   
   
   int toDisk( short iNumber ) {
	   //find which block iNode goes in
	   int block = (iNumber / iNperBlock) + 1;
	   
	   //find the offset in the block that the iNode is in
	   int offset = (iNumber % iNperBlock) * iNodeSize; 
	   
	   //Read block data to write to
	   byte[] data = new byte[blockSize];
	   SysLib.rawread(block, data);
	   
	   //create 32 byte iNode data to put into disk
	   byte [] toEnter = new byte[iNodeSize];
	   int offset2 = 0;
	   
	   //Populate toEnter
       SysLib.int2bytes(length, toEnter, offset2);
       offset2 += iSize;
       SysLib.short2bytes(count, toEnter, offset2);
       offset2 += sSize;
       SysLib.short2bytes(flag, toEnter, offset2);
       offset2 += sSize;

       for (int i = 0; i < directSize; i++){
           SysLib.short2bytes(direct[i], toEnter, offset2);
           offset2 += sSize;
       }

       SysLib.short2bytes(indirect, toEnter, offset2);
       offset2 += sSize;
       
       //Copy toEnter into data and write to disk
       System.arraycopy(toEnter, 0, data, offset, iNodeSize);
       SysLib.rawwrite(block,data);
       
	   return 0;
   }
   
   
   /*
    * addFreeBlock
    * adds free block to the inode as needed.
    * if direct blocks are open it uses those, otherwise uses indirect block
   */
  int addFreeBlock(int offset, short freeBlock){
      int blockNum = offset/blockSize;
      
      //if block num is not in indirect block
      if (blockNum < directSize){
    	  if(direct[blockNum] > 0)
    		  return -1;
          direct[blockNum] = freeBlock;
          return 0;
      }
	  if (indirect < 0) {
		  return -2;
	  }
      else{
          byte[] data = new byte[blockSize];
          SysLib.rawread(indirect,data);

          int blockSpace = (blockNum - directSize) * 2;
          
          if ( SysLib.bytes2short(data, blockSpace) > 0){
              return -1; //block already has data
          }
          else
          {
        	  //update indirect
              SysLib.short2bytes(freeBlock, data, blockSpace);
              SysLib.rawwrite(indirect, data);
          }
          return 0;
      }

  }


  /*
   * createIndirectBlock
   * given blockNumber set up and write to disk the indirect block
   */
 int createIndirectBlock(short blockNumber){
	  //check if theres still room in direct blocks
      for (int i = 0; i < directSize; i++){
          if (direct[i] == -1){
              return -1;
          }
      }
      
      //check if indirect block already exists
      if (indirect != -1){
          return -1;
      }
      
      //set indirect block to blockNumber
      indirect = blockNumber;
      byte[ ] data = new byte[blockSize];
      
      //set all block references in indirect block to -1
      for(int i = 0; i < (blockSize/2); i++){
          SysLib.short2bytes((short) -1, data, i * 2);
      }
      
      //write to disk
      SysLib.rawwrite(blockNumber, data);
      return 1;

  }
 

  /*
   * findBlock
   * Given an offset find a corresponding direct block
   * return the blockNum that it points to
   */
  int findBlock(int offset){
      int blockNum = offset / blockSize; //logical blocknumber that this offset is in
      
      if(blockNum < directSize) {
      	  return direct[blockNum];
      }else {
          if(indirect < 0) {
        	  return -1;
          }
          //indirect exists
          byte[] data = new byte[blockSize];
          SysLib.rawread(indirect, data);

          int blockSpace = (blockNum - directSize) * 2;
          return SysLib.bytes2short(data, blockSpace);
      }
  }
  

  /*free indirect block
   * frees indirect block
   * and returns the data from the indirect block
   */
  byte[] freeIndirectBlock(){
	  
      if (indirect >= 0) { //indirect in use
          byte[] data = new byte[blockSize];
          SysLib.rawread(indirect, data);
          indirect = -1;
          return data;
      }
      else { //not in use
          return null;
      }
  }
}