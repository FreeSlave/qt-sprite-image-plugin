/* Copyright (C) 2015 Roman Chistokhodov <freeslave93@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License (LGPL) as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/

#include "spritedefs.h"

QDataStream &operator<<(QDataStream &stream, const dsprite_t &header)
{
    stream << header.ident << header.version << header.type << header.texFormat;
    stream << header.boundingradius << header.width << header.height;
    stream << header.numframes << header.beamlength << header.synctype;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, dsprite_t &header)
{
    stream >> header.ident >> header.version >> header.type >> header.texFormat;
    stream >> header.boundingradius >> header.width >> header.height;
    stream >> header.numframes >> header.beamlength >> header.synctype;
    return stream;
}

QDataStream &operator<<(QDataStream &stream, const dquakesprite_t &header)
{
    stream << header.ident << header.version << header.type;
    stream << header.boundingradius << header.width << header.height;
    stream << header.numframes << header.beamlength << header.synctype;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, dquakesprite_t &header)
{
    stream >> header.ident >> header.version >> header.type;
    stream >> header.boundingradius >> header.width >> header.height;
    stream >> header.numframes >> header.beamlength >> header.synctype;
    return stream;
}

QDataStream &operator<<(QDataStream &stream, const dspriteframetype_t &frameType)
{
    stream << frameType.type;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, dspriteframetype_t &frameType)
{
    stream >> frameType.type;
    return stream;
}

QDataStream &operator<<(QDataStream &stream, const dspriteframe_t &frame)
{
    stream << frame.origin[0] << frame.origin[1] << frame.width << frame.height;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, dspriteframe_t &frame)
{
    stream >> frame.origin[0] >> frame.origin[1] >> frame.width >> frame.height;
    return stream;
}

