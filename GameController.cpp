#include "GameController.h"

GameController::GameController(QObject* parent): QObject(parent) { this->reset(); }

quint32 GameController::getScore() const { return this->game.get_score(); }
BoardModel* GameController::getBoard() { return &this->board; }
bool GameController::isInGame() const { return this->inGame; }
quint8 GameController::getGameSize() const { return this->game.get_size(); }

void GameController::setInGame(bool status) {
    if (status == this->inGame) { return; }
	this->inGame = status;
	emit inGameChanged();
}

void GameController::setGameSize(quint8 gameSize) {
	if (gameSize > MAX_GAME_SIZE || gameSize < MIN_GAME_SIZE) { return; }
	this->game = game2048::Game(gameSize);
	emit gameSizeChanged();
	this->reset();
}

void GameController::move(const Direction towards) {
	std::vector<game2048::GameAction> moveResult = this->game.move(directionToGameDirection(towards));
	for (const auto& action: moveResult) {
		if (action.merged) {
			this->board.startRemove(action.start_index);
			this->board.edit(action.end_index, action.end_index, true);
		} else if (action.spawned_number) {
			this->board.append({action.start_index, action.spawned_number, false});
		} else {
			this->board.edit(action.start_index, action.end_index, false);
		}
	}
	emit scoreChanged();
}

void GameController::reset() {
	this->game.reset();
	this->board.reset();
	for (const auto& x: this->game.get_board()) {
		if (x == 0) { continue; }
		this->board.append({this->game.to_index(&x), x, false});
	}
	emit scoreChanged();
}

bool GameController::canMove() { return this->game.can_move(); }

void GameController::deleteTileAt(quint8 index) { this->board.remove(index); }

game2048::Direction GameController::directionToGameDirection(Direction direction) {
	switch (direction) {
		case Direction::up: return game2048::Direction::up;
		case Direction::down: return game2048::Direction::down;
		case Direction::right: return game2048::Direction::right;
		case Direction::left: return game2048::Direction::left;
		default: throw std::invalid_argument("Invalid argument for direction.");
	}
}

BoardModel::BoardModel(QObject* parent) : QAbstractListModel(parent) {}

int BoardModel::rowCount(const QModelIndex& parent) const {
	Q_UNUSED(parent)
	return static_cast<int>(this->tiles.size());
}

QHash<int, QByteArray> BoardModel::roleNames() const {
	static QHash<int, QByteArray> mapping {
		{BoardIndexRole, "index"},
		{BoardValueRole, "value"},
		{BoardToDeleteRole, "toDelete"}
	};
	return mapping;
}

QVariant BoardModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid() || index.row() >= this->tiles.size()) { return {}; }
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
	if (valueIncrement) { this->tiles[tileIndex].value++; }
	this->tiles[tileIndex].index = newIndex;
	QModelIndex qIndex = this->index(tileIndex);
	emit this->dataChanged(qIndex, qIndex);
}

int BoardModel::getIndexInList(uint8_t tileIndex, bool toDelete) const {
	return static_cast<int>(std::find_if(this->tiles.begin(), this->tiles.end(), [&tileIndex, &toDelete](const Tile& tile) { return tile.index == tileIndex && tile.toDelete == toDelete; }) - this->tiles.begin());
}

void BoardModel::reset() {
	this->beginResetModel();
	this->tiles.clear();
	this->endResetModel();
}
