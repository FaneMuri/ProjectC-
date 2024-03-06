#include "Service.h"
#include <assert.h>
#include <vector>
#include <map>
using std::map;
using std::pair;

int  conditieTitlu(Carte a, Carte b)
{
	if (a.getTitlu().compare(b.getTitlu()) <= 0)
		return 1;

	return 0;
}

int conditieAutor(Carte a, Carte b)
{
	if (a.getAutor().compare(b.getAutor()) <= 0)
		return 1;

	return 0;
}

int conditieAnGen(Carte a, Carte b)
{
	if (a.getAn() <= b.getAn())
		if (a.getGen().compare(b.getGen()) <= 0)
			return 1;
	return 0;
}


int conditie(Carte a, Carte b, int cond)
{
	if (cond == 1)
		return conditieTitlu(a, b);
	else if (cond == 2)
		return conditieAutor(a, b);
	else
		return conditieAnGen(a, b);
}

vector <Carte> Service::sortByConditie(int cond)
{
	auto carti = getAll();

	for (int i = 0; i < carti.size() - 1; i++)
	{
		for (int j = i + 1; j < carti.size(); j++)
		{
			if (conditie(carti[i], carti[j], cond) == 0)
			{

				auto c = carti[i];
				carti[i] = carti[j];
				carti[j] = c;
			}
		}
	}
	return carti;
}

std::map <string, int >Service::raport(std::map<string, int>  dict)
{
	using std::map;
	auto carti = getAll();

	for (int i = 0; i < carti.size(); i++)
	{
		Carte c = carti[i];
		auto it = dict.find(c.getAutor());
		if (it != dict.end())
		{

			it->second++;
		}
		else
		{
			dict.insert(pair <string, int>(c.getAutor(), 1));
		}

	}
	return dict;
}

Carte Service::search(string titlu)
{
	int ok = 0;
	auto  carti = rep.getAll();
	Carte b{ "Nu extista cartea cautata!" ,"", "" , 0 };
	for (auto c : carti)
	{
		if (c.getTitlu().compare(titlu) == 0)
		{
			ok = 1;
			return c;
		}
	}
	if (ok == 0)
		return b;
}

int   Service::undo()
{
	if (undoActions.empty())
	{
		return 0;
	}
	else {
		undoActions.back()->doUndo();
		undoActions.pop_back();
		return 1;
	}
}

void testRaport()
{
	CarteRepo repo;
	Service service(repo);
	Carte c{ "a","a","a",2015 };
	service.add("a", "a", "a", 2015);
	service.add("a", "a", "a", 2015);
	service.add("a", "a", "a", 2015);
	map<string, int>  dict;
	auto dict2 = service.raport(dict);
	assert(dict2.size() == 1);
}



void testUndo()
{
	CarteRepo repo;
	Service service(repo);
	Carte c{ "a","a","a",2015 };
	service.add("a", "a", "a", 2015);
	service.add("a", "a", "a", 2015);
	service.add("a", "a", "a", 2015);
	service.undo();
	auto carti = service.getAll();
	assert(carti.size() == 2);
	service.remove("a");
	service.undo();
	assert(carti.size() == 2);
	service.modify("a", "b", "b", 25);
	assert(carti.size() == 2);
	service.undo();
	service.undo();
	service.undo();
	service.undo();
	service.undo();
	service.undo();
	assert(service.undo() == 0);


}


void testGetSet()
{
	CarteRepo repo;
	Service service(repo);
	Carte c{ "a","a","a",2015 };
	service.add("a", "a", "a", 2015);
	auto carti = service.getAll();
	assert(carti.size() == 1);
	assert(carti[0].getAn() == 2015);
	assert(carti[0].getAutor() == "a");
	assert(carti[0].getGen() == "a");
	assert(carti[0].getTitlu() == "a");

}

void testModify()
{
	CarteRepo repo;
	Service service(repo);
	Carte c{ "a","a","a",2015 };
	service.add("a", "a", "a", 2015);
	auto carti = service.modify("a", "b", "b", 25);
	assert(carti.getAn() == 2015);
	assert(carti.getAutor() == "a");
	assert(carti.getAn() == 2015);
	//assert(carti[0].getAn() == 25);
	//assert(carti[0].getAutor() == "b");
	//assert(carti[0].getGen() == "b");
	//assert(carti[0].getTitlu() == "a");

}

void testDelete()
{
	CarteRepo repo;
	Service service(repo);
	Carte c{ "a","a","a",2015 };
	service.add("a", "a", "a", 2015);

	service.remove("a");
	auto carti = service.getAll();
	assert(carti.size() == 0);
}

void testSort()
{
	CarteRepo repo;
	Service service(repo);
	service.add("t", "t", "b", 2015);
	service.add("g", "g", "a", 2015);
	service.add("a", "a", "a", 25);
	service.add("b", "b", "a", 35);

	auto carti = service.getAll();
	assert(carti.size() == 4);

	carti = service.sortByConditie(1);
	assert(carti[0].getAn() == 25);
	assert(carti[1].getAn() == 35);

	carti = service.sortByConditie(2);
	assert(carti[0].getAn() == 25);
	assert(carti[1].getAn() == 35);

	carti = service.sortByConditie(3);
	assert(carti[0].getAn() == 25);
	assert(carti[1].getAn() == 35);
}

void testCopyImplement()
{
	CarteRepo repo;
	Service service(repo);
	service.add("t", "t", "b", 2015);
	auto carti = service.getAll();

	Carte c = carti[0];
}
void testService()
{
	testCopyImplement();
	testSort();
	testModify();
	testGetSet();
	testDelete();
	testUndo();
	testRaport();
}