
public class Cache {
	
	/*Private class for each cache entry.
	 * Cache has an array of CacheEntries
	 * Number of Cache Entries = size of Cache
	 * size of DATA/ dataSize = Page size
	 */
	private class CacheEntry{
		byte[] DATA;
		int frameNo;    //corresponds to a frame number in main mem.
		boolean useBit;  //for second chance alg.
		boolean modifiedBit;  //check if program needs to write back to main mem
		
		private CacheEntry(int dataSize) {
			DATA = new byte[dataSize];
			frameNo = -1; //empty
			useBit = false;
			modifiedBit = false;
		}
	}
	
	CacheEntry[] Cache;
	private int pageSize;   //Size of each page
	private int cacheSize;  //Num of pages the Cache can hold
	private int scPtr;    //second chance pointer
	
	//Constructor intializes Cache
	public Cache(int blockSize, int cacheBlocks) {
		Cache = new CacheEntry[cacheBlocks];
		pageSize = blockSize;
		cacheSize = cacheBlocks;
		scPtr = cacheBlocks -1;
		for(int i = 0; i < cacheSize; i++) {
			Cache[i] = new CacheEntry(pageSize);
		}
	}
	
	/*Scans the CacheEntry[] array to check if frame/block is already in cache
	 * if so, read data in cache to buffer
	 * if not, grabs data from DISK and loads it into cache, reads into buffer
	 */
	public synchronized boolean read(int blockId, byte buffer[]) {
		if (blockId < 0 || blockId > 1000) { //is out of bound
			return false;
		}
		
		int cNum= -1;
		for(int i = 0; i < cacheSize; i++) {
			if(Cache[i].frameNo == blockId) {
				cNum = i;
			}
		}
		
		if(cNum < 0) { //is not in cache
			cNum = findEmpty();
			if(cNum < 0) { //no empty found
				cNum = findVictim();
				if(Cache[cNum].modifiedBit) { //has been modified dirty bit
					SysLib.rawwrite(Cache[cNum].frameNo, Cache[cNum].DATA);
					//write to disk
				}
				SysLib.rawread(blockId, Cache[cNum].DATA);
				System.arraycopy(Cache[cNum].DATA, 0, buffer, 0, pageSize);
				Cache[cNum].frameNo = blockId;			
				Cache[cNum].useBit = false;
				Cache[cNum].modifiedBit = false;
				return true;
			}else { //found empty
				SysLib.rawread(blockId, Cache[cNum].DATA);
				System.arraycopy(Cache[cNum].DATA, 0, buffer, 0, pageSize);
				Cache[cNum].frameNo = blockId;		
				Cache[cNum].useBit = false;
				Cache[cNum].modifiedBit = false;
				return true;
			}
		}else { // is in cache
			System.arraycopy(Cache[cNum].DATA, 0, buffer, 0, pageSize);	
			Cache[cNum].useBit = true;
			return true;
		}
	}
	
	/*Scans the CacheEntry[] array to check if frame/block is already in cache
	 * if so, write data in buffer to cache
	 * if not, grabs data from DISK and loads it into cache, reads buffer into cache
	 * dirty bit is set
	 */
	public synchronized boolean write(int blockId, byte buffer[]) {
		if (blockId < 0 || blockId > 1000) { //is out of bound
			return false;
		}
		
		int cNum= -1;
		for(int i = 0; i < cacheSize; i++) {
			if(Cache[i].frameNo == blockId) {
				cNum = i;
			}
		}
		
		if(cNum < 0) { //is not in cache
			cNum = findEmpty();
			if(cNum < 0) { //no empty found
				cNum = findVictim();
				if(Cache[cNum].modifiedBit) { //has been modified
					SysLib.rawwrite(Cache[cNum].frameNo, Cache[cNum].DATA);
					//write to disk
				}
				System.arraycopy(buffer, 0, Cache[cNum].DATA, 0, pageSize);
				Cache[cNum].frameNo = blockId;			
				Cache[cNum].useBit = false;
				Cache[cNum].modifiedBit = true;
				return true;
			}else { //found empty
				System.arraycopy(buffer, 0, Cache[cNum].DATA, 0, pageSize);
				Cache[cNum].frameNo = blockId;		
				Cache[cNum].useBit = false;
				Cache[cNum].modifiedBit = true;
				return true;
			}
		}else { // is in cache
			System.arraycopy(buffer, 0, Cache[cNum].DATA, 0, pageSize);
			Cache[cNum].useBit = true;
			Cache[cNum].modifiedBit = true;
			return true;
		}
	}
	
	/*
	 * Go through all cacheEntries and sync them
	 */
	public synchronized void sync(){
		
		for(int i = 0; i < cacheSize; i++) {
			if(Cache[i].modifiedBit && !(Cache[i].frameNo < 0) 
					&& !(Cache[i].frameNo > 1000)){
				//write to disk
				SysLib.rawwrite(Cache[i].frameNo, Cache[i].DATA);
				//set modified bit off
				Cache[i].modifiedBit = false;       //set modified to false
			}
		}
		//sync
		SysLib.sync();
	}
	
	/*
	 * Go through all cacheEntries and flush them
	 */
	public synchronized void flush(){
		for(int i = 0; i < cacheSize; i++) {
			if(Cache[i].modifiedBit && !(Cache[i].frameNo < 0) 
					&& !(Cache[i].frameNo > 1000)){
				//write to disk
				SysLib.rawwrite(Cache[i].frameNo, Cache[i].DATA);
				//empty cacheEntry
				Cache[i].DATA = new byte[pageSize];
				Cache[i].frameNo = -1; 
				Cache[i].useBit = false;
				Cache[i].modifiedBit = false;      
			}
		}
		//sync
		SysLib.sync();
	}
	
	/*
	 * Helper method
	 * finds next Empty cacheEntry if any
	 */
	private int findEmpty() {
		for(int i = 0; i < cacheSize; i++) {
			if(Cache[i].frameNo < 0) {  //cacheEntry is empty
				return i;
			}
		}
		
		return -1;
	}
	
	/*
	 * Enhanced Second Chance algorithm
	 */
	private int findVictim() {
		int tempPtr = scPtr;
		while(true) {  //STEP 1
			tempPtr = (++tempPtr  % cacheSize);
			if(Cache[tempPtr].useBit || Cache[tempPtr].modifiedBit) {
				// u = 1 || m = 1, do nothing
			}else { //not used, u = 0, m = 0
				scPtr = tempPtr;
				return tempPtr;
			}
			if(tempPtr == scPtr) { //went through and didnt find 
				break;
			}
		}
		tempPtr = scPtr;
		while(true) { // STEP 2
			tempPtr = (++tempPtr  % cacheSize);
			if((!Cache[tempPtr].useBit && Cache[tempPtr].modifiedBit) ||
					(!Cache[tempPtr].useBit && !Cache[tempPtr].modifiedBit)) {
				// u = 0 && m = 1 || u = 0 m = 0
				scPtr = tempPtr;
				return tempPtr;
			}else { 
				Cache[tempPtr].useBit = false;

			}
			if(tempPtr == scPtr) { //went through and didnt find 
				break;
			}
		}
		
		tempPtr = scPtr;
		while(true) { //STEP 1 Repeat to find  u = 0 m= 0
			tempPtr = (++tempPtr  % cacheSize);
			if(Cache[tempPtr].useBit || Cache[tempPtr].modifiedBit) {
				// u = 1 || m = 1, do nothing
			}else { //not used, u = 0, m = 0
				scPtr = tempPtr;
				return tempPtr;
			}
			if(tempPtr == scPtr) { //went through and didnt find 
				break;
			}
		}
		
		tempPtr = scPtr;
		
		while(true) { //STEP 2 repeat in worst case
			tempPtr = (++tempPtr  % cacheSize);
			if((!Cache[tempPtr].useBit && Cache[tempPtr].modifiedBit) ||
					(!Cache[tempPtr].useBit && !Cache[tempPtr].modifiedBit)) {
				// u = 0 && m = 1 || u = 0 m = 0
				scPtr = tempPtr;
				return tempPtr;
			}else { 
				Cache[tempPtr].useBit = false;

			}
		}
	}
	
	
}
