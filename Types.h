#ifndef INC_2048_TYPES_H
#define INC_2048_TYPES_H

#include <QtGlobal>

struct Tile {
	quint8 index;
	quint8 value;
	bool toDelete;
};

#endif //INC_2048_TYPES_H
