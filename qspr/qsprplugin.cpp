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
        return Capabilities(CanRead);
    if (!format.isEmpty())
        return 0;
    if (!device->isOpen())
        return 0;

    Capabilities cap = 0;
    if (device->isReadable() && QSprHandler::canRead(device)) {
        cap |= CanRead;
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
