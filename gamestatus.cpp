#include "gamestatus.h"

GameStatus::GameStatus()
{

}

void GameStatus::setStatus(Game::GameId gameId, GameStatus::Status status)
{
    this->gameStatus[gameId] = status;
}

GameStatus::Status GameStatus::status(Game::GameId gameId)
{
    return this->gameStatus[gameId];
}
