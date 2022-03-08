#ifndef BD3GE_CORE_H
#define BD3GE_CORE_H

#ifdef _WIN32
	#ifdef BD3GE_EXPORT
		#define BD3GE_API __declspec(dllexport)
	#else
		#define BD3GE_API __declspec(dllimport)
	#endif // BD3GE_DLL
#endif // _WIN32

#endif //BD3GE_CORE_H