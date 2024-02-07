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
	Q_PROPERTY(quint32 bestScore READ getBestScore WRITE setBestScore NOTIFY bestScoreChanged)
	Q_PROPERTY(QList<quint8> board READ getBoard NOTIFY boardChanged)

public:
	explicit GameController(QObject* parent = nullptr);
	quint32 getScore();
	quint32 getBestScore();
	QList<quint8> getBoard();
	void setBestScore(const quint32& bestScore);

public slots:
	void move(int towards);
	void reset();
	bool canMove();


signals:
	void scoreChanged();
	void bestScoreChanged();
	void boardChanged();

private:
	game2048::Game game {};

	void updateScore();
};


#endif //INC_2048_GAMECONTROLLER_H
