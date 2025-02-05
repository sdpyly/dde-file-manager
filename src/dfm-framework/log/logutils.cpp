// SPDX-FileCopyrightText: 2021 - 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <dfm-framework/log/logutils.h>

#include <QDateTime>
#include <QMutex>
#include <QDebug>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

DPF_BEGIN_NAMESPACE

/*!
 * \brief checkAppCacheLogDir
 *  检查应用程序缓存日志的文件夹
 * \param subDirName 日志目录下的子目录
 *  默认为空，则检查顶层目录
 */
bool LogUtils::checkAppCacheLogDir(const QString &subDirName)
{
    QString &&cachePath { LogUtils::cachePath() };
    if (cachePath.isEmpty() || !cachePath.contains("cache"))
        return false;
    if (!QFileInfo::exists(cachePath))
        QDir().mkdir(LogUtils::cachePath());

    if (subDirName.isEmpty())
        return false;
    if (!QFileInfo::exists(cachePath + "/" + subDirName))
        return QDir().mkdir(cachePath + "/" + subDirName);

    return true;
}

/*!
 * \brief localDateTime 获取年/月/日/时间
 * \return QString 格式化字符串后的时间
 */
QString LogUtils::localDateTime()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
}

/*!
 * \brief localDate 获取年/月/日
 * \return QString 格式化字符串后的时间
 */
QString LogUtils::localDate()
{
    return QDate::currentDate().toString("yyyy-MM-dd");
}

/*!
 * \brief localDate 获取年/月/日/时间，
 *  年/月/日/与时间之间以逗号分割
 * \return QString 格式化字符串后的时间
 */
QString LogUtils::localDataTimeCSV()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd,hh:mm:ss,zzz");
}

/*!
 * \brief lastTimeStamp 获取输入时间之前指定天数时间戳，
 * 最小单位s
 * \param dateTime 时间
 * \param dayCount 向前的天数
 * \return uint 时间戳
 */
uint LogUtils::lastTimeStamp(const QDateTime &dateTime, uint dayCount)
{
    return dateTime.toTime_t() - (86400 * dayCount);
}

/*!
 * \brief lastDateTime 获取输入时间之前指定天数时间，
 * 最小单位s
 * \param dateTime 时间
 * \param dayCount 向前的天数
 * \return QDateTime 时间
 */
QDateTime LogUtils::lastDateTime(const QDateTime &dateTime, uint dayCount)
{
    return QDateTime::fromTime_t(lastTimeStamp(dateTime, dayCount));
}

/*!
 * \brief containLastDay 判断时间是否包含时间(天)范围
 * 最小单位s
 * \param src 基准时间
 * \param dst 对比时间
 * \param dayCount 往前推的天数
 * \return bool 是否包含的结果
 *
 * |------dst--------src----|
 * |------dayCount----|
 * return true;
 *
 * |-----------dst-------------src|
 *                  |-dayCount--|
 * return false
 */
bool LogUtils::containLastDay(const QDateTime &src, const QDateTime &dst, uint dayCount)
{
    uint srcStamp = src.toTime_t();
    uint dstStamp = dst.toTime_t();

    return dstStamp - (86400 * dayCount) < srcStamp && srcStamp <= dstStamp;
}

/*!
 * \brief toDayZero 获取今天的00:00:00的时间
 * \return
 */
QDateTime LogUtils::toDayZero()
{
    QDateTime dateTime;
    dateTime.setDate(QDate::currentDate());
    dateTime.setTime(QTime(0, 0, 0));
    return dateTime;
}

QString LogUtils::cachePath()
{
    return QStandardPaths::locate(QStandardPaths::CacheLocation, "", QStandardPaths::LocateDirectory);
}

DPF_END_NAMESPACE
