/*******************************************
 *	base.cpp
 *	Created by Casey O'Donnell on Tue Jun 29 2004.
 *	Copyright (c) 2004 Casey O'Donnell. All rights reserved.
 *	Licence: wxWidgets Licence
 ******************************************/

#include "wxcurl/wxcurl_config.h"
#include <wx/xrc/xmlres.h>

#include <wxcurl/http.h>

#include "wxGetDialog.h"

//////////////////////////////////////////////////////////////////////
// Resources
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Event Tables and Other Macros for wxWindows
//////////////////////////////////////////////////////////////////////

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
IMPLEMENT_CLASS(wxGetDialog, wxDialog)
BEGIN_EVENT_TABLE(wxGetDialog, wxDialog)
	EVT_BUTTON(XRCID("file_menu_get"), wxGetDialog::OnGetUrl)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

wxGetDialog::wxGetDialog(wxWindow* pParent)
{
	wxXmlResource::Get()->LoadDialog(this, pParent, "get_dialog");

	SetSize(400,400);

	m_pTextCtrl = XRCCTRL(*this, "text_ctrl", wxTextCtrl);
	m_pHostCtrl = XRCCTRL(*this, "host_text_ctrl", wxTextCtrl);

	m_pUserCtrl = XRCCTRL(*this, "user_text_ctrl", wxTextCtrl);
	m_pPassCtrl = XRCCTRL(*this, "pass_text_ctrl", wxTextCtrl);

	if(m_pUserCtrl && m_pPassCtrl)
	{
		m_szDefaultUser = m_pUserCtrl->GetValue();
		m_szDefaultPass = m_pPassCtrl->GetValue();
	}
}

wxGetDialog::~wxGetDialog()
{

}

//////////////////////////////////////////////////////////////////////
// Event Handlers
//////////////////////////////////////////////////////////////////////

void wxGetDialog::OnGetUrl(wxCommandEvent& WXUNUSED(event))
{
	wxString szHost, szUser, szPass;

	if(m_pHostCtrl && m_pUserCtrl && m_pPassCtrl)
	{
		szHost = m_pHostCtrl->GetValue();
		szUser = m_pUserCtrl->GetValue();
		szPass = m_pPassCtrl->GetValue();

		wxCurlHTTP http(szHost);

		if(szUser != m_szDefaultUser)
			http.SetUsername(szUser);

		if(szPass != m_szDefaultPass)
			http.SetPassword(szPass);

		char*	szBuffer = NULL;

		if(http.Get(szBuffer) > 0)
		{
			if(m_pTextCtrl && szBuffer)
			{
				m_pTextCtrl->SetValue(szBuffer);
				free(szBuffer);
			}
		}
	}
}