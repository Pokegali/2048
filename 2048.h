#ifndef INC_2048_2048_H
#define INC_2048_2048_H

#include <cstdint>
#include <vector>

namespace game2048
{
// move me to cpp file
constexpr auto spawnChance4{.25};
constexpr uint8_t cellAtStart{2};

typedef std::vector<uint8_t> Board;
enum class Direction
{
    up,
    right,
    down,
    left
};

struct GameAction
{
    uint8_t start_index;
    uint8_t end_index;
    bool merged;
    uint8_t spawned_number;
};

class Game
{
public:
    explicit Game(uint8_t size);
    std::vector<GameAction> move(Direction, bool spawn= true);
    bool can_move() const;
    const Board& get_board() const;
    uint8_t get_size() const;
    unsigned int get_score() const;
    void print_board() const;
    void reset();
    void set_board(const Board& new_board);
    uint8_t to_index(const uint8_t* pointer) const;

private:
    Board board{};
    std::vector<uint8_t*> rotated_board{};
    unsigned int score= 0;
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
} // namespace game2048

#endif // INC_2048_2048_H
