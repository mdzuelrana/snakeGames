
const int width = 80; 
const int height = 20; 


int x, y; 
 
int fruitCordX, fruitCordY; 
 
int playerScore; 

int snakeTailX[100], snakeTailY[100]; 

int snakeTailLen; 

enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; 

snakesDirection sDir; 

bool isGameOver;
