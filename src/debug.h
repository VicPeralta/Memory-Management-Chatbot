#ifndef DEBUG_H_
#define DEBUG_H_
#include <iostream>
#include <wchar.h>

#ifdef  _WIN32
	#include<Windows.h>
	#include <debugapi.h>
	#define ASSERT _ASSERTE
#else 
	#include <cassert>
	#include <iostream>
	#define ASSERT assert
#endif //  _WIN32

#define TRACE Tracer(__FILE__, __LINE__)


struct Tracer
{
	char const * m_file;
	unsigned int m_line;
	Tracer(const char* file, unsigned int line) :
		m_file{ file }, m_line{ line }
	{

	}
	#ifdef  _WIN32
		template<typename... Args>
		void operator()(wchar_t const * format, Args...args)
		{
			wchar_t buffer[256];
			auto count = swprintf_s(buffer,
				L"%S (%d): ",
				m_file,
				m_line);
			ASSERT(count != -1);
			ASSERT(_snwprintf_s(
				buffer + count,// El buffer de salida
				_countof(buffer) - count, // El tama?o del buffer
				_countof(buffer) - count - 1, // Max caracteres a escribir
				format,
				args...) != -1);
			OutputDebugString(buffer);
		}
	#else
		template<typename... Args>
		void operator()(wchar_t const * format, Args...args)
		{
			wchar_t buffer[256];

			auto count = swprintf(buffer,
				255,
				L"%S (%d): ",
				m_file,
				m_line);
			ASSERT(count != -1);
			ASSERT(swprintf(
				buffer ,// El buffer de salida
				255,
				format,
				args...) != -1);
			// OutputDebugString(buffer);
			std::wcout << buffer;
		}
	#endif
};

#endif
