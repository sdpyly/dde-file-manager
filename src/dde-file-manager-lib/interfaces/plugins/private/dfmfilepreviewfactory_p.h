/*
 * Copyright (C) 2016 ~ 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     gongheng<gongheng@uniontech.com>
 *
 * Maintainer: zhengyouge<zhengyouge@uniontech.com>
 *             gongheng<gongheng@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DFMFILEPREVIEWFACTORY_P_H
#define DFMFILEPREVIEWFACTORY_P_H

#include <QMap>

#include "dfmglobal.h"

DFM_BEGIN_NAMESPACE

class DFMFilePreview;
class DFMFilePreviewFactoryPrivate
{
public:
    static QMap<const DFMFilePreview*, int> previewToLoaderIndex;
};

DFM_END_NAMESPACE

#endif // DFMFILEPREVIEWFACTORY_P_H
