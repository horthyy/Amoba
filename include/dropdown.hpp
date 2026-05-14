#ifndef DROPDOWN_HPP_INCLUDED
#define DROPDOWN_HPP_INCLUDED

#include "widget.hpp"

// dropdown/legördülő menü kiválasztó widget

class Dropdown : public Widget
{
    public:
        Dropdown(Application* parent, int x, int y, int sx, int sy, std::vector<std::string> values, int max_height = 3, int index = 0);
        /*
        konstruktor paraméterei:
          x: x-pozíció (bal felső sarok)
          y: y-pozíció (bal felsó sarok)
          sx: x-hossz
          sy: y-hossz
          values: a választható elemek felsorolása, string típusú vektor formájában
          max_height (opcionális): a legördülő menüben hány tételszám jelenik meg. alapértelmezett értéke 3.
          index (opcionális): az elemek közül hányadik elem legyen mutatva inicializálás után. alapértelmezett értéke 0, vagyis a első elem.

          megjegyzés:
            mivel a kiválasztó widget függőlegesen méretet változtat,
            az 'sy' és a 'max_height' paraméterek
            értelmezhetők 'kis' és 'nagy' méretekként.

            ez alapján az y-méretek pixelben:
             kis méret  = sy
             nagy méret = max_height*(1+sy)
        */

        ~Dropdown();

        virtual void draw() const override;
        virtual void handle(genv::event ev) override;
        virtual bool is_inside(int mx, int my) override;
        std::string get_value() const;

        void draw_unit(int px, int py, std::string txt) const;
        void draw_page() const;
        void draw_scollbar() const;
        virtual void on_deselection() override;

        double clamp(double x, double a, double b) const;

    protected:
        std::vector<std::string> _values;
        int _index; // jelenleg kiválasztott elem indexe. konstruktorban megadható, alapértelmezetten az első elem.
        int _max_height; // legfeljebb ennyi tételszámot jelenít meg a menü nagy méretben
        bool _dropdown = 0; // igaz ha a legördülő menü látható, hamis ha nem
        int _page_index = 0; // a menü oldalakra van osztva, mindegyiken legfeljebb '_max_height' darab elem van. ez a változó a jelenlegi oldalt tárolja.
        int _number_of_pages; // oldalak száma, nullától indexelve. formula a konstruktorban: (teljes oldalak) + (1 maradék oldal ha van) - 1.
};

#endif // DROPDOWN_HPP_INCLUDED
