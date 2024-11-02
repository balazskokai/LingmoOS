/*
 * Qt5-LINGMO's Library
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
 * Authors: xibowen <xibowen@kylinos.cn>
 *
 */

#ifndef TREEANIMATIONHELPER_H
#define TREEANIMATIONHELPER_H

#include <QObject>
#include "animations/animation-helper.h"

namespace LINGMOConfigStyleSpace {

class ConfigTreeAnimationHelper : public AnimationHelper
{
    Q_OBJECT
public:
    explicit ConfigTreeAnimationHelper(QObject *parent = nullptr);
    bool registerWidget(QWidget *w);
    bool unregisterWidget(QWidget *w);

    AnimatorIface *animator(const QWidget *w);

signals:

public slots:
};
}
#endif // TREEANIMATIONHELPER_H