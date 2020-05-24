#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include "gamestatus.h"

class Settings
{
public:
    static void saveGame(GameStatus *game);
    static GameStatus* loadGame();

protected:
    Settings();

    static QSettings* settings();

    static QString statusToString(GameStatus::Status status);
    static GameStatus::Status statusFromString(QString statusText);
};

#endif // SETTINGS_H
