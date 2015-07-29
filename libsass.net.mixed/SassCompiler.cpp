#include "SassCompiler.hpp"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Text;

namespace LibSassNet
{

	SassCompiler::SassCompiler()
	{
		_sassInterface = gcnew SassInterface();
	}

	SassCompiler::SassCompiler(ISassInterface^ sassInterface)
	{
		_sassInterface = sassInterface;
	}

	System::String^ SassCompiler::Compile(System::String^ source, OutputStyle outputStyle, bool includeSourceComments, int precision, IEnumerable<System::String^>^ includePaths)
	{

		SassOptions^ Options = gcnew SassOptions();
		Options->OutputStyle = (int)outputStyle;
		Options->IncludeSourceComments = includeSourceComments;
		Options->IncludePaths = includePaths != nullptr ? String::Join(";", includePaths) : String::Empty;
		Options->Precision = precision;

		SassContext^ context = gcnew SassContext();
		context->SourceString = source;
		context->Options = Options;

		_sassInterface->Compile(context);

		if (context->ErrorStatus)
		{
			throw gcnew SassCompileException(context->ErrorMessage);
		}

		return context->OutputString;
	}

	CompileFileResult^ SassCompiler::CompileFile(System::String^ inputPath, OutputStyle outputStyle, System::String^ sourceMapPath, bool includeSourceComments, int precision, bool embedMap, IEnumerable<System::String^>^ additionalIncludePaths)
	{

		String^ directoryName = Path::GetDirectoryName(inputPath);
		List<String^>^ includePaths = gcnew List<String^>();
		includePaths->Add(directoryName);

		if (additionalIncludePaths != nullptr)
		{
			includePaths->AddRange(additionalIncludePaths);
		}


		SassOptions^ Options = gcnew SassOptions();
		Options->OutputStyle = (int)outputStyle;
		Options->IncludeSourceComments = includeSourceComments;
		Options->IncludePaths = String::Join(";", includePaths);
		Options->Precision = precision;
		Options->EmbeddedMap = embedMap;

		SassFileContext^ context = gcnew SassFileContext();
		// libsass 3.0 expects utf8 path string, but strings in .NET are utf16, so we need to convert it
		context->InputPath = Utf16ToUtf8(inputPath);
		context->OutputSourceMapFile = sourceMapPath;
		context->Options = Options;

		_sassInterface->Compile(context);

		if (context->ErrorStatus)
		{
			throw gcnew SassCompileException(context->ErrorMessage);
		}

		return gcnew CompileFileResult(context->OutputString, context->OutputSourceMap);
	}

	/// <summary>
	/// Converts utf16 string to utf8
	/// </summary>
	/// <param name="utf16String"></param>
	/// <returns></returns>
	String^ SassCompiler::Utf16ToUtf8(String^ utf16String)
	{
		// Get UTF16 bytes and convert UTF16 bytes to UTF8 bytes
		auto utf16Bytes = Encoding::Unicode->GetBytes(utf16String);
		auto utf8Bytes = Encoding::Convert(Encoding::Unicode, Encoding::UTF8, utf16Bytes);

		// Return UTF8 bytes as ANSI string
		return Encoding::Default->GetString(utf8Bytes);
	}
}
