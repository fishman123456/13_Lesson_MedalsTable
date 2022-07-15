﻿#include <iostream>
#include <cassert>
class MedalRow
{
	char country[4];
	int medals[3];
public:
	static const int GOLD { 0 };
	static const int SILVER{ 1 };
	static const int BRONZE{ 2 };
	MedalRow(const char* countryP, const int* medalsP)
	{
		strcpy_s(country, 4, countryP ? countryP : "NON");
		for (int i{ 0 }; i < 3; ++i)
		{
			medals[i] = medalsP ? medalsP[i] : 0;
		}
	}
	MedalRow() : MedalRow(nullptr, nullptr) {}
	MedalRow& setCountry(const char* countryP)
	{
		if (countryP)
		{
			strcpy_s(country, 4, countryP);
		}
		return *this;
	}
	const char* getCountry()const { return country; }
	
		int& operator[](int idx)
	{
		assert((idx >= 0 and idx < 3) and "Index out "
			"of range!");
		return medals[idx];
	}
	int operator[](int idx)const
	{
		assert((idx >= 0 and idx < 3) and "Index out "
			"of range!");
		return medals[idx];
	}
	void print()const
	{
		std::cout << '[' << country << "]-( ";
		for (int i{ 0 }; i < 3; ++i)
		{
			std::cout << medals[i];
			if (i < 2) { std::cout << '\t'; }
		}
		std::cout << " )\n";
	}
};
class MedalsTable
{
public:
	 int new maxSize { };
private:
	MedalRow medalRows[MedalsTable::maxSize];
	int size;
	int findCountry(const char* country)const
	{
		for (int i{ 0 }; i < size; i++)
		{
			if (strcmp(medalRows[i].getCountry(), country) == 0)
			{
				return i;
			}
			else return -1;
		}
	}
public:
	MedalsTable() : size{ 0 } {};
		MedalRow& operator[](const char* country)
	{
		int idx{ findCountry(country) };
		if (idx == -1)
		{
			assert(size < MedalsTable::maxSize and
				"Table is FULL!");
			idx = size++;
			medalRows[idx].setCountry(country);
		}
		return medalRows[idx];
	}
	const MedalRow& operator[](const char* country)const
	{
		int idx{ findCountry(country) };
		assert(idx != -1 and "Country not found on const "
			"table");
		return medalRows[idx];
	}
	void print()const
	{
			for (int i{ 0 }; i < size; ++i)
			{
				medalRows[i].print();
			}
	}
};
int main()
{
	MedalsTable mt1;
	std::cout << "Medals table #1:\n";
	mt1["UKR"][MedalRow::GOLD] = 14;
	mt1["UKR"][MedalRow::SILVER] = 5;
	mt1["HUN"][MedalRow::BRONZE] = 9;
	mt1["HUN"][MedalRow::GOLD] = 7;
	mt1["POL"][MedalRow::GOLD] = 4;
	mt1["POL"][MedalRow::SILVER] = 2;
	mt1.print();
	// создаем константную копию таблицы №1
	std::cout << "\nMedals table #2:\n";
	const MedalsTable mt2{ mt1 };
	mt2.print();
	// раскомментировав следующую строку можно протестировать
	// проверку отсутствия страны в константной таблице
	// медалей
	// программа аварийно завершиться, что нормально!
	// mt2["SLO"].print();
	return 0;
}