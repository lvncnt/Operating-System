#include <stdio.h>
#include <stdlib.h>

/* Globale variables and constants */
#define PAGE_TABLE_ENTRIES 256 /* number of entries in the page table */
#define TLB_ENTRIES 16
#define FRAME_NUMBER 256
#define FRAME_SIZE 256
#define PAGE_SIZE 256

extern const int PAGE_NUM_MASK;
extern const int PAGE_SHIFT;
extern const int OFFSET_MASK;

extern const char *STARS;
extern const char VALID;
extern const char INVALID;

extern int TLBtail;
extern int TLBhits;
extern int pageFaults;
extern int frameCounter;

extern char *fileAddresses;
extern char *fileBackingStore;

FILE *fpAddresses; /* declare the file pointer */
FILE *fpBackingStore;

/* Data structure for page table, TLB and physical memory  */
struct PageTableEntry { /* each page table entry */
	int frameNumber;
	char validBit;
};

struct PageTableEntry pageTable[PAGE_TABLE_ENTRIES]; /* page table */
int TLB[TLB_ENTRIES][2]; 			/* {page number, frame number} */
char physicalMemory[FRAME_NUMBER][FRAME_SIZE]; 	/* physical memory */

/* Function declaration */
int getPageNumber(int);		/* Get decimal page number */
int getOffset(int);			/* Get decimal offset */
int checkPageTable(int); 	/* Get frame number for page number */
int checkTLB(int);			/* Check TLB */
void updateTLB(int, int); 	/* Update TLB */
int getPhysicalAddress(int);/* Get the physical address for the logical address */
int getValue(int); 			/* Get the value at the physical address */
