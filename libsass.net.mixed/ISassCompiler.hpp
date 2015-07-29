#pragma once

#include "OutputStyle.hpp"
#include "CompileFileResult.hpp"

namespace LibSassNet
{
	public interface class ISassCompiler
	{
	public:
		virtual System::String^ Compile(System::String^ source) = 0;
		virtual System::String^ Compile(System::String^ source,
								OutputStyle outputStyle, 
								bool includeSourceComments,
								int precision, 
								System::Collections::Generic::IEnumerable<System::String^>^ includePaths) = 0;

		virtual CompileFileResult^ CompileFile(System::String^ inputPath) = 0;
		virtual CompileFileResult^ CompileFile(System::String^ inputPath,
			OutputStyle outputStyle,
			System::String^ sourceMapPath,
			bool includeSourceComments) = 0;
		virtual CompileFileResult^ CompileFile(	System::String^ inputPath,
												OutputStyle outputStyle,
												System::String^ sourceMapPath,
												bool includeSourceComments,
												int precision, 
												bool embedMap,
												System::Collections::Generic::IEnumerable<System::String^>^ additionalIncludePaths) = 0;
	};
}
