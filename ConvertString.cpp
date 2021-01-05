#include "StdAfx.h"
#include "ConvertString.h"
#include <locale>
#include <codecvt>        // std::codecvt_utf8
#include <cstdint>        // std::uint_least32_t
#include<atlconv.h>


CConvertString::CConvertString(void)
{
}

CConvertString::~CConvertString(void)
{

}

WCHAR* CConvertString::CharToWChar(const char *pSourse)
{
	USES_CONVERSION;
	return A2W(pSourse);
}

char* CConvertString::WCharToChar(const WCHAR *pSourse)
{
	USES_CONVERSION;
	return W2A(pSourse);
}

std::string CConvertString::WCharToString(const WCHAR * pSourse)
{
	USES_CONVERSION;
	std::string strTemp = W2A(pSourse);
	return strTemp;
}

char* CConvertString::CStringToChar(CString strSourse)
{
	WCHAR *pSource = strSourse.GetBuffer();
	char* pData = WCharToChar(pSource);
	strSourse.ReleaseBuffer();
	return pData;
}

std::string CConvertString::CStringToString(CString strSource)
{
	USES_CONVERSION;
	std::string strTemp = T2A(strSource);
	return strTemp;

}

//wchar_t转成UTF-8
char* CConvertString::WCharToUTF8(const WCHAR* pSoruce)
{
	if (pSoruce == NULL)
	{
		return NULL;
	}
	int a_nSrcSize = wcslen(pSoruce);
	char *pData = NULL;
	if (a_nSrcSize <= 0)
	{
		return pData;

	}
	pData = new char[a_nSrcSize * 4];
	memset(pData, 0, sizeof(char)*a_nSrcSize * 4);

	WideCharToMultiByte(CP_UTF8, 0, pSoruce, -1, pData, a_nSrcSize * 4, NULL, NULL);
	return pData;
}

WCHAR* CConvertString::UTF8ToWChar(const char* pSource)
{
	if (pSource == NULL)
	{
		return NULL;
	}
	int a_nSrcSize = strlen(pSource);
	wchar_t* pData = NULL;
	if (a_nSrcSize < 0)
	{
		return NULL;
	}
	pData = new wchar_t[a_nSrcSize * 4];
	memset(pData, 0, sizeof(wchar_t)*a_nSrcSize * 4);

	MultiByteToWideChar(CP_UTF8, 0, pSource, -1, pData, a_nSrcSize * 4);

	return pData;

}

CString CConvertString::UTF8ToCString(const char* pSource)
{
	if (pSource == NULL)
		return L"";
	CString strData = L"";
	wchar_t *pDara = UTF8ToWChar(pSource);
	strData = pDara;
	delete pDara;
	pDara = NULL;
	return strData;
}

//CString CConvertString::UTF8StringToCString(const std::string strSource)
//{
//	CString strData=L"";
//	if(strSource.empty())
//		return "";
//	wchar_t *pData=UTF8ToWChar(strSource.c_str());
//	strData=pData;
//	delete pData;
//	pData=NULL;
//
//	return strData;
//}

std::string CConvertString::CStringToUTF8String(const CString strValue)
{
	std::wstring wbuffer;
#ifdef _UNICODE
	wbuffer.assign(strValue.GetString(), strValue.GetLength());
#else
	/*
	* 转换ANSI到UNICODE
	* 获取转换后长度
	*/
	int length = ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, (LPCTSTR)strValue, -1, NULL, 0);
	wbuffer.resize(length);
	/* 转换 */
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strValue, -1, (LPWSTR)(wbuffer.data()), wbuffer.length());
#endif

	/* 获取转换后长度 */
	int length = WideCharToMultiByte(CP_UTF8, 0, wbuffer.data(), wbuffer.size(), NULL, 0, NULL, NULL);
	/* 获取转换后内容 */
	std::string buffer;
	buffer.resize(length);

	WideCharToMultiByte(CP_UTF8, 0, strValue, -1, (LPSTR)(buffer.data()), length, NULL, NULL);
	return(buffer);
}


CString CConvertString::UTF8StringToCString(std::string utf8str)
{
	/* 预转换，得到所需空间的大小 */
	int nLen = ::MultiByteToWideChar(CP_UTF8, NULL,
		utf8str.data(), utf8str.size(), NULL, 0);
	/* 转换为Unicode */
	std::wstring wbuffer;
	wbuffer.resize(nLen);
	::MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(),
		(LPWSTR)(wbuffer.data()), wbuffer.length());

#ifdef UNICODE
	return(CString(wbuffer.data(), wbuffer.length()));
#else
	/*
	* 转换为ANSI
	* 得到转换后长度
	*/
	nLen = WideCharToMultiByte(CP_ACP, 0,
		wbuffer.data(), wbuffer.length(), NULL, 0, NULL, NULL);

	std::string ansistr;
	ansistr.resize(nLen);

	/* 把unicode转成ansi */
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)(wbuffer.data()), wbuffer.length(),
		(LPSTR)(ansistr.data()), ansistr.size(), NULL, NULL);
	return(CString(ansistr.data(), ansistr.length()));
#endif
}

std::string CConvertString::UTF8StringToString(const std::string utf8str)
{
	CString strTemp=UTF8StringToCString(utf8str);
	
	return CStringToString(strTemp);
}

std::string CConvertString::UnicodeToUTF8(const std::wstring & wstr)
{
	std::string ret;
	try {
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		ret = wcv.to_bytes(wstr);
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	return ret;
}

std::wstring CConvertString::UTF8ToUnicode(const std::string & str)
{
	std::wstring ret;
	try {

		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		ret = wcv.from_bytes(str);
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	return ret;
}

std::string CConvertString::UnicodeToANSI(const std::wstring & wstr)
{
	std::string ret;
	std::mbstate_t state = {};
	const wchar_t *src = wstr.data();
	size_t len = std::wcsrtombs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) {
		std::unique_ptr< char[] > buff(new char[len + 1]);
		len = std::wcsrtombs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len) {
			ret.assign(buff.get(), len);
		}
	}
	return ret;
}

std::wstring CConvertString::ANSIToUnicode(const std::string & str)
{
	std::wstring ret;
	std::mbstate_t state = {};
	const char *src = str.data();
	size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) {
		std::unique_ptr< wchar_t[] > buff(new wchar_t[len + 1]);
		len = std::mbsrtowcs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len) {
			ret.assign(buff.get(), len);
		}
	}
	return ret;
}

std::string CConvertString::UTF8ToANSI(const std::string & str)
{
	return UnicodeToANSI(UTF8ToUnicode(str));
}

std::string CConvertString::ANSIToUTF8(const std::string & str)
{
	return UnicodeToUTF8(ANSIToUnicode(str));
}



