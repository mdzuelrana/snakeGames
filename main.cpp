
int main() 
{ 
	string playerName; 
	cout << "enter your name: "; 
	cin >> playerName; 
	int dfc = SetDifficulty(); 

	GameInit(); 
	while (!isGameOver) { 
		GameRender(playerName); 
		UserInput(); 
		UpdateGame(); 
		
		
		Sleep(dfc); 
	} 

	return 0; 
}
