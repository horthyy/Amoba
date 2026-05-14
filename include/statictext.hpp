#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP

#include "widget.hpp"


class StaticText : public Widget
{
    public:
        StaticText(Application*, int, int, int, int, std::string, std::string font = "Fonts/LiberationMono-Regular.ttf", int font_size=11);
        virtual ~StaticText();

        void handle(genv::event) override;
        void draw() const override;

        void set_text(std::string);
        std::string get_text() const;

    protected:
        std::string _text;
        std::string _font;
        int _font_size;
};

#endif // STATICTEXT_HPP
