#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Carte.h"

using std::vector ;

class CustomTableModel : public QAbstractTableModel {

private :
	vector<Carte> carti;
public:
	CustomTableModel(const vector<Carte> product_list) : carti{ product_list } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return int(carti.size());
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 2;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setProduct(const vector<Carte> new_list) {


		carti = new_list;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topLeft, bottomRight);
	}

};


