#ifndef INC_2048_2048_H
#define INC_2048_2048_H

#include <array>
#include <random>

namespace game2048 {
	const uint8_t MAX_SIZE = 4;
	const double SPAWN_CHANCE_4 = .25;
	const uint8_t CELLS_AT_START = 2;

	typedef std::array<uint8_t, MAX_SIZE * MAX_SIZE> Board;
	enum class Direction { up, right, down, left };

	typedef struct GameAction {
		uint8_t start_index;
		uint8_t end_index;
		bool merged;
		uint8_t spawned_number;
	} GameAction;

	class Game {
	public:
		Game();
		std::vector<GameAction> move(Direction, bool spawn = true);
		bool can_move() const;
		const Board& get_board() const;
		unsigned int get_score() const;
		void print_board() const;
		void reset();
		void set_board(const Board& new_board);
		long to_index(const uint8_t* pointer) const;

	private:
		Board board {};
		std::array<uint8_t*, MAX_SIZE * MAX_SIZE> rotated_board {};
		unsigned int score = 0;
		std::vector<GameAction> current_turn_actions;

		uint8_t* get_random_empty_cell();
		int spawn_number();
		void move_left();
		void reset_rotation();
		void rotate();
		void merge_on_line(uint8_t line_index);
		void move_line_left(uint8_t line_index);
	};
}


#endif //INC_2048_2048_H
