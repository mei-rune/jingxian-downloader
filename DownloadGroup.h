/***************************************************************
 * Name:      DownloadGroup.h
 * Purpose:   Defines DownloadGroup Class
 * Author:    runner.mei (runner.mei@gmail.com)
 * Created:   2008-11-15
 * Copyright: runner.mei
 * License:
 **************************************************************/

#ifndef DOWNLOAD_GROUP_H
#define DOWNLOAD_GROUP_H

#include <wx/string.h>
#include <wx/list.h>
#include <wx/treectrl.h>

class DownloadGroup : public wxTreeItemData
{
public:
	DownloadGroup();
	DownloadGroup(const wxChar* nm, const wxChar* folder);
	DownloadGroup(const wxChar* nm, const wxChar* folder, const wxStringList& exts);
	~DownloadGroup(void);

	const wxString& Name() const;
	void Name(const wxString& nm);

	const wxString& Folder() const;
	void Folder(const wxString& folder);

	wxStringList& Exts();
	const wxStringList& Exts() const;


    //DECLARE_DYNAMIC_CLASS(DownloadGroup);
private:

	int m_id;	
	wxString m_name;
	wxString m_folder;
	wxString m_icon;
	wxStringList m_exts;
};

#endif // DOWNLOAD_GROUP_H