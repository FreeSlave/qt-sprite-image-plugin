#ifndef SPRITEDEFS_H
#define SPRITEDEFS_H

#define SPRITE_QUAKE_VERSION	1
#define SPRITE_HL_VERSION	2

enum {
    IDSPRITEHEADER = (('P'<<24)+('S'<<16)+('D'<<8)+'I')
};

typedef enum {ST_SYNC=0, ST_RAND } synctype_t;

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

typedef enum { SPR_SINGLE=0, SPR_GROUP } spriteframetype_t;

typedef struct {
    spriteframetype_t	type;
} dspriteframetype_t;

void makeHostEndians(dsprite_t &header);
void makeHostEndians(dquakesprite_t& header);
void makeHostEndians(dspriteframetype_t& frameType);
void makeHostEndians(dspriteframe_t& frame);

void makeLittleEndians(dsprite_t& header);
void makeLittleEndians(dquakesprite_t& header);
void makeLittleEndians(dspriteframetype_t& frameType);
void makeLittleEndians(dspriteframe_t& frame);

#endif // SPRITEDEFS_H
