//Copyright (C) 2013 by TBAPI-0KA
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of
//this software and associated documentation files (the "Software"), to deal in
//the Software without restriction, including without limitation the rights to
//use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
//of the Software, and to permit persons to whom the Software is furnished to do
//so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include <exception>
#include "sass_interface.h"
#include "sass2scss.h"
#include "StringToANSI.hpp"
#include "SassInterface.hpp"
#include "sass_context.h"

using namespace std;

#pragma unmanaged
int DoCompile(
	// In
	const std::string&	includePaths,
	const std::string&	sourceString,
	Sass_Output_Style	outputStyle,
	bool				inclSrcComments,
	int					precision,
	// Out
	int*				errStatus,
	std::string&		errMessage,
	std::string&		outputString
	)
{
	struct Sass_Data_Context* ctx;

	try
	{
		ctx = sass_make_data_context(const_cast<char*>(sourceString.c_str()));
		struct Sass_Options* options = sass_data_context_get_options(ctx);
		struct Sass_Context* ctx_out = sass_data_context_get_context(ctx);

		// copy options around
		sass_option_set_output_style(options, outputStyle);
		sass_option_set_source_comments(options, inclSrcComments);
		sass_option_set_precision(options, precision);
		sass_option_set_include_path(options, includePaths.c_str());
		sass_option_set_omit_source_map_url(options, true);

		sass_compile_data_context(ctx);

		if (errStatus) {
			*errStatus = sass_context_get_error_status(ctx_out);
		}

		if (const char* szErrMessage = sass_context_get_error_message(ctx_out)) {
			errMessage = szErrMessage;
		}

		if (const char* szOutputString = sass_context_get_output_string(ctx_out)) {
			outputString = szOutputString;
		}

		outputString = sass_context_get_output_string(ctx_out);

		sass_delete_data_context(ctx);

		return 0;
	}
	catch (...)
	{
		throw;
	}

}

int DoCompileFile(
	// In
	const std::string&  inputPath,
	const std::string&	mapFile,
	const std::string&	includePaths,
	Sass_Output_Style	outputStyle,
	bool				inclSrcComments,
	int					precision,
	// Out
	int*				errStatus,
	std::string&		errMessage,
	std::string&		outputString,
	std::string&		outputSourceMap
	)
{
	struct Sass_File_Context* ctx;

	try
	{
		ctx = sass_make_file_context(const_cast<char*>(inputPath.c_str()));
		struct Sass_Options* options = sass_file_context_get_options(ctx);
		struct Sass_Context* ctx_out = sass_file_context_get_context(ctx);

		// copy options around
		sass_option_set_output_style(options, outputStyle);
		sass_option_set_source_comments(options, inclSrcComments);
		sass_option_set_precision(options, precision);
		sass_option_set_include_path(options, includePaths.c_str());
		sass_option_set_omit_source_map_url(options, mapFile.empty());
		sass_option_set_source_map_file(options, mapFile.c_str());

		sass_compile_file_context(ctx);

		if (errStatus) {
			*errStatus = sass_context_get_error_status(ctx_out);
		}

		if (const char* szErrMessage = sass_context_get_error_message(ctx_out)) {
			errMessage = szErrMessage;
		}
		if (const char* szOutputString = sass_context_get_output_string(ctx_out)) {
			outputString = szOutputString;
		}
		if (const char* szOutputSourceMap = sass_context_get_source_map_string(ctx_out)) {
			outputSourceMap = szOutputSourceMap;
		}

		sass_delete_file_context(ctx);

		return 0;
	}
	catch (...)
	{
		throw;
	}
}




#pragma managed

namespace LibSassNet
{
	int SassInterface::Compile(SassContext^ sassContext)
	{
		try
		{
			int errStatus = 0;
			std::string errMessage;
			std::string outputString;

			char* szInclPaths = MarshalString(sassContext->Options->IncludePaths);
			char* szSrcStr = MarshalString(sassContext->SourceString);

			int result = DoCompile(	
						// In
						(szInclPaths ? szInclPaths : ""),
						(szSrcStr ? szSrcStr : "" ),
						GetOutputStyle(sassContext->Options->OutputStyle),
						(sassContext->Options->IncludeSourceComments ? true : false),
						sassContext->Options->Precision,
						// Out
						&errStatus,
						errMessage,
						outputString
			);

			sassContext->ErrorStatus = errStatus!=0;
			sassContext->ErrorMessage = gcnew String(errMessage.c_str());
			sassContext->OutputString = gcnew String(outputString.c_str());

			return result;
		}
		catch (exception& e)
		{
			throw gcnew Exception(gcnew String(e.what()));
		}
		catch (...)
		{
			throw gcnew Exception("Unhandled exception in native code");
		}
	}


    Sass_Output_Style SassInterface::GetOutputStyle(int raw)
    {
        switch (raw)
        {
        case 0: return SASS_STYLE_NESTED;
        case 1: return SASS_STYLE_EXPANDED;
        case 2: return SASS_STYLE_COMPACT;
        case 3: return SASS_STYLE_COMPRESSED;
        default: return SASS_STYLE_NESTED;
        }
    }

    int SassInterface::Compile(SassFileContext^ sassFileContext)
    {
		char* szInputPath = 0;
		char* szOutputSourceMapFile = 0;
		char* szIncludePaths = 0;

        try
        {
			int errStatus = 0;
			std::string errMessage, outputString, outputSourceMap;

			if (sassFileContext->InputPath != nullptr )
				szInputPath = MarshalString(sassFileContext->InputPath);
			if (sassFileContext->OutputSourceMapFile != nullptr )
				szOutputSourceMapFile = MarshalString(sassFileContext->OutputSourceMapFile);
			if (sassFileContext->Options->IncludePaths != nullptr )
				szIncludePaths = MarshalString(sassFileContext->Options->IncludePaths);

			int result = DoCompileFile(
				// In
				szInputPath ? szInputPath : "",
				szOutputSourceMapFile ? szOutputSourceMapFile : "",
				szIncludePaths ? szIncludePaths : "",
				GetOutputStyle(sassFileContext->Options->OutputStyle),
				sassFileContext->Options->IncludeSourceComments ? true : false,
				sassFileContext->Options->Precision,
				// Out
				&errStatus,
				errMessage,
				outputString,
				outputSourceMap
				);


			sassFileContext->ErrorStatus = errStatus != 0;
            sassFileContext->ErrorMessage = gcnew String(errMessage.c_str());
            sassFileContext->OutputString = gcnew String(outputString.c_str());
            sassFileContext->OutputSourceMap = gcnew String(outputSourceMap.c_str());

            return result;
        }
        catch (exception& e)
        {
			FreeString(szInputPath);
			FreeString(szOutputSourceMapFile);
			FreeString(szIncludePaths);

            throw gcnew Exception(gcnew String(e.what()));
        }
        catch (...)
        {
			FreeString(szInputPath);
			FreeString(szOutputSourceMapFile);
			FreeString(szIncludePaths);

            throw gcnew Exception("Unhandled exception in native code");
        }
    }

    void SassInterface::Convert(SassToScssConversionContext^ context)
    {
        char* sourceText;
        try
        {
            sourceText = MarshalString(context->SourceText);

            char* result = sass2scss(sourceText, 128);
            context->OutputText = gcnew String(result);

            FreeString(result);
        }
        catch (exception& e)
        {
            throw gcnew Exception(gcnew String(e.what()));
        }
        catch (...)
        {
            throw gcnew Exception("Unhandled exception in native code");
        }
    }

}

