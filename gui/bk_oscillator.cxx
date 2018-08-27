#include "barkinator.hxx"
#include "bk_oscillator.hxx"
#include <iostream>

Fl_Round_Button *radio_button_choice(int x, int y, int w, int h,
        const char *label)
{
    Fl_Round_Button *button = new Fl_Round_Button(x, y, w, h, label);
    button->type(102);
    button->down_box(FL_ROUND_DOWN_BOX);
    return button;
}

BkOscillator::BkOscillator(int osc_number, const char *name)
{
    /* BEGIN: DIMENSIONS AND POSITIONS. */
    // NOTE: Positions are all relative to the group.

    int padding = 25;

    // Radio buttons themselves are squares.
    // TODO: Figure out how labels fit into the width.
    int radio_height = 25;
    int radio_width  = radio_height;

    // group dimensions. TODO: Calculate these.
    int group_height = 200;
    int group_width  = 300;

    /* END:   DIMENSIONS AND POSITIONS. */

    int y_offset = (padding * osc_number) + (group_height * osc_number);

    type = BkSawtooth;

    int group_top = padding;
    group = new Fl_Group(padding, group_top + y_offset,
                         group_width, group_height,
                         name);
    group->box(FL_THIN_UP_BOX);
    group->labelfont(1);

    int radio_top = 40;
    radio_sawtooth = radio_button_choice(45, radio_top + y_offset,
                                         radio_width, radio_height,
                                         "sawtooth");
    radio_square  = radio_button_choice(140, radio_top + y_offset,
                                        radio_width, radio_height,
                                        "square");

//    int freq_top = radio_top + radio_height;
    frequency = new Fl_Spinner(125, 70 + y_offset, 60, 25, "Frequency ");
    frequency->value(30);

    a = new Fl_Slider(60, 110 + y_offset, 256, 25, "A");
    a->type(1);
    a->minimum(1);
    a->maximum(256);
    a->step(1);
    a->value(10);
    a->align(Fl_Align(FL_ALIGN_LEFT));

    b = new Fl_Slider(60, 150 + y_offset, 256, 25, "B");
    b->type(1);
    b->minimum(1);
    b->maximum(256);
    b->step(1);
    b->value(10);
    b->align(Fl_Align(FL_ALIGN_LEFT));

    c = new Fl_Slider(60, 190 + y_offset, 256, 25, "C");
    c->type(1);
    c->minimum(1);
    c->maximum(256);
    c->step(1);
    c->value(10);
    c->align(Fl_Align(FL_ALIGN_LEFT));
}
