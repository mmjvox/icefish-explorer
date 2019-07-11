/* $Id: rfileoperator.h
 * IceFish Explorer is a free File Manager for Linux Desktops for managing
 * local files as well as files on cloud, Dropbox, Onedrive, Googledrive.
 * Additionally, it also serves as a multimedia explorer for your photos,
 * music, videos, documents and other files by providing built-in plugins
 * to open them.
 * © IceFish Community, 2019
 *
 * This file is part of IceFish Explorer.
 *
 * IceFish Explorer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * IceFish Explorer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with IceFish Explorer.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * The project is hosted here,
 * http://www.icefish.tech/index/explorer/0-5
*/

#ifndef RFILEOPERATOR_H
#define RFILEOPERATOR_H

#include <QObject>
#include <QQueue>
#include <QThread>
#include <QtCore>


class RFileOperator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> WaitingProcessList READ WaitingProcessList NOTIFY WaitingProcessListChanged)
    Q_PROPERTY(QList<QObject*> OngoingProcessList READ OngoingProcessList NOTIFY OngoingProcessListChanged)
    Q_PROPERTY(QList<QObject*> CompletedProcessList READ CompletedProcessList NOTIFY CompletedProcessListChanged)

public:
    explicit RFileOperator(QObject *parent = nullptr);

    enum OperationState{
        Ready,
        Running,
        Denied,
        Paused,
        Interrupted,
        Finished
    };
    Q_ENUM(OperationState)

    QList<QObject*> WaitingProcessList() const{ return waitingProcessList;}
    QList<QObject*> OngoingProcessList() const{ return ongoingProcessList;}
    QList<QObject*> CompletedProcessList() const{ return completedProcessList;}

signals:
    void WaitingProcessListChanged();
    void OngoingProcessListChanged();
    void CompletedProcessListChanged();
    void queueContentChanged();

public slots:
    void copyFiles(QString destinationPath);
    void moveFiles(QString destinationPath);
    void deleteFiles(QList<QObject*> fileList);
    void recoverFiles(QList<QObject*> fileList);

private:
    int runningThreadsCount;
    QQueue<QThread*> operationQueue;
    void scheduleThread();
    void resetProcessList();
    void updateCompletedList(QString path = "");

    QList<QObject*> waitingProcessList;
    QList<QObject*> ongoingProcessList;
    QList<QObject*> completedProcessList;

    QFileSystemWatcher watcher;
    QString completedOperationsFilePath;
};

Q_DECLARE_METATYPE(RFileOperator::OperationState)

#endif // RFILEOPERATOR_H
