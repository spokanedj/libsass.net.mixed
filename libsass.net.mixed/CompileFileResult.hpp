#pragma once

namespace LibSassNet
{
	public ref struct CompileFileResult
	{
	private:
		System::String^ _CSS;
		System::String^ _SourceMap;

	public:
		CompileFileResult(System::String^ css, System::String^ sourceMap)
		{
			_CSS = css;
			_SourceMap = sourceMap;
		}

		property System::String^ CSS {
			System::String^ get() { return _CSS; }
		}

		property System::String^ SourceMap {
			System::String^ get() { return _SourceMap; }
		}
	};
}

