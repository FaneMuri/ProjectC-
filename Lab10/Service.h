#pragma once
#include <string>
#include "Carte.h"
#include "CarteRepo.h"
#include "Undo.h"

#include <map>
using std::string;
//using std::function;
using std::unique_ptr;
using std::make_unique;
class Service
{
private:
	CarteRepo& rep;
	vector<unique_ptr<UndoAction>> undoActions;
public:
	Service(CarteRepo& rep) : rep{ rep }
	{

	}
	void add(string titlu, string autor, string gen, int an) {
		Carte c{ titlu,autor,gen,an };
		rep.store(c);
		undoActions.push_back(make_unique<UndoAdauga>(rep, c));
	}

	vector<Carte>& getAll()
	{
		return rep.getAll();
	}

	Carte modify(string titlu, string autor, string gen, int an)
	{
		Carte c{ titlu,autor,gen,an };
		Carte p = rep.modify(c);
		undoActions.push_back(make_unique<UndoModifica>(rep, p, c));
		return p;
	}

	void remove(string titlu)
	{
		auto p = rep.remove(titlu);
		undoActions.push_back(make_unique<UndoSterge>(rep, p));
	}

	Carte search(string titlu);

	vector <Carte> sortByConditie(int cond);

	int  undo();

	std::map <string, int > raport(std::map<string, int>  dict);
	friend UndoAdauga;
};

void testService();
