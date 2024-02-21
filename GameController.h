#ifndef INC_2048_GAMECONTROLLER_H
#define INC_2048_GAMECONTROLLER_H

#include <QAbstractListModel>
#include <QObject>
#include <qqml.h>
#include "2048.h"

typedef struct Tile {
	uint8_t index;
	uint8_t value;
} Tile;

class BoardModel: public QAbstractListModel {
	Q_OBJECT

public:
	enum BoardModelRoles: int {
		BoardIndexRole,
		BoardValueRole
	};

	explicit BoardModel(QObject* parent = nullptr);
	int rowCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	QHash<int, QByteArray> roleNames() const override;
	void append(const Tile& tile);
	void remove(uint8_t index);
	void edit(uint8_t oldIndex, uint8_t newIndex, bool valueIncrement);
	void reset();
	int getIndexInList(uint8_t tileIndex) const;

private:
	QList<Tile> tiles;
};

class GameController: public QObject {
	Q_OBJECT
	QML_ELEMENT
	QML_SINGLETON

	Q_PROPERTY(quint32 score READ getScore NOTIFY scoreChanged)
	Q_PROPERTY(BoardModel* board READ getBoard)
	Q_PROPERTY(bool inGame READ isInGame WRITE setInGame NOTIFY inGameChanged)

public:
	explicit GameController(QObject* parent = nullptr);
	quint32 getScore() const;
	BoardModel* getBoard();
	bool isInGame() const;
	void setInGame(bool);
	Q_INVOKABLE void move(quint8 towards);
	Q_INVOKABLE void reset();
	Q_INVOKABLE bool canMove();

signals:
	void scoreChanged();
	void inGameChanged();

private:
	BoardModel board;
	game2048::Game game {};
	bool inGame = true;
};


#endif //INC_2048_GAMECONTROLLER_H
