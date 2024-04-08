#include "BoardModel.h"
#include "Types.h"

BoardModel::BoardModel(QObject* parent): QAbstractListModel(parent) {}

int BoardModel::rowCount(const QModelIndex& parent) const {
	if (parent.isValid()) {
		return 0;
	}
	return static_cast<int>(tiles.size());
}

QHash<int, QByteArray> BoardModel::roleNames() const {
	static QHash<int, QByteArray> mapping{
			{BoardIndexRole, "index"},
			{BoardValueRole, "value"},
			{BoardToDeleteRole, "toDelete"}};
	return mapping;
}

QVariant BoardModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid() || index.row() >= this->tiles.size()) {
		return {};
	}
	const Tile& tile = this->tiles[index.row()];
	switch (role) {
		case BoardIndexRole:
			return static_cast<int>(tile.index);
		case BoardValueRole:
			return static_cast<int>(tile.value);
		case BoardToDeleteRole:
			return tile.toDelete;
		default:
			return {};
	}
}

void BoardModel::append(const Tile& tile) {
	int size = static_cast<int>(this->tiles.size());
	this->beginInsertRows(QModelIndex(), size, size);
	this->tiles.append(tile);
	this->endInsertRows();
}

void BoardModel::remove(uint8_t index) {
	const auto& tileIndex = this->getIndexInList(index, true);
	this->beginRemoveRows(QModelIndex(), tileIndex, tileIndex);
	this->tiles.removeAt(tileIndex);
	this->endRemoveRows();
}

void BoardModel::startRemove(uint8_t index) {
	const auto& tileIndex = this->getIndexInList(index);
	this->tiles[tileIndex].toDelete = true;
	QModelIndex qIndex = this->index(tileIndex);
	emit this->dataChanged(qIndex, qIndex);
}

void BoardModel::edit(uint8_t oldIndex, uint8_t newIndex, bool valueIncrement) {
	const auto& tileIndex = this->getIndexInList(oldIndex);
	if (valueIncrement) {
		this->tiles[tileIndex].value++;
	}
	this->tiles[tileIndex].index = newIndex;
	QModelIndex qIndex = this->index(tileIndex);
	emit this->dataChanged(qIndex, qIndex);
}

int BoardModel::getIndexInList(uint8_t tileIndex, bool toDelete) const {
	return static_cast<int>(
			std::find_if(this->tiles.begin(), this->tiles.end(), [&tileIndex, &toDelete](const Tile& tile) {
				return tile.index == tileIndex && tile.toDelete == toDelete;
			}) - this->tiles.begin()
	);
}

void BoardModel::reset() {
	this->beginResetModel();
	this->tiles.clear();
	this->endResetModel();
}