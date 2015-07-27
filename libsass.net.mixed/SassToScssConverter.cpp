#include "SassToScssConverter.hpp"

#include "SassInterface.hpp"

namespace LibSassNet
{

	SassToScssConverter::SassToScssConverter()
	{
		_Sass = gcnew SassInterface();
	}

	String^ SassToScssConverter::Convert(String^ source)
	{
		SassToScssConversionContext^ context = gcnew SassToScssConversionContext( source );
		_Sass->Convert(context);

		return context->OutputText;
	}

}
