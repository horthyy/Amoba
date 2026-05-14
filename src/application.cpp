#include "application.hpp"
#include "graphics.hpp"
using namespace genv;

Application::Application(int width, int height, std::string title, color bgcolor /* = BLACK */)
                    : _width(width), _height(height), _title(title), _bgcolor(bgcolor)
{
    gout.open(_width, _height);
    gout.set_title(title);
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

void Application::event_loop()
{
    int sel = -1;
    std::string act = "";
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
                    if(!_widgets[sel]->is_inside(ev.pos_x, ev.pos_y))
                    {

                        _widgets[sel]->deselect();
                        sel = -1;
                    }
                }

                if(sel == -1)
                {
                    for(int i=0;i<_widgets.size();++i)
                    {

                        if (_widgets[i]->is_inside(ev.pos_x, ev.pos_y))
                        {
                            sel = i;
                            _widgets[i]->select();
                            break;
                        }


                    }
                }

            }
        }

        // ha van kiválasztott elem akkor kezeli azt az event alapján
        if (sel != -1)
        {
            _widgets[sel]->handle(ev);
        }

        // elemek kirajzolasa
        background();
        for (int i = 0; i<_widgets.size(); ++i)
        {
            _widgets[i]->draw();
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
