#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "widget.hpp"

#include "dropdown.hpp"
#include "spinbox.hpp"
#include "button.hpp"
#include "statictext.hpp"
#include "rect2.hpp"
#include "amobagrid.hpp"

class Application
{
    public:
        Application(int,int,std::string,genv::color bgcolor = BLACK);
        virtual ~Application();

        void run();
        void register_widget(Widget*);

        // kulonfele seged fuggvenyek
        void upd() const;
        void background() const;
        void background(genv::color) const;

        virtual void action(genv::event) = 0;

    protected:
        std::vector<Widget*> _widgets;
        int _width, _height;
        std::string _title;
        genv::color _bgcolor;
};


#endif // APPLICATION_HPP
