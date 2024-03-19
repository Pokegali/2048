#ifndef INC_2048_GAMECONTROLLER_H
#define INC_2048_GAMECONTROLLER_H

#include "2048.h"
#include "BoardModel.h"
#include <QAbstractListModel>
#include <QObject>
#include <qqml.h>

class GameController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(quint32 score READ getScore NOTIFY scoreChanged)
    Q_PROPERTY(bool inGame READ isInGame WRITE setInGame NOTIFY inGameChanged)
    Q_PROPERTY(quint8 gameSize READ getGameSize WRITE setGameSize NOTIFY gameSizeChanged)
    Q_PROPERTY(BoardModel* board READ getBoard CONSTANT)


public:
	static const int MAX_GAME_SIZE = 8;
	static const int MIN_GAME_SIZE = 2;

	enum class Direction {
		up, down, right, left
	};
	Q_ENUM(Direction)

	explicit GameController(QObject* parent = nullptr);
	quint32 getScore() const;
	BoardModel* getBoard();
	bool isInGame() const;
	void setInGame(bool);
	quint8 getGameSize() const;
	void setGameSize(quint8);
	Q_INVOKABLE void move(GameController::Direction towards);
	Q_INVOKABLE void reset();
	Q_INVOKABLE bool canMove();
	Q_INVOKABLE void deleteTileAt(quint8 index);

	static game2048::Direction directionToGameDirection(GameController::Direction);

signals:
    void scoreChanged();
    void inGameChanged();
    void gameSizeChanged();

private:
    BoardModel board;
    game2048::Game game{4};
    bool inGame= true;
};


#endif //INC_2048_GAMECONTROLLER_H
