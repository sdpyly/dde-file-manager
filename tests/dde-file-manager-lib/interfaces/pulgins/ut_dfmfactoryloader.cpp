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
#include <QDir>
#include <QStringList>
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include <QObject>
#include <qpluginloader.h>
#include <QJsonObject>

#include "plugins/dfmfilepreviewplugin.h"
#include "stub.h"
#include "interfaces/dfmbaseview.h"
#include "plugins/dfmviewplugin.h"

#define private public
#define protected public
#include "interfaces/plugins/dfmfactoryloader.h"
#include "interfaces/plugins/private/dfmfactoryloader_p.h"

DFM_USE_NAMESPACE

namespace  {
    class TestDFMFactoryLoader : public testing::Test
    {
    public:
        void SetUp() override
        {
            m_pTester = new DFMFactoryLoader("com.deepin.filemanager.DFMFileControllerFactoryInterface_iid",
                                             "/controllers",
                                             Qt::CaseInsensitive,
                                             false);
            std::cout << "start TestDFMFactoryLoader";
        }
        void TearDown() override
        {
            if(m_pTester)
                delete  m_pTester;
            std::cout << "end TestDFMFactoryLoader";
        }
    public:
        DFMFactoryLoader *m_pTester;
    };
}

TEST_F(TestDFMFactoryLoader, testInit)
{
    EXPECT_NE(m_pTester, nullptr);
}

TEST_F(TestDFMFactoryLoader, testMetaData)
{
    QList<QPluginLoader *> lst;
    QPluginLoader* pload = new QPluginLoader("/file1");
    lst << pload;
    m_pTester->d_func()->pluginLoaderList = lst;
    QList<QJsonObject> lst1 = m_pTester->metaData();
    EXPECT_EQ(lst1.count(), 1);

}

TEST_F(TestDFMFactoryLoader, testInstance)
{
    QObject* pobject = m_pTester->instance(0);
    EXPECT_EQ(pobject, nullptr);
}

TEST_F(TestDFMFactoryLoader, testInstance2)
{
    QObject* pobject = m_pTester->instance(-1);
    EXPECT_EQ(pobject, nullptr);
}

TEST_F(TestDFMFactoryLoader, testInstance3)
{
    QList<QPluginLoader *> lst;
    QPluginLoader* pload = new QPluginLoader("/file1");
    lst << pload;
    m_pTester->d_func()->pluginLoaderList = lst;

    QObject*(*stub_instance)() = []()->QObject*{
        return (new QObject());
    };
    Stub stu;
    stu.set(ADDR(QPluginLoader, instance), stub_instance);

    QObject* pobject = m_pTester->instance(0);
    EXPECT_NE(pobject, nullptr);
}

#if defined(Q_OS_UNIX) && !defined (Q_OS_MAC)
TEST_F(TestDFMFactoryLoader, testPluginLoader)
{
    QPluginLoader *pObject = m_pTester->pluginLoader("video/*");
    EXPECT_EQ(pObject, nullptr);
}

TEST_F(TestDFMFactoryLoader, testPluginLoaderList)
{
    QList<QPluginLoader *> lst = m_pTester->pluginLoaderList("video/*");
    EXPECT_EQ(lst.count(), 0);
}
#endif

TEST_F(TestDFMFactoryLoader, testKeyMap)
{
    QList<QPluginLoader *> lst;
    QPluginLoader* pload = new QPluginLoader("/file1");
    lst << pload;
    m_pTester->d_func()->pluginLoaderList = lst;

    QJsonArray(*stub_toArray)() = []()->QJsonArray{
        QJsonArray arry;
        arry.insert(0, QJsonValue("0"));
        arry.insert(1, QJsonValue("1"));
        return  arry;

    };
    Stub stu;
    stu.set((QJsonArray(QJsonValue::*)()const)ADDR(QJsonValue, toArray), stub_toArray);

    QMultiMap<int, QString> map = m_pTester->keyMap();
    EXPECT_EQ(map.count(), 2);
}

TEST_F(TestDFMFactoryLoader, testIndexOf)
{
    QList<QPluginLoader *> lst;
    QPluginLoader* pload = new QPluginLoader("video/*");
    lst << pload;
    m_pTester->d_func()->pluginLoaderList = lst;

    QJsonArray(*stub_toArray)() = []()->QJsonArray{
        QJsonArray arry;
        arry.insert(0, QJsonValue("0"));
        arry.insert(1, QJsonValue("video/*"));
        return  arry;

    };
    Stub stu;
    stu.set((QJsonArray(QJsonValue::*)()const)ADDR(QJsonValue, toArray), stub_toArray);

    int r = m_pTester->indexOf("video/*");
    EXPECT_EQ(r, 0);
}

TEST_F(TestDFMFactoryLoader, testGetAllIndexByKey)
{
    QList<QPluginLoader *> lst;
    QPluginLoader* pload = new QPluginLoader("video/*");
    lst << pload;
    m_pTester->d_func()->pluginLoaderList = lst;

    QJsonArray(*stub_toArray)() = []()->QJsonArray{
        QJsonArray arry;
        arry.insert(0, QJsonValue("0"));
        arry.insert(1, QJsonValue("video/*"));
        return  arry;

    };
    Stub stu;
    stu.set((QJsonArray(QJsonValue::*)()const)ADDR(QJsonValue, toArray), stub_toArray);

    QList<int> lst1 = m_pTester->getAllIndexByKey("video/*");
    EXPECT_EQ(lst.count(), 1);
}

TEST_F(TestDFMFactoryLoader, testUpdate)
{
    bool(*stub2_contains)(const QString &, Qt::CaseSensitivity) = [](const QString &, Qt::CaseSensitivity)->bool{
        return false;
    };

    Stub stub2;
    stub2.set((bool(QStringList::*)(const QString &str, Qt::CaseSensitivity cs)const)ADDR(QStringList, contains), stub2_contains);

    bool(*stub_exists)(const QString&) = [](const QString&)->bool{
        return true;
    };

    Stub stub;
    stub.set((bool(QDir::*)(const QString&)const) ADDR(QDir, exists), stub_exists);

    QStringList(*stub3_entryList)(QDir::Filters, QDir::SortFlags) = [](QDir::Filters, QDir::SortFlags)->QStringList{
        QStringList lst;
        lst << "libdde-image-preview-plugin.so"
            << "libdde-music-preview-plugin.so"
            << "libdde-pdf-preview-plugin.so"
            << "libdde-text-preview-plugin.so"
            << "libdde-video-preview-plugin.so";
        return lst;
    };

    Stub stub3;
    stub3.set((QStringList(QDir::*)(QDir::Filters, QDir::SortFlags)const)ADDR(QDir, entryList), stub3_entryList);

    EXPECT_NO_FATAL_FAILURE(m_pTester->update());
}

TEST_F(TestDFMFactoryLoader, testUpdate2)
{
    bool(*stub_isRootUser)() = []()->bool{
        return true;
    };
    Stub stu;
    stu.set(ADDR(DFMGlobal, isRootUser), stub_isRootUser);

    EXPECT_NO_FATAL_FAILURE(m_pTester->update());
}

TEST_F(TestDFMFactoryLoader, testUpdate3)
{
    bool(*stub2_contains)(const QString &, Qt::CaseSensitivity) = [](const QString &, Qt::CaseSensitivity)->bool{
        return true;
    };

    Stub stub2;
    stub2.set((bool(QStringList::*)(const QString &str, Qt::CaseSensitivity cs)const)ADDR(QStringList, contains), stub2_contains);

    EXPECT_NO_FATAL_FAILURE(m_pTester->update());
}

TEST_F(TestDFMFactoryLoader, testUpdate4)
{
    bool(*stub2_contains)(const QString &, Qt::CaseSensitivity) = [](const QString &, Qt::CaseSensitivity)->bool{
        return false;
    };

    Stub stub2;
    stub2.set((bool(QStringList::*)(const QString &str, Qt::CaseSensitivity cs)const)ADDR(QStringList, contains), stub2_contains);

    bool(*stub_exists)(const QString&) = [](const QString&)->bool{
        return true;
    };

    Stub stub;
    stub.set((bool(QDir::*)(const QString&)const) ADDR(QDir, exists), stub_exists);

    QStringList(*stub3_entryList)(QDir::Filters, QDir::SortFlags) = [](QDir::Filters, QDir::SortFlags)->QStringList{
        QStringList lst;
        lst << "libdde-image-preview-plugin.so"
            << "libdde-music-preview-plugin.so"
            << "libdde-pdf-preview-plugin.so"
            << "libdde-text-preview-plugin.so"
            << "libdde-video-preview-plugin.so";
        return lst;
    };

    Stub stub3;
    stub3.set((QStringList(QDir::*)(QDir::Filters, QDir::SortFlags)const)ADDR(QDir, entryList), stub3_entryList);

    bool(*stub_load)() = []()->bool{
        return true;
    };
    Stub stub4;
    stub4.set(ADDR(QPluginLoader, load), stub_load);

    QString(*stub_toString)() = []()->QString{
        return QString("com.deepin.filemanager.DFMFileControllerFactoryInterface_iid");
    };
    Stub stub5;
    stub5.set((QString(QJsonValue::*)()const)ADDR(QJsonValue, toString), stub_toString);

    int(*stub_size)() = []()->int{
        return 1;
    };
    Stub stub6;
    stub6.set(ADDR(QJsonArray, size), stub_size);

    EXPECT_NO_FATAL_FAILURE(m_pTester->update());
}

TEST_F(TestDFMFactoryLoader, testRefreshAll)
{
    void(*stub_update)() = [](){

    };
    Stub stu;
    stu.set(ADDR(DFMFactoryLoader, update), stub_update);
    EXPECT_NO_FATAL_FAILURE(m_pTester->refreshAll());
}

TEST_F(TestDFMFactoryLoader, testDLoadPlugin)
{
    DFMFactoryLoader* ploader = new DFMFactoryLoader("com.deepin.filemanager.DFMFileControllerFactoryInterface_iid",
                                                    "/controllers",
                                                    Qt::CaseInsensitive,
                                                    false);
    QList<QPluginLoader *> lst;
    QPluginLoader* pload = new QPluginLoader("video/*");
    lst << pload;
    ploader->d_func()->pluginLoaderList = lst;

    QJsonArray(*stub_toArray)() = []()->QJsonArray{
        QJsonArray arry;
        arry.insert(0, QJsonValue("0"));
        arry.insert(1, QJsonValue("video/*"));
        return  arry;

    };
    Stub stu;
    stu.set((QJsonArray(QJsonValue::*)()const)ADDR(QJsonValue, toArray), stub_toArray);

    QString key("video/*");
    DFMBaseView* pview = dLoadPlugin<DFMBaseView, DFMViewPlugin>(ploader, key);
    EXPECT_EQ(pview, nullptr);
}

TEST_F(TestDFMFactoryLoader, testDLoadPluginList)
{
    DFMFactoryLoader* ploader = new DFMFactoryLoader("com.deepin.filemanager.DFMFileControllerFactoryInterface_iid",
                                                    "/controllers",
                                                    Qt::CaseInsensitive,
                                                    false);

    QList<QPluginLoader *> lst;
    QPluginLoader* pload = new QPluginLoader("video/*");
    lst << pload;
    ploader->d_func()->pluginLoaderList = lst;

    QJsonArray(*stub_toArray)() = []()->QJsonArray{
        QJsonArray arry;
        arry.insert(0, QJsonValue("0"));
        arry.insert(1, QJsonValue("video/*"));
        return  arry;

    };
    Stub stu;
    stu.set((QJsonArray(QJsonValue::*)()const)ADDR(QJsonValue, toArray), stub_toArray);

    QList<DFMBaseView*> lst2 = dLoadPluginList<DFMBaseView, DFMViewPlugin>(ploader, "video/*");
    EXPECT_EQ(lst.count(), 1);
}
