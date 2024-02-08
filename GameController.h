#ifndef INC_2048_GAMECONTROLLER_H
#define INC_2048_GAMECONTROLLER_H

#include <QObject>
#include <qqml.h>
#include "2048.h"

class GameController: public QObject {
	Q_OBJECT
	QML_ELEMENT
	QML_SINGLETON

	Q_PROPERTY(quint32 score READ getScore NOTIFY scoreChanged)
	Q_PROPERTY(QList<quint8> board READ getBoard NOTIFY boardChanged)
	Q_PROPERTY(bool inGame READ isInGame WRITE setInGame NOTIFY inGameChanged)

public:
	explicit GameController(QObject* parent = nullptr);
	quint32 getScore() const;
	QList<quint8> getBoard() const;
	bool isInGame() const;
	void setInGame(bool);
	Q_INVOKABLE void move(quint8 towards);
	Q_INVOKABLE void reset();
	Q_INVOKABLE bool canMove();

signals:
	void scoreChanged();
	void boardChanged();
	void inGameChanged();

private:
	game2048::Game game {};
	bool inGame = true;
};


#endif //INC_2048_GAMECONTROLLER_H
