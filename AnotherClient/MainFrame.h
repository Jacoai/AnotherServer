#pragma once
#include <wx/wx.h>
#include "Socket.h"
#include <string>
#include "settingsPanel.h"

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
	wxTextCtrl* textChat;

private:
	Socket* mySoket = new Socket();
	std::string buf;

};

