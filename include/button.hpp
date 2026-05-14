#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include "widget.hpp"


class Button : public Widget
{
public:
    Button(Application*,
           int, int, int, int,
           std::string,
           std::function<void()>);
    virtual ~Button();

    void draw() const override;
    void handle(genv::event) override;
    void action();

protected:
    std::string _label;

    std::function<void()> _f;
};

#endif // BUTTON_HPP
