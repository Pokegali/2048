#include "2048.h"

#include <iostream>
#include <string>
#include <vector>
#include <random>

inline constexpr uint8_t operator "" _ui8(unsigned long long arg) noexcept {
	return static_cast<uint8_t>(arg);
}

namespace game2048
{
static std::string number_repr(uint8_t repr_number)
{
    if(repr_number == 0)
    {
        return "    ";
    }
    const unsigned int number= 1 << repr_number;
    std::string repr= std::to_string(number);
    if(number < 10)
    {
        return "  " + repr + " ";
    }
    else if(number < 100)
    {
        return " " + repr + " ";
    }
    else if(number < 1000)
    {
        return " " + repr;
    }
    else
    {
        return repr;
    }
}
} // namespace game2048

using namespace game2048;

static std::random_device random_device;
static std::mt19937 rng(random_device());

Game::Game(uint8_t size) : size(size)
{
    this->rotated_board.resize(size * size);
    this->board.resize(size * size);
    for(uint8_t i= 0; i < CELLS_AT_START; i++)
    {
        this->spawn_number();
    }
}

uint8_t* Game::get_random_empty_cell()
{
    std::vector<uint8_t*> empty_cells;
    for(uint8_t& element : this->board)
    {
        if(element == 0)
        {
            empty_cells.emplace_back(&element);
        }
    }
    if(empty_cells.empty())
    {
        return nullptr;
    }
    std::uniform_int_distribution<unsigned long> distribution(0, empty_cells.size() - 1);
    return empty_cells[distribution(rng)];
}

int Game::spawn_number() {
	uint8_t* cell = this->get_random_empty_cell();
	if (cell == nullptr) { return 1; }
	static std::bernoulli_distribution spawn_4(SPAWN_CHANCE_4);
	uint8_t number = spawn_4(rng) ? 2 : 1;
	*cell = number;
	uint8_t index = this->to_index(cell);
	this->current_turn_actions.emplace_back() = {index, index, false, number};
	return 0;
}

void Game::merge_on_line(uint8_t line_index) {
	uint8_t** line_start = &*this->rotated_board.begin() + this->size * line_index;
	uint8_t** line_end = line_start + this->size;
	uint8_t active = 0;
	uint8_t** x;
	for (uint8_t** pointer = line_start; pointer < line_end; pointer++) {
		if (**pointer == active && active != 0) {
			**x = 0;
			**pointer = active + 1;
			this->score += 1 << (active + 1);
			this->current_turn_actions.emplace_back() = {this->to_index(*x), this->to_index(*pointer), true, 0_ui8};
			active = 0;
		} else {
			if (**pointer != 0) {
				active = **pointer;
				x = pointer;
			}
		}
	}
}

void Game::move_line_left(uint8_t line_index) {
	uint8_t** line_start = &*this->rotated_board.begin() + this->size * line_index;
	uint8_t** line_end = line_start + this->size;
	uint8_t** current_index = line_start;
	for (uint8_t** pointer = line_start; pointer < line_end; pointer++) {
		if (**pointer != 0) {
			if (pointer != current_index) {
				this->current_turn_actions.emplace_back() = {this->to_index(*pointer), this->to_index(*current_index), false, 0_ui8};
			}
			**(current_index++) = **pointer;
		}
	}
	while (current_index < line_end) {
		**(current_index++) = 0;
	}
}

void Game::merge_on_line(uint8_t line_index)
{
    uint8_t** line_start= &*this->rotated_board.begin() + this->size * line_index;
    uint8_t** line_end= line_start + this->size;
    uint8_t active= 0;
    uint8_t** x;
    for(uint8_t** pointer= line_start; pointer < line_end; pointer++)
    {
        if(**pointer == active && active != 0)
        {
            **x= 0;
            **pointer= active + 1;
            this->score+= 1 << (active + 1);
            this->current_turn_actions.emplace_back(this->to_index(*x), this->to_index(*pointer), true, NULL);
            active= 0;
        }
        else
        {
            if(**pointer != 0)
            {
                active= **pointer;
                x= pointer;
            }
        }
    }
}

void Game::move_line_left(uint8_t line_index)
{
    uint8_t** line_start= &*this->rotated_board.begin() + this->size * line_index;
    uint8_t** line_end= line_start + this->size;
    uint8_t** current_index= line_start;
    for(uint8_t** pointer= line_start; pointer < line_end; pointer++)
    {
        if(**pointer != 0)
        {
            if(pointer != current_index)
            {
                this->current_turn_actions.emplace_back(this->to_index(*pointer), this->to_index(*current_index), false,
                                                        NULL);
            }
            **(current_index++)= **pointer;
        }
    }
    while(current_index < line_end)
    {
        **(current_index++)= 0;
    }
>>>>>>> 11345e2 (update)
}

void Game::move_left()
{
    for(uint8_t i= 0; i < this->size; i++)
    {
        this->merge_on_line(i);
        this->move_line_left(i);
    }
}

void Game::rotate()
{
    unsigned int i, j;
    uint8_t* tmp;
    auto& matrix= this->rotated_board;
    for(i= 0; i < this->size / 2; i++)
    {
        for(j= i; j < static_cast<uint8_t>(this->size - i - 1); j++)
        {
            tmp= matrix[i * this->size + j];
            matrix[i * this->size + j]= matrix[(j + 1) * this->size - i - 1];
            matrix[(j + 1) * this->size - i - 1]= matrix[(this->size - i) * this->size - j - 1];
            matrix[(this->size - i) * this->size - j - 1]= matrix[(this->size - j - 1) * this->size + i];
            matrix[(this->size - j - 1) * this->size + i]= tmp;
        }
    }
}

void Game::reset_rotation()
{
    uint8_t* start= &*this->board.begin();
    uint8_t** rotated_start= &*this->rotated_board.begin();
    for(uint8_t i= 0; i < this->size * this->size; i++)
    {
        *(rotated_start + i)= start + i;
    }
}

std::vector<GameAction> Game::move(Direction dir, bool spawn)
{
    this->current_turn_actions.clear();
    this->reset_rotation();
    switch(dir)
    {
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
    if(spawn && !this->current_turn_actions.empty())
    {
        this->spawn_number();
    }
    return this->current_turn_actions;
}

void Game::print_board() const
{
    const auto OUTPUT_LENGTH= static_cast<uint8_t>(5 * this->size + 1);
    const std::string LINE_SEPARATOR(OUTPUT_LENGTH, '-');
    std::cout << LINE_SEPARATOR << std::endl;
    for(unsigned int i= 0; i < this->size; i++)
    {
        std::cout << "|";
        for(unsigned int j= 0; j < this->size; j++)
        {
            std::cout << number_repr(this->board[i * this->size + j]) << "|";
        }
        std::cout << std::endl << LINE_SEPARATOR << std::endl;
    }
}

const Board& Game::get_board() const
{
    return this->board;
}
unsigned int Game::get_score() const
{
    return this->score;
}
uint8_t Game::get_size() const
{
    return this->size;
}

bool Game::can_move() const
{
    unsigned int i, j, current_x, current_y;
    for(i= 0; i < this->size; i++)
    {
        current_x= 0;
        current_y= 0;
        for(j= 0; j < this->size; j++)
        {
            if(this->board[i * this->size + j] == current_x || this->board[j * this->size + i] == current_y
               || !this->board[i * this->size + j])
            {
                return true;
            }
            current_x= this->board[i * this->size + j];
            current_y= this->board[j * this->size + i];
        }
    }
    return false;
}

void Game::reset()
{
    for(uint8_t& tile : this->board)
    {
        tile= 0;
    }
    this->score= 0;
    for(uint8_t i= 0; i < CELLS_AT_START; i++)
    {
        this->spawn_number();
    }
}

long Game::to_index(const uint8_t* pointer) const
{
    return pointer - &this->board[0];
}

void Game::set_board(const Board& new_board)
{
    this->board= new_board;
}
