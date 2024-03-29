/*******************************************
 *	base.cpp
 *	Created by Casey O'Donnell on Tue Jun 29 2004.
 *	Copyright (c) 2004 Casey O'Donnell. All rights reserved.
 *	Licence: wxWidgets Licence
 ******************************************/

#include "wxcurl/wxcurl_config.h"
#include <wx/xrc/xmlres.h>
#include <wxcurl/dav.h>
#include "wxMkcolDialog.h"

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
IMPLEMENT_CLASS(wxMkcolDialog, wxDialog)
BEGIN_EVENT_TABLE(wxMkcolDialog, wxDialog)
	EVT_BUTTON(XRCID("mkcol_button"), wxMkcolDialog::OnMkcol)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

wxMkcolDialog::wxMkcolDialog(wxWindow* pParent)
{
	wxXmlResource::Get()->LoadDialog(this, pParent, "mkcol_dialog");

	SetSize(400, -1);

	m_pMkcolCtrl	= XRCCTRL(*this, "mkcol_text_ctrl", wxTextCtrl);
	m_pUserCtrl		= XRCCTRL(*this, "user_text_ctrl", wxTextCtrl);
	m_pPassCtrl		= XRCCTRL(*this, "pass_text_ctrl", wxTextCtrl);

	m_pResponseCtrl	= XRCCTRL(*this, "response_text_ctrl", wxTextCtrl);

	if(m_pMkcolCtrl && m_pUserCtrl && m_pPassCtrl)
	{
		m_szDefaultMkcol	= m_pMkcolCtrl->GetValue();
		m_szDefaultUser		= m_pUserCtrl->GetValue();
		m_szDefaultPass		= m_pPassCtrl->GetValue();
	}
}

wxMkcolDialog::~wxMkcolDialog()
{

}

//////////////////////////////////////////////////////////////////////
// Event Handlers
//////////////////////////////////////////////////////////////////////

void wxMkcolDialog::OnMkcol(wxCommandEvent& WXUNUSED(event))
{
	if(m_pMkcolCtrl && m_pUserCtrl && m_pPassCtrl)
	{
		wxString szMkcol	= m_pMkcolCtrl->GetValue();
		wxString szUser		= m_pUserCtrl->GetValue();
		wxString szPass		= m_pPassCtrl->GetValue();

		wxString szResponse;

		if((szMkcol == m_szDefaultMkcol))
		{
			wxMessageBox("Please change the MKCOL location.", "Error...", wxICON_INFORMATION|wxOK, this);
		}
		else if((szUser == m_szDefaultUser) && (szPass == m_szDefaultPass))
		{
			wxMessageBox("Please change the username or password.", "Error...", wxICON_INFORMATION|wxOK, this);
		}
		else
		{
			// Do it!
			wxCurlDAV dav(szMkcol, szUser, szPass);

			if(dav.Mkcol())
			{
					szResponse = "SUCCESS!\n\n";
					szResponse += wxString::Format("\nResponse Code: %d\n\n", dav.GetResponseCode());
					szResponse += dav.GetResponseHeader();
					szResponse += "\n\n";
					szResponse += dav.GetResponseBody();

					if(m_pResponseCtrl)
						m_pResponseCtrl->SetValue(szResponse);
			}
			else
			{
					szResponse = "FAILURE!\n\n";
					szResponse += wxString::Format("\nResponse Code: %d\n\n", dav.GetResponseCode());
					szResponse += dav.GetResponseHeader();
					szResponse += "\n\n";
					szResponse += dav.GetResponseBody();
					szResponse += "\n\n";
					szResponse += dav.GetErrorString();

					if(m_pResponseCtrl)
						m_pResponseCtrl->SetValue(szResponse);
			}
		}
	}
}

