#pragma once

namespace LibSassNet
{
	/// <summary>
	/// Converts SASS to SCSS
	/// </summary>
	public interface class ISassToScssConverter
	{
	public:
		virtual System::String^ Convert(System::String^ source) = 0;
	};
}

