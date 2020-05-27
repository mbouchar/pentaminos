/* Copyright (C) Mathieu Bouchard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "settings.h"

#include <QMetaEnum>

Settings::Settings()
{
}

QSettings* Settings::settings()
{
    QSettings *settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "Mathieu Bouchard", "Pentaminos");
    return settings;
}

QString Settings::statusToString(GameStatus::Status status)
{
    const auto metaEnum = QMetaEnum::fromType<GameStatus::Status>();
    return metaEnum.valueToKey(static_cast<int>(status));
}

GameStatus::Status Settings::statusFromString(QString statusText)
{
    const auto metaEnum = QMetaEnum::fromType<GameStatus::Status>();
    bool ok;
    int value = metaEnum.keyToValue(statusText.toStdString().c_str(), &ok);
    if (ok) {
        return (GameStatus::Status) value;
    } else {
        return GameStatus::NeverTried;
    }
}

void Settings::saveGame(GameStatus *gameStatus)
{
    QSettings *settings = Settings::settings();

    settings->beginGroup("Pentaminos");
    settings->setValue("4A", statusToString(gameStatus->status(Game::Pentamino4A)));
    settings->setValue("4B", statusToString(gameStatus->status(Game::Pentamino4B)));
    settings->setValue("4C", statusToString(gameStatus->status(Game::Pentamino4C)));
    settings->setValue("4D", statusToString(gameStatus->status(Game::Pentamino4D)));
    settings->setValue("4E", statusToString(gameStatus->status(Game::Pentamino4E)));
    settings->setValue("4F", statusToString(gameStatus->status(Game::Pentamino4F)));
    settings->setValue("4G", statusToString(gameStatus->status(Game::Pentamino4G)));
    settings->setValue("4H", statusToString(gameStatus->status(Game::Pentamino4H)));
    settings->setValue("4I", statusToString(gameStatus->status(Game::Pentamino4I)));
    settings->setValue("4J", statusToString(gameStatus->status(Game::Pentamino4J)));
    settings->setValue("4K", statusToString(gameStatus->status(Game::Pentamino4K)));
    settings->setValue("4L", statusToString(gameStatus->status(Game::Pentamino4L)));
    settings->setValue("5A", statusToString(gameStatus->status(Game::Pentamino5A)));
    settings->setValue("5B", statusToString(gameStatus->status(Game::Pentamino5B)));
    settings->setValue("5C", statusToString(gameStatus->status(Game::Pentamino5C)));
    settings->setValue("5D", statusToString(gameStatus->status(Game::Pentamino5D)));
    settings->setValue("5E", statusToString(gameStatus->status(Game::Pentamino5E)));
    settings->setValue("5F", statusToString(gameStatus->status(Game::Pentamino5F)));
    settings->setValue("5G", statusToString(gameStatus->status(Game::Pentamino5G)));
    settings->setValue("5H", statusToString(gameStatus->status(Game::Pentamino5H)));
    settings->setValue("12", statusToString(gameStatus->status(Game::Pentamino12)));
    settings->endGroup();

    settings->sync();
    delete settings;
}

GameStatus* Settings::loadGame()
{
    QSettings *settings = Settings::settings();

    GameStatus *status = new GameStatus();
    QString neverTried = Settings::statusToString(GameStatus::NeverTried);

    settings->beginGroup("Pentaminos");
    status->setStatus(Game::Pentamino4A, Settings::statusFromString(settings->value("4A", neverTried).toString()));
    status->setStatus(Game::Pentamino4B, Settings::statusFromString(settings->value("4B", neverTried).toString()));
    status->setStatus(Game::Pentamino4C, Settings::statusFromString(settings->value("4C", neverTried).toString()));
    status->setStatus(Game::Pentamino4D, Settings::statusFromString(settings->value("4D", neverTried).toString()));
    status->setStatus(Game::Pentamino4E, Settings::statusFromString(settings->value("4E", neverTried).toString()));
    status->setStatus(Game::Pentamino4F, Settings::statusFromString(settings->value("4F", neverTried).toString()));
    status->setStatus(Game::Pentamino4G, Settings::statusFromString(settings->value("4G", neverTried).toString()));
    status->setStatus(Game::Pentamino4H, Settings::statusFromString(settings->value("4H", neverTried).toString()));
    status->setStatus(Game::Pentamino4I, Settings::statusFromString(settings->value("4I", neverTried).toString()));
    status->setStatus(Game::Pentamino4J, Settings::statusFromString(settings->value("4J", neverTried).toString()));
    status->setStatus(Game::Pentamino4K, Settings::statusFromString(settings->value("4K", neverTried).toString()));
    status->setStatus(Game::Pentamino4L, Settings::statusFromString(settings->value("4L", neverTried).toString()));
    status->setStatus(Game::Pentamino5A, Settings::statusFromString(settings->value("5A", neverTried).toString()));
    status->setStatus(Game::Pentamino5B, Settings::statusFromString(settings->value("5B", neverTried).toString()));
    status->setStatus(Game::Pentamino5C, Settings::statusFromString(settings->value("5C", neverTried).toString()));
    status->setStatus(Game::Pentamino5D, Settings::statusFromString(settings->value("5D", neverTried).toString()));
    status->setStatus(Game::Pentamino5E, Settings::statusFromString(settings->value("5E", neverTried).toString()));
    status->setStatus(Game::Pentamino5F, Settings::statusFromString(settings->value("5F", neverTried).toString()));
    status->setStatus(Game::Pentamino5G, Settings::statusFromString(settings->value("5G", neverTried).toString()));
    status->setStatus(Game::Pentamino5H, Settings::statusFromString(settings->value("5H", neverTried).toString()));
    status->setStatus(Game::Pentamino12, Settings::statusFromString(settings->value("12", neverTried).toString()));
    settings->endGroup();

    delete settings;

    return status;
}
