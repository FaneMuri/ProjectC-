#pragma once
#include <string>
#include <iostream >
using std::string;
//using namespace std;

class Carte
{
private:
	string titlu;
	string autor;
	string gen;
	int an;
public:
	int getAn() const
	{
		return an;
	}


	string getTitlu()const;
	string getAutor()const;
	string getGen()const;
	Carte(string titlu, string autor, string gen, int an) : titlu{ titlu }, autor{ autor }, gen{ gen }, an{ an } {

	}

	Carte(const Carte& c) : titlu{ c.titlu }, autor{ c.autor }, gen{ c.gen }, an{ c.an } {  // copy constructor;

	}
};

