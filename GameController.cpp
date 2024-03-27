#include "GameController.h"

namespace constants
{
constexpr auto maxGameSize{8};
constexpr auto MinGameSize{2};
} // namespace constants

GameController::GameController(QObject* parent) : QObject(parent)
{
    this->reset();
}

void GameController::setGameSize(quint8 gameSize)
{
    if(gameSize > constants::maxGameSize || gameSize < constants::MinGameSize)
    {
        return;
    }
    this->game= game2048::Game(gameSize);
    emit gameSizeChanged();
    this->reset();
}

void GameController::move(const Direction towards)
{
    std::vector<game2048::GameAction> moveResult= this->game.move(directionToGameDirection(towards));
    for(const auto& action : moveResult)
    {
        if(action.merged)
        {
            this->board.startRemove(action.start_index);
            this->board.edit(action.end_index, action.end_index, true);
        }
        else if(action.spawned_number)
        {
            this->board.append({action.start_index, action.spawned_number, false});
        }
        else
        {
            this->board.edit(action.start_index, action.end_index, false);
        }
    }
    emit scoreChanged();
}

void GameController::reset()
{
    this->game.reset();
    this->board.reset();
    for(const auto& x : this->game.get_board())
    {
        if(x == 0)
        {
            continue;
        }
        this->board.append({this->game.to_index(&x), x, false});
    }
    emit scoreChanged();
}

quint32 GameController::getScore() const
{
    return this->game.get_score();
}

BoardModel* GameController::getBoard()
{
    return &board;
}
bool GameController::isInGame() const
{
    return this->inGame;
}
quint8 GameController::getGameSize() const
{
    return this->game.get_size();
}

void GameController::setInGame(bool status)
{
    if(status == this->inGame)
    {
        return;
    }
    this->inGame= status;
    emit inGameChanged();
}

game2048::Direction GameController::directionToGameDirection(Direction direction)
{
    switch(direction)
    {
    case Direction::up:
        return game2048::Direction::up;
    case Direction::down:
        return game2048::Direction::down;
    case Direction::right:
        return game2048::Direction::right;
    case Direction::left:
        return game2048::Direction::left;
    default:
        throw std::invalid_argument("Invalid argument for direction.");
    }
}
bool GameController::canMove()
{
    return this->game.can_move();
}

void GameController::deleteTileAt(quint8 index)
{
    this->board.remove(index);
}
