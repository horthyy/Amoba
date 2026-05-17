#include "application.hpp"
#include "graphics.hpp"
using namespace genv;

Application::Application(int width, int height, std::string title, color bgcolor /* = BLACK */)
                    : _width(width), _height(height), _title(title), _bgcolor(bgcolor)
{
    gout.open(_width, _height);
    gout.set_title(title);
    background();
}

Application::~Application()
{
    for (Widget* w : _widgets)
    {
        delete w;
    }
}

void Application::register_widget(Widget* w) {
    _widgets.push_back(w);
}

void Application::run()
{
    int sel = -1;
    event ev;
    while(gin >> ev && ev.keycode != key_escape)
    {
        // kattintás figyelõ
        if (ev.type == ev_mouse)
        {

            if(ev.button == btn_left) // bal eger le
            {

                if(sel != -1)
                {
                    if(!_widgets[sel]->is_inside(ev.pos_x, ev.pos_y) || !_widgets[sel]->is_visible())
                    {

                        _widgets[sel]->deselect();
                        sel = -1;
                    }
                }

                if(sel == -1)
                {
                    for(int i=0;i<_widgets.size();++i)
                    {

                        if (_widgets[i]->is_inside(ev.pos_x, ev.pos_y) && _widgets[i]->is_visible() && _widgets[i]->is_enabled())
                        {
                            sel = i;
                            _widgets[i]->select();
                            break;
                        }


                    }
                }

            }
        }

        action(ev);
        // ha van kiválasztott elem akkor kezeli azt az event alapján
        if (sel != -1)
        {
            if (_widgets[sel]->is_visible())
                {_widgets[sel]->handle(ev);}
            else
                {_widgets[sel]->deselect();
                sel = -1;}
        }

        // elemek kirajzolasa
        background();
        for (int i = 0; i<_widgets.size(); ++i)
        {
            if(_widgets[i]->is_visible()) {_widgets[i]->draw();}
        }


        upd();
    }
}


// utils
void Application::upd() const {gout << refresh;}


void Application::background() const
{
    gout << _bgcolor << move_to(0,0) << box(_width-1,_height-1);
}

void Application::background(color CLR) const
{
    gout << CLR << move_to(0,0) << box(_width-1,_height-1);
}

size_t Application::get_width() const
{
    return _width;
}

size_t Application::get_height() const
{
    return _height;
}

void Application::set_background(color c)
{
    _bgcolor = c;
}

color Application::get_background() const
{
    return _bgcolor;
}
