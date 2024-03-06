#pragma once
#include <vector>
#include "Carte.h"

using std::vector;

class CarteRepo
{
private:
	vector <Carte> carti;
public:



	void store(const Carte& c)
	{
		carti.push_back(c);
	}

	vector<Carte>& getAll()
	{
		return carti;
	}

	Carte modify(Carte& c);

	Carte remove(string titlu);
};


