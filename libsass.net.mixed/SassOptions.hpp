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

#pragma once

#using <System.dll>

using namespace System;

namespace LibSassNet
{
	public ref class SassOptions
	{
		public:
			property int OutputStyle;
			property bool IncludeSourceComments;
			property int Precision;
			property String^ IncludePaths;
			property bool EmbeddedMap;
	};

	public ref class SassContext
	{
		public:
			property String^ SourceString;
			property String^ OutputString;
			property SassOptions^ Options;
			property bool ErrorStatus;
			property String^ ErrorMessage;
	};

	public ref class SassFileContext
	{
		public:
			property String^ InputPath;
			property String^ OutputString;
			property String^ OutputSourceMapFile;
			property String^ OutputSourceMap;
			property SassOptions^ Options;
			property bool ErrorStatus;
			property String^ ErrorMessage;
	};

	public ref class SassFolderContext
	{
		public:
			property String^ SearchPath;
			property String^ OutputPath;
			property SassOptions^ Options;
			property bool ErrorStatus;
			property String^ ErrorMessage;
	};

	public ref class SassToScssConversionContext
	{
		public:
			SassToScssConversionContext(String^ sourceText) 
			{ 
				SourceText = sourceText;
			}

			property String^ SourceText;
			property String^ OutputText;
	};
}