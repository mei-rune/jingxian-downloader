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

#include <list>

class download_group
{
public:
	download_group();
	~download_group(void);

	//const jxString& Name() const;
	//void Name(const jxString& nm);

	//const jxString& Folder() const;
	//void Folder(const jxString& folder);

	//std::list<jxString>& Exts() const;
	//const std::list<jxString>& Exts() const;

private:
	
	//jxString m_name;		
	//jxString m_folder;	
	//jxString exts;		

	std::list<download_group> m_childs;
};

#endif // DOWNLOAD_GROUP_H