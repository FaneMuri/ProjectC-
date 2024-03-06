#pragma once
#include "Service.h"
class UndoAction {
public:
	virtual void doUndo() {};  virtual ~UndoAction() {};
};

class UndoAdauga : public UndoAction {
private:
	Carte produsAdaugat;
	CarteRepo& rep;
public:
	UndoAdauga(CarteRepo& rep, const Carte& p) : rep{ rep }, produsAdaugat{ p } {}
	void doUndo() override {
		rep.remove(produsAdaugat.getTitlu());

	}
};

class UndoSterge : public UndoAction {
private:
	Carte produsSters;
	CarteRepo& rep;
public:
	UndoSterge(CarteRepo& rep, const Carte& p) : rep{ rep }, produsSters{ p } {}
	void doUndo() override {
		rep.store(produsSters);
	}
};

class UndoModifica : public UndoAction {
private:
	Carte produsModificat;
	Carte ProdusVechi;
	CarteRepo& rep;
public:
	UndoModifica(CarteRepo& rep, const Carte& p1, const Carte& p2) : rep{ rep }, produsModificat{ p1 }, ProdusVechi{ p2 } {}
	void doUndo() override {
		rep.modify(produsModificat);
	}
};
