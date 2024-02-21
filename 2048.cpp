#include "2048.h"

#include <iostream>
#include <vector>

namespace game2048 {
	static std::string number_repr(uint8_t repr_number) {
		if (repr_number == 0) { return "    "; }
		const unsigned int number = 1 << repr_number;
		std::string repr = std::to_string(number);
		if (number < 10) { return "  " + repr + " "; }
		else if (number < 100) { return " " + repr + " "; }
		else if (number < 1000) { return " " + repr; }
		else { return repr; }
	}
}

using namespace game2048;

Game::Game() {
	for (uint8_t i = 0; i < CELLS_AT_START; i++) { this->spawn_number(); }
}

uint8_t* Game::get_random_empty_cell() {
	std::vector<uint8_t*> empty_cells;
	for (Line& line: this->board) {
		for (uint8_t& element: line) {
			if (element == 0) {
				empty_cells.emplace_back(&element);
			}
		}
	}
	if (empty_cells.empty()) { return nullptr; }
	return empty_cells[arc4random() % empty_cells.size()];
}

int Game::spawn_number() {
	uint8_t* cell = this->get_random_empty_cell();
	if (cell == nullptr) { return 1; }
	uint8_t number = arc4random() < UINT32_MAX * SPAWN_CHANCE_4 ? 2 : 1;
	*cell = number;
	long index = cell - this->board.at(0).begin();
	this->current_turn_actions.emplace_back(index, index, false, number);
	return 0;
}

void Game::merge_on_line(uint8_t line_index) {
	auto& line = this->rotated_board.at(line_index);
	uint8_t active = 0;
	uint8_t x;
	for (uint8_t i = 0; i < MAX_SIZE; i++) {
		if (*line[i] == active && active != 0) {
			*line[x] = 0;
			*line[i] = active + 1;
			this->score += 1 << (active + 1);
			this->current_turn_actions.emplace_back(to_index(line[x]), to_index(line[i]), true, NULL);
			active = 0;
		} else {
			if (*line[i] != 0) {
				active = *line[i];
				x = i;
			}
		}
	}
}

void Game::move_line_left(uint8_t line_index) {
	auto& line = this->rotated_board.at(line_index);
	uint8_t index = 0;
	for (uint8_t i = 0; i < MAX_SIZE; i++) {
		if (*line[i] != 0){
			if (i != index) {
				this->current_turn_actions.emplace_back(to_index(line[i]), to_index(line[index]), false, NULL);
			}
			*line[index++] = *line[i];
		}
	}
	while (index < MAX_SIZE) {
		*line[index++] = 0;
	}
}

void Game::move_left() {
	for (uint8_t i = 0; i < MAX_SIZE; i++) {
		this->merge_on_line(i);
		this->move_line_left(i);
	}
}

void Game::rotate() {
	uint8_t i, j;
	uint8_t* tmp;
	auto& matrix = this->rotated_board;
	for (i = 0; i < MAX_SIZE / 2; i++) {
		for (j = i; j < static_cast<uint8_t>(MAX_SIZE - i - 1); j++) {
			tmp = matrix[i][j];
			matrix[i][j] = matrix[j][MAX_SIZE - i - 1];
			matrix[j][MAX_SIZE - i - 1] = matrix[MAX_SIZE - i - 1][MAX_SIZE - j - 1];
			matrix[MAX_SIZE - i - 1][MAX_SIZE - j - 1] = matrix[MAX_SIZE - j - 1][i];
			matrix[MAX_SIZE - j - 1][i] = tmp;
		}
	}
}

void Game::reset_rotation() {
	uint8_t* start = this->board.at(0).begin();
	uint8_t** rotated_start = this->rotated_board.at(0).begin();
	for (uint8_t i = 0; i < MAX_SIZE * MAX_SIZE; i++) {
		*(rotated_start + i) = start + i;
	}
}

std::vector<GameAction> Game::move(Direction dir) {
	this->current_turn_actions.clear();
	this->reset_rotation();
	switch (dir) {
		case Direction::up:
			this->rotate();
			this->move_left();
			break;
		case Direction::right:
			this->rotate();
			this->rotate();
			this->move_left();
			break;
		case Direction::down:
			this->rotate();
			this->rotate();
			this->rotate();
			this->move_left();
			break;
		case Direction::left:
			this->move_left();
			break;
		default:
			return {};
	}
	if (!this->current_turn_actions.empty()) { this->spawn_number(); }
	return this->current_turn_actions;
}

void Game::print_board() const {
	static constexpr uint8_t OUTPUT_LENGTH = 5 * MAX_SIZE + 1;
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

const Board& Game::get_board() const { return this->board; }
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

long Game::to_index(const uint8_t* pointer) const { return pointer - &this->board[0][0]; }
