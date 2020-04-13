#include "Ramp.h"

Ramp::Ramp(const uint8_t zone1, const uint8_t row1, const uint8_t column1, const uint8_t zone2) {
    this->zone1 = zone1;
    this->row1 = row1;
    this->column1 = column1;
    this->zone2 = zone2;
    row2 = 0;
    column2 =0;
}

uint8_t Ramp::getZone1() {
    return zone1;
}

uint8_t Ramp::getRow1() {
    return row1;
}

uint8_t Ramp::getColumn1() {
    return column1;
}

uint8_t Ramp::getZone2() {
    return zone2;
}

uint8_t Ramp::getRow2() {
    return row2;
}

uint8_t Ramp::getColumn2() {
    return column2;
}

void Ramp::moveCoords(const uint8_t zone, const char row_or_column) {
    if (zone == zone1) {
        switch (row_or_column) {
        case 'R':
                ++row1;
            break;
        case 'C':
                ++column1;
            break;
        }
    } else if (zone == zone2) {
        switch (row_or_column) {
        case 'R':
                ++row2;
            break;
        case 'C':
                ++column2;
            break;
        }
    }
}