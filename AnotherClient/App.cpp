#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* mainFrame = new MainFrame("C++ GUI");

    mainFrame->SetClientSize(600, 500);
    mainFrame->Center();
    mainFrame->Show();

    return true;
}
