#include "barkinator.hxx"
#include "bk_oscillator.hxx"
#include <iostream>

Fl_Double_Window* make_window()
{
    Fl_Double_Window* w = new Fl_Double_Window(350, 600, "Window");
    BkOscillator *osc1 = new BkOscillator(1, "Oscillator #1");
    BkOscillator *osc2 = new BkOscillator(2, "Oscillator #2");

    (void)osc1;
    (void)osc2;

    w->end();
    //w->size_range(300, 300, 1000, 1000);
    w->end();

    return w;
}

int main(int argc, char *argv[])
{
    Fl_Double_Window *window = make_window();
    window->show(argc, argv);

    return Fl::run();
}
