#pragma once
#include <vector>
#include <string.h>
#include <random>
#include "Carte.h"
#include "CarteRepo.h"
#include "Service.h"

using std::vector;
using std::string;

class Cos
{
private:
	Service& service;
	vector <Carte> cos;
public:

	Cos(Service& rep) : service{ rep }
	{

	}

	void addCos(string titlu);

	vector<Carte> allCos()
	{
		return cos;
	}

	vector <Carte> deleteAll()
	{
		cos.clear();
		return cos;
	}

	vector <Carte > generate(int nr);

	void exp(string nume);
};

void testCos();