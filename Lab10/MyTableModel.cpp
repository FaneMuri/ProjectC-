#include "MyTableModel.h"
#include <qfont.h>
#include <qbrush.h>
QVariant CustomTableModel::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int col = index.column();

	if (role == Qt::DisplayRole) {
		if (col == 0)
			return QString::fromStdString(carti[row].getTitlu());
		else if (col == 1)
			return QString::fromStdString(carti[row].getAutor());
	}
	return QVariant();
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const {

	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section) {
		case 0:
			return QString("Titlu");
		case 1:
			return QString("Autor");
		}
	}

	return QVariant();
}