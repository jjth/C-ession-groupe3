
#define RESET 0


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

ListingLine *initialisationLine(int size,int id, char c0, char c1, char c2, char c3);
void addALine(ListingLine *listingLine, int size, int id, char c0, char c1, char c2, char c3);
int deleteALine(ListingLine *listingLine, int id);
void displayListing(ListingLine *listingLine, int size);
char getCharacter(ListingLine *listingLine, int idLine,int idCharacter);
void setCharacter(ListingLine *listingLine, int idLine,int idCharacter,char c);
void setCharacterColor(ListingLine *listingLine, int idLine,int idColor,int c);
int getCharacterColor(ListingLine *listingLine, int idLine,int idColor);
