#include "barkinator.hxx"
#include "bk_oscillator.hxx"

BarkinatorUI::BarkinatorUI()
{
    window = new Fl_Double_Window(350, 600, "Window");
    oscillators[0] = new BkOscillator(0, "Oscillator #1");
    oscillators[1] = new BkOscillator(1, "Oscillator #2");
    window->end();
}

int main(int argc, char *argv[])
{
    BarkinatorUI *ui = new BarkinatorUI();
    ui->window->show(argc, argv);

    return Fl::run();
}
