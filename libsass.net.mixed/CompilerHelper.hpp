#pragma once

#include <string>

#include "sass.h"

class CompilerHelper
{
public:
	static int DoCompile(
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
		);

	static int DoCompileFile(
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
		);

};


