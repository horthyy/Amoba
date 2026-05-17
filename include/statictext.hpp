#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP

#include "widget.hpp"


class StaticText : public Widget
{
    public:
        StaticText(Application*, int, int, int, int, std::string,
                   genv::color pcolor = genv::color(0,0,0),
                   size_t font_size=20,
                   std::string font = "Fonts/LiberationMono-Regular.ttf");
        virtual ~StaticText();

        void handle(genv::event) override;
        void draw() const override;

        void set_text(std::string);
        std::string get_text() const;

    protected:
        std::string _text;
        std::string _font;
        int _font_size;
        genv::color _color;
};

#endif // STATICTEXT_HPP
