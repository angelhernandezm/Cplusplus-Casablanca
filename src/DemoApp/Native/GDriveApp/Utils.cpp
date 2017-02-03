#include "pch.h"
#include "Utils.h"

using namespace GDriveApp;

Platform::String^ StringUtil::ParseException(const char* ex) {
	std::wostringstream ss;
	auto retval = ref new String(L"There's been an exception: ");
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utf16conv;
	ss << utf16conv.from_bytes(ex) << std::endl;
	retval = String::Concat(retval, ref new Platform::String(ss.str().data()));

	return retval;
}