#pragma once
#include <wx/wx.h>
#include "Socket.h"
#include <string>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

	wxDECLARE_EVENT_TABLE();
	void OnBtnCliced(wxCommandEvent& evt);
	void TextChanged(wxCommandEvent& evt);
	void Send(wxCommandEvent& evt);
	void SetIp(wxCommandEvent& evt);
	void SetHostport(wxCommandEvent& evt);

private:
	Socket* mySoket = new Socket();
	std::string buf;

	wxStaticText* IpLabel;
	wxStaticText* PortLabel;
	wxTextCtrl* textInput;
	wxTextCtrl* textChat;
	wxTextCtrl* textNick;
};

