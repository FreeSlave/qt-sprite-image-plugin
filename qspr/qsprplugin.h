/* Copyright (C) 2015 Roman Chistokhodov <freeslave93@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License (LGPL) as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/

#ifndef QSPRPLUGIN_H
#define QSPRPLUGIN_H

#include <QImageIOPlugin>


class QSprPlugin : public QImageIOPlugin
{
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QImageIOHandlerFactoryInterface" FILE "qspr.json")
#endif // QT_VERSION >= 0x050000

public:
    QSprPlugin(QObject *parent = 0);
    QImageIOHandler* create(QIODevice* device, const QByteArray& format = QByteArray()) const;
    Capabilities capabilities(QIODevice *device, const QByteArray &format) const;
#if QT_VERSION < 0x050000
    QStringList keys() const;
#endif
};

#endif // QSPRPLUGIN_H
