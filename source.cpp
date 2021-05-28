#include <iostream> 
#include <cmath>
#include <iomanip>
#include <string>
#include <algorithm>
#include <stdlib.h>
// Colors
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
// Example cout << RED << "hello world" << RESET << endl;
// Note: If you don't use RESET the color will remain changed until the next time you use a color code.
// Note : If It DoesNot Work Just Use "#include <stdlib.h>" library And Put "system("CLS");" In The Main

// Vaiables
const int Grid_Row_Size = 6; //Minimum --> 4 , Normal Game --> 6
const int Grid_Col_Size = 7; //Minimum --> 4 , Normal Game --> 7
const int Symboles_Size = 5; //Minimum --> 2 , Normal Game --> 5
char Grid[Grid_Row_Size][Grid_Col_Size] = { };
int Pos_X[Grid_Col_Size] = { };
bool Pos_X_Bool = 0; // To Check If All Columns Has Reached It's Maximum Value
bool Symboles_Bool = 0; // To Check If User's Symbol Input is In The Symboles list
//Initializing Colored Positions --> -1 To Prevent Coloring Cell (0,0)
int Colored_Winner_Pos_Horizontal[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };
int Colored_Winner_Pos_Vertical[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };
int Colored_Winner_Pos_Diagonal_1[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };
int Colored_Winner_Pos_Diagonal_2[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };
int Winner = 0, Input;
std::string Player_1, Player_2;
//char Symboles[Symboles_Size] = { '@' , '#' , '$' , '%' , '&' }; Standard List , Standard Size  --> Symboles_Size = 5
char Symboles[Symboles_Size] = { '@' , '#' , '$' , '%' , '&' };
char Player_1_Symbol, Player_2_Symbol;
int Counter = 1;

// A Function To Welcome The Players And Reads Inputs
void Welcome() {
	// Clears The Screen
	system("CLS");
	// Welcome message & Reads Players Names
	std::cout << "Hello, Please Enter Your Names : \n"
		<< "Note : Player 1 Always plays First :)\n"
		<< "Player 1's Name : ";
	getline(std::cin, Player_1);
	while (Player_1.size() > 11) {
		std::cout << "Player 1's Name (Shoud Be Less Than 11 characters) : ";
		getline(std::cin, Player_1);
	}
	std::cout << "Player 2's Name : ";
	getline(std::cin, Player_2);
	while (Player_2.size() > 11) {
		std::cout << "Player 2's Name (Shoud Be Less Than 11 characters) : ";
		getline(std::cin, Player_2);
	}
	std::cout << "Welcome " << BOLDRED << Player_1 << RESET << " And " << BOLDBLUE << Player_2 << RESET << " !\n";
	// Choosing Symbols
	std::cout << BOLDRED << Player_1 << RESET << " ,Please Choose A Symbol From {";
	for (int i = 0; i < Symboles_Size; i++) {
		if (Symboles[i] != 'X') {
			std::cout << "'" << Symboles[i] << "'";
			if (Counter <= Symboles_Size - 1)
				std::cout << " , ";
			Counter++;
		}
		if (i == Symboles_Size - 1)
			std::cout << "} : ";
	}
	while (true) {
		Counter = 1;
		std::cin >> Player_1_Symbol;
		Symboles_Bool = 0;
		for (int i = 0; i < Symboles_Size ; i++) {
			if (Symboles[i] == Player_1_Symbol && Symboles[i] != 'X') {
				Symboles_Bool = 1;
				break;
			}
			else {
				Symboles_Bool = 0;
			}
		}
		if (Symboles_Bool) {
			for (int i = 0; i < Symboles_Size; i++) {
				if (Symboles[i] == Player_1_Symbol) {
					Symboles[i] = 'X';
					break;
				}
			}
			break;
		}
		else {
			std::cout << BOLDRED << Player_1 << RESET << " ,Please Choose A Valid Symbol From {";
			for (int i = 0; i < Symboles_Size; i++) {
				if (Symboles[i] != 'X') {
					std::cout << "'" << Symboles[i] << "'";
					if (Counter <= Symboles_Size - 1)
						std::cout << " , ";
					Counter++;
				}
				if (i == Symboles_Size - 1)
					std::cout << "} : ";
			}
			// clears the error flags
			std::cin.clear();
			// this line discards all the input waiting in the stream
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	std::cout << BOLDBLUE << Player_2 << RESET << " ,Please Choose A Symbol From {";
	for (int i = 0; i < Symboles_Size; i++) {
		if (Symboles[i] != 'X') {
			std::cout << "'" << Symboles[i] << "'";
			if (Counter <= Symboles_Size - 2)
				std::cout << " , ";
			Counter++;
		}
		if (i == Symboles_Size - 1)
			std::cout << "} : ";
	}
	while (true) {
		Counter = 1;
		std::cin >> Player_2_Symbol;
		if (Player_2_Symbol == Player_1_Symbol) {
			std::cout << BOLDBLUE << Player_2 << RESET << " ,Donot Choose " << BOLDRED << Player_1 << RESET << "'s Symbol : '" << Player_1_Symbol << "'\n";
			std::cout << BOLDBLUE << Player_2 << RESET << " ,Please Choose A Symbol From {";
			for (int i = 0; i < Symboles_Size; i++) {
				if (Symboles[i] != 'X') {
					std::cout << "'" << Symboles[i] << "'";
					if (Counter <= Symboles_Size - 2)
						std::cout << " , ";
					Counter++;
				}
				if (i == Symboles_Size - 1)
					std::cout << "} : ";
			}
			continue;
		}
		Symboles_Bool = 0;
		for (int i = 0; i < Symboles_Size; i++) {
			if (Symboles[i] == Player_2_Symbol && Symboles[i] != 'X') {
				Symboles_Bool = 1;
				break;
			}
			else {
				Symboles_Bool = 0;
			}
		}
		if (Symboles_Bool) {
			for (int i = 0; i < Symboles_Size; i++) {
				if (Symboles[i] == Player_2_Symbol) {
					Symboles[i] = 'X';
					break;
				}
			}
			break;
		}
		else {
			std::cout << BOLDBLUE << Player_2 << RESET << " ,Please Choose A Valid Symbol From {";
			// clears the error flags
			std::cin.clear();
			// this line discards all the input waiting in the stream
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			for (int i = 0; i < Symboles_Size; i++) {
				if (Symboles[i] != 'X') {
					std::cout << "'" << Symboles[i] << "'";
					if (Counter <= Symboles_Size - 2)
						std::cout << " , ";
					Counter++;
				}
				if (i == Symboles_Size - 1)
					std::cout << "} : ";
			}
		}
	}
}
// A Function To Draw The Grid
void Draw() {
	std::cout << BOLDBLUE
		<< "================================================================================\n"
		<< "||  ██████╗ ██████╗ ███╗   ██╗███╗   ██╗███████╗ ██████╗████████╗    ██╗  ██╗ ||\n"
		<< "|| ██╔════╝██╔═══██╗████╗  ██║████╗  ██║██╔════╝██╔════╝╚══██╔══╝    ██║  ██║ ||\n"
		<< "|| ██║     ██║   ██║██╔██╗ ██║██╔██╗ ██║█████╗  ██║        ██║       ███████║ ||\n"
		<< "|| ██║     ██║   ██║██║╚██╗██║██║╚██╗██║██╔══╝  ██║        ██║       ╚════██║ ||\n"
		<< "|| ╚██████╗╚██████╔╝██║ ╚████║██║ ╚████║███████╗╚██████╗   ██║            ██║ ||\n"
		<< "||  ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝ ╚═════╝   ╚═╝            ╚═╝ ||\n"
		<< "||" << BOLDRED << "                                                       ╔╦╗┬ ┬┬─┐ ┬┌┬┐┌─┐┌┐┌ " << BOLDBLUE << "||\n"
		<< "||" << BOLDRED << "                                                 BY :   ║ │ │├┬┘ ││││├─┤│││ " << BOLDBLUE << "||\n"
		<< "||" << BOLDRED << "                                                        ╩ └─┘┴└─└┘┴ ┴┴ ┴┘└┘ " << BOLDBLUE << "||\n"
		<< "================================================================================\n"
		<< RESET << "\n";
	for (int i = 0; i < Grid_Col_Size; i++) {
		std::cout << "==   ==";
		if (i < Grid_Col_Size - 1)
			std::cout << "  ";
		else if (i == Grid_Col_Size - 1)
			std::cout << "\n";
	}
	for (int i = Grid_Row_Size - 1; i >= 0; i--) {
		for (int j = 0; j < Grid_Col_Size; j++) {
			std::cout << "|| ";
			if (Winner == 1 || Winner == 2) {
				// Horizontal Check
				if (((i == Colored_Winner_Pos_Horizontal[0] && j == Colored_Winner_Pos_Horizontal[1]) ||
					(i == Colored_Winner_Pos_Horizontal[2] && j == Colored_Winner_Pos_Horizontal[3]) ||
					(i == Colored_Winner_Pos_Horizontal[4] && j == Colored_Winner_Pos_Horizontal[5]) ||
					(i == Colored_Winner_Pos_Horizontal[6] && j == Colored_Winner_Pos_Horizontal[7])) ||
					// Vertical Check
					((i == Colored_Winner_Pos_Vertical[0] && j == Colored_Winner_Pos_Vertical[1]) ||
					(i == Colored_Winner_Pos_Vertical[2] && j == Colored_Winner_Pos_Vertical[3]) ||
					(i == Colored_Winner_Pos_Vertical[4] && j == Colored_Winner_Pos_Vertical[5]) ||
					(i == Colored_Winner_Pos_Vertical[6] && j == Colored_Winner_Pos_Vertical[7])) ||
					// Diagonal Check 1
					((i == Colored_Winner_Pos_Diagonal_1[0] && j == Colored_Winner_Pos_Diagonal_1[1]) ||
					(i == Colored_Winner_Pos_Diagonal_1[2] && j == Colored_Winner_Pos_Diagonal_1[3]) ||
					(i == Colored_Winner_Pos_Diagonal_1[4] && j == Colored_Winner_Pos_Diagonal_1[5]) ||
					(i == Colored_Winner_Pos_Diagonal_1[6] && j == Colored_Winner_Pos_Diagonal_1[7])) ||
					// Diagonal Check 2
					((i == Colored_Winner_Pos_Diagonal_2[0] && j == Colored_Winner_Pos_Diagonal_2[1]) ||
					(i == Colored_Winner_Pos_Diagonal_2[2] && j == Colored_Winner_Pos_Diagonal_2[3]) ||
					(i == Colored_Winner_Pos_Diagonal_2[4] && j == Colored_Winner_Pos_Diagonal_2[5]) ||
					(i == Colored_Winner_Pos_Diagonal_2[6] && j == Colored_Winner_Pos_Diagonal_2[7]))) {
					std::cout << BOLDGREEN << Grid[i][j] << RESET;
				}
				else {
					if (Grid[i][j] == Player_1_Symbol)
						std::cout << BOLDRED << Grid[i][j] << RESET;
					else if (Grid[i][j] == Player_2_Symbol)
						std::cout << BOLDBLUE << Grid[i][j] << RESET;
					else
						std::cout << Grid[i][j];
				}
			}
			else {
				if (Grid[i][j] == Player_1_Symbol)
					std::cout << BOLDRED << Grid[i][j] << RESET;
				else if (Grid[i][j] == Player_2_Symbol)
					std::cout << BOLDBLUE << Grid[i][j] << RESET;
				else
					std::cout << Grid[i][j];
			}
			std::cout << " ||";
			if (j < Grid_Col_Size - 1)
				std::cout << "  ";
		}
		std::cout << "\n";
	}
	for (int i = 0; i < Grid_Col_Size; i++) {
		std::cout << "=======";
		if (i < Grid_Col_Size - 1)
			std::cout << "==";
		else if (i == Grid_Col_Size - 1)
			std::cout << "\n";
	}
	for (int i = 1; i <= Grid_Col_Size; i++) {
		std::cout << "|| " << i << " ||";
		if (i < Grid_Col_Size)
			std::cout << "  ";
		else if (i == Grid_Col_Size)
			std::cout << "\n";
	}
	for (int i = 0; i < Grid_Col_Size; i++) {
		std::cout << "=======";
		if (i < Grid_Col_Size - 1)
			std::cout << "==";
		else if (i == Grid_Col_Size - 1)
			std::cout << "\n";
	}
}
// A Function To Check if One Of The Players Is A Winner !
void Win() {
	for (int i = 0; i < Grid_Col_Size; i++) {
		if (Pos_X[i] == Grid_Row_Size) {
			Pos_X_Bool = 1;
		}	
		else {
			Pos_X_Bool = 0;
			break;
		}
	}
	if (Pos_X_Bool) {
		// Draw Check
		Winner = -1;
	}
	else {
		// Horizontal Check
		for (int i = 0; i < Grid_Row_Size; i++) {
			for (int j = 0; j < Grid_Col_Size - 3; j++) {
				if (Grid[i][j] == Player_1_Symbol && Grid[i][j + 1] == Player_1_Symbol && Grid[i][j + 2] == Player_1_Symbol && Grid[i][j + 3] == Player_1_Symbol) {
					Winner = 1;
					Colored_Winner_Pos_Horizontal[0] = Colored_Winner_Pos_Horizontal[2] = Colored_Winner_Pos_Horizontal[4] = Colored_Winner_Pos_Horizontal[6] = i;
					Colored_Winner_Pos_Horizontal[1] = j;
					Colored_Winner_Pos_Horizontal[3] = j + 1;
					Colored_Winner_Pos_Horizontal[5] = j + 2;
					Colored_Winner_Pos_Horizontal[7] = j + 3;
					break;
				}
				else if (Grid[i][j] == Player_2_Symbol && Grid[i][j + 1] == Player_2_Symbol && Grid[i][j + 2] == Player_2_Symbol && Grid[i][j + 3] == Player_2_Symbol) {
					Winner = 2;
					Colored_Winner_Pos_Horizontal[0] = Colored_Winner_Pos_Horizontal[2] = Colored_Winner_Pos_Horizontal[4] = Colored_Winner_Pos_Horizontal[6] = i;
					Colored_Winner_Pos_Horizontal[1] = j;
					Colored_Winner_Pos_Horizontal[3] = j + 1;
					Colored_Winner_Pos_Horizontal[5] = j + 2;
					Colored_Winner_Pos_Horizontal[7] = j + 3;
					break;
				}
			}
			if (Winner != 0)
				break;
		}

		// Vertical Check
		for (int j = 0; j < Grid_Col_Size; j++) {
			for (int i = 0; i < Grid_Row_Size - 3; i++) {
				if (Grid[i][j] == Player_1_Symbol && Grid[i + 1][j] == Player_1_Symbol && Grid[i + 2][j] == Player_1_Symbol && Grid[i + 3][j] == Player_1_Symbol) {
					Winner = 1;
					Colored_Winner_Pos_Vertical[0] = i;
					Colored_Winner_Pos_Vertical[2] = i + 1;
					Colored_Winner_Pos_Vertical[4] = i + 2;
					Colored_Winner_Pos_Vertical[6] = i + 3;
					Colored_Winner_Pos_Vertical[1] = Colored_Winner_Pos_Vertical[3] = Colored_Winner_Pos_Vertical[5] = Colored_Winner_Pos_Vertical[7] = j;
					break;
				}
				else if (Grid[i][j] == Player_2_Symbol && Grid[i + 1][j] == Player_2_Symbol && Grid[i + 2][j] == Player_2_Symbol && Grid[i + 3][j] == Player_2_Symbol) {
					Winner = 2;
					Colored_Winner_Pos_Vertical[0] = i;
					Colored_Winner_Pos_Vertical[2] = i + 1;
					Colored_Winner_Pos_Vertical[4] = i + 2;
					Colored_Winner_Pos_Vertical[6] = i + 3;
					Colored_Winner_Pos_Vertical[1] = Colored_Winner_Pos_Vertical[3] = Colored_Winner_Pos_Vertical[5] = Colored_Winner_Pos_Vertical[7] = j;
					break;
				}
			}
			if (Winner != 0)
				break;
		}

		// Diagonal Check 1
		for (int i = 0; i < Grid_Row_Size - 3; i++) {
			for (int j = 3; j < Grid_Col_Size; j++) {
				if (Grid[i][j] == Player_1_Symbol && Grid[i + 1][j - 1] == Player_1_Symbol && Grid[i + 2][j - 2] == Player_1_Symbol && Grid[i + 3][j - 3] == Player_1_Symbol) {
					Winner = 1;
					Colored_Winner_Pos_Diagonal_1[0] = i;
					Colored_Winner_Pos_Diagonal_1[1] = j;
					Colored_Winner_Pos_Diagonal_1[2] = i + 1;
					Colored_Winner_Pos_Diagonal_1[3] = j - 1;
					Colored_Winner_Pos_Diagonal_1[4] = i + 2;
					Colored_Winner_Pos_Diagonal_1[5] = j - 2;
					Colored_Winner_Pos_Diagonal_1[6] = i + 3;
					Colored_Winner_Pos_Diagonal_1[7] = j - 3;
					break;
				}
				else if (Grid[i][j] == Player_2_Symbol && Grid[i + 1][j - 1] == Player_2_Symbol && Grid[i + 2][j - 2] == Player_2_Symbol && Grid[i + 3][j - 3] == Player_2_Symbol) {
					Winner = 2;
					Colored_Winner_Pos_Diagonal_1[0] = i;
					Colored_Winner_Pos_Diagonal_1[1] = j;
					Colored_Winner_Pos_Diagonal_1[2] = i + 1;
					Colored_Winner_Pos_Diagonal_1[3] = j - 1;
					Colored_Winner_Pos_Diagonal_1[4] = i + 2;
					Colored_Winner_Pos_Diagonal_1[5] = j - 2;
					Colored_Winner_Pos_Diagonal_1[6] = i + 3;
					Colored_Winner_Pos_Diagonal_1[7] = j - 3;
					break;
				}
			}
			if (Winner != 0)
				break;
		}
		// Diagonal Check 2
		for (int i = 0; i < Grid_Row_Size - 3; i++) {
			for (int j = Grid_Col_Size - 4; j >= 0; j--) {
				if (Grid[i][j] == Player_1_Symbol && Grid[i + 1][j + 1] == Player_1_Symbol && Grid[i + 2][j + 2] == Player_1_Symbol && Grid[i + 3][j + 3] == Player_1_Symbol) {
					Winner = 1;
					Colored_Winner_Pos_Diagonal_2[0] = i;
					Colored_Winner_Pos_Diagonal_2[1] = j;
					Colored_Winner_Pos_Diagonal_2[2] = i + 1;
					Colored_Winner_Pos_Diagonal_2[3] = j + 1;
					Colored_Winner_Pos_Diagonal_2[4] = i + 2;
					Colored_Winner_Pos_Diagonal_2[5] = j + 2;
					Colored_Winner_Pos_Diagonal_2[6] = i + 3;
					Colored_Winner_Pos_Diagonal_2[7] = j + 3;
					break;
				}
				else if (Grid[i][j] == Player_2_Symbol && Grid[i + 1][j + 1] == Player_2_Symbol && Grid[i + 2][j + 2] == Player_2_Symbol && Grid[i + 3][j + 3] == Player_2_Symbol) {
					Winner = 2;
					Colored_Winner_Pos_Diagonal_2[0] = i;
					Colored_Winner_Pos_Diagonal_2[1] = j;
					Colored_Winner_Pos_Diagonal_2[2] = i + 1;
					Colored_Winner_Pos_Diagonal_2[3] = j + 1;
					Colored_Winner_Pos_Diagonal_2[4] = i + 2;
					Colored_Winner_Pos_Diagonal_2[5] = j + 2;
					Colored_Winner_Pos_Diagonal_2[6] = i + 3;
					Colored_Winner_Pos_Diagonal_2[7] = j + 3;
					break;
				}
			}
			if (Winner != 0)
				break;
		}
	}
}
// A Function To Start Playing And Filling The Grid
void Play() {
	while (Winner == 0) {
		std::cout << std::flush;
		system("CLS");
		Draw();
		std::cout << BOLDRED << Player_1 << RESET << " ,It's Your Turn ;)\n"
			<< "Please Enter The Place From 1 --> " << Grid_Col_Size << " : ";
		// clears the error flags
		std::cin.clear();
		// this line discards all the input waiting in the stream
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> Input;
		if (Input >= 1 && Input <= Grid_Col_Size && Pos_X[Input - 1] <= Grid_Row_Size - 1) {
			Grid[Pos_X[Input - 1]][Input - 1] = Player_1_Symbol;
			Pos_X[Input - 1]++;
		}
		else {
			while (!(Input >= 1 && Input <= Grid_Col_Size && Pos_X[Input - 1] <= Grid_Row_Size - 1)) {
				std::cout << "Please Enter A Valid Number From 1 -->  " << Grid_Col_Size << " : ";
				// clears the error flags
				std::cin.clear();
				// this line discards all the input waiting in the stream
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> Input;
				if (Input >= 1 && Input <= Grid_Col_Size && Pos_X[Input - 1] <= Grid_Row_Size - 1) {
					Grid[Pos_X[Input - 1]][Input - 1] = Player_1_Symbol;
					Pos_X[Input - 1]++;
					break;
				}
			}
		}
		std::cout << std::flush;
		system("CLS");
		Draw();
		Win();
		if (Winner != 0)
			break;
		std::cout << BOLDBLUE << Player_2 << RESET << " ,It's Your Turn ;)\n"
			<< "Please Enter The Place From 1 --> " << Grid_Col_Size << " : ";
		// clears the error flags
		std::cin.clear();
		// this line discards all the input waiting in the stream
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> Input;
		if (Input >= 1 && Input <= Grid_Col_Size && Pos_X[Input - 1] <= Grid_Row_Size - 1) {
			Grid[Pos_X[Input - 1]][Input - 1] = Player_2_Symbol;
			Pos_X[Input - 1]++;
		}
		else {
			while (!(Input >= 1 && Input <= Grid_Col_Size && Pos_X[Input - 1] <= Grid_Row_Size - 1)) {
				std::cout << "Please Enter A Valid Number From 1 --> " << Grid_Col_Size << " : ";
				// clears the error flags
				std::cin.clear();
				// this line discards all the input waiting in the stream
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> Input;
				if (Input >= 1 && Input <= Grid_Col_Size && Pos_X[Input - 1] <= Grid_Row_Size - 1) {
					Grid[Pos_X[Input - 1]][Input - 1] = Player_2_Symbol;
					Pos_X[Input - 1]++;
					break;
				}
			}
		}
		std::cout << std::flush;
		system("CLS");
		Draw();
		Win();
	}
}
// A Function To Decide Who Is The Winner
void IsWinner() {
	if (Winner == 1) {
		std::cout << std::flush;
		system("CLS");
		Draw();
		std::cout << "\n";
		std::cout << "================================================================================\n"
			<< "||" << BOLDGREEN << "        The Winner Is : " << BOLDRED << Player_1 << BOLDGREEN << " And It's Great Symbol Is : " << "'" << Player_1_Symbol << "'.";
		for (int i = 0; i < (19 - Player_1.size()); i++) {
			std::cout << ' ';
		}
		std::cout << RESET << " ||\n";
		std::cout << "================================================================================\n";

	}
	else if (Winner == 2) {
		std::cout << std::flush;
		system("CLS");
		Draw();
		std::cout << "\n";
		std::cout << "================================================================================\n"
			<< "||" << BOLDGREEN << "        The Winner Is : " << BOLDBLUE << Player_2 << BOLDGREEN << " And It's Great Symbol Is : " << "'" << Player_2_Symbol << "'.";
		for (int i = 0; i < (19 - Player_2.size()); i++) {
			std::cout << ' ';
		}
		std::cout << RESET << " ||\n";
		std::cout << "================================================================================\n";

	}
	else if (Winner == -1) {
		std::cout << std::flush;
		system("CLS");
		Draw();
		std::cout << "\n";
		std::cout << "================================================================================\n"
			<< "||      " << BOLDMAGENTA
			<< "                       The Game Is DRAW !                       "
			<< RESET << "      ||\n"
			<< "================================================================================\n";

	}
}
// The Programme Starts From Here Of Course -__-
int main() {
	Welcome();
	for(int i = 0; i < 6; i++)
		for(int j = 0; j < 7; j++)
			Grid[i][j] = ' ';
	Play();
	IsWinner();
	return 0;
}

