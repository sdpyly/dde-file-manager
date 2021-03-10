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
*/

#include <gtest/gtest.h>

#include "interfaces/plugins/dfmfilecontrollerfactory.h"

DFM_USE_NAMESPACE

namespace  {
    class TestDFMFileControllerFactory : public testing::Test
    {
    public:
        void SetUp() override
        {
            std::cout << "start TestDFMFileControllerFactory";
        }
        void TearDown() override
        {
            std::cout << "end TestDFMFileControllerFactory";
        }
    public:
    };
}

TEST_F(TestDFMFileControllerFactory, testCreate)
{
    DAbstractFileController *pr = DFMFileControllerFactory::create("video/*");
    EXPECT_EQ(pr, nullptr);
}

TEST_F(TestDFMFileControllerFactory, testKeys)
{
    QStringList lst = DFMFileControllerFactory::keys();
    EXPECT_EQ(lst.count(), 0);
}
