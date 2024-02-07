#ifndef INC_2048_2048_H
#define INC_2048_2048_H

#include <array>
#include <random>

namespace game2048 {
	const uint8_t MAX_SIZE = 4;
	const float SPAWN_CHANCE_4 = .25;
	const uint8_t CELLS_AT_START = 2;

	typedef std::array<uint8_t, MAX_SIZE> Line;
	typedef std::array<Line, MAX_SIZE> Board;
	typedef std::pair<uint8_t, uint8_t> Coordinates; // (x, y)
	enum class Direction { up, right, down, left };

	class Random {
	public:
		Random();
		unsigned long get_long(unsigned long max);
		bool get_success(double success_chance);

	private:
		std::minstd_rand generator;
	};

	class Game {
	public:
		Game();
		bool move(Direction);
		bool can_move() const;
		Board get_board() const;
		unsigned int get_score() const;
		void print_board() const;
		void reset();

	private:
		Board board = Board();
		Random random = Random();
		unsigned int score = 0;

		Coordinates get_random_empty_cell();
		int spawn_number();
		bool move_left();
		void rotate();
	};
}


#endif //INC_2048_2048_H
