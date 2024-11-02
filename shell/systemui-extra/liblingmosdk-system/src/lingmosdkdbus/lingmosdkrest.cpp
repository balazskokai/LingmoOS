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

#include "lingmosdkrest.h"
#include "../systeminfo/libkysysinfo.h" // 分辨率

KySdkRest::KySdkRest(QObject *parent) : QObject(parent)
{

}
QStringList KySdkRest::getSysLegalResolution() const
{
    QStringList res = {};
    char **power = kdk_system_get_resolving_power();
    size_t count = 0;
    while(power[count])
    {
        res << QString::fromLocal8Bit(power[count]);
        count ++;
    }
    kdk_resolving_freeall(power);
    return res;
}