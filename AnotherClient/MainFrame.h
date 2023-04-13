#pragma once
#include <wx/wx.h>
#include "Socket.h"
class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

	wxDECLARE_EVENT_TABLE();
	void OnBtnCliced(wxCommandEvent& evt);
	void TextChanged(wxCommandEvent& evt);

private:
	Socket* mySoket = new Socket();
};

