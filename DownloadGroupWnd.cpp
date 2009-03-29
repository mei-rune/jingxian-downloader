/***************************************************************
 * Name:      DownloadTaskList.cpp
 * Purpose:   Code for DownloadGroupWnd Class
 * Author:    runner.mei (runner.mei@gmail.com)
 * Created:   2008-11-15
 * Copyright: runner.mei
 * License:
 **************************************************************/

#include "pre_config.h"
#include <wx/tokenzr.h>
#include "icons/downloadGroupImageList.xpm"
#include "icons/jingxian_16.xpm"
#include "DownloadGroupWnd.h"
#include "GroupEditor.h"


IMPLEMENT_DYNAMIC_CLASS(wxDownloadGroupEvent, wxEvent);

wxDownloadGroupEvent::wxDownloadGroupEvent()
{
}

wxDownloadGroupEvent::wxDownloadGroupEvent(const wxDownloadGroupEvent& e)
{
}


DownloadGroupWnd::DownloadGroupWnd(wxXmlNode* nodeList,
			   wxWindow *parent, wxWindowID id,
               const wxPoint& pos,
               const wxSize& size,
               long style,
               const wxValidator& validator,
               const wxString& name )
			   : wxTreeCtrl( parent, id, pos, size, style, validator, name)
{
	AssignImageList( new wxImageList(16, 16, true) );
	this->GetImageList()->Add( wxImage( jingxian_16 ) );
	wxImage downloadGroupImage( downloadGroupImageList );

	for(int i = 0; i < 17; i ++ )
	{
		this->GetImageList()->Add( downloadGroupImage.GetSubImage( wxRect( 16*i, 0, 16,16 ) ) );
	}
	
	//AddRoot( _("jingxian_downloader"), 0 );
    wxTreeItemId root = AddRoot( _("jingxian_downloader"), 0 );

	if( NULL == nodeList)
	{
    insertItem( root, 2, _("downloading") );
	wxTreeItemId downloaded = insertItem( root, 4, _("downloaded") );
	insertItem( downloaded, 3, _("music") );
	}
	else
	{
		loadElement(root, nodeList );
	}

	Connect( wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler( DownloadGroupWnd::on_category_right_click ), NULL, this );
	Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( DownloadGroupWnd::on_category_select_changed ), NULL, this );
}

DownloadGroupWnd::~DownloadGroupWnd(void)
{
	Disconnect( wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler( DownloadGroupWnd::on_category_right_click ), NULL, this );
	Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( DownloadGroupWnd::on_category_select_changed ), NULL, this );
}


void DownloadGroupWnd::loadElement(wxTreeItemId parent, wxXmlNode* nodeList )
{
	for( wxXmlNode* nd = nodeList->GetChildren(); NULL != nd; nd = nd->GetNext() )
	{
		
		DownloadGroup* downloadGroup = new DownloadGroup(nd->GetName()
				, nd->GetPropVal(wxT("Folder"), nd->GetName() ));
		
		wxStringTokenizer tkz(nd->GetPropVal( "Exts" , wxT("") ), wxT(";"));
		while ( tkz.HasMoreTokens() )
		{
			downloadGroup->Exts().Add( tkz.GetNextToken().c_str() );
		}

		wxString iconString = nd->GetPropVal(wxT("Icon"), "3");
		long icon = ::wxAtoi( iconString );
		if( iconString.ToLong( &icon ) )
		{
			loadElement( InsertItem( parent, -1, downloadGroup->Name(),icon,-1, downloadGroup ), nd );
		}
		else
		{
			loadElement( InsertItem( parent, -1, downloadGroup->Name(),3,-1, downloadGroup ), nd );
		}
	}
}

wxTreeItemId DownloadGroupWnd::insertItem(wxTreeItemId parent,int icon, const wxChar* nm, const wxChar* folder, const wxStringList& exts)
{
	DownloadGroup* downloadGroup = new DownloadGroup(nm, folder, exts);
	return InsertItem( parent, 0, downloadGroup->Name(),icon,-1, downloadGroup );
}

wxTreeItemId DownloadGroupWnd::insertItem(wxTreeItemId parent, int icon,const wxChar* nm, const wxStringList& exts)
{
	DownloadGroup* downloadGroup = new DownloadGroup(nm, nm, exts);
	return InsertItem( parent, 0, downloadGroup->Name(),icon,-1, downloadGroup );
}


void DownloadGroupWnd::onPopupMenu( wxTreeEvent& e )
{
    wxMenu menu;
	Connect( menu.Append( wxID_ANY, _("&Open"))->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DownloadGroupWnd::onEditCategory ) );
	menu.AppendSeparator();
	Connect( menu.Append( wxID_ANY, _("&New category"))->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DownloadGroupWnd::onNewCategory ) );
	Connect( menu.Append( wxID_ANY, _("&Delete category"))->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DownloadGroupWnd::onDeleteCategory ) );
    menu.AppendSeparator();
	Connect( menu.Append( wxID_ANY, _("&Properties"))->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DownloadGroupWnd::onShowProperties ) );

    PopupMenu(&menu, e.GetPoint().x, e.GetPoint().y);
}

void DownloadGroupWnd::onSelectedGroup( wxTreeEvent& e )
{
	e.Skip(); 
}

void DownloadGroupWnd::onEditCategory( wxCommandEvent& e )
{
}

void DownloadGroupWnd::onNewCategory( wxCommandEvent& e )
{
	GroupEditor editor( this );
	if(wxID_OK != editor.ShowModal() )
		return;
}

void DownloadGroupWnd::onDeleteCategory( wxCommandEvent& e )
{
	if( wxID_OK != ::wxMessageBox( _("Are you sure?\r\nThis will delete all group downloads!"),
		_("Confirmation" ), wxOK |wxCANCEL, this ) )
		return;

	this->Delete( this->GetSelection() );
}


void DownloadGroupWnd::onShowProperties( wxCommandEvent& e )
{
	GroupEditor editor( this );
	if(wxID_OK != editor.ShowModal() )
		return;
}