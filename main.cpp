#include "graphics.hpp"

using namespace genv;

int main()
{
    gout.open(740,740);
    gout.set_title("Amoba");
    gout << refresh;
    event ev;
    while(gin >> ev && ev.keycode != key_escape)
    {

    }
    return 0;
}
