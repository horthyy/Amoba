#ifndef AMOBATILE_HPP
#define AMOBATILE_HPP

#include "rect2.hpp"


class AmobaTile : public Rect2
{
    public:
        AmobaTile(Application*, int, int);
        virtual ~AmobaTile();

        void set_symbol(char);
        char get_symbol() const;

        void draw() const override;
        void handle(genv::event) override;

    protected:
        char _symbol;
        /* _symbol 3 lehetséges értéke jelöli, milyen jel van a mezõn:
             - 'o', kör
             - 'x', kereszt
             - 'e', üres mezõ
        */
};

#endif // AMOBATILE_HPP
