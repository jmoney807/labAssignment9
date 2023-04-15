#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
    struct RecordType *next;
};

// Fill out this structure
struct HashType
{
   struct RecordType *h;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    return (x % tableSize);
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    int index = 0;
    index = hash(record->id,tableSize);

    if (hashTable[index].h == NULL)
    {
        hashTable[index].h = record;
    }
    else
    {
		struct RecordType *temp = hashTable[index].h;

        while (temp->next != NULL)
            temp = temp->next;
		temp->next = record;
		temp->next->next = NULL;
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    // for each entry in the table
        // print the contents in that index
        // The output should look like this (for example): "Index 1 -> 21715, Q, 16 -> 28876, a, 26 -> NULL"
	int i;

	for (i=0;i<hashSz;++i)
	{
		printf("Index %d -> ", i);

		struct RecordType *temp = pHashArray[i].h;
		while (temp != NULL)
		{
			printf("%d, %c, %d -> ", temp->id, temp->name, temp->order);
			temp = temp->next;
		}
		printf("NULL\n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	// Initialize the hash table
    // create a variable hashTableSize and assign it a value
    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    // for each record in pRecords, insert it into the hash table using the insertRecord function
    // call the display records function
    // free all the allocated memory
    int tableSize = 11;
    
    struct HashType *hashTable = (struct HashType*) calloc(tableSize, sizeof(struct HashType));

    for (int i = 0; i < recordSz; i++)
    {
        insertRecord(hashTable,&pRecords[i],tableSize);
    }

	displayRecordsInHash(hashTable, tableSize);

	free(hashTable);
    free(pRecords);

    return 0;
}