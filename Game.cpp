#include "Game.h"

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
    
    while(true) {
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
                    gotoXY(startX, startY);
                    cout << tmp;
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
    }
}

void GAME::menu() {
	const char Title[][82] = { { 32,95,95,95,95,95,32,32,     32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		  32,32,32,32,32,'_',32,	   32,32,32,32,32,  32,32,32,'_','_','_','_',32,	32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,	   32,32,32,32,32,		 32,32,32,	  32,32,32,32,32,32,32,		   },
								 { 32,'_',95,95,95,95,32,32,     32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		  32,32,32,32,32,'_',32,	   32,32,32,32,32,  32,32,32,'_','_','_','_',32,	32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,	   32,32,32,32,32,		 32,32,32,	  32,32,32,32,32,32,32,		   },
								{ '|',32,32,'_','_',32,92,32,	 32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		  32,32,32,32,'|',32,178,	   32,32,32,32,32,  32,32,'/',32,'_','_','_',178,	32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,	   32,32,32,32,32,		 32,32,32,	  32,32,32,32,32,32,32,		   },
								{ '|',32,178,'_','_',')',32,')', 32,32,'_','_','_',32,32,	 32,32,'_','_',32,'_',32,	  32,32,'_','_','|',32,178,	   32,32,32,32,32,  32,'/',32,32,178,32,32,32,		32,'_',32,'_','_',32,	 32,32,'_','_','_',32,32,	 32,'_','_','_',32,    32,'_','_','_',32,	 '(','_',')', 32,'_',32,'_','_',32,32,	  32,32,'_','_',32,'_',32},
								{ '|',32,32,'_',32,32,'/',32,	 32,'/',32,'_',32,'\\',32,	 32,'/',32,'_','\'',32,178,	  32,'/',32,'_',32,32,178,	   32,32,32,32,32,  '|',32,32,32,178,32,32,32,		'|',32,'\'','_','_',178, 32,'/',32,'_',32,'\\',32,	 '/',32,'_','_',178,   '/',32,'_','_',178,   '|',32,178,  '|',32,'\'','_',32,'\\',32, 32,'/',32,'_','\'',32,178},
								{ '|',32,178,32,92,32,92,32,	 '(',32,'(','_',')',32,')',	 '(',32,'(','_',')',32,178,	  '(',32,'(','_',')',32,178,   32,32,32,32,32,  32,'\\',32,32,178,'_','_','_',  '|',32,178,32,32,32,	 '(',32,'(','_',')',32,')',  '\\','_','_',32,'\\', '\\','_','_',32,'\\', '|',32,178,  '|',32,178,32,'|',32,178,	  '(',32,'(','_',')',32,178},
								{ '|','_',178,32,32,92,'_',92,	 32,'\\','_','_','_','/',32, 32,'\\','_','_',',','_',178, 32,'\\','_','_',',','_',178, 32,32,32,32,32,  32,32,'\\','_','_','_','_',178, '|','_',178,32,32,32,	 32,'\\','_','_','_','/',32, 178,'_','_','_','/',  178,'_','_','_','/',  '|','_',178, '|','_',178,32,'|','_',179, 32,'\\','_','_',',',32,178},
								{ 32,32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,32,32,		  32,32,32,32,32,32,32,		   32,32,32,32,32,  32,32,32,32,32,32,32,32,		32,32,32,32,32,32,		 32,32,32,32,32,32,32,		 32,32,32,32,32,	   32,32,32,32,32,		 32,32,32,	  32,32,32,32,32,32,32,		  32,178,'_','_','_','/'} };
	int y = 10, x = 45;
	int i, j;
	for (i = 0; i < 8; ++i) {
		gotoXY(x, y++);
		for (j = 0; j < 82; ++j) {
			cout << Title[i][j];
		}
	}
	x += 28;
	y += 2;
	string prompt[] = { "1. New game", "2. Load game", "3. Settings", "4. Exit" };
	const int length = 4;
	int choice = 0;
	while (true) {
		choice = returnChoice(prompt, length, x, y);
		switch (choice)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			exit(1);
			break;
		}
		}
		break;
	}
}

int GAME::returnChoice(string menu[], const int length, int x, int y) {
	int choice = 0;
	while (true) {
		for (int i = 0; i < length; i++)
		{
			gotoXY(x, y + i);
			cout << "                      ";
		}
		for (int i = 0; i < length; i++)
		{
			if (i == choice)
			{
				TextColor(250);
				gotoXY(x, y + i);
				cout << menu[i];
				TextColor(7);
			}
			else
			{
				gotoXY(x, y + i);
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

bool GAME::printCongrat() {
	int x = 45, y = 10;
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
	x = 70;
	y = 20;
	gotoXY(x, y);
	cout << "Wanna start new game?\n";
	x = 75;
	y = 22;
	string prompt[] = { "1. Yes", "2. No"};
	const int length = 2;
	int choice = 0;
	while (true) {
		choice = returnChoice(prompt, length, x, y);
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

bool GAME::printLose() {
	int x = 65, y = 10;
	const string title[8] = {
	" _____               _     _ _ _ ",
	"/  __ \\             | |   | | | |",
	"| /  \\/_ __ __ _ ___| |__ | | | |",
	"| |   | '__/ _` / __| '_ \\| | | |",
	"| \\__/\\ | | (_| \\__ \\ | | |_|_|_|",
	" \\____/_|  \\__,_|___/_| |_(_|_|_)",
	"                                  ", 
	"                                  "};
	for (int i = 0; i < 8; i++) {
		gotoXY(x, y++);
		cout << title[i] << "\n";
	}
	x += 10;
	y += 2;
	gotoXY(x, y);
	cout << "Wanna replay?\n";
	x += 3;
	y += 2;
	string prompt[] = { "1. Yes", "2. No" };
	const int length = 2;
	int choice = 0;
	while (true) {
		choice = returnChoice(prompt, length, x, y);
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

bool GAME::saveGameMenu() {
	int x = 35, y = 10;
	const string title[8] = {
	"                     _     _                                                          ___  ",
	"                    | |   | |                                                        |__ \\ ",
	"__      ____ _ _ __ | |_  | |_ ___    ___  __ ___   _____    __ _  __ _ _ __ ___   ___  ) |",
	"\\ \\ /\\ / / _` | '_ \\| __| | __/ _ \\  / __|/ _` \\ \\ / / _ \\  / _` |/ _` | '_ ` _ \\ / _ \\/ / ",
	" \\ V  V / (_| | | | | |_  | || (_) | \\__ \\ (_| |\\ V /  __/ | (_| | (_| | | | | | |  __/_|  ",
	"  \\_/\\_/ \\__,_|_| |_|\\__|  \\__\\___/  |___/\\__,_| \\_/ \\___|  \\__, |\\__,_|_| |_| |_|\\___(_)  ",
	"                                                             __/ |                         ",
	"                                                            |___/                          "};
	for (int i = 0; i < 8; i++) {
		gotoXY(x, y++);
		cout << title[i] << "\n";
	}
	x = 75;
	y = 20;
	string prompt[] = { "1. Yes", "2. No" };
	const int length = 2;
	int choice = 0;
	while (true) {
		choice = returnChoice(prompt, length, x, y);
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
}

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

int main() {
	GAME g;
	resizeConsole(1300, 700);
	g.menu();
}
