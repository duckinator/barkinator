#include "barkinator.hxx"
#include "bk_oscillator.hxx"
#include <iostream>

Fl_Round_Button *bk_radio_choice(int x, int y, int w, int h,
        const char *label)
{
    Fl_Round_Button *button = new Fl_Round_Button(x, y, w, h, label);
    button->type(102);
    button->down_box(FL_ROUND_DOWN_BOX);
    return button;
}

Fl_Slider *bk_slider(int x, int y, int w, int h, const char *label,
        int minimum, int maximum, int value, int step = 1)
{
    Fl_Slider *s = new Fl_Slider(x, y, w, h, label);
    s->type(1);
    s->minimum(minimum);
    s->maximum(maximum);
    s->step(step);
    s->value(value);
    s->align(Fl_Align(FL_ALIGN_LEFT));

    return s;
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
    radio_sawtooth = bk_radio_choice(45, radio_top + y_offset,
                                     radio_width, radio_height,
                                     "sawtooth");
    radio_square  = bk_radio_choice(140, radio_top + y_offset,
                                    radio_width, radio_height,
                                    "square");

    frequency = new Fl_Spinner(125, 70 + y_offset, 60, 25, "Frequency ");
    frequency->value(30);

    a = bk_slider(60, 110 + y_offset, 256, 25, "A",
            1 /* min */, 256 /* max */, 10 /* value */);
    b = bk_slider(60, 150 + y_offset, 256, 25, "B",
            1 /* min */, 256 /* max */, 10 /* value */);
    c = bk_slider(60, 190 + y_offset, 256, 25, "C",
            1 /* min */, 256 /* max */, 10 /* value */);
}
