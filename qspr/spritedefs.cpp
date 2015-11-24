
#include "spritedefs.h"

#include <QtEndian>

void makeHostEndians(dsprite_t &header)
{
    header.ident = qFromLittleEndian(header.ident);
    header.type = qFromLittleEndian(header.type);
    header.version = qFromLittleEndian(header.version);
    header.texFormat = qFromLittleEndian(header.texFormat);
    header.boundingradius = qFromLittleEndian(header.boundingradius);
    header.width = qFromLittleEndian(header.width);
    header.height = qFromLittleEndian(header.height);
    header.numframes = qFromLittleEndian(header.numframes);
    header.synctype = qFromLittleEndian(header.synctype);
}

void makeHostEndians(dquakesprite_t &header)
{
    header.ident = qFromLittleEndian(header.ident);
    header.type = qFromLittleEndian(header.type);
    header.version = qFromLittleEndian(header.version);
    header.boundingradius = qFromLittleEndian(header.boundingradius);
    header.width = qFromLittleEndian(header.width);
    header.height = qFromLittleEndian(header.height);
    header.numframes = qFromLittleEndian(header.numframes);
    header.synctype = qFromLittleEndian(header.synctype);
}

void makeHostEndians(dspriteframetype_t &frameType)
{
    frameType.type = qFromLittleEndian(frameType.type);
}

void makeHostEndians(dspriteframe_t &frame)
{
    frame.origin[0] = qFromLittleEndian(frame.origin[0]);
    frame.origin[1] = qFromLittleEndian(frame.origin[1]);
    frame.width = qFromLittleEndian(frame.width);
    frame.height = qFromLittleEndian(frame.height);
}

void makeLittleEndians(dsprite_t &header)
{
    header.ident = qToLittleEndian(header.ident);
    header.type = qToLittleEndian(header.type);
    header.version = qToLittleEndian(header.version);
    header.texFormat = qToLittleEndian(header.texFormat);
    header.boundingradius = qToLittleEndian(header.boundingradius);
    header.width = qToLittleEndian(header.width);
    header.height = qToLittleEndian(header.height);
    header.numframes = qToLittleEndian(header.numframes);
    header.synctype = qToLittleEndian(header.synctype);
}

void makeLittleEndians(dquakesprite_t &header)
{
    header.ident = qToLittleEndian(header.ident);
    header.type = qToLittleEndian(header.type);
    header.version = qToLittleEndian(header.version);
    header.boundingradius = qToLittleEndian(header.boundingradius);
    header.width = qToLittleEndian(header.width);
    header.height = qToLittleEndian(header.height);
    header.numframes = qToLittleEndian(header.numframes);
    header.synctype = qToLittleEndian(header.synctype);
}

void makeLittleEndians(dspriteframetype_t &frameType)
{
    frameType.type = qToLittleEndian(frameType.type);
}

void makeLittleEndians(dspriteframe_t &frame)
{
    frame.origin[0] = qToLittleEndian(frame.origin[0]);
    frame.origin[1] = qToLittleEndian(frame.origin[1]);
    frame.width = qToLittleEndian(frame.width);
    frame.height = qToLittleEndian(frame.height);
}
