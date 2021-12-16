#include "Game.h"

GAME::GAME() {
	map = new MAP(this);
}

GAME::~GAME() {
	delete map;
}

//setting ver1
/*
void GAME::setting() {
	system("cls");
	string opt[2] = { "1. Sound:", "2. Back to menu" };
	string sound[2] = { " << OFF >>", " << ON  >>" };
	int option = 0, optSound = 1;
	char key;

	gotoXY(85, 16);
	cout << "SETTINGS";
	gotoXY(80, 18);
	TextColor(11);
	cout << opt[0] + sound[1];
	TextColor(15);
	gotoXY(80, 20);
	cout << opt[1];

	while (true) {
		if (_kbhit) {
			key = _getch();
			if (key == 'W' || key == 'w' || key == 72) {
				gotoXY(80, 18 + option * 2);
				cout << opt[option];
				if (option == 0) cout << sound[optSound];
				option--;
				if (option < 0) option = 1;
				gotoXY(80, 18 + option * 2);
				TextColor(11);
				cout << opt[option];
				if (option == 0) cout << sound[optSound];
				TextColor(15);
			}
			else if (key == 'S' || key == 's' || key == 80) {
				gotoXY(80, 18 + option * 2);
				cout << opt[option];
				if (option == 0) cout << sound[optSound];
				option++;
				if (option > 1) option = 0;
				gotoXY(80, 18 + option * 2);
				TextColor(11);
				cout << opt[option];
				if (option == 0) cout << sound[optSound];
				TextColor(15);
			}
			else if (key == 'A' || key == 'a' || key == 75 || key == 'd' || key == 'D' || key == '77') {
				if (option != 0)
					continue;
				optSound = !optSound;
				gotoXY(89, 18);
				TextColor(11);
				cout << sound[optSound];
				TextColor(15);
			}
			else if (key == 13) {
				if (option != 1)
					continue;
				system("cls");
				return;
			}
		}
	}

}
*/
void GAME::setting()
{
	system("cls");
	string opt[2] = { "1. Sound:", "2. Back to menu" };
	string sound[2] = { " << ON >>", " << OFF >>" };
	int option = 0;
	char key;

	drawRecDouble(83, 15, 11, 1);
	gotoXY(85, 16);
	cout << "SETTINGS";
	gotoXY(80, 19);
	TextColor(11);
	cout << opt[0] + sound[isMute];
	TextColor(15);
	gotoXY(80, 21);
	cout << opt[1];

	while (true) {
		if (_kbhit) {
			key = _getch();
			if (key == 'W' || key == 'w' || key == 72) {
				gotoXY(80, 19 + option * 2);
				cout << opt[option];
				if (option == 0) cout << sound[isMute];
				option--;
				if (option < 0) option = 1;
				gotoXY(80, 19 + option * 2);
				TextColor(11);
				cout << opt[option];
				if (option == 0) cout << sound[isMute];
				clickSound(isMute);
				TextColor(15);
			}
			else if (key == 'S' || key == 's' || key == 80) {
				gotoXY(80, 19 + option * 2);
				cout << opt[option];
				if (option == 0) cout << sound[isMute];
				option++;
				if (option > 1) option = 0;
				gotoXY(80, 19 + option * 2);
				TextColor(11);
				cout << opt[option];
				if (option == 0) cout << sound[isMute];
				clickSound(isMute);
				TextColor(15);
			}
			else if (key == 'A' || key == 'a' || key == 75 || key == 'd' || key == 'D' || key == 77) {
				if (option != 0)
					continue;
				isMute = !isMute;
				map->setMute(isMute);
				gotoXY(89, 19);
				cout << "            ";
				TextColor(11);
				gotoXY(89, 19);
				cout << sound[isMute];
				TextColor(15);
				chooseSound(false);
			}
			else if (key == 13) {
				if (option != 1)
					continue;
				chooseSound(isMute);
				system("cls");
				return;
			}
		}
	}
}

void GAME::newGame() {
	system("cls");
	Nocursortype();
	TextColor(ColorCode_White);

	drawInputNameBar();

	bool notiFlag = 0;
	string tmp = "";
	int startX = 56;
	int startY = 21;

	UnNocursortype();
	gotoXY(startX, startY);

	//map->~MAP();			//new game, map is reset
	//new(&map) MAP(this);

	while (true) {
		unsigned char ch = _getch();
		if (ch == 0 || ch == 224) {
			_getch();
			continue;
		}
		else {
			if (ch == ESC) {
				// back to the previous menu
				return;
			}
			else if (ch == ENTER) {
				if (tmp.size() > 32)
					continue;
				subNewGame();
				map->setPlayerName(tmp);
				map->runGame();
				system("cls");
				return;
			}
			else if (ch == BACKSPACE) {
				if (!tmp.empty()) {
					Nocursortype();
					tmp.pop_back();
					gotoXY(startX, startY);
					cout << "                                                                                 ";
					if (tmp.size() <= 32 && notiFlag) {
						notiFlag = false;
						gotoXY(startX - 17, startY + 2);
						cout << "                                                  ";
						gotoXY(startX + tmp.size(), startY);
					}
					//gotoXY(startX, startY);
					//cout << tmp;
					UnNocursortype();
				}
			}
			else {
				if (tmp.size() == 81) //input name bar bounding box
					continue;
				Nocursortype();
				tmp.push_back(ch);
				if (tmp.size() > 32 && !notiFlag) {
					notiFlag = true;
					TextColor(ColorCode_DarkRed);
					gotoXY(startX - 17, startY + 2);
					cout << "Your name must be between 0 and 32 characters long";
					TextColor(ColorCode_White);
				}
				gotoXY(startX, startY);
				cout << tmp;
				UnNocursortype();
			}
		}
		//keyboardSound(isMute);			//sound when type by keyboard
	}
}

void GAME::title() {
	const char Title[][82] = { { 32,95,95,95,95,95,32,32,     32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		  32,32,32,32,32,'_',32,	   32,32,32,32,32,  32,32,32,'_','_','_','_',32,	32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,	   32,32,32,32,32,		 32,32,32,	  32,32,32,32,32,32,32,		   },
								 { 32,'_',95,95,95,95,32,32,     32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		  32,32,32,32,32,'_',32,	   32,32,32,32,32,  32,32,32,'_','_','_','_',32,	32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,	   32,32,32,32,32,		 32,32,32,	  32,32,32,32,32,32,32,		   },
								{ '|',32,32,'_','_',32,92,32,	 32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		  32,32,32,32,'|',32,178,	   32,32,32,32,32,  32,32,'/',32,'_','_','_',178,	32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,	   32,32,32,32,32,		 32,32,32,	  32,32,32,32,32,32,32,		   },
								{ '|',32,178,'_','_',')',32,')', 32,32,'_','_','_',32,32,	 32,32,'_','_',32,'_',32,	  32,32,'_','_','|',32,178,	   32,32,32,32,32,  32,'/',32,32,178,32,32,32,		32,'_',32,'_','_',32,	 32,32,'_','_','_',32,32,	 32,'_','_','_',32,    32,'_','_','_',32,	 '(','_',')', 32,'_',32,'_','_',32,32,	  32,32,'_','_',32,'_',32},
								{ '|',32,32,'_',32,32,'/',32,	 32,'/',32,'_',32,'\\',32,	 32,'/',32,'_','\'',32,178,	  32,'/',32,'_',32,32,178,	   32,32,32,32,32,  '|',32,32,32,178,32,32,32,		'|',32,'\'','_','_',178, 32,'/',32,'_',32,'\\',32,	 '/',32,'_','_',178,   '/',32,'_','_',178,   '|',32,178,  '|',32,'\'','_',32,'\\',32, 32,'/',32,'_','\'',32,178},
								{ '|',32,178,32,92,32,92,32,	 '(',32,'(','_',')',32,')',	 '(',32,'(','_',')',32,178,	  '(',32,'(','_',')',32,178,   32,32,32,32,32,  32,'\\',32,32,178,'_','_','_',  '|',32,178,32,32,32,	 '(',32,'(','_',')',32,')',  '\\','_','_',32,'\\', '\\','_','_',32,'\\', '|',32,178,  '|',32,178,32,'|',32,178,	  '(',32,'(','_',')',32,178},
								{ '|','_',178,32,32,92,'_',92,	 32,'\\','_','_','_','/',32, 32,'\\','_','_',',','_',178, 32,'\\','_','_',',','_',178, 32,32,32,32,32,  32,32,'\\','_','_','_','_',178, '|','_',178,32,32,32,	 32,'\\','_','_','_','/',32, 178,'_','_','_','/',  178,'_','_','_','/',  '|','_',178, '|','_',178,32,'|','_',179, 32,'\\','_','_',',',32,178},
								{ 32,32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		  32,32,32,32,32,32,32,		   32,32,32,32,32,  32,32,32,32,32,32,32,32,		32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,	   32,32,32,32,32,		 32,32,32,	  32,32,32,32,32,32,32,		  32,178,'_','_','_','/'} };
	int y = 7, x = 45;
	int i, j;
	for (i = 0; i < 8; ++i) {
		gotoXY(x, y++);
		for (j = 0; j < 82; ++j) {
			cout << Title[i][j];
		}
	}
}


void GAME::menu() {
	title();
	drawLoadingBar();
	system("cls");
	title();
	int x = 75;
	int y = 17;
	string prompt[] = { "1. New game", "2. Load game", "3. Settings", "4. Exit" };
	const int length = 4;
	int choice = 0;
	while (true) {
		//choice = returnChoice(prompt, length, x, y);
		choice = returnChoice2(isMute, prompt, length, x, y);
		while (true)
		{
			switch (choice)
			{
			case 0:
			{
				newGame();
				title();
				break;
			}
			case 1:
			{
				break;
			}
			case 2:
			{
				setting();
				title();
				break;
			}
			case 3:
			{
				system("cls");
				exit(1);
				break;
			}
			}
			break;
		}
	}
}

void GAME::loadGameMenu(vector<string>& fileName, bool& noSaveGame, int& startX, int& startY, string& path, int& option, int& maxFile) {
	string tmp;
	ifstream ifs;
	noSaveGame = false;
	path = "./SaveGame/";
	ifs.open(path + "SaveGameFileName.txt");
	if (!ifs.is_open())
		noSaveGame = true;
	while (!ifs.eof()) {
		getline(ifs, tmp, '\n');
		if (tmp == "")
			continue;
		fileName.push_back(tmp);
	}
	ifs.close();

	startX = 87;
	startY = 14;

	if (fileName.size() == 0) noSaveGame = true;
	option = 0;
	maxFile = min(fileName.size(), 5);
	if (noSaveGame) {
		TextColor(ColorCode_Yellow);
		gotoXY(startX - 6, startY);
		cout << "No save game!\n";
		gotoXY(startX - 12, startY + 2);
		cout << "Press any key to continue\n";
		_getch();
		return;
	}
	else {
		drawRecSingle(startX - 40, startY, 80, maxFile * 2 + 2);
		startY += 2;
		for (int i = 0; i < maxFile; i++) {
			if (i == 0) {
				gotoXY(startX - (fileName[i].size() / 2) - 3, startY + 2 * i);
				TextColor(ColorCode_Yellow);
				cout << ">> " << fileName[i];
			}
			else {
				gotoXY(startX - (fileName[i].size() / 2) - 1, startY + 2 * i);
				TextColor(ColorCode_White);
				cout << fileName[i];
			}
		}
	}

}

void GAME::loadGame() {
	system("cls");
	int startX = 80;
	int startY = 10;

	// load game board
	TextColor(ColorCode_DarkCyan);
	gotoXY(startX + 2, startY + 1);
	cout << "LOAD GAME";

	gotoXY(startX + 1, startY);
	for (int i = 0; i < 11; ++i) //10 is the size of " NEW GAME "
		cout << char(205);

	gotoXY(startX + 1, startY + 2);
	for (int i = 0; i < 11; ++i) //10 is the size of " NEW GAME "
		cout << char(205);

	gotoXY(startX, startY);
	cout << char(201);
	gotoXY(startX, startY + 2);
	cout << char(200);

	gotoXY(startX + 12, startY); // +11 because " NEW GAME " is 10 and plus 1 more  
	cout << char(187);
	gotoXY(startX + 12, startY + 2); // +11 because " NEW GAME " is 10 and plus 1 more
	cout << char(188);

	gotoXY(startX, startY + 1);
	cout << char(186);
	gotoXY(startX + 12, startY + 1);
	cout << char(186);

	vector<string> fileName;
	bool noSaveGame;
	string path;
	int option, maxFile;
	loadGameMenu(fileName, noSaveGame, startX, startY, path, option, maxFile);
	string tmpS = fileName[option];
	while (true) {
		if (_kbhit()) {
			unsigned char key = _getch();
			if (!noSaveGame && (key == 'W' || key == 'w')) {
				if (!option)
					continue;
				else {
					//print the old selection back to white
					gotoXY(startX - (tmpS.size() / 2) - 3, startY);
					cout << "                                        ";
					gotoXY(startX - (tmpS.size() / 2) - 1, startY);
					TextColor(ColorCode_White);
					cout << tmpS;

					//print the new selection to dark cyan
					startY -= 2;
					tmpS = fileName[--option];
					gotoXY(startX - (tmpS.size() / 2) - 3, startY);
					cout << "                                        ";
					gotoXY(startX - (tmpS.size() / 2) - 3, startY);
					TextColor(ColorCode_Yellow);
					cout << ">> " << tmpS;
				}
			}
			else if (!noSaveGame && (key == 'S' || key == 's')) {
				if (option == maxFile - 1)
					continue;
				else {
					//print the old selection back to white
					gotoXY(startX - (tmpS.size() / 2) - 3, startY);
					cout << "                                        ";
					gotoXY(startX - (tmpS.size() / 2) - 1, startY);
					TextColor(ColorCode_White);
					cout << tmpS;

					//print the new selection to dark cyan
					startY += 2;
					tmpS = fileName[++option];
					gotoXY(startX - (tmpS.size() / 2) - 3, startY);
					cout << "                                        ";
					gotoXY(startX - (tmpS.size() / 2) - 3, startY);
					TextColor(ColorCode_Yellow);
					cout << ">> " << tmpS;
				}
			}
			else if (!noSaveGame && key == ENTER) {
				map->loadGame(path + fileName[option] + ".txt");
				return; 
			}
			else if (key == ESC) {
				system("cls");
				return;
			}
		}
	}
}

int GAME::backToMenu() {
	system("cls");
	int x = 50, y = 10;
	const string title[8] = {
	" _                _      _                                    ___  ",
	"| |              | |    | |                                  |__ \\ ",
	"| |__   __ _  ___| | __ | |_ ___    _ __ ___   ___ _ __  _   _  ) |",
	"| '_ \\ / _` |/ __| |/ / | __/ _ \\  | '_ ` _ \\ / _ \\ '_ \\| | | |/ / ",
	"| |_) | (_| | (__|   <  | || (_) | | | | | | |  __/ | | | |_| |_|  ",
	"|_.__/ \\__,_|\\___|_|\\_\\  \\__\\___/  |_| |_| |_|\\___|_| |_|\\__,_(_)  ",
	"                                                                    " };
	drawRecDouble(42, 9, 80, 7);
	for (int i = 0; i < 7; i++) {
		gotoXY(x, y++);
		cout << title[i] << "\n";
	}

	x = 74;
	y = 20;
	string prompt[] = { "1. Back and save", "2. Back without save", "3. Cancel" };
	const int length = 3;
	int choice = 0;
	while (true) {
		choice = returnChoice(prompt, length, x, y);
		switch (choice)
		{
		case 0:
			//Back and save
			system("cls");
			saveGameMenu();
			return 0;
			break;
		case 1:
			//Back without save
			return 1;
			break;
		case 2:
			//Cancel
			return 2;
			break;
		}
		break;
	}
}

int returnChoice(string menu[], const int length, int x, int y) {
	int choice = 0;
	while (true) {
		for (int i = 0; i < length; i++)
		{
			gotoXY(x, y + i);
			for (int j = 0; j < menu[i].length(); ++j)
				cout << " ";
		}
		for (int i = 0; i < length; i++)
		{
			if (i == choice)
			{
				TextColor(250);
				gotoXY(x, y + 2 * i);
				cout << menu[i];
				TextColor(7);
			}
			else
			{
				gotoXY(x, y + 2 * i);
				cout << menu[i];
			}
		}
		while (1)
		{
			if (_kbhit())
			{
				char key = _getch();
				if (key == 'W' || key == 'w' || key == 72)
				{
					if (choice > 0)
						choice--;
					else
						choice = length - 1;
					break;
				}
				if (key == 'S' || key == 's' || key == 80)
				{
					if (choice < length - 1)
						choice++;
					else
						choice = 0;
					break;
				}
				if (key == 13)
				{
					return choice;
				}
			}
		}
	}
}

int returnChoice2(bool mute, string menu[], const int length, int x, int y)
{
	int choice = 0;
	clickSound(true);
	while (true) {
		for (int i = 0; i < length; i++)
		{
			gotoXY(x, y + i);
			for (int j = 0; j < menu[i].length(); ++j)
				cout << " ";
		}
		for (int i = 0; i < length; i++)
		{
			if (i == choice)
			{
				TextColor(250);
				gotoXY(x, y + 2 * i);
				cout << menu[i];
				TextColor(7);
			}
			else
			{
				gotoXY(x, y + 2 * i);
				cout << menu[i];
			}
		}
		while (1)
		{
			if (_kbhit())
			{
				char key = _getch();
				if (key == 'W' || key == 'w' || key == 72)
				{
					if (choice > 0)
						choice--;
					else
						choice = length - 1;
					break;
				}
				if (key == 'S' || key == 's' || key == 80)
				{
					if (choice < length - 1)
						choice++;
					else
						choice = 0;
					break;
				}
				if (key == 13)
				{
					chooseSound(mute);
					return choice;
				}
			}
		}
		clickSound(mute);
	}
}

void GAME::printCongrat() {
	system("cls");
	int x = 53, y = 10;
	const string title[8] = {
	"                                 _         _       _   _             ",
	"                                | |       | |     | | (_)            ",
	"  ___ ___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_ _  ___  _ __  ",
	" / __/ _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` | __| |/ _ \\| '_ \\ ",
	"| (_| (_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | (_) | | | |",
	" \\___\\___/|_| |_|\\__, |_|  \\__,_|\\__|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|",
	"                  __/ |                                              ",
	"                 |___/                                               " };
	for (int i = 0; i < 8; i++) {
		gotoXY(x, y++);
		cout << title[i] << "\n";
	}
	x = 65;
	y = 20;
	gotoXY(x, y);
	cout << "GOOD GAME! YOU ARE THE BEST ROAD CROSSER!\n";
	gotoXY(x + 12, y + 2);
	cout << "BACK TO MENU?";
	x = 80;
	y = 24;
	string prompt[] = { "1. Yes", "2. Also yes" };
	const int length = 2;
	int choice = returnChoice(prompt, 2, x, y);
	return;
}

bool GAME::printLose() {
	system("cls");
	int x = 65, y = 10;
	const string title[8] = {
	" _____               _     _ _ _ ",
	"/  __ \\             | |   | | | |",
	"| /  \\/_ __ __ _ ___| |__ | | | |",
	"| |   | '__/ _` / __| '_ \\| | | |",
	"| \\__/\\ | | (_| \\__ \\ | | |_|_|_|",
	" \\____/_|  \\__,_|___/_| |_(_|_|_)",
	"                                  ",
	"                                  " };
	for (int i = 0; i < 8; i++) {
		gotoXY(x, y++);
		cout << title[i] << "\n";
	}
	x += 5;
	y += 2;
	gotoXY(x, y);
	cout << "SEE YOU IN THE PARADISE...\n";
	gotoXY(x + 5, y + 2);
	cout << "WANNA REPLAY?";
	x += 8;
	y += 4;
	string prompt[] = { "1. Yes", "2. No" };
	const int length = 2;
	int choice = 0;
	while (true) {
		//choice = returnChoice(prompt, length, x, y);
		choice = returnChoice2(isMute, prompt, length, x, y);
		switch (choice)
		{
		case 0:
		{
			return true;
			break;
		}
		case 1:
		{
			return false;
			break;
		}
		}
		break;
	}
}

bool GAME::levelUp() {
	system("cls");
	int x = 68, y = 10;
	const string title[8] = {
	" _                _               ",
	"| |              | |              ",
	"| | _____   _____| |  _   _ _ __  ",
	"| |/ _ \\ \\ / / _ \\ | | | | | '_ \\ ",
	"| |  __/\\ V /  __/ | | |_| | |_) |",
	"|_|\\___| \\_/ \\___|_|  \\__,_| .__/ ",
	"                           | |    ",
	"                           |_|    " };
	drawRecDouble(64, 9, 40, 8);
	for (int i = 0; i < 8; i++) {
		gotoXY(x, y++);
		cout << title[i] << "\n";
	}
	x = 65;
	y = 20;
	gotoXY(x, y);
	cout << "BIN! BIN! BIN! YOU HAVE PASSED THE LEVEL!\n";
	gotoXY(x + 14, y + 2);
	cout << "KEEP GOING?";
	x = 81;
	y = 24;
	string prompt[] = { "1. Yes", "2. No" };
	const int length = 2;
	int choice = 0;
	while (true) {
		//choice = returnChoice(prompt, length, x, y);
		choice = returnChoice2(isMute, prompt, length, x, y);
		switch (choice)
		{
		case 0:
			return true;
			break;
		case 1:
			return false;
			break;
		}
		break;
	}
}

bool GAME::saveGameMenu() {
	system("cls");
	int x = 40, y = 10;
	const string title[8] = {
	"                     _     _                                                          ___  ",
	"                    | |   | |                                                        |__ \\ ",
	"__      ____ _ _ __ | |_  | |_ ___    ___  __ ___   _____    __ _  __ _ _ __ ___   ___  ) |",
	"\\ \\ /\\ / / _` | '_ \\| __| | __/ _ \\  / __|/ _` \\ \\ / / _ \\  / _` |/ _` | '_ ` _ \\ / _ \\/ / ",
	" \\ V  V / (_| | | | | |_  | || (_) | \\__ \\ (_| |\\ V /  __/ | (_| | (_| | | | | | |  __/_|  ",
	"  \\_/\\_/ \\__,_|_| |_|\\__|  \\__\\___/  |___/\\__,_| \\_/ \\___|  \\__, |\\__,_|_| |_| |_|\\___(_)  ",
	"                                                             __/ |                         ",
	"                                                            |___/                          " };
	for (int i = 0; i < 8; i++) {
		gotoXY(x, y++);
		cout << title[i] << "\n";
	}
	x = 80;
	y = 20;
	string prompt[] = { "1. Yes", "2. No" };
	const int length = 2;
	int choice = 0;
	while (true) {
		//choice = returnChoice(prompt, length, x, y);
		choice = returnChoice2(isMute, prompt, length, x, y);
		switch (choice)
		{
		case 0:
		{
			//save game function
			return true;
			break;
		}
		case 1:
		{
			return false;
			break;
		}
		}
		break;
	}
}

/*
bool GAME::backToMenu() {
	int x = 50, y = 10;
	const string title[8] = {
	" _                _      _                                    ___  ",
	"| |              | |    | |                                  |__ \\ ",
	"| |__   __ _  ___| | __ | |_ ___    _ __ ___   ___ _ __  _   _  ) |",
	"| '_ \\ / _` |/ __| |/ / | __/ _ \\  | '_ ` _ \\ / _ \\ '_ \\| | | |/ / ",
	"| |_) | (_| | (__|   <  | || (_) | | | | | | |  __/ | | | |_| |_|  ",
	"|_.__/ \\__,_|\\___|_|\\_\\  \\__\\___/  |_| |_| |_|\\___|_| |_|\\__,_(_)  ",
	"                                                                    ",
	"                                                                    " };
	for (int i = 0; i < 8; i++) {
		gotoXY(x, y++);
		cout << title[i] << "\n";
	}
	x = 75;
	y = 20;
	string prompt[] = { "1. Save Game", "2. Cancel" };
	const int length = 2;
	int choice = 0;
	while (true) {
		choice = returnChoice(prompt, length, x, y);
		switch (choice)
		{
		case 0:
		{
			system("cls");
			saveGameMenu();
			return true;
			break;
		}
		case 1:
		{
			//cancel
			return false;
			break;
		}
		}
		break;
	}
}*/

void drawLoadingBar() {
	int startX = 55;
	int startY = 17;

	gotoXY(startX, startY + 1);
	cout << "Loading ";

	gotoXY(startX + 14, startY);
	for (int i = 0; i < 51; i++)
		cout << char(205);

	gotoXY(startX + 14, startY + 2);
	for (int i = 0; i < 51; i++)
		cout << char(205);

	gotoXY(startX + 13, startY);
	cout << char(201);
	gotoXY(startX + 13, startY + 2);
	cout << char(200);

	gotoXY(startX + 65, startY);
	cout << char(187);
	gotoXY(startX + 65, startY + 2);
	cout << char(188);

	gotoXY(startX + 13, startY + 1);
	cout << char(186);
	gotoXY(startX + 65, startY + 1);
	cout << char(186);

	for (int i = 0; i <= 100; i++) {
		gotoXY(startX + 8, startY + 1);
		cout << i << "%";
		if (!(i % 2)) {
			gotoXY(startX + 14 + i / 2, startY + 1);
			cout << char(219);
		}
		Sleep(10);
	}
}

void subNewGame() {
	system("cls");
	Nocursortype();
	TextColor(ColorCode_White);

	int startX = 55;
	int startY = 20;
	clock_t begin, end;
	begin = clock();

	/*
		do something here
	*/

	drawLoadingBar();

	end = clock();

	gotoXY(startX + 13, startY);
	cout << "Loading time: " << (float)(end - begin) / CLOCKS_PER_SEC << "s";
	gotoXY(startX + 13, startY + 2);
	cout << "Press any key to continue...";
	_getch();
}

void drawInputNameBar() {
	int startX = 82;
	int startY = 17;

	// new game board
	TextColor(ColorCode_DarkCyan);
	gotoXY(startX + 2, startY + 1);
	cout << "NEW GAME";

	gotoXY(startX + 1, startY);
	for (int i = 0; i < 10; ++i) //10 is the size of " NEW GAME "
		cout << char(205);

	gotoXY(startX + 1, startY + 2);
	for (int i = 0; i < 10; ++i) //10 is the size of " NEW GAME "
		cout << char(205);

	gotoXY(startX, startY);
	cout << char(201);
	gotoXY(startX, startY + 2);
	cout << char(200);

	gotoXY(startX + 11, startY); // +11 because " NEW GAME " is 10 and plus 1 more  
	cout << char(187);
	gotoXY(startX + 11, startY + 2); // +11 because " NEW GAME " is 10 and plus 1 more
	cout << char(188);

	gotoXY(startX, startY + 1);
	cout << char(186);
	gotoXY(startX + 11, startY + 1);
	cout << char(186);

	// enter your name board
	startX = 37;
	startY = 20;

	gotoXY(startX + 2, startY + 1);
	cout << "Enter your name: ";

	gotoXY(startX + 1, startY);
	for (int i = 0; i < 100; i++)
		cout << char(205);

	gotoXY(startX + 1, startY + 2);
	for (int i = 0; i < 100; i++)
		cout << char(205);

	gotoXY(startX, startY);
	cout << char(201);
	gotoXY(startX, startY + 2);
	cout << char(200);

	gotoXY(startX + 101, startY);
	cout << char(187);
	gotoXY(startX + 101, startY + 2);
	cout << char(188);

	gotoXY(startX, startY + 1);
	cout << char(186);
	gotoXY(startX + 101, startY + 1);
	cout << char(186);

	TextColor(ColorCode_White);
}


void drawRecSingle(int ox, int oy, short width, short height) {
	gotoXY(ox, oy);
	cout << (char)218;				//Top-left corner
	for (int i = 1; i <= width; ++i) {
		cout << (char)196;
	}
	cout << (char)191 << endl;
	gotoXY(ox, ++oy);
	for (int i = 1; i <= height; ++i) {
		cout << (char)179;
		for (int j = 1; j <= width; ++j) {
			cout << " ";
		}
		cout << (char)179 << endl;
		gotoXY(ox, ++oy);
	}

	cout << (char)192;
	for (int i = 1; i <= width; ++i) {
		cout << (char)196;
	}
	cout << (char)217;
}

void drawRecDouble(int ox, int oy, short width, short height) {
	gotoXY(ox, oy);
	cout << (char)201;					//Top-left corner
	for (int i = 1; i <= width; ++i) {
		cout << (char)205;
	}
	cout << (char)187 << endl;
	gotoXY(ox, ++oy);
	for (int i = 1; i <= height; ++i) {
		cout << (char)186;
		for (int j = 1; j <= width; ++j) {
			cout << " ";
		}
		cout << (char)186 << endl;
		gotoXY(ox, ++oy);
	}

	cout << (char)200;
	for (int i = 1; i <= width; ++i) {
		cout << (char)205;
	}
	cout << (char)188;
}

void gameSound(bool mute)
{
	if (mute)
		PlaySound(NULL, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	else
		PlaySound(TEXT("soundTrack.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

void clickSound(bool mute)
{
	if (mute)
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
	else
	{
		PlaySound(TEXT("click.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

void chooseSound(bool mute)
{
	if (mute)
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
	else
	{
		PlaySound(TEXT("choose.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

void keyboardSound(bool mute)
{
	if (mute)
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
	else
	{
		PlaySound(TEXT("keyboard.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

int main() {
	GAME g;
	resizeConsole(1300, 700);
	Nocursortype();
	g.menu();
}
