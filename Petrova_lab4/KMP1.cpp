#include "pch.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#define TEST
int main() {
	string sample; // шаблон
	string text; // исходный текст
	cin >> sample;
	cin >> text;
	vector<size_t> prefix(sample.length()); // массив который хранит префиксы для шаблона
	// часть отвечающую за префикс функцию
	size_t last_prefix = prefix[0] = 0;
	// поиск префикс-функции для шаблона
	for (size_t i = 1; i < sample.length(); i++) {
		while (last_prefix > 0 && sample[last_prefix] != sample[i])
			last_prefix = prefix[last_prefix - 1];
		if (sample[last_prefix] == sample[i])
			last_prefix++;
		prefix[i] = last_prefix;
	}
#ifdef TEST
	cout << "the result of the prefix function:\n";
	for (size_t i = 0; i < prefix.size(); i++) {
		cout << sample[i] << " ";
	}
	cout << endl;
	for (size_t i = 0; i < prefix.size(); i++) {
		cout << prefix[i] << " ";
	}
	cout << endl;
#endif
	// прогон строки и сравнение с префикс-функцией
	last_prefix = 0;
	bool was_founded = false;
	bool was_first = false;
	for (size_t i = 0; i < text.length(); i++) {
		while (last_prefix > 0 && sample[last_prefix] != text[i]) // пока значение префикс функции >0 и символ шаблона = символу текста
			last_prefix = prefix[last_prefix - 1];
		if (sample[last_prefix] == text[i]) // если символ шаблона от значения префикс-функции равно тексту
		{
#ifdef TEST
			for (size_t j = 0; j < last_prefix; j++) {
				cout << " ";
			}
			cout << "coincidence " << i << " liter " << text[i] << " [" << last_prefix << "]";
			if (i && !last_prefix&&was_founded)
				cout << " end line found";
			cout << endl;
			was_founded = false;
#endif
			last_prefix++;
		}
		if (last_prefix == sample.length()) { // если значение префикс-функции равно длине шаблона
#ifdef TEST
			cout << "\nlength coincided with the length of the template\n";
			was_first = false;
			was_founded = true;
#endif
			if (was_first)
				cout << ",";
			was_first = true; // вхождение найдено, 
#ifndef TEST
			cout << i + 1 - sample.length(); // выводим символ начала вхождения
#endif
		}
	}
	if (!was_first)
		cout << -1;
}