#include "pch.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#define TEST
int main() {
	string sample; // шаблон
	string text; // исходный текст
	cin >> text;
	cin >> sample;
	// сравниваем длину текста и длину шаблона
	// если они не равны, то выводим -1
	if (text.length() != sample.length()) {
		cout << -1;
		return 0;
	}
	text += text;
		vector<size_t> prefix(sample.length()); // массив который хранит префиксы для шаблона
	// часть отвечающую за префикс функцию
	size_t last_prefix = prefix[0] = 0;
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
		while (last_prefix > 0 && sample[last_prefix] != text[i])// пока значение префикс функции >0 и символ шаблона = символу текста
			last_prefix = prefix[last_prefix - 1];
		if (sample[last_prefix] == text[i]) // если символ шаблона от значения префикс-функции равно тексту
		{
#ifdef TEST
			for (size_t j = 0; j < last_prefix; j++) {
				cout << " ";
			}
			cout << "coincidence " << i << " liter " << text[i] << " [" << last_prefix << "]";
			if (i && !last_prefix&&was_founded)
			cout << endl;
			was_founded = false;
#endif
			last_prefix++;
		}
		if (last_prefix == sample.length()) { // если значение префикс-функции равно длине шаблона
#ifdef TEST
			cout << "\nthe entry found in ";
			was_first = false;
			was_founded = true;
#endif
				was_first = true; // вхождение найдено
				cout << i + 1 - sample.length() << " liter"; // выводим символ, с которого начинается циклическое вхождение
				i = text.length();
		}
	}
	if (!was_first)
		cout << -1 << "entry not found";
}