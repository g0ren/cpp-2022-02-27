#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

/*
 * Задание 1. Есть некоторый текст. Используя стандартные
 строковые функции из библиотеки языка C:
 ■ ■ Найдите и замените вхождение некоторого слова на
 заданное пользователем слово.
 ■ ■ Изменить текст таким образом, чтобы каждое пред-
 ложение начиналось с большой буквы.
 ■ ■ Посчитайте сколько раз каждая буква встречается
 в тексте.
 ■ ■ Посчитайте сколько раз цифры встречаются в тексте.
 */
char* replace(char *line, char *what, char *with, int counter = -1);
bool isLC(char c);
char toUC(char c);
char* capitalize(char *line);
int countChar(char *line, char c);
void countAll(char *line);
int countDigits(char *line);


int main() {
	char *text = new char[1024] { };
	cout << "Enter text:" << endl;
	cin.getline(text, 1024);
	text = replace(text, "txt", "docx", 2);
	cout << text << endl;
	text = capitalize(text);
	cout << text << endl;
	countAll(text);
	cout << countDigits(text);
	return 0;
}

/*
 * Найдите и замените вхождение некоторого слова на
 заданное пользователем слово.

 Поскольку я не понял, надо заменить одно вхождение, или несколько, или все,
 я добавил в функцию параметр counter. Если counter положителен, функция
 заменит ровно counter первых вхождений, если отрицателен — заменит все вхождения,
 которые найдёт, если 0, то ничего не заменит.
 */
char* replace(char *line, char *what, char *with, int counter) {
	if (counter == 0)
		return line;
	char *point = strstr(line, what);
	if (point == nullptr)
		return line;
	char *res = new char[strlen(line) + strlen(with) - strlen(what)] { };
	char *read { line }, *write { res };
	for (; read < point; read++, write++) {
		*write = *read;
	}
	strcat(res, with);
	read += strlen(what);
	write += strlen(with);
	for (; *read != 0; read++, write++) {
		*write = *read;
	}
	delete[] line;
	if (strstr(res, what) == nullptr)
		return res;
	else
		return replace(res, what, with, counter - 1);
}

/*
 * Изменить текст таким образом, чтобы каждое пред-
 ложение начиналось с большой буквы.
 Я исхожу из того, что текст начинается с буквы и что предложения разделяются
 последовательностью символов ". "
 */
bool isLC(char c) {
	return (c >= 'a' && c <= 'z');
}

char toUC(char c) {
	return (isLC(c) ? c - 32 : c);
}

char* capitalize(char *line) {
	char *res = new char[strlen(line)] { };
	strcpy(res, line);
	char *point = res;
	*point = toUC(*point);
	while (1) {
		point = strstr(point, ". ");
		if (!point || !*point)
			break;
		point += 2;
		*point = toUC(*point);
	}
	return res;
}

/*
 * Посчитайте сколько раз каждая буква встречается
 в тексте.
 Опять же, поскольку я не понял, что именно это значит, я сделал функцию,
 которая выводит количество вхождений каждого символа в тексте, если символ
 в тексте есть
 */
int countChar(char *line, char c) {
	int n { };
	for (int i = 0; i < strlen(line); i++)
		if (line[i] == c)
			n++;
	return n;
}

void countAll(char *line) {
	for (int i = 1; i < 256; i++)
		if (countChar(line, i) > 0)
			cout << (char) i << ": " << countChar(line, i) << endl;
}

/*
 * Посчитайте сколько раз цифры встречаются в тексте.
 */
int countDigits(char *line) {
	int n { };
	for (int i = '0'; i <= '9'; i++)
		n += countChar(line, i);
	return n;
}
