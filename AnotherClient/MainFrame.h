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

private:
	Socket* mySoket = new Socket();
	std::string buf;
};

