/* $Id: notificationmodel.cpp
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

#include "notificationmodel.h"

NotificationModel::NotificationModel(QObject *parent)
    : QObject(parent){
}

void NotificationModel::Notify(Error code){
    if(code == Error::FileAlreadyExist){
        header = "That name is already occupied";
        comment = "Please chose the suggested name or something else.";
    }
    else if(code == Error::NoPermission){
        header = "Permission Insufficient";
        comment = "You don't have required permissions to modify this thing.";
    }
    else if(code == Error::PathDoesntExist){
        header = "Unknown Path";
        comment = "File path specified was not located.";
    }
    else if(code == Error::RemovalFailed){
        header = "Removal Failed";
        comment = "Failed to remove from trash";
    }

    emit HeaderChanged();
    emit CommentChanged();
    emit showNotification();
}
