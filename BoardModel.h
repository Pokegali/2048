#ifndef INC_2048_BOARDMODEL_H
#define INC_2048_BOARDMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QObject>
#include <QVariant>
#include "Types.h"

class BoardModel: public QAbstractListModel {
	Q_OBJECT

public:
	enum BoardModelRoles: int {
		BoardIndexRole,
		BoardValueRole,
		BoardToDeleteRole
	};

	explicit BoardModel(QObject* parent = nullptr);
	int rowCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	QHash<int, QByteArray> roleNames() const override;
	void append(const Tile& tile);
	void startRemove(uint8_t index);
	void remove(uint8_t index);
	void edit(uint8_t oldIndex, uint8_t newIndex, bool valueIncrement);
	void reset();
	int getIndexInList(uint8_t tileIndex, bool toDelete = false) const;

private:
	QList<Tile> tiles;
};

#endif //INC_2048_BOARDMODEL_H
