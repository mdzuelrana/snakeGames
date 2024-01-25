void GameInit() 
{ 
	isGameOver = false; 
	sDir = STOP; 
	x = width / 2; 
	y = height / 2; 
	fruitCordX = rand() % width; 
	fruitCordY = rand() % height; 
	playerScore = 0; 
}
