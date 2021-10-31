#include <iostream>
#include <windows.h>
#include <myheader.h>
using namespace std;
const int sudoku_size = 9, sudoku_size_1D = sudoku_size * sudoku_size, fill_sudoku_size = 80;
int sudoku_2D[sudoku_size][sudoku_size], sudoku_1D[sudoku_size_1D], row, column, i, j, put_num, try_num;
void GotoXY(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorCoord;
	cursorCoord.X = x;
	cursorCoord.Y = y;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}
int build_num() {
	static int num = 0;
	if (num == sudoku_size)num = 0;
	return ++num;
}
int circle(int& num) {
	if (num == sudoku_size)num = 0;
	return ++num;
}
void set_zero() {
	for (i = 0; i < 9; i++)
		if (build_num() == 9)break;
}
void clear_2D() {
	int i, j;
	for (i = 0; i < sudoku_size; i++)
		for (j = 0; j < sudoku_size; j++)
		{
			sudoku_2D[i][j] = 63;
		}
}
bool check_for_clean(int valu, int row, int column) {
	int i;
	for (i = 0; i < sudoku_size; i++) {
		if (i == column)continue;
		if (valu == sudoku_2D[row][i])return false;
	}
	for (i = 0; i < sudoku_size; i++) {
		if (i == row)continue;
		if (valu == sudoku_2D[i][column])return false;
	}
	return true;
}
void clean_2D() {
	for (i = 0; i < sudoku_size; i++)
		for (j = 0; j < sudoku_size; j++) {
			if (!check_for_clean(sudoku_2D[i][j], i, j))
				sudoku_2D[i][j] = 63;
		}
}
void print_in_middle_sudoku_2D() {
	int i, j = 0, k = 0;
	static int c = 2;
	for (i = 0; i < 9; i++) {
		GotoXY(70, c);
		for (j = 0; j < 9; j++) {
			if (sudoku_2D[i][j] == 63)cout << " " << " " << "|";
			else cout << " " << sudoku_2D[i][j] << "|";
		}
		c++;
	}
	c++;
	cout << "\n";
}
void random_choise() {
	int x, p_i, p_j;
	clear_2D();
	for (i = 0; i < fill_sudoku_size; i++) {
		x = rnd() % 9 + 1;
		p_i = rnd() % 9;
		p_j = rnd() % 9;
		sudoku_2D[p_i][p_j] = x;
	}
	clean_2D();
}

bool check_non_rec(int valu, int row, int column) {
	return 0;
}
bool check_row_rec(int valu, int row, int column) {
	if (column == sudoku_size)return true;
	if (sudoku_2D[row][column] != valu && column < sudoku_size) {
		if (check_row_rec(valu, row, column + 1))
			return true;
	}
	return false;
}
bool check_column_rec(int valu, int column, int row) {
	if (row == sudoku_size)return true;
	if (sudoku_2D[row][column] != valu && row < sudoku_size) {
		if (check_column_rec(valu, column, row + 1))
			return true;
	}
	return false;
}

int solution_rec(int row, int column) {
	if (row == sudoku_size && column == sudoku_size) {
		cout << "found";
		return 1;
	}
	if (sudoku_2D[row][column] != 63) {
		if (column == 9) {
			column = 0;
			row++;
		}
		solution_rec(row, column + 1);
	}
	if (sudoku_2D[row][column] == 63) {
		for (try_num = 1; try_num <= sudoku_size; try_num++) {
			if (check_row_rec(try_num, row, 0) && check_column_rec(try_num, column, 0)) {
				sudoku_2D[row][column] = try_num;
				if (solution_rec(row, column + 1))return 1;
			}
		}
	}
	return 1;
}
void solution_non_rec() {
	for (int i = 0; i < sudoku_size_1D; i++) {
		sudoku_1D[i] = i % sudoku_size;
	}
}



int main()
{
	random_choise();
	print_in_middle_sudoku_2D();
	solution_rec(0, 0);
	print_in_middle_sudoku_2D();


	return 0;
}