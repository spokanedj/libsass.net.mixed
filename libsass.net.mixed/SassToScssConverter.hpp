
#pragma once

#include "ISassInterface.hpp"
#include "ISassToScssConverter.hpp"

namespace LibSassNet
{

	public ref class SassToScssConverter : public ISassToScssConverter
	{
	private:
		property ISassInterface^ _Sass;

	public:
		SassToScssConverter();
		virtual System::String^ Convert(System::String^ source);
	};

}
