#ifndef INC_2048_TEST2048_H
#define INC_2048_TEST2048_H

#include <QObject>
#include "2048.h"

class Test2048: public QObject {
	Q_OBJECT

private slots:
	void moveTest_data();
	void moveTest();
	void spawnTest();

private:
	game2048::Game game {4};
};

#endif //INC_2048_TEST2048_H
