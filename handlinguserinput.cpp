
void UserInput() 
{ 
	
	if (_kbhit()) { 
		
		switch (_getch()) { 
		case 'a': 
			sDir = LEFT; 
			break; 
		case 'd': 
			sDir = RIGHT; 
			break; 
		case 'w': 
			sDir = UP; 
			break; 
		case 's': 
			sDir = DOWN; 
			break; 
		case 'x': 
			isGameOver = true; 
			break; 
		} 
	} 
}
