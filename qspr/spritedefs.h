/* Copyright (C) 2015 Roman Chistokhodov <freeslave93@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License (LGPL) as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/

#ifndef SPRITEDEFS_H
#define SPRITEDEFS_H

#include <QDataStream>

#define SPRITE_QUAKE_VERSION	1
#define SPRITE_HL_VERSION	2

enum {
    IDSPRITEHEADER = (('P'<<24)+('S'<<16)+('D'<<8)+'I')
};

enum {ST_SYNC=0, ST_RAND };

typedef int synctype_t;

typedef struct {
    int			ident;
    int			version;
    int			type;
    int			texFormat;
    float		boundingradius;
    int			width;
    int			height;
    int			numframes;
    float		beamlength;
    synctype_t	synctype;

    enum {SIZE = 40};
} dsprite_t;

typedef struct {
    int			ident;
    int			version;
    int			type;
    float		boundingradius;
    int			width;
    int			height;
    int			numframes;
    float		beamlength;
    synctype_t	synctype;
    enum {SIZE = 36};
} dquakesprite_t;

enum {
    SPR_VP_PARALLEL_UPRIGHT	=	0,
    SPR_FACING_UPRIGHT		=	1,
    SPR_VP_PARALLEL			=	2,
    SPR_ORIENTED			=	3,
    SPR_VP_PARALLEL_ORIENTED=	4,
    SPR_LABEL               =   5,
    SPR_LABEL_SCALE         =   6,
    SPR_OVERHEAD            =   7
};

enum {
    SPR_NORMAL				=	0,
    SPR_ADDITIVE			=	1,
    SPR_INDEXALPHA			=	2,
    SPR_ALPHTEST			=	3
};

typedef struct {
    int			origin[2];
    int			width;
    int			height;
} dspriteframe_t;

typedef struct {
    int			numframes;
} dspritegroup_t;

typedef struct {
    float	interval;
} dspriteinterval_t;

enum { SPR_SINGLE=0, SPR_GROUP };
typedef int spriteframetype_t;

typedef struct {
    spriteframetype_t	type;
} dspriteframetype_t;

QDataStream &operator<<(QDataStream &, const dsprite_t &);
QDataStream &operator>>(QDataStream &, dsprite_t &);

QDataStream &operator<<(QDataStream &, const dquakesprite_t &);
QDataStream &operator>>(QDataStream &, dquakesprite_t &);

QDataStream &operator<<(QDataStream &, const dspriteframetype_t &);
QDataStream &operator>>(QDataStream &, dspriteframetype_t &);

QDataStream &operator<<(QDataStream &, const dspriteframe_t &);
QDataStream &operator>>(QDataStream &, dspriteframe_t &);

#endif // SPRITEDEFS_H
