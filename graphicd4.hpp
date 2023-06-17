#ifndef GRAPHICD4_HPP_INCLUDED
#define GRAPHICD4_HPP_INCLUDED

#ifndef WINDOWS_H_INCLUDED
#define WINDOWS_H_INCLUDED
#include <windows.h>
#endif // WINDOWS_H_INCLUDED

namespace grphd
{
    namespace generic
    {
        struct Coords;
    }

    namespace console
    {
        char stdColor = 07;
        void gotoXY(grphd::generic::Coords);
        void clearScr();
        void setOutptClr(char);
        void stop();
        void resetColor();
    }

    namespace graphic
    {
        struct Pixel;
        class Grid;
        class Entity;
    }
}

#include "graphicd4.cpp"

#endif // GRAPHICD4_HPP_INCLUDED
