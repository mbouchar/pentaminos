#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include <QMap>
#include <QString>
#include <QObject>

#include "game.h"

class GameStatus : public QObject
{
    Q_OBJECT

public:
    enum Status { NeverTried, Tried, Won };
    Q_ENUM(Status)

    GameStatus();

    void setStatus(Game::GameId gameId, Status status);
    Status status(Game::GameId gameId);

private:
    QMap<Game::GameId, Status> gameStatus;
};

#endif // GAMESTATUS_H
