#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SYSTEMEMORY 1024
#define VIRTUALMEMORY 16384
#define PAGESIZE 1024
#define PAGENUMBER 16384
#define PAGEFRAMENUBER 1024

#define FRAME_TLB 't'

typedef struct PageTableEntry
{
    unsigned int page_frame_index;
    unsigned char frame_attributes;
}PageTableEntry;

typedef struct PageTable
{
    struct PageTableEntry** entries;
    unsigned int size;
}PageTable;

typedef struct TLBEntry
{
    unsigned int page_index;
    unsigned int page_frame_index;
    unsigned char frame_attributes;
}TLBEntry;

typedef struct TLB
{
    struct TLBEntry** entries;
    unsigned int size;
}TLB;

typedef struct Process
{
    unsigned char process_id;
    struct PageTable* page_table;
}Process;

typedef struct MMU
{
    struct TLB* tlb;
    struct Process* process;
}MMU;

typedef struct ED_209
{
    struct MMU* mmu;
}ED_209;

void printSystemInfo(void){
    printf("System-memory: %d KiB\nVirtual-memory: %d KiB\n", SYSTEMEMORY, VIRTUALMEMORY);
    printf("Page-size: %d KiB\nPages: %d\nPage-frames: %d", PAGESIZE, PAGENUMBER, PAGEFRAMENUBER);
}

PageTable* createPagetable(void){
    PageTable* pt = (PageTable*)malloc(sizeof(PageTable));
    PageTableEntry* pageTableEntry = (PageTableEntry*)calloc(PAGENUMBER, sizeof(PageTableEntry));
    pt->entries = calloc(PAGENUMBER, sizeof(PageTableEntry*));
    pt->size = PAGENUMBER;
    return pt;
}

TLB* createTLB(unsigned int size){
    TLB* tlb = malloc(sizeof(TLB));
    tlb->entries = calloc(sizeof(TLBEntry), size);
    tlb->size = size;
    return tlb;
}

Process* createProcess(unsigned char id){
    Process* process = malloc(sizeof(Process));
    process->process_id = id;
    process->page_table = createPagetable();
    return process;
}

unsigned int countTLBEntries(Process* p){
    unsigned int count = 0;
    for (int i = 0; i < p->page_table->size ; ++i) {
        if(p->page_table->entries[i]->frame_attributes == FRAME_TLB){
            count++;
        }
    }
}


int main() {
    Process *process = createProcess('a');
    process->page_table->entries[0]->frame_attributes = FRAME_TLB;
    printf("%c", process->page_table->entries[1]->frame_attributes);

    return 0;
}
