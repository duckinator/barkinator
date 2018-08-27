#ifndef BK_OSCILLATOR_HXX
#define BK_OSCILLATOR_HXX

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Spinner.H>
#include <FL/Fl_Slider.H>

enum BkOscillatorType {
    BkSawtooth,
    BkSquare,
};

class BkOscillator {
    public:
        BkOscillatorType type;

        Fl_Group *group;

        Fl_Round_Button *radio_sawtooth;
        Fl_Round_Button *radio_square;

        Fl_Spinner* frequency;

        Fl_Slider *a;
        Fl_Slider *b;
        Fl_Slider *c;

        BkOscillator(int osc_number);
};

#endif
