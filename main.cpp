#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<ctime>

unsigned int difficulty = 0;

// Inefficiency at its finest:
const std::vector<std::vector<std::string>> initialGameBoard =
{ 
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"},
	{"#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#", "#"}
};

std::vector<std::vector<std::string>> mineLocations;
std::vector<std::vector<std::string>> gameState;

void optionSelect(int* variableSelector, std::vector<std::string> options) {
	for (int i = 0; i < options.size(); i++) {
		std::cout << i + 1 << ": " << options[i] << std::endl;
	}
	int temporaryOp = 0;
	std::cin >> temporaryOp;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		temporaryOp = -1;
	}

	*variableSelector = temporaryOp;
}

void endGame(bool win) {
	system("cls");
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			std::cout << " " << gameState[i][j] << " ";
		}
		std::cout << std::endl;
	}
	if (win) {
		std::cout << "Contragulations!" << std::endl;
		std::cout << "You uncovered the entire board without hitting a mine!" << std::endl;
		system("pause");
	}
	else {
		std::cout << "You hit a mine!" << std::endl;
		std::cout << "Game over!" << std::endl;
		system("pause");
	}
	system("cls");
}

bool checkForWin() {
	bool hasWon = true;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (gameState[i][j] == "#" || gameState[i][j] == "F") {
				if (mineLocations[i][j] != "X") {
					hasWon = false;
				}
			}
		}
	}

	return hasWon;
}

void playMain() {
	int selectedRow = 0;
	int selectedColumn = 0;
	
	bool gameOver = false;
	while (!gameOver) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				std::cout << " " << gameState[i][j] << " ";
			}
			std::cout << std::endl;
		}

		std::cout << "Enter the row you want to target: ";
		int op;
		std::cin >> op;
		
		if (std::cin.fail() || op < 1 || op > 20) {
			system("cls");
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Error: Invalid input\n" << std::endl;
		}
		else {
			selectedRow = op;
			std::cout << "\nEnter the column you want to target: ";
			std::cin >> op;
			if (std::cin.fail() || op < 1 || op > 20) {
				system("cls");
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Error: Invalid input\n" << std::endl;
			}
			else {
				selectedColumn = op;
				std::cout << "\nChoose to either dig or flag that space: ";
				std::string action;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::getline(std::cin, action);
				system("cls");

				if (action == "dig" || action == "Dig") {
					if (mineLocations[selectedRow - 1][selectedColumn - 1] == "X") {
						gameState[selectedRow - 1][selectedColumn - 1] = "X";
						gameOver = true;
						endGame(false);
					}
					else {
						unsigned int minesAround = 0;

						// Code to detect mines around this tile.
						// Direct left of tile.
						if (selectedColumn - 2 >= 0) {
							if (mineLocations[selectedRow - 1][selectedColumn - 2] == "X") {
								minesAround++;
							}
						}

						// Direct right of tile.
						if (selectedColumn <= 19) {
							if (mineLocations[selectedRow - 1][selectedColumn] == "X") {
								minesAround++;
							}
						}

						// Directly above.
						if (selectedRow - 2 >= 0) {
							if (mineLocations[selectedRow - 2][selectedColumn - 1] == "X") {
								minesAround++;
							}
						}

						// Directly below.
						if (selectedRow <= 19) {
							if (mineLocations[selectedRow][selectedColumn - 1] == "X") {
								minesAround++;
							}
						}

						// Diagonally up-left.
						if (selectedRow - 2 >= 0 && selectedColumn - 2 >= 0) {
							if (mineLocations[selectedRow - 2][selectedColumn - 2] == "X") {
								minesAround++;
							}
						}

						// Diagonally up-right
						if (selectedRow - 2 >= 0 && selectedColumn <= 19) {
							if (mineLocations[selectedRow - 2][selectedColumn] == "X") {
								minesAround++;
							}
						}

						// Diagonally down-left.
						if (selectedRow <= 19 && selectedColumn - 2 >= 0) {
							if (mineLocations[selectedRow][selectedColumn - 2] == "X") {
								minesAround++;
							}
						}

						// Diagonally down-right
						if (selectedRow <= 19 && selectedColumn <= 19) {
							if (mineLocations[selectedRow][selectedColumn] == "X") {
								minesAround++;
							}
						}

						gameState[selectedRow - 1][selectedColumn - 1] = std::to_string(minesAround);
					}
				}
				else if (action == "flag" || action == "Flag") {
					gameState[selectedRow - 1][selectedColumn - 1] = "F";
				}
				else {
					std::cout << "Error: Invalid input\n" << std::endl;
				}
			}
		}
		if (checkForWin()) {
			gameOver = true;
			endGame(true);
		}
	}
}

void setup() {
	std::cout << "Loading..." << std::endl;
	mineLocations = initialGameBoard;
	gameState = initialGameBoard;

	srand(time(0));

	int numberOfMines = 0;
	switch (difficulty) {
	case 1:
		numberOfMines = 3;
		break;
	case 2:
		numberOfMines = 5;
		break;
	case 3:
		numberOfMines = 10;
		break;
	default:
		numberOfMines = 5;
		break;
	}

	for (int i = 0; i < 20; i++) {
		std::vector<int> tiles = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
		for (int j = 0; j < numberOfMines; j++) {
			int selectedTile = tiles[rand() % tiles.size()];
			tiles.erase(std::find(tiles.begin(), tiles.end(), selectedTile));
			mineLocations[i][selectedTile] = "X";
		}
	}
	system("cls");
	playMain();
}

void difficultySelect() {
	bool hasSelected = false;
	while (!hasSelected) {
		std::cout << "Select your difficulty:" << std::endl;

		int op;
		optionSelect(&op, {"Easy", "Normal", "Hard"});
		system("cls");

		if (op < 1 || op > 3) {
			std::cout << "Error: Invalid input\n" << std::endl;
		}
		else {
			difficulty = op;
			hasSelected = true;
		}
	}
	setup();
}

int main() {
	bool hasSelected = false;
	while (!hasSelected) {
		std::cout << "Minesweeper" << std::endl;
		std::cout << "By Boinga15" << std::endl;

		int op;
		optionSelect(&op, {"Play", "Quit"});
		system("cls");

		switch (op) {
		case 1:
			difficultySelect();
			break;
		case 2:
			hasSelected = true;
			break;
		default:
			std::cout << "Error: Invalid input\n" << std::endl;
			break;
		}
	}
}