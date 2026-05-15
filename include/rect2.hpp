#ifndef RECT2_HPP
#define RECT2_HPP

#include "widget.hpp"


class Rect2 : public Widget
{
    public:
        Rect2(Application*, int, int, int, int, genv::color);
        virtual ~Rect2();

        void set_color(genv::color);
        genv::color get_color() const;

        void draw() const override;
        void handle(genv::event) override;

    protected:
        genv::color _color;
};

#endif // RECT2_HPP
