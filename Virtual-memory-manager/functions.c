#include "header.h"

/* Get decimal page number */
int getPageNumber(int logicalAddress) {
	return (logicalAddress & PAGE_NUM_MASK) >> PAGE_SHIFT;
}

/* Get decimal offset */
int getOffset(int logicalAddress) {
	return logicalAddress & OFFSET_MASK;
}

/* Check page table: return corresponding frame number for page number */
int checkPageTable(int pageNumber) {

	int frameNumber;
	// page table hit
	if (pageTable[pageNumber].validBit == VALID) {
		frameNumber = pageTable[pageNumber].frameNumber;
		return frameNumber;
	}

	// else: page fault
	pageFaults++;

	// seek to the right pageNumber
	// read in that page from BACKING STORE
	char page[PAGE_SIZE];
	fseek(fpBackingStore, pageNumber * PAGE_SIZE, SEEK_SET);
	fread(page, 1, PAGE_SIZE, fpBackingStore);

	// store in a page frame in physical memory
	int i; 
	for (i = 0; i < PAGE_SIZE; i++) {
		physicalMemory[frameCounter][i] = page[i];
	}

	// update page table
	// set the page table [pageNumber] = frameCounter
	// set page number valid
	pageTable[pageNumber].validBit = VALID;
	pageTable[pageNumber].frameNumber = frameCounter;

	frameNumber = frameCounter;
	frameCounter++;
	return frameNumber;
}

/* Check TLB */
int checkTLB(int pageNumber) {
	int frameNumber = -1;
	int i; 
	for (i = 0; i < TLB_ENTRIES; i++) {
		if (TLB[i][0] == pageNumber) {
			// TLB hit
			TLBhits++;
			frameNumber = TLB[i][0];
			break;
		}
	}
	return frameNumber;
}

/* Update TLB */
void updateTLB(int pageNumber, int frameNumber) {
	TLB[TLBtail][0] = pageNumber;
	TLB[TLBtail][1] = frameNumber;
	TLBtail = (TLBtail + 1) % TLB_ENTRIES;
}

/* Get the physical address for the logical address */
int getPhysicalAddress(int logicalAddress) {

	int pageNumber = getPageNumber(logicalAddress);
	int offset = getOffset(logicalAddress);

	// try to obtain frame number from TLB
	int frameNumber = checkTLB(pageNumber);

	// TLB miss: try obtain frame number from page table {page number: frame number}
	if (frameNumber == -1) {
		frameNumber = checkPageTable(pageNumber);

		// update TLB
		updateTLB(pageNumber, frameNumber);
	}

	return ((frameNumber << PAGE_SHIFT) + offset);
}

/* Get the value at the physical address */
int getValue(int physicalAddress) {
	int frameNumber = ((physicalAddress & PAGE_NUM_MASK) >> PAGE_SHIFT);
	int offset = (physicalAddress & OFFSET_MASK);
	return physicalMemory[frameNumber][offset];
}
