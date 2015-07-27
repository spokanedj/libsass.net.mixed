#pragma once

#using <System.dll>
using namespace System;

namespace LibSassNet
{
	public ref class SassCompileException : Exception
	{
	public:
		explicit SassCompileException(String^ message)
			: Exception(message)
		{
		}
	};
}
