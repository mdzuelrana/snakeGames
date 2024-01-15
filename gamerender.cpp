
void GameRender(string playerName) 
{ 
	system("cls"); 

	
	for (int i = 0; i < width + 2; i++) 
		cout << "-"; 
	cout << endl; 

	for (int i = 0; i < height; i++) { 
		for (int j = 0; j <= width; j++) { 
			
			if (j == 0 || j == width) 
				cout << "|"; 
			
			if (i == y && j == x) 
				cout << "O"; 
		
			else if (i == fruitCordY && j == fruitCordX) 
				cout << "#"; 
			
			else { 
				bool prTail = false; 
				for (int k = 0; k < snakeTailLen; k++) { 
					if (snakeTailX[k] == j 
						&& snakeTailY[k] == i) { 
						cout << "o"; 
						prTail = true; 
					} 
				} 
				if (!prTail) 
					cout << " "; 
			} 
		} 
		cout << endl; 
	} 

	
	for (int i = 0; i < width + 2; i++) 
		cout << "-"; 
	cout << endl; 

	
	cout << playerName << "'s Score: " << playerScore 
		<< endl; 
}
