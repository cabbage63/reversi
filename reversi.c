#include    <stdio.h>
#include    <ctype.h>
#include    "reversi.h"

void startGame(void){
    /* 
        Initialize
    */
    int dataArr[SIZE*SIZE];
    int validArr[SIZE*SIZE];
    int color, game_state;

    game_state = 0;
    color = BLACK;

    initData(dataArr);
    showBoard(dataArr);
    
    /*
        Roop
    */
    while( game_state != 2 ){
        //update validation array
        updateValidArr(dataArr, validArr, color);
        if( checkPuttability(validArr)){
            goTurn(dataArr, validArr, color);            
            toggleColor(&color);
            game_state = 0;
        }else{
            toggleColor(&color);
            game_state++;
        }
    }
    if( checkStoneNum(dataArr, BLACK) > checkStoneNum(dataArr, WHITE) ){
        printf("Black WIN\nBlack: %d\nWHITE: %d\n",
            checkStoneNum(dataArr,BLACK), checkStoneNum(dataArr,WHITE));
    }else{        
        printf("WHITE WIN\nBlack: %d\nWHITE: %d\n",
            checkStoneNum(dataArr,BLACK), checkStoneNum(dataArr,WHITE));
    }
}

void showBoard(int *data)
{
    int x,y;
    printf("  ");
    for( x=0; x<SIZE; x++){
        printf("%d ", x);
    }
    printf("\n");

    for( y=0; y<SIZE; y++){
        printf("%d|", y);
        for( x=0; x<SIZE; x++){
            putSymbol( *retCell(data, x, y ));
            printf(" ");
        }
        
        if( y == SIZE/2 ){
            printf("\tWhite: %d", checkStoneNum(data,WHITE));
        }else if( y == SIZE / 2 - 1 ){
            printf("\tBlack: %d", checkStoneNum(data,BLACK));
        }
        putchar('\n');
    }
}

void putSymbol(int num)
{
    switch(num){
        case 0:
            putchar('-');
            break;
        case 1:
            putchar('x');
            break;
        case 2:
            putchar('o');
            break;
    }
}

int *initData(int *data)
{
    int x,y,center;
    for( y=0; y<SIZE; y++){
        for( x=0; x<SIZE; x++){
            *retCell(data, x, y) = EMPTY;
        }
    }
    
    center = SIZE/2;
    *retCell(data, center, center) = BLACK;
    *retCell(data, center-1, center-1) = BLACK;
    *retCell(data, center, center-1) = WHITE;
    *retCell(data, center-1, center) = WHITE;
    
    return data;
}

/*
data: data array
x: x-coordination 1~SIZE
y: y-coordination 1~SIZE
*/
int *retCell(int *data, int x, int y)
{
    return (data + ( (x)+(y)*SIZE));
}

int inputX(void){
    int x;
    printf("input X: ");
    if(scanf("%d", &x)!=1)
        scanf("%*s");
    while( x < 0 || SIZE <= x ){
        printf("Please input a number 1~%d\n", SIZE);
        printf("input X: ");
        //scanf("%d", &x); 
        if(scanf("%d", &x)!=1)
            scanf("%*s");
        }
    return x;
}

int inputY(void){
    int y;
    printf("input Y: ");
    //scanf("%d", &y);
    if(scanf("%d", &y)!=1)
        scanf("%*s");
    while( y < 0 || SIZE <= y ){
        printf("Please input a number 1~%d\n", SIZE);
        printf("input Y: ");
        //scanf("%d", &y);
        if(scanf("%d", &y)!=1)
            scanf("%*s");
    }
    return y;
}

void showDirectionMap(int *map)
{
    int x,y;
    printf("  ");
    for( x=0; x<SIZE; x++){
        printf("%d", x);
    }
    printf("\n");

    for( y=0; y<SIZE; y++){
        printf("%d|", y);
        for( x=0; x<SIZE; x++){
            printf( "%d", *retCell(map, x, y ) );
        }
        putchar('\n');
    }
}

void showValidMap(int *map)
{
    int x,y;
    printf("  ");
    for( x=0; x<SIZE; x++){
        printf("%d ", x);
    }
    printf("\n  ");
    for( x=0; x<SIZE; x++){
        printf("_");
    }
    printf("\n");

    for( y=0; y<SIZE; y++){
        printf("%d|", y);
        for( x=0; x<SIZE; x++){
            printf( "%d ", *retCell(map, x, y ) != 0 );
        }
        putchar('\n');
    }
}

/*
    data: board map
    map:  map array to update
    color: Black or White
*/
void updateValidArr(int *data, int *map, int color){
    int x,y;
    for( y=0; y<SIZE; y++){
        for( x=0; x<SIZE; x++){
            int ct, result, initState;
            int *nowCell;
            nowCell = retCell(data, x, y);
            result = 0;
            if( color == BLACK){
                initState = 0;
            }else if(color == WHITE){
                initState = 2;
            }
            
            if( *nowCell != EMPTY ){
                result = 0;
            }else{
                //validation on each direction
                for(ct = 1; ct != 0x100; ct <<= 1){
                    result |= checkValid(data, x, y, initState, ct);
                }
            }
            *retCell(map, x, y) = result;
        }
    }
}

int checkValid(int *data, int x, int y, int state, int direction){
    int vx, vy, dx,dy;
    vx = 0;
    vy = 0;

    switch(direction){
        case UC:
            vx = 0;
            vy = -1;
            break;
        case UR:
            vx = 1;
            vy = -1;
            break;
        case MR:
            vx = 1;
            vy = 0;
            break;
        case BR:
            vx = 1;
            vy = 1;
            break;
        case BC:
            vx = 0;
            vy = 1;
            break;
        case BL:
            vx = -1;
            vy = 1;
            break;
        case ML:
            vx = -1;
            vy = 0;
            break;
        case UL:
            vx = -1;
            vy = -1;
            break;
    }
    dx = x + vx;
    dy = y + vy;
    if( 0 <= dx && dx < SIZE && 0 <= dy && dy < SIZE ){
        
        switch(state){
            case 0:
                if(*retCell(data, dx, dy) == WHITE){
                    return checkValid(data, dx, dy, 1, direction);
                }
                break;
            case 1:
                if(*retCell(data, dx, dy) == WHITE){
                    return checkValid(data, dx, dy, 1, direction);
                }else if(*retCell(data, dx, dy) == BLACK){
                    return direction;
                }
                break;
            case 2:
                if(*retCell(data, dx, dy) == BLACK){
                    return checkValid(data, dx, dy, 3, direction);
                }
                break;
            case 3:
                if(*retCell(data, dx, dy) == BLACK){
                    return checkValid(data, dx, dy, 3, direction);
                }
                else if(*retCell(data, dx, dy) == WHITE){
                    return direction;
                }
                break;
        }
    }
    return 0;
}

void putStone(int *data, int *map, int x, int y, int color){
    int ct, initState;
    int nowCellValid;
    nowCellValid = *retCell(map, x, y);
    if( color == BLACK){
        initState = 0;
    }else if(color == WHITE){
        initState = 2;
    }
    
    if( nowCellValid ){
        for(ct = 1; ct != 0x100; ct <<= 1){
            if( ct & nowCellValid ){
               turnStone(data, x, y, initState, ct);
            }
        }
    }
}

int turnStone(int *data, int x, int y, int state, int direction){
    int vx, vy, dx,dy;
    vx = 0;
    vy = 0;
    switch(direction){
        case UC:
            vx = 0;
            vy = -1;
            break;
        case UR:
            vx = 1;
            vy = -1;
            break;
        case MR:
            vx = 1;
            vy = 0;
            break;
        case BR:
            vx = 1;
            vy = 1;
            break;
        case BC:
            vx = 0;
            vy = 1;
            break;
        case BL:
            vx = -1;
            vy = 1;
            break;
        case ML:
            vx = -1;
            vy = 0;
            break;
        case UL:
            vx = -1;
            vy = -1;
            break;
    }
    dx = x + vx;
    dy = y + vy;

    if( 0 <= dx && dx < SIZE && 0 <= dy && dy < SIZE ){
        
        switch(state){
            int nextStoneColor;
            case 0:
                if(*retCell(data, dx, dy) == WHITE){
                    *retCell(data, x, y) = BLACK;
                    *retCell(data, dx, dy) = BLACK;
                    return turnStone(data, dx, dy, 1, direction);
                }
                break;
            case 1:
                if(*retCell(data, dx, dy) == WHITE){
                    *retCell(data, dx, dy) = BLACK;
                    return turnStone(data, dx, dy, 1, direction);
                }else if(*retCell(data, dx, dy) == BLACK){
                    return direction;
                }
                break;
            case 2:
                if(*retCell(data, dx, dy) == BLACK){
                    *retCell(data, x, y) = WHITE;
                    *retCell(data, dx, dy) = WHITE;
                    return turnStone(data, dx, dy, 3, direction);
                }
                break;
            case 3:
                if(*retCell(data, dx, dy) == BLACK){
                    *retCell(data, dx, dy) = WHITE;
                    return turnStone(data, dx, dy, 3, direction);
                }
                else if(*retCell(data, dx, dy) == WHITE){
                    return direction;
                }
                break;
        }
    }
    return 0;
}

void goTurn(int *data, int *map, int color)
{
    int x,y;
    
    if( color == BLACK){
        printf("Black turn\n");
    }else{
        printf("White turn\n");
    }

    //input coordinate and validation
    x = inputX();
    y = inputY();
    while( *retCell(map, x, y) == 0 ){
        printf("You cannot place a stone on (%d, %d).\n", x, y);
        x = inputX();
        y = inputY();
    }
    putStone(data, map, x, y, color);
    printf("*********************************\n");
    showBoard(data);
}

/*
    return
        1: there is a place that a stone can be put at.
        0: there is no place that a stone can be put at.
*/
int checkPuttability(int *map){
    int x, y, result;
    result = 0;
    for( x = 0; x < SIZE; x++){
        for( y = 0; y < SIZE; y++){
            if(*retCell(map, x, y)) result = 1;
        }
    }
    return result;
}

/*
    toggle WHITE and BLACK
*/
void toggleColor(int *c){
    if( *c == BLACK ){
        *c = WHITE;
    }else{
        *c = BLACK;
    }
}

/*
    return the # of stones of specified color
*/
int checkStoneNum(int *data, int color){
    int x, y, num;
    num = 0;
    for( x = 0; x < SIZE; x++){
        for( y = 0; y < SIZE; y++){
            if(*retCell(data, x, y) == color) num++;
        }
    }
    return num;
}
