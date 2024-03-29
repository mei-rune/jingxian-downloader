/*******************************************
 *	base.cpp
 *	Created by Casey O'Donnell on Tue Jun 29 2004.
 *	Copyright (c) 2004 Casey O'Donnell. All rights reserved.
 *	Licence: wxWidgets Licence
 ******************************************/

#include "wxcurl/wxcurl_config.h"
#include "wx/xrc/xmlres.h"              // XRC XML resouces
#include <wxcurl/ftp.h>
#include "wxFTPMkdirDialog.h"

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
IMPLEMENT_CLASS(wxFTPMkdirDialog, wxDialog);

BEGIN_EVENT_TABLE(wxFTPMkdirDialog, wxDialog)
	EVT_BUTTON(XRCID("mkdir_button"), wxFTPMkdirDialog::OnMkdir)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

wxFTPMkdirDialog::wxFTPMkdirDialog(wxWindow* pParent)
{
	wxXmlResource::Get()->LoadDialog(this, pParent, "mkdir_ftp_dialog");

	SetSize(400, -1);

	m_pMkdirCtrl	= XRCCTRL(*this, "mkdir_text_ctrl", wxTextCtrl);
	m_pUserCtrl		= XRCCTRL(*this, "user_text_ctrl", wxTextCtrl);
	m_pPassCtrl		= XRCCTRL(*this, "pass_text_ctrl", wxTextCtrl);

	m_pResponseCtrl	= XRCCTRL(*this, "response_text_ctrl", wxTextCtrl);

	if(m_pMkdirCtrl && m_pUserCtrl && m_pPassCtrl)
	{
		m_szDefaultMkdir	= m_pMkdirCtrl->GetValue();
		m_szDefaultUser		= m_pUserCtrl->GetValue();
		m_szDefaultPass		= m_pPassCtrl->GetValue();
	}
}

wxFTPMkdirDialog::~wxFTPMkdirDialog()
{

}

//////////////////////////////////////////////////////////////////////
// Event Handlers
//////////////////////////////////////////////////////////////////////

void wxFTPMkdirDialog::OnMkdir(wxCommandEvent& WXUNUSED(event))
{
	if(m_pMkdirCtrl && m_pUserCtrl && m_pPassCtrl)
	{
		wxString szMkdir	= m_pMkdirCtrl->GetValue();
		wxString szUser		= m_pUserCtrl->GetValue();
		wxString szPass		= m_pPassCtrl->GetValue();

		wxString szResponse;

		if((szMkdir == m_szDefaultMkdir))
		{
			wxMessageBox("Please change the MKDIR location.", "Error...", wxICON_INFORMATION|wxOK, this);
		}
		else if((szUser == m_szDefaultUser) && (szPass == m_szDefaultPass))
		{
			wxMessageBox("Please change the username or password.", "Error...", wxICON_INFORMATION|wxOK, this);
		}
		else
		{
			// Do it!
			wxCurlFTP ftp(szMkdir, szUser, szPass);

			if(ftp.MkDir())
			{
					szResponse = "SUCCESS!\n\n";
					szResponse += wxString::Format("\nResponse Code: %d\n\n", ftp.GetResponseCode());
					szResponse += ftp.GetResponseHeader();
					szResponse += "\n\n";
					szResponse += ftp.GetResponseBody();

					if(m_pResponseCtrl)
						m_pResponseCtrl->SetValue(szResponse);
			}
			else
			{
					szResponse = "FAILURE!\n\n";
					szResponse += wxString::Format("\nResponse Code: %d\n\n", ftp.GetResponseCode());
					szResponse += ftp.GetResponseHeader();
					szResponse += "\n\n";
					szResponse += ftp.GetResponseBody();
					szResponse += "\n\n";
					szResponse += ftp.GetErrorString();

					if(m_pResponseCtrl)
						m_pResponseCtrl->SetValue(szResponse);
			}
		}
	}
}

