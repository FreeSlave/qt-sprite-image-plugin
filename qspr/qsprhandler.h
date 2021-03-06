/* Copyright (C) 2015 Roman Chistokhodov <freeslave93@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License (LGPL) as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/

#ifndef QSPRHANDLER_H
#define QSPRHANDLER_H

#include <QImageIOHandler>
#include <QVector>
#include <QRgb>
#include <QSize>

template<typename T>
bool readStruct(QIODevice* device, T& t)
{
    char* bytes = reinterpret_cast<char*>(&t);
    return device->read(bytes, sizeof(T)) == sizeof(T);
}

struct SpriteHeader
{
    SpriteHeader();

    int version;
    int type;
    int texFormat;
    QSize size;
    int numFrames;
};

class QSprHandler : public QImageIOHandler
{
public:
    explicit QSprHandler();
    bool canRead() const;
    int currentImageNumber() const;
    int imageCount() const;
    bool jumpToImage(int imageNumber);
    bool jumpToNextImage();
    int loopCount() const;
    int nextImageDelay() const;
    QVariant option(ImageOption option) const;
    bool read(QImage *image);
    bool supportsOption(ImageOption option) const;
    bool write(const QImage &image);

    static bool canRead(QIODevice* device, int *version = 0);

private:
    static bool readSpriteHeader(QIODevice* device, SpriteHeader* header);
    static QVector<QRgb> readPalette(QIODevice* device, const SpriteHeader& header);

    bool readFrame(QImage *presult);

    SpriteHeader _header;
    QVector<QRgb> _palette;
    QVector<QImage> _frames; //cache
    int _frameIndex;
    int _nextIndex;
};

#endif // QSPRHANDLER_H
