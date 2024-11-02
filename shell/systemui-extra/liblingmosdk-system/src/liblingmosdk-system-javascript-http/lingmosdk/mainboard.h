/*
 * liblingmosdk-system's Library
 *
 * Copyright (C) 2023, KylinSoft Co., Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: Yunhe Liu <liuyunhe@kylinos.cn>
 *
 */

#ifndef MAINBOARD_H
#define MAINBOARD_H

#include <QWidget>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDebug>
#include <QDBusReply>
#include <QJsonArray>
#include <QJsonObject>
#include "lingmosdkdbus.h"

class Mainboard : public QWidget
{
    Q_OBJECT
public:
    explicit Mainboard(QWidget *parent = nullptr);
    Mainboard(QString urlPath);
    int dbusConnect;
    Kysdkdbus kdbus;
    QString ServerName ;
    QString ServerInterface;
    QString ServerPath;
    QJsonObject deal_mainboard();
    QJsonObject deal_mainboard_path();
private:
    QStringList path_list;
    QString path;

public slots:
    QString getMainboardName();
    QString getMainboardDate();
    QString getMainboardSerial();
    QString getMainboardVendor();

signals:

};

#endif // MAINBOARD_H