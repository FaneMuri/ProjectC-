#include "Lab10.h"
#include "Gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CarteRepo repo;
    Service serv { repo };
    testService();
    //GuiCos* d = new GuiCos{c};
    Gui* e = new Gui{serv};
    e->show();
   
    return a.exec();
}
