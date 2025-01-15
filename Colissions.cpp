#include <iostream>
#include "Colissions.h"

bool CheckColec(float imariof, float jmariof, float wh, float x1, float y1) {
    return (imariof <= x1 + wh && imariof + wh >= x1 && jmariof < y1 + wh && jmariof + wh > y1);
}

bool CheckBlock(float imariof, float jmariof, float wh, float x1, float y1) {
    return (imariof < x1 + wh && imariof + wh > x1 && jmariof< y1 + wh && jmariof + wh > y1);
}

