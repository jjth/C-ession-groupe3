
#define RESET 0
#define SIZE_STACK 1000

typedef struct Line Line;
struct Line {
    int id;
    int* colors;
    char* line;
    Line *next;
};

typedef struct Ti Ti;
struct Ti {
	int id;
	Line* line;
	Ti *next;
};

typedef struct ListingLine ListingLine;
struct ListingLine {
    Line *first;
};

typedef struct ListingTi ListingTi;
struct ListingTi {
    Ti *first;
};

typedef struct stack stack;
struct stack{
	int top;
	int size;
	char* array;
};

ListingLine *initialisationLine();
void addALine(ListingLine *listingLine, int size, int id, char *str);
int deleteALine(ListingLine *listingLine, int id);
void displayListingValue(ListingLine *listingLine, int size);
void displayListingColor(ListingLine *listingLine, int size);
char getCharacter(ListingLine *listingLine, int idLine,int idCharacter);
void setCharacter(ListingLine *listingLine, int idLine,int idCharacter,char c);
void setCharacterColor(ListingLine *listingLine, int idLine,int idColor,int c);
int getCharacterColor(ListingLine *listingLine, int idLine,int idColor);
int getNeighbors(ListingLine *myListing,int nbLine,int nbColunm,int x,int y,int d,char t);

struct stack* create_stack(int size);
int isFull(struct stack* st);
int isEmpty(struct stack* st);
void push(struct stack* st, char element);
char pop(struct stack* st);