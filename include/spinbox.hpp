#ifndef SPINBOX_HPP_INCLUDED
#define SPINBOX_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"

// spinbox/számot ábrázoló kijelzõ számbeállító widget

class Spinbox : public Widget
{
    public:
        Spinbox(Application* parent, int x, int y, int sx, int sy, int value, int lowlimit, int uplimit);
        /*
        konstruktor paraméterei:
          x: x-pozíció (bal felsõ sarok)
          y: y-pozíció (bal felsó sarok)
          sx: x-hossz
          sy: y-hossz
          value: a kijelzõ által mutatott érték inicializálás után.
          lowlimit: az intervallum alsó határa, ennél kisebb számot nem mutat a kijelzõ.
          uplimit: az intervallum felsõ határa, ennél nagyobb számot nem mutat a kijelzõ.
        */
        ~Spinbox();

        virtual void draw() const override;
        virtual void handle(genv::event ev) override;
        int get_value() const;
        void clamp_value();

    protected:
        int _value;
        int _lowlimit;
        int _uplimit;
};

#endif // SPINBOX_HPP_INCLUDED
