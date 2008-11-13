///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include <wx/aui/auibook.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////
#define ID_USER_START                                                 2000
#define wxID_COMMAND_MENU_NEW_DOWNLOAD                                ID_USER_START+1
#define wxID_COMMAND_MENU_ADD_BATCH_DOWNLOAD                          ID_USER_START+2
#define wxID_COMMAND_MENU_LAUNCH_DOWNLOAD_FILE                        ID_USER_START+3
#define wxID_COMMAND_MENU_BROWSE_FOLDER                               ID_USER_START+4
#define wxID_COMMAND_MENU_CHECK_FOR_FILE_UPDATE                       ID_USER_START+5
#define wxID_COMMAND_MENU_DOWNLOAD_AGAIN                              ID_USER_START+6
#define wxID_COMMAND_MENU_START_DOWNLOAD                              ID_USER_START+7
#define wxID_COMMAND_MENU_PAUSE_DOWNLOAD                              ID_USER_START+8
#define wxID_COMMAND_MENU_SCHEDULE_DOWNLOAD                           ID_USER_START+9
#define wxID_COMMAND_MENU_START_DOWNLOAD_ALL                          ID_USER_START+10
#define wxID_COMMAND_MENU_PAUSE_DOWNLOAD_ALL                          ID_USER_START+11
#define wxID_COMMAND_MENU_IMPORT_DOWNLOAD_LIST                        ID_USER_START+12
#define wxID_COMMAND_MENU_IMPORT_BROKEN_DOWNLOADS                     ID_USER_START+13
#define wxID_COMMAND_MENU_IMPORT_LINKS_FROM_LOCAL_FILE                ID_USER_START+14
#define wxID_COMMAND_MENU_EXPORT_DOWNLOAD_LIST                        ID_USER_START+15
#define wxID_COMMAND_MENU_EXPORT_DOWNLOAD_INFORMATION                 ID_USER_START+16
#define wxID_COMMAND_MENU_EXIT                                        ID_USER_START+17
#define wxID_COMMAND_MENU_SELECT_ALL                                  ID_USER_START+18
#define wxID_COMMAND_MENU_INVERT_SELECTION                            ID_USER_START+19
#define wxID_COMMAND_MENU_FIND                                        ID_USER_START+20
#define wxID_COMMAND_MENU_FIND_NEXT                                   ID_USER_START+21
#define wxID_COMMAND_MENU_MOVE_UP                                     ID_USER_START+22
#define wxID_COMMAND_MENU_MOVE_DOWN                                   ID_USER_START+23
#define wxID_COMMAND_MENU_DELETE_DOWNLOAD                             ID_USER_START+24
#define wxID_COMMAND_MENU_MOVE_TO                                     ID_USER_START+25
#define wxID_COMMAND_MENU_VIEW_TOOLBAR                                ID_USER_START+26
#define wxID_COMMAND_MENU_VIEW_STATUSBAR                              ID_USER_START+27
#define wxID_COMMAND_MENU_VIEW_DETAIL                                 ID_USER_START+28
#define wxID_COMMAND_MENU_VIEW_DROP_ZONE                              ID_USER_START+29
#define wxID_COMMAND_MENU_VIEW_CATEGORY                               ID_USER_START+30
#define wxID_COMMAND_MENU_EXPORT_DOWNLOAD                             ID_USER_START+31
#define wxID_COMMAND_MENU_RENAME_FILE                                 ID_USER_START+32
#define wxID_COMMAND_MENU_COMMET_AS_FILENAME                          ID_USER_START+33
#define wxID_COMMAND_MENU_NEW_CATEGORY                                ID_USER_START+34
#define wxID_COMMAND_MENU_MOVE_CATEGORY                               ID_USER_START+35
#define wxID_COMMAND_MENU_DELETE_CATEGORY                             ID_USER_START+36
#define wxID_COMMAND_MENU_CATEGORY_PROPERTIES                         ID_USER_START+37
#define wxID_COMMAND_MENU_NEW_DATABASE                                ID_USER_START+38
#define wxID_COMMAND_MENU_OPEN_DATABASE                               ID_USER_START+39
#define wxID_COMMAND_MENU_MERGE_DATABASE                              ID_USER_START+40
#define wxID_COMMAND_MENU_SAVE_DATABASE                               ID_USER_START+41
#define wxID_COMMAND_MENU_BACKUP_TO_DATABASE                          ID_USER_START+42
#define wxID_COMMAND_MENU_IMPORT_DATABASE_FROM_PREVIOUS_FILE          ID_USER_START+43
#define wxID_COMMAND_MENU_IMPORT_DATABASE_FROM_PREVIOUS_BATCH_FILE    ID_USER_START+44
#define wxID_COMMAND_MENU_VIEW_DOWNLOAD_PROPERTIES                    ID_USER_START+45
#define wxID_COMMAND_MENU_VIEW_PROPERTIES_HISTORY                     ID_USER_START+46
#define wxID_COMMAND_MENU_CONNECT_OR_DISCONNECT                       ID_USER_START+47
#define wxID_COMMAND_MENU_SAVE_AS_DEFAULT                             ID_USER_START+48
#define wxID_COMMAND_MENU_SHOW_DEFAULT_DOWNLOAD_PROPERTIES            ID_USER_START+49
#define wxID_COMMAND_MENU_OPTIONS                                     ID_USER_START+50
#define wxID_COMMAND_MENU_HELP                                        ID_USER_START+51
#define wxID_COMMAND_MENU_CHECK_FOR_A_NEW_VERSION                     ID_USER_START+52
#define wxID_COMMAND_MENU_ABOUT                                       ID_USER_START+53
#define wxID_COMMAND_MENU_COPY_URL_TO_CLIPBROAD                       ID_USER_START+54
#define wxID_COMMAND_TOOL_NEW_DOWNLOAD                                ID_USER_START+55
#define wxID_COMMAND_TOOL_START_DOWNLOAD                              ID_USER_START+56
#define wxID_COMMAND_TOOL_PAUSE_DOWNLOAD                              ID_USER_START+57
#define wxID_COMMAND_TOOL_DELETE_DOWNLOAD                             ID_USER_START+58
#define wxID_COMMAND_TOOL_OPEN_DOWNLOAD                               ID_USER_START+59
#define wxID_COMMAND_TOOL_BROWSE_FOLDER                               ID_USER_START+60
#define wxID_COMMAND_TOOL_DOWNLOAD_PROPERTIES                         ID_USER_START+61
#define wxID_COMMAND_TOOL_MOVE_UP                                     ID_USER_START+62
#define wxID_COMMAND_TOOL_MOVE_DOWN                                   ID_USER_START+63
#define wxID_COMMAND_TOOL_DOWNLOAD_OPTION                             ID_USER_START+64
#define wxID_COMMAND_TOOL_FIND_DOWNLOAD                               ID_USER_START+65
#define wxID_COMMAND_TOOL_FIND_NEXT_DOWNLOAD                          ID_USER_START+66
#define wxID_WINDOW_DOWNLOADSPLITTER                                  ID_USER_START+67

///////////////////////////////////////////////////////////////////////////////
/// Class jxFrame
///////////////////////////////////////////////////////////////////////////////
class jxFrame : public wxFrame 
{
	private:
	
		wxBitmap m_bitmap_browse_folder[2];
		wxBitmap m_bitmap_delete_download[2];
		wxBitmap m_bitmap_download_properties[2];
		wxBitmap m_bitmap_find[2];
		wxBitmap m_bitmap_find_next[2];
		wxBitmap m_bitmap_move_down[2];
		wxBitmap m_bitmap_move_up[2];
		wxBitmap m_bitmap_new_download[2];
		wxBitmap m_bitmap_open_download_file[2];
		wxBitmap m_bitmap_options[2];
		wxBitmap m_bitmap_pause_download[2];
		wxBitmap m_bitmap_start_download[2];

		void initBitmap(const wxBitmap& xpm, int index );
		void initialize();

		void initializeDownloadList();
		void initializeCategoryTree();

		wxToolBar* createToolBar();
		wxMenuBar* createMenuBar();
        wxPanel* createDownloadPanel( wxWindow* mainSplitter );
        wxPanel* createTreePanel( wxWindow* mainSplitter );
        wxPanel* createGraphPanel( wxAuiNotebook* downloadBook );
        wxPanel* createLogPanel( wxAuiNotebook* downloadBook );

	protected:

		wxTreeCtrl* m_category_tree;
		wxListCtrl* m_download_list;

		wxTreeCtrl* m_download_thread_view;
		wxListCtrl* m_download_txt_view;
		
		// event handlers, overide them in your derived class
		 void on_new_download( wxCommandEvent& e );
		 void on_add_batch_dwonload( wxCommandEvent& e );
		 void on_launch_dwonload_file( wxCommandEvent& e );
		 void on_browse_folder( wxCommandEvent& e );
		 void on_check_for_file_update( wxCommandEvent& e );
		 void on_download_again( wxCommandEvent& e );
		 void on_start_download( wxCommandEvent& e );
		 void on_pause_download( wxCommandEvent& e );
		 void on_schedule_download( wxCommandEvent& e );
		 void on_start_all_downloads( wxCommandEvent& e );
		 void on_pause_all_downloads( wxCommandEvent& e );
		 void on_import_download_list( wxCommandEvent& e );
		 void on_import_broken_downloads( wxCommandEvent& e );
		 void on_import_links_from_local_file( wxCommandEvent& e );
		 void on_export_download_list( wxCommandEvent& e );
		 void on_export_download_information( wxCommandEvent& e );
		 void on_exit( wxCommandEvent& e );
		 void on_select_all_downloads( wxCommandEvent& e );
		 void on_invert_selection( wxCommandEvent& e );
		 void on_find_download( wxCommandEvent& e );
		 void on_find_next_download( wxCommandEvent& e );
		 void on_move_up( wxCommandEvent& e );
		 void on_move_down( wxCommandEvent& e );
		 void on_delete_download( wxCommandEvent& e );
		 void on_move_to( wxCommandEvent& e );
		 void on_copy_url_to_clipbroad( wxCommandEvent& e );
		 void on_show_detail_panel( wxCommandEvent& e );
		 void on_drop_zone_window( wxCommandEvent& e );
		 void on_show_class_panel( wxCommandEvent& e );
		 void on_export_download_file( wxCommandEvent& e );
		 void on_rename_file( wxCommandEvent& e );
		 void on_rename_commet_as_filename( wxCommandEvent& e );
		 void on_new_category( wxCommandEvent& e );
		 void on_move_category_to( wxCommandEvent& e );
		 void on_delete_category( wxCommandEvent& e );
		 void on_show_category_properties_window( wxCommandEvent& e );
		 void on_new_database( wxCommandEvent& e );
		 void on_open_database( wxCommandEvent& e );
		 void on_merge_database( wxCommandEvent& e );
		 void on_save_database( wxCommandEvent& e );
		 void on_backup_to_database( wxCommandEvent& e );
		 void on_imprt_previous_file_to_database( wxCommandEvent& e );
		 void on_imprt_previous_batch_file_to_database( wxCommandEvent& e );
		 void on_show_download_properties_window( wxCommandEvent& e );
		 void on_show_properties_history_window( wxCommandEvent& e );
		 void on_connect_or_disconnect( wxCommandEvent& e );
		 void on_save_option_as_defauilt( wxCommandEvent& e );
		 void on_show_option_window( wxCommandEvent& e );
		 void on_goto_online_help( wxCommandEvent& e );
		 void on_check_for_a_new_version( wxCommandEvent& e );
		 void on_about( wxCommandEvent& e );
		 void on_main_splitter_sash_position_changed( wxSplitterEvent& e );
		 void on_category_right_click( wxTreeEvent& e );
		 void on_category_select_changed( wxTreeEvent& e );
		 void on_download_list_select_changed( wxListEvent& e );
		 void on_download_threads_right_click( wxTreeEvent& e );
		 void on_download_list_select_changed( wxTreeEvent& e );
		 void on_splitterOnIdle( wxIdleEvent& e);

	
	public:
		jxFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("jinxian downloader"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 530,495 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~jxFrame();
};

///////////////////////////////////////////////////////////////////////////////
/// Class optionDialog
///////////////////////////////////////////////////////////////////////////////
class optionDialog : public wxDialog 
{
	private:
	
	protected:
		wxTreeCtrl* m_option_tree;
	
	public:
		optionDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Options..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 689,551 ), long style = wxDEFAULT_DIALOG_STYLE );
		~optionDialog();
	
};

#endif //MAINFRAME_H
