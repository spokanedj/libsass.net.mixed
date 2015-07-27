#include "CompilerHelper.hpp"

#include <sass_context.h>


int CompilerHelper::DoCompile(
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

		sass_delete_data_context(ctx);

		return 0;
	}
	catch (...)
	{
		throw;
	}

}

int CompilerHelper::DoCompileFile(
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

