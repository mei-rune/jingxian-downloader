/***************************************************************
 * Name:      VirtualFileSystem.cpp
 * Purpose:   Defines VirtualFileSystem Class
 * Author:    runner.mei (runner.mei@gmail.com)
 * Created:   2008-11-14
 * Copyright: runner.mei ()
 * License:
 **************************************************************/

#include "pre_config.h"
#include "VirtualFileSystem.h"


VirtualFileSystem VirtualFileSystem::_virtualFS;

VirtualFileSystem::VirtualFileSystem(void)
:_config( wxT("jx.config") ){
}

VirtualFileSystem::~VirtualFileSystem(void)
{
}


VirtualFileSystem& VirtualFileSystem::Get()
{
	return _virtualFS;
}
	
const wxFileName& VirtualFileSystem::GetConfig() const
{
	return _config;
}

	
void VirtualFileSystem::SetBaseDirectory( const wxString& dir)
{
	_baseDirectory = dir;
	_config = wxFileName( dir, wxT("jx.config") );
}