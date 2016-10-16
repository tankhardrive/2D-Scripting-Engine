#ifndef TSS_UTILITY_UTIL_H_
#define TSS_UTILITY_UTIL_H_



//////////////////////////////////////////////////////////////////////////
//					Copy and Assignment protect a class
//////////////////////////////////////////////////////////////////////////
#define COPY_ASSIGN_PROTECT(_class)\
	private:\
	_class(_class& copyClass); \
	_class& operator=(const _class& rhs)


//////////////////////////////////////////////////////////////////////////
//				Create a singleton with default constructor
//////////////////////////////////////////////////////////////////////////
#define LAZY_SINGLETON(_class)\
	public:\
	~_class();\
	static _class* GetInstance()\
	{\
		static _class myClass; \
		return &myClass; \
	}\
	private:\
	_class(); \
	COPY_ASSIGN_PROTECT(_class)


//////////////////////////////////////////////////////////////////////////
//				Stop a function from being overridden any more
//////////////////////////////////////////////////////////////////////////
#define NO_OVERRIDE(_function)\
	_function final


//////////////////////////////////////////////////////////////////////////
//				Define a completely virtual function
//////////////////////////////////////////////////////////////////////////
#define PURE_VIRTUAL(_function)\
	virtual _function = 0


//////////////////////////////////////////////////////////////////////////
//					SAFE DELETE
//////////////////////////////////////////////////////////////////////////
#define SAFE_DELETE(_ptr)\
if (_ptr)\
{\
	delete _ptr; \
	_ptr = NULL; \
}


#endif