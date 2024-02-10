#include "GameController.h"

#include <array>

GameController::GameController(QObject *parent): QObject(parent) {}

template<typename T, unsigned int Size>
QList<T> listFromMatrix(const std::array<std::array<T, Size>, Size>& matrix) {
	QList<T> result;
	for (auto& row: matrix) { std::copy(row.begin(), row.end(), std::back_inserter(result)); }
	return result;
}

quint32 GameController::getScore() const { return this->game.get_score(); }
QList<quint8> GameController::getBoard() const { return listFromMatrix<uint8_t, game2048::MAX_SIZE>(this->game.get_board()); }
bool GameController::isInGame() const { return this->inGame; }

void GameController::setInGame(bool status) {
    if (status == this->inGame) { return; }
	this->inGame = status;
	emit inGameChanged();
}


void GameController::move(const quint8 towards) {
	game2048::Direction direction;
	switch (towards) {
		case 0: direction = game2048::Direction::up; break;
		case 1: direction = game2048::Direction::right; break;
		case 2: direction = game2048::Direction::down; break;
		case 3: direction = game2048::Direction::left; break;
		default: return;
	}
	this->game.move(direction);
	emit boardChanged();
	emit scoreChanged();
}

void GameController::reset() {
	this->game.reset();
	emit boardChanged();
	emit scoreChanged();
}

bool GameController::canMove() { return this->game.can_move(); }
