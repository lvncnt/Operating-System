#include "header.h"

const char *STARS = "******************************************";
const char VALID = 'v'; 			/* Whether the mapping is valid */
const char INVALID = 'i';
const int PAGE_NUM_MASK = 0xFF00;	/* bit-mask: 1111,1111,0000,0000 */
const int PAGE_SHIFT = 8; 			/* bit-shift: 8-bit page number */
const int OFFSET_MASK = 0xFF;		/* bit-mask: 0000,0000,1111,1111 */

int TLBtail; 						/* tail(current position) at the TLB */
int TLBhits; 						/* store number of TLB hits */
int pageFaults; 					/* store number of page faults */
int frameCounter;

char *fileAddresses;				/* file pointer (addresses.txt) */ 
char *fileBackingStore;				/* file pointer (BACKING_STORE.bin) */ 

int main(int argc, char ** argv) {

	// Get file names from command arguments 
	if (argc < 3) {
		printf("! Missing input file names\n");
		printf("! Try to run like this:\n");
		printf("\t./translate addresses.txt BACKING_STORE.bin\n");
		exit(EXIT_FAILURE);
	}

	fileAddresses = argv[1]; 	// "addresses.txt";
	fileBackingStore = argv[2]; // "BACKING_STORE.bin";

	TLBtail = 0;
	TLBhits = 0;
	pageFaults = 0;
	frameCounter = 0;

	// Initialize TLB
	int i;
	for (i = 0; i < TLB_ENTRIES; i++) {
		TLB[i][0] = -1;
	}

	// Initialize page table
	for (i = 0; i < PAGE_TABLE_ENTRIES; i++) {
		pageTable[i].frameNumber = -1;
		pageTable[i].validBit = INVALID;
	}

	// Open files for reading
	fpAddresses = fopen(fileAddresses, "r");
	fpBackingStore = fopen(fileBackingStore, "r");
	if (fpAddresses == NULL || fpBackingStore == NULL) {
		perror("Error opening the file");
		exit(EXIT_FAILURE);
	}

	// Seek to the begining of the file
	fseek(fpAddresses, SEEK_SET, 0);

	size_t len = 0;
	ssize_t read;
	char *line = NULL;
	int addressCounter = 0;

	while ((read = getline(&line, &len, fpAddresses)) != -1) {
		// Read logical addresses
		int logicalAddress = atoi(line);

		// Translate logical address to physical address
		int physicalAddress = getPhysicalAddress(logicalAddress);
		addressCounter++;

		printf("Virtual Address: %d Physical Address: %d Value: %d\n",
				logicalAddress, physicalAddress, getValue(physicalAddress));
	}

	fclose(fpAddresses);

	// Report statistics: Page-fault rate, TLB hit rate etc.
	printf("%s\n", STARS);
	printf("Number of Translated Addresses = %d\n", addressCounter);
	printf("Page Faults = %d\n", pageFaults);
	printf("%s = %.3f\n", "Page Fault Rate", (float) pageFaults / addressCounter);
	printf("TLB Hits = %d\n", TLBhits);
	printf("%s = %.3f\n", "TLB Hit Rate", (float) TLBhits / addressCounter);

	return 0;
}

