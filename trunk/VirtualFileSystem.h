/***************************************************************
 * Name:      VirtualFileSystem.h
 * Purpose:   Defines VirtualFileSystem Class
 * Author:    runner.mei (runner.mei@gmail.com)
 * Created:   2008-11-14
 * Copyright: runner.mei ()
 * License:
 **************************************************************/

#ifndef VIRTUALFILESYSTEM_H
#define VIRTUALFILESYSTEM_H


#include "wx/filename.h"

class VirtualFileSystem
{
public:
	~VirtualFileSystem(void);

	static VirtualFileSystem& Get();

	const wxFileName& GetConfig() const;

	friend class jxApp;
private:
	
	VirtualFileSystem(void);

	void SetBaseDirectory( const wxString& dir);
	
	wxString _baseDirectory;

	wxFileName _config;

	static VirtualFileSystem _virtualFS;
};


#endif // VIRTUALFILESYSTEM_H