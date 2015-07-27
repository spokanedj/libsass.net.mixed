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

namespace LibSassNet
{
	typedef void (__stdcall *FileAccessDelegate)(const char* path);

	class CallbackManager
	{
		private:
			FileAccessDelegate _fileAccessDelegate;

			CallbackManager();

			CallbackManager(CallbackManager const&);
			void operator=(CallbackManager const&);

		public:
			static CallbackManager& getInstance();

			void set_file_access_callback(FileAccessDelegate callBack);
			void unset_file_access_callback();
			void trigger_file_access_callback(const char* path);
	};
}