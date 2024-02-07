#include "2048.h"

#include <iostream>
#include <vector>

namespace game2048 {
	static bool is_valid(const Coordinates& coordinates) {
		return coordinates.first < MAX_SIZE && coordinates.second < MAX_SIZE;
	}

	typedef struct MoveResult {
		unsigned int score;
		bool has_moved;
	} MoveResult;

	static std::string number_repr(uint8_t repr_number) {
		if (repr_number == 0) { return "    "; }
		const unsigned int number = 1 << repr_number;
		std::string repr = std::to_string(number);
		if (number < 10) { return "  " + repr + " "; }
		else if (number < 100) { return " " + repr + " "; }
		else if (number < 1000) { return " " + repr; }
		else { return repr; }
	}

	static MoveResult merge_on_line(Line& line) {
		uint8_t active = 0;
		uint8_t x;
		MoveResult result {};
		for (uint8_t i = 0; i < MAX_SIZE; i++) {
			if (line[i] == active && active != 0) {
				line[x] = 0;
				line[i] = active + 1;
				result.score += 1 << (active + 1);
				result.has_moved = true;
				active = 0;
			} else {
				if (line[i] != 0) {
					active = line[i];
					x = i;
				}
			}
		}
		return result;
	}

	static bool move_line_left(Line& line) {
		uint8_t index = 0;
		for (uint8_t i = 0; i < MAX_SIZE; i++) {
			if (line[i] != 0) { line[index++] = line[i]; }
		}
		bool has_moved = false;
		while (index < MAX_SIZE) {
			uint8_t& next = line[index++];
			has_moved |= next;
			next = 0;
		}
		return has_moved;
	}
}

using namespace game2048;

Game::Game() {
	for (uint8_t i = 0; i < CELLS_AT_START; i++) { this->spawn_number(); }
}

Coordinates Game::get_random_empty_cell() {
	std::vector<Coordinates> empty_cells;
	for (uint8_t i = 0; i < MAX_SIZE; i++) {
		for (uint8_t j = 0; j < MAX_SIZE; j++) {
			if (this->board[i][j] == 0) {
				empty_cells.emplace_back(j, i);
			}
		}
	}
	if (empty_cells.empty()) { return {-1, -1}; }
	return empty_cells[this->random.get_long(empty_cells.size())];
}

int Game::spawn_number() {
	Coordinates cell = this->get_random_empty_cell();
	if (!is_valid(cell)) { return 1; }
	this->board[cell.second][cell.first] = this->random.get_success(SPAWN_CHANCE_4) ? 2 : 1;
	return 0;
}

bool Game::move_left() {
	bool has_moved = false;
	for (auto& line: this->board) {
		MoveResult merge_result = merge_on_line(line);
		this->score += merge_result.score;
		has_moved |= merge_result.has_moved | move_line_left(line);
	}
	return has_moved;
}

void Game::rotate() {
	uint8_t i, j, tmp;
	for (i = 0; i < MAX_SIZE / 2; i++) {
		for (j = i; j < static_cast<uint8_t>(MAX_SIZE - i - 1); j++) {
			tmp = this->board[i][j];
			this->board[i][j] = this->board[j][MAX_SIZE - i - 1];
			this->board[j][MAX_SIZE - i - 1] = this->board[MAX_SIZE - i - 1][MAX_SIZE - j - 1];
			this->board[MAX_SIZE - i - 1][MAX_SIZE - j - 1] = this->board[MAX_SIZE - j - 1][i];
			this->board[MAX_SIZE - j - 1][i] = tmp;
		}
	}
}

bool Game::move(Direction dir) {
	bool has_moved;
	switch (dir) {
		case Direction::up:
			this->rotate();
			has_moved = this->move_left();
			this->rotate();
			this->rotate();
			this->rotate();
			break;
		case Direction::right:
			this->rotate();
			this->rotate();
			has_moved = this->move_left();
			this->rotate();
			this->rotate();
			break;
		case Direction::down:
			this->rotate();
			this->rotate();
			this->rotate();
			has_moved = this->move_left();
			this->rotate();
			break;
		case Direction::left:
			has_moved = this->move_left();
			break;
		default:
			return false;
	}
	if (has_moved) { this->spawn_number(); }
	return has_moved;
}

void Game::print_board() const {
	constexpr uint8_t OUTPUT_LENGTH = 5 * MAX_SIZE + 1;
	const std::string LINE_SEPARATOR(OUTPUT_LENGTH, '-');
	std::cout << LINE_SEPARATOR << std::endl;
	for (const Line& line : this->board) {
		std::cout << "|";
		for (const uint8_t& number: line) {
			std::cout << number_repr(number) << "|";
		}
		std::cout << std::endl << LINE_SEPARATOR << std::endl;
	}
}

Board Game::get_board() const { return this->board; }
unsigned int Game::get_score() const { return this->score; }

bool Game::can_move() const {
	uint8_t i, j, current_x, current_y;
	for (i = 0; i < MAX_SIZE; i++) {
		current_x = 0;
		current_y = 0;
		for (j = 0; j < MAX_SIZE; j++) {
			if (this->board[i][j] == current_x || this->board[j][i] == current_y || !this->board[i][j]) { return true; }
			current_x = this->board[i][j];
			current_y = this->board[j][i];
		}
	}
	return false;
}

void Game::reset() {
	for (Line& line: this->board) {
		for (uint8_t& tile: line) { tile = 0; }
	}
	this->score = 0;
	for (uint8_t i = 0; i < CELLS_AT_START; i++) { this->spawn_number(); }
}

Random::Random() {
	struct timespec now {};
	int status = clock_gettime(CLOCK_REALTIME, &now);
	if (status != 0) {
		std::cerr << "Could not get current time to initialize random (status " << status << ")" << std::endl;
		exit(1);
	}
	this->generator.seed(static_cast<unsigned long>(now.tv_nsec));
}

unsigned long Random::get_long(unsigned long max) {
	return this->generator() % max;
}

bool Random::get_success(double success_chance) {
	return get_long(100000) < static_cast<unsigned long>(success_chance * 100000);
}
