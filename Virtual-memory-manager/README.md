
This project consists of writing a program that translates logical to physical addresses for a virtual address space of size *2^16 = 65,536* bytes. The program will read from a file containing logical addresses and, using a TLB as well as a page table, will translate each logical address to its corresponding physical address and output the value of the byte stored at the translated physical address. 

## BUILDING
 
To build the C program, run:
`make translate`

## EXECUTION 

After building is finished, run the program via:
`./translate addresses.txt BACKING_STORE.bin`, where the second argument shall be the name of the file containing logical addresses, and the third argument shall be the name of the file representing the backing store. 

## FEATURES
The program reads in the file addresses.txt, which contains integer values representing logical addresses, and file `BACKING STORE.bin`, which represents the backing store. 


Then it will translate each logical address to a physical address and determines the contents of the signed byte stored at the correct physical address.


Finally, the program will output the following values:


- The logical address being translated
- The corresponding physical address
- The signed byte value stored at the translated physical address 
- Page-fault rate 
- TLB hit rate

