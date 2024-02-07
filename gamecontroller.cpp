#include "gamecontroller.h"

#include <array>

GameController::GameController(QObject *parent): QObject(parent) {}

template<typename T, unsigned int Size>
QList<T> listFromMatrix(std::array<std::array<T, Size>, Size> matrix) {
	QList<T> result;
	for (auto& row: matrix) { std::copy(row.begin(), row.end(), std::back_inserter(result)); }
	return result;
}

quint32 GameController::getScore() { return this->game.get_score(); }
quint32 GameController::getBestScore() { return 0; }
QList<quint8> GameController::getBoard() { return listFromMatrix<uint8_t, 4>(this->game.get_board()); }

void GameController::updateScore() {
	const quint32& score = this->game.get_score();
	emit scoreChanged();
	if (score > this->getBestScore()) {
		this->setBestScore(score);
	}
}

void GameController::setBestScore(const quint32& bestScore) {
	emit bestScoreChanged();
}

void GameController::move(int towards) {
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
	this->updateScore();
}

void GameController::reset() {
	this->game.reset();
	emit boardChanged();
	this->updateScore();
}

bool GameController::canMove() { return this->game.can_move(); }
