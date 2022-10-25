/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     zhangsheng<zhangsheng@uniontech.com>
 *
 * Maintainer: max-lv<lvwujun@uniontech.com>
 *             lanxuesong<lanxuesong@uniontech.com>
 *             xushitong<xushitong@uniontech.com>
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
#ifndef OPTICAL_H
#define OPTICAL_H

#include "dfmplugin_optical_global.h"

#include <dfm-framework/dpf.h>

namespace dfmplugin_optical {

class Optical : public dpf::Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.deepin.plugin.filemanager" FILE "optical.json")

public:
    virtual void initialize() override;
    virtual bool start() override;

private:
    void addOpticalCrumbToTitleBar();
    void addFileOperations();
    void addCustomTopWidget();
    void addDelegateSettings();
    void addPropertySettings();

private:
    void bindEvents();

private slots:
    void onDeviceChanged(const QString &id);
};

}

#endif   // OPTICAL_H
