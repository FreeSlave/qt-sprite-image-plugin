/* Copyright (C) 2015 Roman Chistokhodov <freeslave93@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License (LGPL) as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/

#include "qsprplugin.h"
#include "qsprhandler.h"

QSprPlugin::QSprPlugin(QObject *parent) :
    QImageIOPlugin(parent)
{
}

QImageIOHandler* QSprPlugin::create(QIODevice *device, const QByteArray &format) const
{
    QImageIOHandler *handler = new QSprHandler;
    handler->setDevice(device);
    handler->setFormat(format);
    return handler;
}

QImageIOPlugin::Capabilities QSprPlugin::capabilities(QIODevice *device, const QByteArray &format) const
{
    if (format == "spr" || format == "SPR")
        return Capabilities(CanRead|CanWrite);
    if (!format.isEmpty())
        return 0;
    if (!device->isOpen())
        return 0;

    Capabilities cap = 0;
    if (device->isReadable() && QSprHandler::canRead(device)) {
        cap |= CanRead;
    }
    if (device->isWritable()) {
        cap |= CanWrite;
    }
    return cap;
}

#if QT_VERSION < 0x050000
QStringList QSprPlugin::keys() const
{
    return QStringList() << "spr";
}
#endif

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qspr, QSprPlugin)
#endif // QT_VERSION < 0x050000
