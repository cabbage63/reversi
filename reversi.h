#define SIZE  8

//chip
#define EMPTY 0
#define BLACK 1
#define WHITE 2

//direcion
#define UC 1
#define UR 1<<1
#define MR 1<<2
#define BR 1<<3
#define BC 1<<4
#define BL 1<<5
#define ML 1<<6
#define UL 1<<7

void startGame(void);

/* display */
void showBoard(int *data);
void putSymbol(int num);
int *initData(int *data);
int *retCell(int *data, int x, int y);

/* input data */
int inputX(void);
int inputY(void);

/* check where is the stones put off */
void updateValidArr(int *data, int *map, int color);
int checkValid(int *data, int x, int y, int state, int direction);
int checkPuttability(int *map);

/* show validation map */
void showDirectionMap(int *map);
void showValidMap(int *map);

/* put a stone */
void putStone(int *data, int *map, int x, int y, int color);
int turnStone(int *data, int x, int y, int state, int direction);
void toggleColor(int *c);

/* progress 1 turn */
void goTurn(int *data, int *map, int color);

/* game state checker */
int checkStoneNum(int *data, int color);