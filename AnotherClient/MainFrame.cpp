#include "MainFrame.h"
#include "Socket.h"
#include <thread>

enum IDs
{
	BUTTON_ID_Entry = 2,
	BUTTON_ID_Send = 3,
	TEXT_ID_Input = 4,
	TEXT_ID_Nick = 5,
	TEXT_ID_Chat = 6,
	Menu_ID_IP = 7,
	Menu_ID_Hostport = 8
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(BUTTON_ID_Entry, MainFrame::OnBtnCliced)
EVT_BUTTON(BUTTON_ID_Send, MainFrame::Send)
EVT_TEXT(TEXT_ID_Input, MainFrame::TextChanged)
EVT_MENU(Menu_ID_IP, MainFrame::SetIp)
EVT_MENU(Menu_ID_Hostport, MainFrame::SetHostport)
wxEND_EVENT_TABLE()

void changeText(char* recv);

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	
	wxPanel* panel = new wxPanel(this);
	
	wxButton* buttonEntry = new wxButton(panel, BUTTON_ID_Entry, "Войти", wxPoint(225,60), wxSize(150,50));
	wxButton* btnSend = new wxButton(panel, BUTTON_ID_Send, "Отправить", wxPoint(496,426), wxSize(90,35));
		
	wxTextCtrl* textInput = new wxTextCtrl(panel, TEXT_ID_Input, "", wxPoint(15, 407), wxSize(460, 75), wxTE_MULTILINE);
	wxTextCtrl* textNick = new wxTextCtrl(panel, TEXT_ID_Nick, "", wxPoint(9, 73), wxSize(200, 20));
	textChat = new wxTextCtrl(panel, TEXT_ID_Chat, "", wxPoint(15,150), wxSize(550,225), wxTE_READONLY);

	wxStaticText* hint1 = new wxStaticText(panel, wxID_ANY, "Введите ваше сообщение:", wxPoint(15, 382), wxSize(156, 15));
	wxStaticText* hintNick = new wxStaticText(panel, wxID_ANY, "Введите ваш ник:",wxPoint(9,53), wxSize(103,15));

	wxStaticText* ipHint = new wxStaticText(panel, wxID_ANY, "IP адрес сервера: ", wxPoint(418, 61), wxSize(111, 15));
	wxStaticText* portHint = new wxStaticText(panel, wxID_ANY, "Порт сервера:", wxPoint(418,87),wxSize(85,15));
	IpLabel = new wxStaticText(panel, wxID_ANY, "", wxPoint(528, 61), wxSize(72, 15));
	PortLabel = new wxStaticText(panel, wxID_ANY, "", wxPoint(511, 87), wxSize(36, 15));

	wxMenuBar* menubar = new wxMenuBar();
	wxMenu* menu = new wxMenu();
	
	menu->Append(Menu_ID_IP, "Ввести IP");
	menu->Append(Menu_ID_Hostport, "Ввести Hostport");
	menubar->Append(menu, "Меню");	
	SetMenuBar(menubar);
	
	IpLabel->SetLabelText(mySoket->GetIP());
	PortLabel->SetLabelText(mySoket->GetPort());
	CreateStatusBar();
}


void MainFrame::OnBtnCliced(wxCommandEvent& evt)
{
	wxLogStatus("Connecting...");
	mySoket->Setaddrinfo();
	int res = mySoket->Connect();
	if (res != 0)
		wxLogStatus("Oh no, connectiin fail");

	else
	{
		wxLogStatus("Connected");
		const auto f = [this]()
		{
			int res = 0;
			for (;; Sleep(75))
			{
				std::memset(mySoket->recvbuf, 0, sizeof(mySoket->recvbuf));
				res = recv(mySoket->ConnectSocket, mySoket->recvbuf, mySoket->recvbuflen, 0);
				if (res > 0)
				{
					CallAfter([this]()
						{
							this->textChat->ChangeValue(mySoket->recvbuf);
						}
					);
				}
			}
		};

		std::thread bck{ f };
		bck.detach();
	}
}

void MainFrame::TextChanged(wxCommandEvent& evt)
{
	buf = evt.GetString();
}

void MainFrame::Send(wxCommandEvent& evt)
{
	strcpy(mySoket->sendbuf, buf.c_str());	
	send(mySoket->ConnectSocket, mySoket->sendbuf, (int)strlen(mySoket->sendbuf), 0);
}

void MainFrame::SetIp(wxCommandEvent& evt)
{
	wxTextEntryDialog* d = new wxTextEntryDialog(this, "Введите IP","IP");

	if (d->ShowModal() == wxID_OK)
	{		
		std::string tmp = d->GetValue().ToStdString();
		mySoket->DEFAULT_IP = tmp.c_str();
		IpLabel->SetLabelText(mySoket->GetIP());

	}
	else 
		wxLogStatus("not ok");
}

void MainFrame::SetHostport(wxCommandEvent& evt)
{
	wxTextEntryDialog* d = new wxTextEntryDialog(this, "Введите Hostport", "Hostport");

	if (d->ShowModal() == wxID_OK)
	{
		std::string tmp = d->GetValue().ToStdString();
		mySoket->DEFAULT_PORT = tmp.c_str();
		PortLabel->SetLabelText(mySoket->GetPort());
	}
	else
		wxLogStatus("not ok");

}




