
void UpdateGame() 
{ 
	int prevX = snakeTailX[0]; 
	int prevY = snakeTailY[0]; 
	int prev2X, prev2Y; 
	snakeTailX[0] = x; 
	snakeTailY[0] = y; 

	for (int i = 1; i < snakeTailLen; i++) { 
		prev2X = snakeTailX[i]; 
		prev2Y = snakeTailY[i]; 
		snakeTailX[i] = prevX; 
		snakeTailY[i] = prevY; 
		prevX = prev2X; 
		prevY = prev2Y; 
	} 

	switch (sDir) { 
	case LEFT: 
		x--; 
		break; 
	case RIGHT: 
		x++; 
		break; 
	case UP: 
		y--; 
		break; 
	case DOWN: 
		y++; 
		break; 
	} 

	
	if (x >= width || x < 0 || y >= height || y < 0) 
		isGameOver = true; 

	
	for (int i = 0; i < snakeTailLen; i++) { 
		if (snakeTailX[i] == x && snakeTailY[i] == y) 
			isGameOver = true; 
	} 

	
	if (x == fruitCordX && y == fruitCordY) { 
		playerScore += 10; 
		fruitCordX = rand() % width; 
		fruitCordY = rand() % height; 
		snakeTailLen++; 
	} 
}
