#include "Field.h"

void FieldOrigin::init() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            const int8_t pos = i + j * width;
            if (i > 0) neibs.at(pos).push_back(pos - 1);
            if (i < width - 1) neibs.at(pos).push_back(pos + 1);
            if (j > 0) {
                if (j % 2 == 0) {
                    neibs.at(pos).push_back(pos - width);
                    if (i > 0) neibs.at(pos).push_back(pos - width - 1);
                } else {
                    neibs.at(pos).push_back(pos - width);
                    if (i < width - 1) neibs.at(pos).push_back(pos - width + 1);
                }
            }
            if (j < height - 1) {
                if (j % 2 == 0) {
                    neibs.at(pos).push_back(pos + width);
                    if (i > 0) neibs.at(pos).push_back(pos + width - 1);
                } else {
                    neibs.at(pos).push_back(pos + width);
                    if (i < width - 1) neibs.at(pos).push_back(pos + width + 1);
                }
            }
        }
    }
}
