
#ifdef _USE_APPUTILITY_DLL_
#	ifdef APPUTILITYDLL_EXPORTS
#		define APPUTILITYDLL_API __declspec(dllexport)
#	else
#		define APPUTILITYDLL_API __declspec(dllimport)
#	endif
#else
#	define APPUTILITYDLL_API 
#endif 

