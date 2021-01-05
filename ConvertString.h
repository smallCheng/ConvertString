#pragma once

class CConvertString
{
public:
	CConvertString(void);
	~CConvertString(void);

public:
	static WCHAR* CharToWChar(const char *pSourse);
	static char* WCharToChar(const WCHAR *pSourse);
	static std::string WCharToString(const WCHAR *pSourse);
	static char* CStringToChar(CString strSourse);
	static std::string CStringToString(CString strSource);
	static char* WCharToUTF8( const WCHAR* pSperce);
	static WCHAR* UTF8ToWChar(const char* pSource);
	static CString UTF8ToCString(const char* pSource);
	//static CString UTF8StringToCString(const std::string strSource);
	static std::string CStringToUTF8String(const CString strValue);
	static CString UTF8StringToCString(const std::string utf8str);
	static std::string UTF8StringToString(const std::string utf8str);

	static std::string UnicodeToUTF8(const std::wstring & wstr);
	static std::wstring UTF8ToUnicode(const std::string & str);
	static std::string UnicodeToANSI(const std::wstring & wstr);
	static std::wstring ANSIToUnicode(const std::string & str);
	static std::string UTF8ToANSI(const std::string & str);
	static std::string ANSIToUTF8(const std::string & str);
};
