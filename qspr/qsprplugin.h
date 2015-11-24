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
