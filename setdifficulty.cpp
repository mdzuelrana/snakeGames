
int SetDifficulty() 
{ 
	int dfc, choice; 
	cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
			"\nNOTE: if not chosen or pressed any other "
			"key, the difficulty will be automatically set "
			"to medium\nChoose difficulty level: "; 
	cin >> choice; 
	switch (choice) { 
	case '1': 
		dfc = 50; 
		break; 
	case '2': 
		dfc = 100; 
		break; 
	case '3': 
		dfc = 150; 
		break; 
	default: 
		dfc = 100; 
	} 
	return dfc; 
}
