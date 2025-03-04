#include <string>
#include <iostream>
#include "DecueLib1.hpp"

using namespace std;

bool Palind(string str) {
	Decue<char> dec;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
		{
			dec.push_back(tolower(str[i]));
		}
	}

	while (!dec.is_empty())
	{
		if (dec.front() != dec.back()) {
			return false;
		}

		if (dec.front() == dec.back() && dec.size_() == 1) { 
			return true;
		};

		dec.pop_front();
		dec.pop_back();
	}
	return true;
}

class point {
public:
	int x;
	int y;
};

// z векторное произведение
int Zvector(point A, point B, point C) {
	return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x);
}

//алгоритм Грекхема
void algGragham (point* points, int quantity, Decue<point>& shell) {
	if (quantity < 0) {
		return;
	}


	//стартовые точки(1 действие)
	point start = points[0];
	for (int i = 1; i < quantity; i++) {
		if (points[i].x < start.x || (points[i].x == start.x && points[i].y < start.y)) {
			start = points[i];
		}
	}



	// сортировка точек (2 действие)
	for (int i = 0; i < quantity - 1; i++) {
		for (int j = 0; j < quantity - i - 1; j++) { 
			if (Zvector(start, points[j], points[j + 1]) < 0) {
				point temp = points[j];
				points[j] = points[j + 1];
				points[j + 1] = temp;
			}
		}
	}

	shell.push_back(points[0]);
	shell.push_back(points[1]);

	//3 действие
	for (int i = 2; i < quantity; i++) {
		while (shell.size_() > 1) {
			point second = shell.back(); // вторая вершина дека (последняя добавленная)
			shell.pop_back(); // удаляем временно 2 точку из дека


			// проверка дека на пустоту
			if (shell.is_empty()) {
				shell.push_back(second);
				break;
			}

			point first = shell.back(); // первая точка


			// если проиведение положительное то возвращаем вторую точку, которую удалили в строке 78
			if (Zvector(first, second, points[i]) > 0) {
				shell.push_back(second);
				cout << "Добавляем точку " << i << second.x << second.y;
				break;
			}
		}
		shell.push_back(points[i]); // добавляем очередную точку в оболочку
	}
}




int main() {
	setlocale(LC_ALL, "Rus");
	int choice = 0;
	Decue<char> dec;
	Decue<point> Shell;
	//point points[] = { {0, 0}, {1, 1}, {2, 2}, {2, 0}, {2, 4}, {3, 3}, {0, 3}, {5, 2}, {7, 0}, {5, 3}, {9, 19} };
	//point points[] = { {2, -1}, {-2, 1}, {3, 2}, {-3, -2}, {3, -3} };
	point points[] = { {0, 0}, {2, 1}, {3, 0}, {4, -1}, {4, 2}, {5, 0} };
	int quantity = sizeof(points) / sizeof(points[0]);
	string str_ = "";
	while (choice != 3) {
		cout << "Что хотите выполнить? \n1. Проверка на палиндром \n2. Алгоритм Грэхема\n3. Выход.\n";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Введите слово: ";
			cin >> str_;
			cout << endl;
			if (Palind(str_)) {
				cout << "Это палиндром!" << endl;
			}
			else {
				cout << "Не палиндром!" << endl;
			};
			break;
		case 2:
			algGragham(points, quantity, Shell);
			cout << "Список точек оболочки:\n";
			while (!Shell.is_empty()) {
				point p = Shell.front();
				Shell.pop_front();
				cout << endl << "(" << p.x << ", " << p.y << ")\n";
			}
			cout << endl;
		case 3:
			cout << "Завершение";
			break;
		default:
			cout << "Ошибка ввода";
			break;
		}
	}
}