#include "Test2048.h"

#include <qdebug.h>
#include <QtTest>

void Test2048::moveTest_data() {
	QTest::addColumn<game2048::Board>("initial");
	QTest::addColumn<game2048::Direction>("direction");
	QTest::addColumn<game2048::Board>("expected");
	QTest::addColumn<int>("score");

	QTest::addRow("up")
			<< game2048::Board({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1})
			<< game2048::Direction::up
			<< game2048::Board({1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})
			<< 0;
	QTest::addRow("down")
			<< game2048::Board({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1})
			<< game2048::Direction::down
			<< game2048::Board({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1})
			<< 0;
	QTest::addRow("right")
			<< game2048::Board({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1})
			<< game2048::Direction::right
			<< game2048::Board({0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1})
			<< 0;
	QTest::addRow("left")
			<< game2048::Board({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1})
			<< game2048::Direction::left
			<< game2048::Board({1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0})
			<< 0;
	QTest::addRow("up, two tiles")
			<< game2048::Board({1, 0, 0, 0, 2, 2, 2, 2, 0, 0, 1, 0, 0, 0, 0, 1})
			<< game2048::Direction::up
			<< game2048::Board({1, 2, 2, 2, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0})
			<< 0;
	QTest::addRow("down, two tiles")
			<< game2048::Board({1, 0, 0, 0, 0, 1, 0, 0, 2, 2, 2, 2, 0, 0, 0, 1})
			<< game2048::Direction::down
			<< game2048::Board({0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 2, 2, 2, 2, 1})
			<< 0;
	QTest::addRow("right, two tiles")
			<< game2048::Board({1, 0, 2, 0, 0, 1, 2, 0, 0, 0, 2, 0, 0, 0, 2, 1})
			<< game2048::Direction::right
			<< game2048::Board({0, 0, 1, 2, 0, 0, 1, 2, 0, 0, 0, 2, 0, 0, 2, 1})
			<< 0;
	QTest::addRow("left, two tiles")
			<< game2048::Board({1, 2, 0, 0, 0, 2, 0, 0, 0, 2, 1, 0, 0, 2, 0, 1})
			<< game2048::Direction::left
			<< game2048::Board({1, 2, 0, 0, 2, 0, 0, 0, 2, 1, 0, 0, 2, 1, 0, 0})
			<< 0;
	QTest::addRow("merge up")
			<< game2048::Board({1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0})
			<< game2048::Direction::up
			<< game2048::Board({2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})
			<< 4 * 4;
	QTest::addRow("merge down")
			<< game2048::Board({1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0})
			<< game2048::Direction::down
			<< game2048::Board({0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 2, 2, 2})
			<< 4 * 4;
	QTest::addRow("merge right")
			<< game2048::Board({1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0})
			<< game2048::Direction::right
			<< game2048::Board({0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1, 2})
			<< 4 * 3;
	QTest::addRow("merge left")
			<< game2048::Board({1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0})
			<< game2048::Direction::left
			<< game2048::Board({2, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 1, 0, 0})
			<< 4 * 3;
	QTest::addRow("no move up")
			<< game2048::Board({1, 2, 2, 1, 2, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2})
			<< game2048::Direction::up
			<< game2048::Board({1, 2, 2, 1, 2, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2})
			<< 0;
	QTest::addRow("no move down")
			<< game2048::Board({0, 0, 0, 1, 0, 0, 0, 2, 2, 1, 0, 1, 1, 2, 2, 2})
			<< game2048::Direction::down
			<< game2048::Board({0, 0, 0, 1, 0, 0, 0, 2, 2, 1, 0, 1, 1, 2, 2, 2})
			<< 0;
}

void Test2048::moveTest() {
	QFETCH(game2048::Board, initial);
	QFETCH(game2048::Direction, direction);
	QFETCH(game2048::Board, expected);
	QFETCH(int, score);
	game.reset();
	game.set_board(initial);
	game.move(direction, false);
	QCOMPARE(game.get_board(), expected);
	QCOMPARE(game.get_score(), score);
}

void Test2048::spawnTest() {
	game.reset();
	game.set_board({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
	game.move(game2048::Direction::up);
	int notNullCount = 0;
	for (const uint8_t& tile: game.get_board()) {
		if (tile == 0) { continue; }
		notNullCount++;
		QVERIFY(tile == 1 || tile == 2);
	}
	QCOMPARE(notNullCount, 5);
}

QTEST_MAIN(Test2048)
