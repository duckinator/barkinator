#ifndef BARKINATOR_HXX
#define BARKINATOR_HXX

#include "bk_oscillator.hxx"

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

Fl_Double_Window* make_window();

#define BK_MAX_OSCILLATORS 10

class BarkinatorUI {
    public:
        Fl_Double_Window *window;
        BkOscillator *oscillators[BK_MAX_OSCILLATORS];
        BarkinatorUI();
};

#endif
