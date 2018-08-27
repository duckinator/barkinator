#include "barkinator.hxx"
#include "bk_oscillator.hxx"
#include <iostream>

BkOscillator::BkOscillator(int osc_number, const char *name)
{
    if (osc_number < 1) {
        std::cerr << "BkOscillator() got an osc_number < 1." << std::endl;
        exit(1);
    }

    int x_offset = (25 * osc_number) + (300 * (osc_number - 1));

    type = BkSawtooth;

    group = new Fl_Group(x_offset, 25, 300, 200, name);
    group->box(FL_THIN_UP_BOX);
    group->labelfont(1);

    radio_sawtooth = new Fl_Round_Button(45, 40, 25, 25, "sawtooth");
    radio_sawtooth->type(102);
    radio_sawtooth->down_box(FL_ROUND_DOWN_BOX);

    radio_square = new Fl_Round_Button(140, 40, 25, 25, "square");
    radio_square->type(102);
    radio_square->down_box(FL_ROUND_DOWN_BOX);

    frequency = new Fl_Spinner(125, 70, 60, 25, "Frequency ");
    frequency->value(30);

    a = new Fl_Slider(60, 110, 256, 25, "A");
    a->type(1);
    a->minimum(1);
    a->maximum(256);
    a->step(1);
    a->value(10);
    a->align(Fl_Align(FL_ALIGN_LEFT));

    b = new Fl_Slider(60, 150, 256, 25, "B");
    b->type(1);
    b->minimum(1);
    b->maximum(256);
    b->step(1);
    b->value(10);
    b->align(Fl_Align(FL_ALIGN_LEFT));

    c = new Fl_Slider(60, 190, 256, 25, "C");
    c->type(1);
    c->minimum(1);
    c->maximum(256);
    c->step(1);
    c->value(10);
    c->align(Fl_Align(FL_ALIGN_LEFT));
}
