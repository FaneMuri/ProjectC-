#pragma once
#include "Carte.h"
#include "CarteRepo.h"
#include "Service.h"
#include "MyTableModel.h"
#include <iostream>
#include <map>
#include "Cos.h"



#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>  // permite perechi eticheta combo-uri;
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/QTableView>
#include <QTableView>
#include <qdebug.h>
#include <qmessagebox.h>

#include <vector>
#include <string>

class Gui : public QWidget {

public:
	Gui(Service& srv) : srv{ srv }
	{
		initGui();
		loadData(srv.getAll());
		//loadTable(srv.getAll());
		initConnect();
	}
private:
	QListWidget* lst = new QListWidget;
	QTableWidget* tabel = new  QTableWidget{6,4};
	
	

	QHBoxLayout* lyMain = new QHBoxLayout{};


	Service& srv;
	Cos c{ srv };


	CustomTableModel* model = new CustomTableModel{ srv.getAll() };
	QTableView* tabel1 = new QTableView;

	QLineEdit* titlu = new QLineEdit;
	QLineEdit*  autor= new QLineEdit;
	QLineEdit* gen = new QLineEdit;
	QLineEdit* an = new QLineEdit;


	QPushButton* btAdd = new QPushButton{"&Add"};
	QPushButton* btMod = new QPushButton{"&Modify"};
	QPushButton* btDel = new QPushButton{"&Delete"};
	QPushButton* btSrc = new QPushButton{"&Search"};
	QPushButton* btFltTitle = new QPushButton{"&Filtrare Titlu"};
	QPushButton* btS1 = new QPushButton{"&Sortare titlu"};
	QPushButton* btS2 = new QPushButton{"&Sortare autor"};
	QPushButton* btS3 = new QPushButton{"&Sortare an+gen"};
	QPushButton* btUndo = new QPushButton{"&Undo"};
	QPushButton* btCos = new QPushButton{"&Cos"};
	QPushButton* btRap = new QPushButton{"&Raport"};
	QPushButton* btTabel = new QPushButton{"&Tabel"};


	void loadTable(vector<Carte> carti);

	void loadData(vector<Carte> carti);

	void initGui();

	void initConnect();

};



class GuiCos : public QWidget  {

public:
	GuiCos(Cos& beg) : beg { beg }
	{
		initGuiCos();
		loadDataCos(beg.allCos());
		initConnectCos();
	}
private:
	QListWidget* lst = new QListWidget;
	Cos& beg;

	QLineEdit* titlu = new QLineEdit;
	QLineEdit* nrelem = new QLineEdit;
	QLineEdit* exp = new QLineEdit;


	QPushButton* btAdd = new QPushButton{ "&Adaugare" };
	QPushButton* btExport = new QPushButton{ "&Export" };
	QPushButton* btGol = new QPushButton{ "&Golire cos" };
	QPushButton* btGen = new QPushButton{ "&Generate" };
	QPushButton* btExit = new QPushButton{ "&Exit" };
	


	void loadDataCos(vector<Carte> carti);

	void initGuiCos();

	void initConnectCos();
};
