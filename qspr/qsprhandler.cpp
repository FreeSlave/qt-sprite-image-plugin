#include <QtEndian>
#include <QDataStream>
#include <QVariant>
#include <QImage>
#include <QColor>
#include <cmath>

#include "qsprhandler.h"
#include "spritedefs.h"

static const quint8* quakePalette()
{
    static quint8 palette[] =
    {
    // marked: colormap colors: cb = (colormap & 0xF0);cb += (cb >= 128 && cb < 224) ? 4 : 12;
    // 0x0*
        0,0,0,        15,15,15,     31,31,31,     47,47,47,     63,63,63,     75,75,75,     91,91,91,     107,107,107,
        123,123,123,  139,139,139,  155,155,155,  171,171,171,  187,187,187,  203,203,203,  219,219,219,  235,235,235,
    // 0x1*                                                   0 ^
        15,11,7,      23,15,11,     31,23,11,     39,27,15,     47,35,19,     55,43,23,     63,47,23,     75,55,27,
        83,59,27,     91,67,31,     99,75,31,     107,83,31,    115,87,31,    123,95,35,    131,103,35,   143,111,35,
    // 0x2*                                                   1 ^
        11,11,15,     19,19,27,     27,27,39,     39,39,51,     47,47,63,     55,55,75,     63,63,87,     71,71,103,
        79,79,115,    91,91,127,    99,99,139,    107,107,151,  115,115,163,  123,123,175,  131,131,187,  139,139,203,
    // 0x3*                                                   2 ^
        0,0,0,        7,7,0,        11,11,0,      19,19,0,      27,27,0,      35,35,0,      43,43,7,      47,47,7,
        55,55,7,      63,63,7,      71,71,7,      75,75,11,     83,83,11,     91,91,11,     99,99,11,     107,107,15,
    // 0x4*                                                   3 ^
        7,0,0,        15,0,0,       23,0,0,       31,0,0,       39,0,0,       47,0,0,       55,0,0,       63,0,0,
        71,0,0,       79,0,0,       87,0,0,       95,0,0,       103,0,0,      111,0,0,      119,0,0,      127,0,0,
    // 0x5*                                                   4 ^
        19,19,0,      27,27,0,      35,35,0,      47,43,0,      55,47,0,      67,55,0,      75,59,7,      87,67,7,
        95,71,7,      107,75,11,    119,83,15,    131,87,19,    139,91,19,    151,95,27,    163,99,31,    175,103,35,
    // 0x6*                                                   5 ^
        35,19,7,      47,23,11,     59,31,15,     75,35,19,     87,43,23,     99,47,31,     115,55,35,    127,59,43,
        143,67,51,    159,79,51,    175,99,47,    191,119,47,   207,143,43,   223,171,39,   239,203,31,   255,243,27,
    // 0x7*                                                   6 ^
        11,7,0,       27,19,0,      43,35,15,     55,43,19,     71,51,27,     83,55,35,     99,63,43,     111,71,51,
        127,83,63,    139,95,71,    155,107,83,   167,123,95,   183,135,107,  195,147,123,  211,163,139,  227,179,151,
    // 0x8*                                                   7 ^        v 8
        171,139,163,  159,127,151,  147,115,135,  139,103,123,  127,91,111,   119,83,99,    107,75,87,    95,63,75,
        87,55,67,     75,47,55,     67,39,47,     55,31,35,     43,23,27,     35,19,19,     23,11,11,     15,7,7,
    // 0x9*                                                   9 v
        187,115,159,  175,107,143,  163,95,131,   151,87,119,   139,79,107,   127,75,95,    115,67,83,    107,59,75,
        95,51,63,     83,43,55,     71,35,43,     59,31,35,     47,23,27,     35,19,19,     23,11,11,     15,7,7,
    // 0xA*                                                  10 v
        219,195,187,  203,179,167,  191,163,155,  175,151,139,  163,135,123,  151,123,111,  135,111,95,   123,99,83,
        107,87,71,    95,75,59,     83,63,51,     67,51,39,     55,43,31,     39,31,23,     27,19,15,     15,11,7,
    // 0xB*                                                  11 v
        111,131,123,  103,123,111,  95,115,103,   87,107,95,    79,99,87,     71,91,79,     63,83,71,     55,75,63,
        47,67,55,     43,59,47,     35,51,39,     31,43,31,     23,35,23,     15,27,19,     11,19,11,     7,11,7,
    // 0xC*                                                  12 v
        255,243,27,   239,223,23,   219,203,19,   203,183,15,   187,167,15,   171,151,11,   155,131,7,    139,115,7,
        123,99,7,     107,83,0,     91,71,0,      75,55,0,      59,43,0,      43,31,0,      27,15,0,      11,7,0,
    // 0xD*                                                  13 v
        0,0,255,      11,11,239,    19,19,223,    27,27,207,    35,35,191,    43,43,175,    47,47,159,    47,47,143,
        47,47,127,    47,47,111,    47,47,95,     43,43,79,     35,35,63,     27,27,47,     19,19,31,     11,11,15,
    // 0xE*
        43,0,0,       59,0,0,       75,7,0,       95,7,0,       111,15,0,     127,23,7,     147,31,7,     163,39,11,
        183,51,15,    195,75,27,    207,99,43,    219,127,59,   227,151,79,   231,171,95,   239,191,119,  247,211,139,
    // 0xF*                                                  14 ^
        167,123,59,   183,155,55,   199,195,55,   231,227,87,   127,191,255,  171,231,255,  215,255,255,  103,0,0,
        139,0,0,      179,0,0,      215,0,0,      255,0,0,      255,243,147,  255,247,199,  255,255,255,  159,91,83
    }; //

    return palette;
}

SpriteHeader::SpriteHeader() : version(0), type(0), texFormat(0), numFrames(0)
{

}

bool QSprHandler::canRead(QIODevice *device, int* version)
{
    if (!device) {
        return false;
    }

    qint64 oldPos = device->pos();

    QDataStream stream(device);
    stream.setByteOrder(QDataStream::LittleEndian);

    int id, ver;
    stream >> id >> ver;

    if (version) {
        *version = ver;
    }

    device->seek(oldPos);

    return stream.status() == QDataStream::Ok && id == IDSPRITEHEADER && (ver == SPRITE_HL_VERSION || ver == SPRITE_QUAKE_VERSION);
}

bool QSprHandler::readSpriteHeader(QIODevice* device, SpriteHeader* header)
{
    int version = 0;
    if (!canRead(device, &version)) {
        return false;
    }

    QDataStream stream(device);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    if (version == SPRITE_HL_VERSION) {
        dsprite_t sprHeader;
        stream >> sprHeader;

        header->version = sprHeader.version;
        header->type = sprHeader.type;
        header->texFormat = sprHeader.texFormat;
        header->numFrames = sprHeader.numframes;
        header->size = QSize(sprHeader.width, sprHeader.height);
        return stream.status() == QDataStream::Ok;
    } else if (version == SPRITE_QUAKE_VERSION) {
        dquakesprite_t sprHeader;
        stream >> sprHeader;

        header->version = sprHeader.version;
        header->type = sprHeader.type;
        header->numFrames = sprHeader.numframes;
        header->size = QSize(sprHeader.width, sprHeader.height);
        return stream.status() == QDataStream::Ok;
    } else {
        return false;
    }
}

QVector<QRgb> QSprHandler::readPalette(QIODevice *device, const SpriteHeader &header)
{
    if (header.version == SPRITE_HL_VERSION) {
        QDataStream stream(device);
        stream.setByteOrder(QDataStream::LittleEndian);
        short paletteSize = 0;
        stream >> paletteSize;

        if (paletteSize != 256) {
            return QVector<QRgb>();
        }

        QByteArray paletteBytes(paletteSize*3, '\0');
        if (stream.readRawData(paletteBytes.data(), paletteBytes.size()) < paletteBytes.size()) {
            return QVector<QRgb>();
        }

        QVector<QRgb> palette(paletteSize);
        const quint8* data = reinterpret_cast<const quint8*>(paletteBytes.constData());
        if (header.texFormat == SPR_INDEXALPHA)
        {
            for (int i=0; i<paletteSize; ++i)
                palette[i] = qRgba(data[765], data[766], data[767], i);
        }
        else
        {
            for (int i=0; i<paletteSize; ++i)
                palette[i] = qRgba(data[i*3+0], data[i*3+1], data[i*3+2], 0xFF);
        }
        return palette;
    } else if (header.version == SPRITE_QUAKE_VERSION) {
        QVector<QRgb> palette(256);
        const quint8* pal = quakePalette();
        for (int i=0; i<palette.size(); ++i) {
            palette[i] = qRgba(pal[i*3+0], pal[i*3+1], pal[i*3+2], 0xFF);
        }
        return palette;
    } else {
        return QVector<QRgb>();
    }
}

QSprHandler::QSprHandler() : _frameIndex(-1), _nextIndex(0), _startPos(0)
{
}

bool QSprHandler::canRead() const
{
    if (_frameIndex == -1) {
        if (canRead(device())) {
            setFormat("spr");
            return true;
        } else {
            return false;
        }
    } else {
        return _nextIndex >= 0 && _nextIndex < _header.numFrames;
    }
}

int QSprHandler::currentImageNumber() const
{
    return _frameIndex;
}

int QSprHandler::imageCount() const
{
    return _header.numFrames;
}

bool QSprHandler::jumpToImage(int imageNumber)
{
    if (imageNumber >= 0 && imageNumber < _header.numFrames) {
        _nextIndex = imageNumber;
        return true;
    }
    return false;
}

bool QSprHandler::jumpToNextImage()
{
    return _header.numFrames && jumpToImage((_frameIndex + 1) % _header.numFrames);
}

int QSprHandler::loopCount() const
{
    return -1;
}

int QSprHandler::nextImageDelay() const
{
    return 100;
}

QVariant QSprHandler::option(ImageOption option) const
{
    if (option == ImageFormat) {
        return QImage::Format_Indexed8;
    } else if (option == Size) {
        qint64 pos = device()->pos();
        SpriteHeader header;
        bool ok = readSpriteHeader(device(), &header);
        device()->seek(pos);
        if (ok) {
            return header.size;
        }
    } else if (option == BackgroundColor) {
        qint64 pos = device()->pos();
        QColor color;
        SpriteHeader header;
        if (readSpriteHeader(device(), &header)) {
            QVector<QRgb> palette = readPalette(device(), header);
            if (header.version == SPRITE_QUAKE_VERSION || header.texFormat == SPR_ALPHTEST) {
                color = QColor::fromRgba(palette.last());
            }
        }
        device()->seek(pos);
        return color;
    } else if (option == Animation) {
        return true;
    }
    return QVariant();
}

bool QSprHandler::read(QImage *image)
{
    if (_frameIndex == -1) {
        int version;
        if (!canRead(device(), &version)) {
            return false;
        }
        if (readSpriteHeader(device(), &_header)) {
            _palette = readPalette(device(), _header);
            if (_palette.empty()) {
                return false;
            }
            _startPos = device()->pos();
        } else {
            return false;
        }
    }

    if (_nextIndex < _header.numFrames ) {
        if (_nextIndex == 0 && _frames.empty()) {
            QImage result;
            if (readFrame(&result)) {
                _frames.append(result);
            } else {
                return false;
            }
        }

        if (_nextIndex > 0 && _frames.size() == 1) {
            //cache all frames when requested frame other than the first
            for (int i=1; i<_header.numFrames; ++i) {
                QImage image;
                if (readFrame(&image)) {
                    _frames.append(image);
                } else {
                    return false;
                }
            }
        }

        if (_nextIndex < _frames.size()) {
            *image = _frames.at(_nextIndex);
            _frameIndex = _nextIndex++;
            return true;
        }
    }

    return false;
}

bool QSprHandler::readFrame(QImage *presult)
{
    QDataStream stream(device());
    stream.setByteOrder(QDataStream::LittleEndian);

    dspriteframetype_t frametype;
    stream >> frametype;

    if (frametype.type == SPR_SINGLE) {
        dspriteframe_t frameStruct;
        stream >> frameStruct;

        QByteArray dataArr(frameStruct.width*frameStruct.height, '\0');
        if (stream.readRawData(dataArr.data(), dataArr.size()) < dataArr.size()) {
            return false;
        }

        const uchar* dataBytes = reinterpret_cast<const uchar*>(dataArr.constData());
        QImage result(frameStruct.width, frameStruct.height, QImage::Format_Indexed8);
        result.setColorTable(_palette);

        uchar* imageData = result.bits();
        for (int j=0; j<frameStruct.width*frameStruct.height; ++j) {
            imageData[j] = dataBytes[j];
        }
        *presult = result;
        return stream.status() == QDataStream::Ok;
    } else {
        return false;
    }
}

bool QSprHandler::supportsOption(ImageOption option) const
{
    return option == ImageFormat || option == Size || option == Animation || option == BackgroundColor;
}

bool QSprHandler::write(const QImage &image)
{
    const QSize size = image.size();

    dsprite_t header;
    header.ident = IDSPRITEHEADER;
    header.version = SPRITE_HL_VERSION;
    header.type = SPR_VP_PARALLEL;
    header.texFormat = SPR_ADDITIVE;
    header.boundingradius = sqrt(static_cast<float>(size.width()*size.width() + size.height()*size.height()))/2;
    header.width = size.width();
    header.height = size.height();
    header.numframes = 1;
    header.beamlength = 0;
    header.synctype = ST_SYNC;

    QDataStream stream(device());
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    stream << header;

    QImage converted = image.convertToFormat(QImage::Format_Indexed8);
    QVector<QRgb> colorTable = converted.colorTable();
    colorTable.resize(256);
    short paletteSize = static_cast<short>(colorTable.size());

    stream << paletteSize;

    quint8* palBytes = new quint8[paletteSize*3];
    for (int i=0; i<colorTable.size(); ++i)
    {
        QRgb rgb = colorTable.at(i);
        palBytes[i*3+0] = static_cast<quint8>(qRed(rgb));
        palBytes[i*3+1] = static_cast<quint8>(qGreen(rgb));
        palBytes[i*3+2] = static_cast<quint8>(qBlue(rgb));
    }

    stream.writeRawData(reinterpret_cast<const char*>(palBytes), paletteSize*3);
    delete[]palBytes;

    dspriteframetype_t frametype;
    frametype.type = SPR_SINGLE;

    dspriteframe_t frame;
    frame.origin[0] = -size.width()/2;
    frame.origin[1] = size.height()/2;
    frame.width = size.width();
    frame.height = size.height();

    stream << frametype;
    stream << frame;
    stream.writeRawData(reinterpret_cast<const char*>(converted.bits()), size.width() * size.height());

    return stream.status() != QDataStream::WriteFailed;
}
