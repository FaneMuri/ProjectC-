#include "CarteRepo.h"
#include <assert.h>
#include <vector>
#include <optional>

Carte CarteRepo::modify(Carte& b)
{
	for (int i = 0; i < carti.size(); i++)
	{
		Carte c = carti[i];
		if (c.getTitlu().compare(b.getTitlu()) == 0)
		{
			carti[i] = b;
			return c;
		}
	}

}

Carte  CarteRepo::remove(string titlu)
{

	auto it = carti.begin();
	for (int i = 0; i < carti.size(); i++)
	{
		Carte c = carti[i];
		if (c.getTitlu().compare(titlu) == 0)
		{
			auto it = carti.begin() + i;
			carti.erase(it);
			return c;
		}
	}
}