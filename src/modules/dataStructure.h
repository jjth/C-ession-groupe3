
#define RESET 0
#define SIZE_STACK 1000

typedef struct Line Line;
struct Line {
    int id;
    int* colors;
    char* line;
    Line *next;
};

typedef struct ListingLine ListingLine;
struct ListingLine {
    Line *first;
};


typedef struct Ti Ti;
struct Ti {
	int id;
	ListingLine* matrix;
	Ti *next;
};
typedef struct ListingTi ListingTi;
struct ListingTi {
    Ti *first;
};

ListingLine *initialisationLine();
ListingTi *initialisationTi();
void addALine(ListingLine *listingLine, int size, int id, char *str);
void AddLineQueue(ListingLine *listingLine, int size, int id, char *str);
void addTi(ListingTi *myListingTi, int id, ListingLine* matrix);
int deleteALine(ListingLine *listingLine, int id);
int compare2matrix(ListingLine *myList1,ListingLine *myList2);
void displayListingValue(ListingLine *listingLine, int size);
void displayListingColor(ListingLine *listingLine, int size);
char getCharacter(ListingLine *listingLine, int idLine,int idCharacter);
void setCharacter(ListingLine *listingLine, int idLine,int idCharacter,char c);
void setCharacterColor(ListingLine *listingLine, int idLine,int idColor,int c);
int getCharacterColor(ListingLine *listingLine, int idLine,int idColor);
int getNeighbors(int nbLine,int nbColunm,int x,int y,int d,char t);
ListingLine *createCopy(ListingLine *listingLine, int size);
int isCycle(ListingTi *myListTi, ListingLine *myListingLine);
