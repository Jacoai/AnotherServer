#include "MainFrame.h"
#include "Socket.h"

enum IDs
{
	BUTTON_ID_Entry = 2,
	BUTTON_ID_Send = 3,
	TEXT_ID = 4,
	TEXT_ID_Nick = 5,
	TEXT_ID_Chat = 6
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(BUTTON_ID_Entry, MainFrame::OnBtnCliced)
	EVT_TEXT(TEXT_ID, MainFrame::TextChanged)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	
	wxPanel* panel = new wxPanel(this);
	
	wxButton* buttonEntry = new wxButton(panel, BUTTON_ID_Entry, "Войти", wxPoint(225,60), wxSize(150,50));
	wxButton* btnSend = new wxButton(panel, BUTTON_ID_Send, "Отправить", wxPoint(496,426), wxSize(90,35));
	
	wxTextCtrl* textInput = new wxTextCtrl(panel, TEXT_ID, "", wxPoint(15, 407), wxSize(460, 75), wxTE_MULTILINE);
	wxTextCtrl* textNick = new wxTextCtrl(panel, TEXT_ID_Nick, "", wxPoint(9, 73), wxSize(200, 20));
	wxTextCtrl* textChat = new wxTextCtrl(panel, TEXT_ID_Chat, "", wxPoint(15,150), wxSize(550,225), wxTE_READONLY);

	
	wxStaticText* hint1 = new wxStaticText(panel, wxID_ANY, "Введите ваше сообщение:", wxPoint(15, 382), wxSize(156, 15));
	wxStaticText* hintNick = new wxStaticText(panel, wxID_ANY, "Введите ваш ник:",wxPoint(9,53), wxSize(103,15));

	CreateStatusBar();
}

void MainFrame::OnBtnCliced(wxCommandEvent& evt)
{
	int res = mySoket->Connect();

	wxLogStatus("res");
}

void MainFrame::TextChanged(wxCommandEvent& evt)
{
	wxLogStatus(evt.GetString());
}
