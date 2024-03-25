#ifndef INC_2048_2048_H
#define INC_2048_2048_H

#include <cstdint>
#include <vector>

namespace game2048 {
	const double SPAWN_CHANCE_4 = .25;
	const uint8_t CELLS_AT_START = 2;

	typedef std::vector<uint8_t> Board;
	enum class Direction { up, right, down, left };

	typedef struct GameAction {
		uint8_t start_index;
		uint8_t end_index;
		bool merged;
		uint8_t spawned_number;
	} GameAction;

	class Game {
	public:
		explicit Game(uint8_t size);
		std::vector<GameAction> move(Direction, bool spawn = true);
		bool can_move() const;
		const Board& get_board() const;
		uint8_t get_size() const;
		unsigned int get_score() const;
		void print_board() const;
		void reset();
		void set_board(const Board& new_board);
		long to_index(const uint8_t* pointer) const;

	private:
		Board board {};
		std::vector<uint8_t*> rotated_board {};
		unsigned int score = 0;
		uint8_t size;
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
