#include "Gui.h"

//using namespace std;
using std::string;
using std::vector;
using std::to_string;
using std::map;
using std::pair;

void Gui::loadData(vector<Carte> carti)
{ /*
	lst->clear();
	for (auto c : carti) {
		string b = c.getTitlu() + " " + c.getAutor() + " "  + c.getGen() +" " + to_string(c.getAn());
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(b));
		lst->addItem(item);
	}
	*/
	model->setProduct(carti);
}

void Gui::loadTable(vector<Carte> carti)
{

	tabel->clearContents();
	tabel->setRowCount(carti.size());

	int ln=0;

	for (auto& c : carti)
	{
		tabel->setItem(ln, 0, new QTableWidgetItem(QString::fromStdString(c.getTitlu())));
		tabel->setItem(ln, 1, new QTableWidgetItem(QString::fromStdString(c.getAutor())));
		tabel->setItem(ln, 2, new QTableWidgetItem(QString::fromStdString(c.getGen())));
		tabel->setItem(ln, 3, new QTableWidgetItem(QString::number(c.getAn())));
		ln++;



	}
}

void Gui::initGui()
{	

	
	
	
	setLayout(lyMain);
	//lyMain->addWidget(lst);
	tabel1->setModel(model);
	lyMain->addWidget(tabel1);
	
	QStringList header;
	header << "Titlu" << "Autor" << "Gen" << "An";
	tabel->setHorizontalHeaderLabels(header);

	//lyMain->addWidget(tabel);

	auto stgLy = new QVBoxLayout;
	
	auto formLy = new QFormLayout;
	formLy->addRow("Titlu", titlu);
	formLy->addRow("Autor", autor);
	formLy->addRow("Gen", gen );
	formLy->addRow("An", an);
	stgLy->addLayout(formLy);



	auto lyBtn = new QHBoxLayout{};
	lyBtn->addWidget(btAdd);
	lyBtn->addWidget(btMod);
	lyBtn->addWidget(btDel);
	lyBtn->addWidget(btSrc);
	lyBtn->addWidget(btFltTitle);

	auto lyBtn2 = new QHBoxLayout{};
	
	lyBtn2->addWidget(btS1);
	lyBtn2->addWidget(btS2);
	lyBtn2->addWidget(btS3);
	lyBtn2->addWidget(btUndo);
	lyBtn2->addWidget(btCos);
	lyBtn2->addWidget(btRap);
	

	stgLy->addLayout(lyBtn);
	stgLy->addLayout(lyBtn2);

	lyMain->addLayout(stgLy);
}

void Gui::initConnect() {
	
	
	
	
	// for add button
	QObject::connect(btAdd, &QPushButton::clicked, [&]() {

		auto titlu1 = titlu->text();
		auto autor1 = autor->text();
		auto gen1 = gen->text();
		auto an1 = an->text();
		int anBun = an1.toInt();
		srv.add(titlu1.toStdString() , autor1.toStdString(), gen1.toStdString(), anBun);
		loadData(srv.getAll());
		//loadTable(srv.getAll());
		});


	// for modify button

	QObject::connect(btMod, &QPushButton::clicked, [&]() {

		auto titlu1 = titlu->text();
		auto autor1 = autor->text();
		auto gen1 = gen->text();
		auto an1 = an->text();
		int anBun = an1.toInt();
		srv.modify(titlu1.toStdString(), autor1.toStdString(), gen1.toStdString(), anBun);
		loadData(srv.getAll());
		});


	// for delete
	QObject::connect(btDel, &QPushButton::clicked, [&]() {

		auto titlu1 = titlu->text();
		
		srv.remove(titlu1.toStdString());
		loadData(srv.getAll());
		});


	// for Search
	QObject::connect(btSrc, &QPushButton::clicked, [&]() {

		auto titlu1 = titlu->text();

		auto c = srv.search(titlu1.toStdString());
		string b = c.getTitlu() + " " + c.getAutor() + " " + c.getGen() + " " + to_string(c.getAn());
		QMessageBox::information(nullptr, "Search", QString::fromStdString(b));
		});

	QObject::connect(btFltTitle, &QPushButton::clicked, [&]() {

		auto titlu1 = titlu->text();

		auto c = srv.search(titlu1.toStdString());
		string b = c.getTitlu() + " " + c.getAutor() + " " + c.getGen() + " " + to_string(c.getAn());
		QMessageBox::information(nullptr, "Filter", QString::fromStdString(b));
		});



	// for sortari 
	QObject::connect(btS1, &QPushButton::clicked, [&]() {

		loadData(srv.sortByConditie(1));
		});
	QObject::connect(btS2, &QPushButton::clicked, [&]() {

		loadData(srv.sortByConditie(2));
		});
	QObject::connect(btS3, &QPushButton::clicked, [&]() {

		loadData(srv.sortByConditie(3));
		});

	// for undo
	QObject::connect(btUndo, &QPushButton::clicked, [&]() {

		auto x = srv.undo();
		loadData(srv.getAll());
		if (x == 0)
		QMessageBox::information(nullptr, "Undo Info", "Nu se mai poate face undo!");
		else 
			QMessageBox::information(nullptr, "Undo Info", "S-a facut undo!");

		});


	// for Cos
	QObject::connect(btCos, &QPushButton::clicked, [&]() {

		
		GuiCos* d = new GuiCos{c};
		d->show();
		});

	QObject::connect(btRap, &QPushButton::clicked, [&]() {
		
		vector <QPushButton*> btnList;
		
		
		//QWidget* w{};
		//QVBoxLayout* ly = new QVBoxLayout{};
		map <string, int> dict;
		dict = srv.raport(dict);
		
		int k = 0;
		for (const auto& p : dict)
		{
			QPushButton* btn = new QPushButton(QString::fromStdString(p.first));
			btnList.push_back(btn);
			lyMain->addWidget(btnList[k]);
			int a = p.second;
			QObject::connect(btnList[k], &QPushButton::clicked, [&]() {
				string aa = to_string(a) ;
				QMessageBox::information(nullptr, "Info CATE", QString::fromStdString(aa));
				
				
				});
			k++;
		}


		//w->setLayout(ly);
		//w->show();
		
		
		});



}


void GuiCos::loadDataCos(vector<Carte> carti)
{
	lst->clear();
	for (auto c : carti) {
		string b = c.getTitlu() + " " + c.getAutor() + " " + c.getGen() + " " + to_string(c.getAn());
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(b));
		lst->addItem(item);
	}
}

void GuiCos::initGuiCos()
{


	QHBoxLayout* lyMain = new QHBoxLayout{};

	setLayout(lyMain);
	lyMain->addWidget(lst);



	auto stgLy = new QVBoxLayout;

	auto formLy = new QFormLayout;
	formLy->addRow("Titlu", titlu);
	formLy->addRow("Numar", nrelem);
	formLy->addRow("Nume Export", exp);

	stgLy->addLayout(formLy);



	auto lyBtn = new QHBoxLayout{};
	
	lyBtn->addWidget(btAdd);
	lyBtn->addWidget(btExport);
	lyBtn->addWidget(btGol);
	lyBtn->addWidget(btGen);
	
	lyBtn->addWidget(btExit);
	


	stgLy->addLayout(lyBtn);
	

	lyMain->addLayout(stgLy);
}

void GuiCos::initConnectCos() {
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {

		auto  sel = lst->selectedItems();
		if (sel.isEmpty())
		{
			// le dau la toate spatiu gol;
		}
		else
		{
			auto item_selected = sel.at(0);
			item_selected->text();
			item_selected->data(Qt::UserRole);
		}
		});


	QObject::connect(btExit, &QPushButton::clicked, [&]() {
		
		QMessageBox::information(nullptr, "Info", "Ati iesit din fereastra cos!!!");
		close(); // pt inchidere fereastra!
		});

	QObject::connect(btAdd, &QPushButton::clicked, [&]() {

		auto titlu1 = titlu->text();
		beg.addCos(titlu1.toStdString());
		loadDataCos(beg.allCos());

	
		
		
		
		auto  bagaje = beg.allCos();
		int sz = bagaje.size();
		string b = "Nr el introduse in cos este : " + to_string(sz);
		
		
		QMessageBox::information(nullptr, "Info", QString::fromStdString(b));
		
		});


	QObject::connect(btExport, &QPushButton::clicked, [&]() {

		
		
		//loadDataCos(beg.allCos());
		auto st = exp->text();
		beg.exp(st.toStdString());
	


		auto  bagaje = beg.allCos();
		int sz = bagaje.size();
		string b = "Nr el introduse in cos este : " + to_string(sz);


		QMessageBox::information(nullptr, "Info", QString::fromStdString(b));

		});

	QObject::connect(btGol, &QPushButton::clicked, [&]() {

		
		beg.deleteAll();
		loadDataCos(beg.allCos());

		auto  bagaje = beg.allCos();
		int sz = bagaje.size();
		string b = "Nr el introduse in cos este : " + to_string(sz);


		QMessageBox::information(nullptr, "Info", QString::fromStdString(b));

		});


	QObject::connect(btGen, &QPushButton::clicked, [&]() {

		auto n = nrelem->text();
		beg.generate(n.toInt());
		loadDataCos(beg.allCos());

		auto  bagaje = beg.allCos();
		int sz = bagaje.size();
		string b = "Nr el introduse in cos este : " + to_string(sz);


		QMessageBox::information(nullptr, "Info", QString::fromStdString(b));

		});

}
