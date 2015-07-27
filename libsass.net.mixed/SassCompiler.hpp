#pragma once

#include "ISassCompiler.hpp"
#include "SassInterface.hpp"
#include "SassCompilerException.hpp"


namespace LibSassNet
{
	public ref class SassCompiler : ISassCompiler
	{
	private:
		property ISassInterface^ _sassInterface;

	public:
		SassCompiler();
		SassCompiler(ISassInterface^ sassInterface);

		virtual System::String^ Compile(System::String^ source) {
			return Compile(source, OutputStyle::Nested, false, 5, nullptr);
		}
		virtual System::String^ Compile(System::String^ source, OutputStyle outputStyle, bool includeSourceComments, int precision, System::Collections::Generic::IEnumerable<System::String^>^ includePaths);

		virtual CompileFileResult^ CompileFile(System::String^ inputPath) {
			return CompileFile(inputPath, OutputStyle::Nested, nullptr, false);
		}
		virtual CompileFileResult^ CompileFile(System::String^ inputPath,
			OutputStyle outputStyle,
			System::String^ sourceMapPath,
			bool includeSourceComments) {
			return CompileFile(inputPath, outputStyle, sourceMapPath, includeSourceComments, 5, nullptr);
		}
		virtual CompileFileResult^ CompileFile(System::String^ inputPath, OutputStyle outputStyle, System::String^ sourceMapPath, bool includeSourceComments, int precision, System::Collections::Generic::IEnumerable<System::String^>^ additionalIncludePaths);

	private:
		/// <summary>
		/// Converts utf16 string to utf8
		/// </summary>
		/// <param name="utf16String"></param>
		/// <returns></returns>
		static String^ Utf16ToUtf8(String^ utf16String);
	};
}
