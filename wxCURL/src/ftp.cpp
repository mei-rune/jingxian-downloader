/*******************************************
 *	base.cpp
 *	Created by Casey O'Donnell on Tue Jun 29 2004.
 *	Copyright (c) 2004 Casey O'Donnell. All rights reserved.
 *	Licence: wxWidgets Licence
 ******************************************/

#include "pre_config.h"
#include "wxcurl/wxcurl_config.h"
#include "wxcurl/ftp.h"

wxCurlFTP::wxCurlFTP(const wxString& szURL /*= wxEmptyString*/, const wxString& szUserName /*= wxEmptyString*/, const wxString& szPassword /*= wxEmptyString*/, wxEvtHandler* pEvtHandler /*= NULL*/, const bool& bSendUpdateEvents /*= false*/, const bool& bSendBeginEndEvents /*= false*/)
: wxCurlBase(szURL, szUserName, szPassword, pEvtHandler, bSendUpdateEvents, bSendBeginEndEvents),
  m_pQuote(NULL), m_pPreQuote(NULL), m_pPostQuote(NULL),
  m_bCreateMissingDirs(true), m_bUsePortOption(false), m_bUseEPRT(false), m_bUseEPSV(false), m_bAppend(false),
  m_tmMode(kASCII),
  m_szPortParam("-")
{
}

wxCurlFTP::~wxCurlFTP()
{
	ResetAllQuoteLists();
}

//////////////////////////////////////////////////////////////////////
// Member Data Access Methods
//////////////////////////////////////////////////////////////////////

void wxCurlFTP::SetTransferMode(const TransferMode& tmMode)
{
	m_tmMode = tmMode;
}

wxCurlFTP::TransferMode wxCurlFTP::GetTransferMode() const
{
	return m_tmMode;
}

void wxCurlFTP::SetToBinary()
{
	SetTransferMode(kBINARY);
}

void wxCurlFTP::SetToAscii()
{
	SetTransferMode(kASCII);
}

bool wxCurlFTP::IsAscii() const
{
	return m_tmMode == kASCII;
}

bool wxCurlFTP::IsBinary() const
{
	return m_tmMode == kBINARY;
}

void wxCurlFTP::UsePortOption(const bool& bUsePort)
{
	m_bUsePortOption = bUsePort;
}

bool wxCurlFTP::UsePortOption() const
{
	return m_bUsePortOption;
}

void wxCurlFTP::SetPortParam(const wxString& szParam /*= _T("-")*/)
{
	m_szPortParam = szParam;
}

wxString wxCurlFTP::GetPortParam() const
{
	return m_szPortParam;
}

void wxCurlFTP::UseEPRT(const bool& bUseEPRT)
{
	m_bUseEPRT = bUseEPRT;
}

bool wxCurlFTP::UseEPRT() const
{
	return m_bUseEPRT;
}

void wxCurlFTP::UseEPSV(const bool& bUseEPSV)
{
	m_bUseEPSV = bUseEPSV;
}

bool wxCurlFTP::UseEPSV() const
{
	return m_bUseEPSV;
}

void wxCurlFTP::AppendOnUpload(const bool& bAppend)
{
	m_bAppend = bAppend;
}

bool wxCurlFTP::AppendOnUpload() const
{
	return m_bAppend;
}

void wxCurlFTP::CreateMissingDirs(const bool& bCreateMissing)
{
	m_bCreateMissingDirs = bCreateMissing;
}

bool wxCurlFTP::CreateMissingDirs() const
{
	return m_bCreateMissingDirs;
}

bool wxCurlFTP::SetQuoteList(const wxArrayString& arrQuote)
{
	ResetQuoteList();

	for(unsigned int i = 0; i < arrQuote.Count(); i++)
	{
		m_pQuote = curl_slist_append(m_pQuote, arrQuote[i]);
	}

	return (m_pQuote != NULL);
}

bool wxCurlFTP::AppendQuote(const wxString& szQuote, const bool& bClear /*= false*/)
{
	if(bClear)
		ResetQuoteList();

	m_pQuote = curl_slist_append(m_pQuote, szQuote);

	return (m_pQuote != NULL);
}

bool wxCurlFTP::SetPreQuoteList(const wxArrayString& arrQuote)
{
	ResetPreQuoteList();

	for(unsigned int i = 0; i < arrQuote.Count(); i++)
	{
		m_pPreQuote = curl_slist_append(m_pPreQuote, arrQuote[i]);
	}

	return (m_pPreQuote != NULL);
}

bool wxCurlFTP::AppendPreQuote(const wxString& szQuote, const bool& bClear /*= false*/)
{
	if(bClear)
		ResetPreQuoteList();

	m_pPreQuote = curl_slist_append(m_pPreQuote, szQuote);

	return (m_pPreQuote != NULL);
}

bool wxCurlFTP::SetPostQuoteList(const wxArrayString& arrQuote)
{
	ResetPostQuoteList();

	for(unsigned int i = 0; i < arrQuote.Count(); i++)
	{
		m_pPostQuote = curl_slist_append(m_pPostQuote, arrQuote[i]);
	}

	return (m_pPostQuote != NULL);
}

bool wxCurlFTP::AppendPostQuote(const wxString& szQuote, const bool& bClear /*= false*/)
{
	if(bClear)
		ResetPostQuoteList();

	m_pPostQuote = curl_slist_append(m_pPostQuote, szQuote);

	return (m_pPostQuote != NULL);
}

//////////////////////////////////////////////////////////////////////
// Action Methods
//////////////////////////////////////////////////////////////////////

bool wxCurlFTP::Get(const wxString& szFilePath, const wxString& szRemoteFile /*= wxEmptyString*/)
{
	wxFFileOutputStream outStream(szFilePath);

	return Get(outStream, szRemoteFile);
}

size_t wxCurlFTP::Get(char*& buffer, const wxString& szRemoteFile /*= wxEmptyString*/)
{
	wxMemoryOutputStream outStream;

	buffer = NULL;
	size_t iRetVal = 0;

	if(Get(outStream, szRemoteFile))
	{
		iRetVal = outStream.GetSize();

		buffer = (char*)malloc(iRetVal + 1);

		if(buffer)
		{
			outStream.CopyTo(buffer, outStream.GetSize());
			buffer[iRetVal] = '\0';
			return iRetVal;
		}

		free(buffer);
		buffer = NULL;
	}

	return 0;
}

bool wxCurlFTP::Get(wxOutputStream& buffer, const wxString& szRemoteFile /*= wxEmptyString*/)
{
	if(m_pCURL && buffer.IsOk())
	{
		SetCurlHandleToDefaults();

		m_szCurrFullURL = m_szBaseURL + szRemoteFile;

		SetOpt(CURLOPT_URL, m_szCurrFullURL.c_str());
		SetOpt(CURLOPT_WRITEFUNCTION, wxcurl_stream_write);
		SetOpt(CURLOPT_WRITEDATA, (void*)&buffer);

		if(Perform())
		{
			GetInfo(CURLINFO_RESPONSE_CODE, &m_iResponseCode);

			return ((m_iResponseCode > 199) && (m_iResponseCode < 299));
		}
	}

	return false;
}

bool wxCurlFTP::Put(const wxString& szFilePath, const wxString& szRemoteFile /*= wxEmptyString*/)
{
	wxFFileInputStream inStream(szFilePath);

	return Put(inStream, szRemoteFile);
}

bool wxCurlFTP::Put(const char* buffer, size_t size, const wxString& szRemoteFile /*= wxEmptyString*/)
{
	wxMemoryInputStream inStream(buffer, size);

	return Put(inStream, szRemoteFile);
}

bool wxCurlFTP::Put(wxInputStream& buffer, const wxString& szRemoteFile /*= wxEmptyString*/)
{
	curl_off_t iSize = 0;

	if(m_pCURL && buffer.IsOk())
	{
		SetCurlHandleToDefaults();

		iSize = buffer.GetSize();

		if(iSize == (~(size_t)0))
			return false;

		m_szCurrFullURL = m_szBaseURL + szRemoteFile;

		SetOpt(CURLOPT_UPLOAD, TRUE);
		SetOpt(CURLOPT_URL, m_szCurrFullURL.c_str());
		SetOpt(CURLOPT_READFUNCTION, wxcurl_stream_read);
		SetOpt(CURLOPT_READDATA, (void*)&buffer);
		SetOpt(CURLOPT_INFILESIZE_LARGE, iSize);

		if(Perform())
		{
			GetInfo(CURLINFO_RESPONSE_CODE, &m_iResponseCode);

			return ((m_iResponseCode > 199) && (m_iResponseCode < 300));
		}
	}

	return false;
}

bool wxCurlFTP::MkDir(const wxString& szRemoteLoc /*= wxEmptyString*/)
{
	if(m_pCURL)
	{
		SetCurlHandleToDefaults();

		m_szCurrFullURL = m_szBaseURL + szRemoteLoc;

		if(m_szCurrFullURL.Last() != '/')
			m_szCurrFullURL += "/";

		SetOpt(CURLOPT_FTP_CREATE_MISSING_DIRS, TRUE);
		SetOpt(CURLOPT_URL, m_szCurrFullURL.c_str());
		SetOpt(CURLOPT_NOBODY, TRUE);

		if(Perform())
		{
			GetInfo(CURLINFO_RESPONSE_CODE, &m_iResponseCode);

			return ((m_iResponseCode > 199) && (m_iResponseCode < 300));
		}
	}

	return false;
}

bool wxCurlFTP::RmDir(const wxString& szRemoteLoc /*= wxEmptyString*/)
{
	if(m_pCURL)
	{
		SetCurlHandleToDefaults();

		m_szCurrFullURL = m_szBaseURL + szRemoteLoc;

		if(m_szCurrFullURL.Last() != '/')
			m_szCurrFullURL += "/";

		m_szCurrFullPath = m_szCurrFullURL.Left(m_szCurrFullURL.Len() - 1).BeforeLast('/');
		m_szCurrFullPath += "/";
		m_szCurrFilename = m_szCurrFullURL.Left(m_szCurrFullURL.Len() - 1).AfterLast('/');

		if(m_szCurrFilename.IsEmpty())
			return false;

		AppendPostQuote("RMD " + m_szCurrFilename, true);

		SetCurlHandleQuoteOpts();

		SetOpt(CURLOPT_URL, m_szCurrFullPath.c_str());
		SetOpt(CURLOPT_NOBODY, TRUE);

		if(Perform())
		{
			ResetAllQuoteLists();

			GetInfo(CURLINFO_RESPONSE_CODE, &m_iResponseCode);

			return ((m_iResponseCode > 199) && (m_iResponseCode < 300));
		}

		ResetAllQuoteLists();
	}

	return false;
}

bool wxCurlFTP::Delete(const wxString& szRemoteLoc /*= wxEmptyString*/)
{
	if(m_pCURL)
	{
		SetCurlHandleToDefaults();

		m_szCurrFullURL = m_szBaseURL + szRemoteLoc;
		m_szCurrFullPath = m_szCurrFullURL.BeforeLast('/');
		m_szCurrFullPath += "/";
		m_szCurrFilename = m_szCurrFullURL.AfterLast('/');

		if(m_szCurrFilename.IsEmpty())
			return RmDir(szRemoteLoc);

		AppendPostQuote("DELE " + m_szCurrFilename, true);

		SetCurlHandleQuoteOpts();

		SetOpt(CURLOPT_URL, m_szCurrFullPath.c_str());
		SetOpt(CURLOPT_NOBODY, TRUE);

		if(Perform())
		{
			ResetAllQuoteLists();

			GetInfo(CURLINFO_RESPONSE_CODE, &m_iResponseCode);

			return ((m_iResponseCode > 199) && (m_iResponseCode < 300));
		}

		ResetAllQuoteLists();
	}

	return false;
}

bool wxCurlFTP::Rename(const wxString& szRemoteLocName, const wxString& szRemoteFile /*= wxEmptyString*/)
{
	if(m_pCURL)
	{
		SetCurlHandleToDefaults();

		m_szCurrFullURL = m_szBaseURL + szRemoteFile;
		m_szCurrFullPath = m_szCurrFullURL.BeforeLast('/');
		m_szCurrFullPath += "/";
		m_szCurrFilename = m_szCurrFullURL.AfterLast('/');

		if(m_szCurrFilename.IsEmpty())
			return false;

		AppendPostQuote("RNFR " + m_szCurrFilename, true);
		AppendPostQuote("RNTO " + szRemoteLocName);

		SetCurlHandleQuoteOpts();

		SetOpt(CURLOPT_URL, m_szCurrFullPath.c_str());
		SetOpt(CURLOPT_NOBODY, TRUE);

		if(Perform())
		{
			ResetAllQuoteLists();

			GetInfo(CURLINFO_RESPONSE_CODE, &m_iResponseCode);

			return ((m_iResponseCode > 199) && (m_iResponseCode < 300));
		}

		ResetAllQuoteLists();
	}

	return false;
}

bool wxCurlFTP::List(const wxString& szRemoteLoc /*= wxEmptyString*/)
{
	if(m_pCURL)
	{
		SetCurlHandleToDefaults();

		m_szCurrFullURL = m_szBaseURL + szRemoteLoc;

		SetOpt(CURLOPT_URL, m_szCurrFullURL.c_str());
		SetOpt(CURLOPT_CUSTOMREQUEST, "LIST");
		SetOpt(CURLOPT_WRITEFUNCTION, wxcurl_str_write);
		SetOpt(CURLOPT_WRITEDATA, (void*)&m_szResponseBody);

		if(Perform())
		{
			GetInfo(CURLINFO_RESPONSE_CODE, &m_iResponseCode);

			return ((m_iResponseCode > 199) && (m_iResponseCode < 300));
		}
	}

	return false;
}

bool wxCurlFTP::Nlst(const wxString& szRemoteLoc /*= wxEmptyString*/)
{
	if(m_pCURL)
	{
		SetCurlHandleToDefaults();

		m_szCurrFullURL = m_szBaseURL + szRemoteLoc;

		SetOpt(CURLOPT_URL, m_szCurrFullURL.c_str());
		SetOpt(CURLOPT_CUSTOMREQUEST, "NLST");
		SetOpt(CURLOPT_WRITEFUNCTION, wxcurl_str_write);
		SetOpt(CURLOPT_WRITEDATA, (void*)&m_szResponseBody);

		if(Perform())
		{
			GetInfo(CURLINFO_RESPONSE_CODE, &m_iResponseCode);

			return ((m_iResponseCode > 199) && (m_iResponseCode < 300));
		}
	}

	return false;
}

bool wxCurlFTP::Info(const wxString& szRemoteLoc /*= wxEmptyString*/)
{
	if(m_pCURL)
	{
		SetCurlHandleToDefaults();

		m_szCurrFullURL = m_szBaseURL + szRemoteLoc;

		SetOpt(CURLOPT_HEADER, TRUE);
		SetOpt(CURLOPT_NOBODY, TRUE);
		SetOpt(CURLOPT_URL, m_szCurrFullURL.c_str());
		SetOpt(CURLOPT_WRITEFUNCTION, wxcurl_str_write);
		SetOpt(CURLOPT_WRITEDATA, (void*)&m_szResponseBody);

		if(Perform())
		{
			GetInfo(CURLINFO_RESPONSE_CODE, &m_iResponseCode);

			return ((m_iResponseCode > 199) && (m_iResponseCode < 299));
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////
// Helper Methods
//////////////////////////////////////////////////////////////////////

void wxCurlFTP::SetCurlHandleToDefaults()
{
	wxCurlBase::SetCurlHandleToDefaults();

	m_szCurrFilename = wxEmptyString;
	m_szCurrFullPath = wxEmptyString;

	if(m_bUsePortOption)
	{
		SetOpt(CURLOPT_FTPPORT, m_szPortParam.c_str());
	}

	if(m_bUseEPRT)
	{
		SetOpt(CURLOPT_FTP_USE_EPRT, TRUE);
	}

	if(m_bUseEPSV)
	{
		SetOpt(CURLOPT_FTP_USE_EPSV, TRUE);
	}

	if(m_bCreateMissingDirs)
	{
		SetOpt(CURLOPT_FTP_CREATE_MISSING_DIRS, TRUE);
	}

	if(m_bAppend)
	{
		SetOpt(CURLOPT_FTPAPPEND, TRUE);
	}

	if(m_tmMode == kASCII)
	{
		SetOpt(CURLOPT_TRANSFERTEXT, TRUE);
	}
}

void wxCurlFTP::SetCurlHandleQuoteOpts()
{
	if(m_pQuote)
	{
		SetOpt(CURLOPT_QUOTE, m_pQuote);
	}

	if(m_pPreQuote)
	{
		SetOpt(CURLOPT_PREQUOTE, m_pPreQuote);
	}

	if(m_pPostQuote)
	{
		SetOpt(CURLOPT_POSTQUOTE, m_pPostQuote);
	}
}

void wxCurlFTP::ResetAllQuoteLists()
{
	ResetQuoteList();
	ResetPreQuoteList();
	ResetPostQuoteList();
}

void wxCurlFTP::ResetQuoteList()
{
	if(m_pQuote)
	{
		curl_slist_free_all(m_pQuote);

		m_pQuote = NULL;

		SetOpt(CURLOPT_QUOTE, NULL);
	}
}

void wxCurlFTP::ResetPreQuoteList()
{
	if(m_pPreQuote)
	{
		curl_slist_free_all(m_pPreQuote);

		m_pPreQuote = NULL;

		SetOpt(CURLOPT_PREQUOTE, NULL);
	}
}

void wxCurlFTP::ResetPostQuoteList()
{
	if(m_pPostQuote)
	{
		curl_slist_free_all(m_pPostQuote);

		m_pPostQuote = NULL;

		SetOpt(CURLOPT_POSTQUOTE, NULL);
	}
}



