#include "MiniginPCH.h"
#include "Log.h"
#include <iostream>


std::basic_streambuf<char>::int_type engine::DebugStreambuf::overflow(int_type c)
{
	if (c != EOF)
	{
		char buffer[] = {static_cast<char>(c), '\0'};
		OutputDebugStringA(buffer);
	}
	return c;
}

engine::Cout2VisualStudioDebugOutput::Cout2VisualStudioDebugOutput()
{
	default_stream = std::cout.rdbuf(&dbgstream);
}

engine::Cout2VisualStudioDebugOutput::~Cout2VisualStudioDebugOutput()
{
	std::cout.rdbuf(default_stream);
}
