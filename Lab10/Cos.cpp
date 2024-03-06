#include "Cos.h"
#include <assert.h>
#include <fstream>

using std::ofstream;

void Cos::addCos(string titlu)
{
	auto carti = service.getAll();
	auto it = find_if(carti.begin(), carti.end(), [titlu](const Carte& obj) {return obj.getTitlu() == titlu; });
	if (it != carti.end())
	{
		int index = std::distance(carti.begin(), it); // l-am gasit si il stochez
		cos.push_back(carti[index]);
	}
}

vector <Carte> Cos::generate(int nr)
{
	auto v = service.getAll();
	for (int i = 1; i <= nr; i++)
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, v.size() - 1);
		int rndNr = dist(mt);// numar aleator intre [0,size-1]
		cos.push_back(v[rndNr]);
	}
	return cos;
}


void Cos::exp(string nume)
{
	ofstream f(nume);
	f << "<html>";
	f << "<body>";
	f << "<table style=\"border:1px solid black;margin-left:auto;margin-right:auto;\">";
	f << "<tr>";
	f << "<td>" << "Titlu" << "</td>";
	f << "<td>" << "Autor" << "</td>";
	f << "<td>" << "Gen" << "</td>";
	f << "<td>" << "An" << "</td>";
	f << "</tr>";
	for (const auto& c : cos)
	{
		f << "<tr>";
		f << "<td>" << c.getTitlu() << "</td>";
		f << "<td>" << c.getAutor() << "</td>";
		f << "<td>" << c.getGen() << "</td>";
		f << "<td>" << c.getAn() << "</td>";
		f << "</tr>";
	}
	f << "</table>";
	f << "</body>";
	f << "</html>";
	f.close();
}


void testCos()
{
	CarteRepo repo;
	Service service(repo);
	Carte c{ "a","a","a",2015 };
	service.add("a", "a", "a", 2015);
	service.add("s", "a", "a", 2015);
	service.add("d", "a", "a", 2015);
	Cos bagaj(service);

	bagaj.addCos("a");
	auto carti = bagaj.allCos();
	assert(carti.size() == 1);
	carti = bagaj.deleteAll();
	assert(carti.size() == 0);
	carti = bagaj.generate(5);
	assert(carti.size() == 5);

	bagaj.exp("File.html");
	carti = bagaj.allCos();
	assert(carti.size() == 5);

}