#include "barkinator.hxx"
#include "bk_oscillator.hxx"

BarkinatorUI::BarkinatorUI()
{
    window = new Fl_Double_Window(350, 600, "Window");
    for (int i = 0; i < BK_MAX_OSCILLATORS; i++) {
        oscillators[i] = new BkOscillator(i);
    }
    window->end();
}

int main(int argc, char *argv[])
{
    BarkinatorUI *ui = new BarkinatorUI();
    ui->window->show(argc, argv);

    return Fl::run();
}
