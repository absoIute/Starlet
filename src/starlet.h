#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <immintrin.h>

/* INTERNAL Macros for manually imported functions */

/// <summary>Declares the internal typedef & function pointer within the class.</summary>
#define SX_FUNC_DECL(RETURN_TYPE, CLASS, FUNC, ...) \
	typedef RETURN_TYPE (CLASS:: *SX_TYPEDEF(FUNC))(__VA_ARGS__); \
	static SX_TYPEDEF(FUNC) SX_PTR(FUNC); \
	static SX_TYPEDEF(FUNC) SX_OG_PTR(FUNC); \
	RETURN_TYPE FUNC(__VA_ARGS__)

#define SX_FUNC_STATIC_DECL(RETURN_TYPE, CONVENTION, FUNC, ...) \
	typedef RETURN_TYPE (CONVENTION *SX_TYPEDEF(FUNC))(__VA_ARGS__); \
	static SX_TYPEDEF(FUNC) SX_PTR(FUNC); \
	static SX_TYPEDEF(FUNC) SX_OG_PTR(FUNC); \
	static RETURN_TYPE CONVENTION FUNC(__VA_ARGS__)

#define SX_FUNC_VIRTUAL_DECL(RETURN_TYPE, CLASS, FUNC, ...) \
	typedef RETURN_TYPE (CLASS:: *SX_TYPEDEF(FUNC))(__VA_ARGS__); \
	static SX_TYPEDEF(FUNC) SX_PTR(FUNC); \
	static SX_TYPEDEF(FUNC) SX_OG_PTR(FUNC)

/// <summary>Initialises the function pointer as null to resolve the symbol.</summary>
#define SX_FUNC_DEF(CLASS, FUNC) \
	CLASS::SX_TYPEDEF(FUNC) CLASS::SX_PTR(FUNC) = nullptr; \
	CLASS::SX_TYPEDEF(FUNC) CLASS::SX_OG_PTR(FUNC) = nullptr

/// <summary>Doesn't actually do anything, just a placeholder for pure virtual functions.</summary>
#define SX_FUNC_VPURE(RETURN_TYPE, CLASS, FUNC, ...)

/// <summary>Initialises the function pointer. Should only be used in the class' SX_INIT function.</summary>
#define SX_FUNC_INIT(OFFSET, FUNC) SX_PTR(FUNC) = sx_member_cast<SX_TYPEDEF(FUNC)>(reinterpret_cast<void *>(handle + OFFSET)); \
	SX_OG_PTR(FUNC) = SX_PTR(FUNC)



/* Macros for hooking manually imported functions */

/// <summary>Declares the class to be hooked, do not inherit any other classes.</summary>
#define SX_HOOK_CLASS_DECL(CLASS) class SX_CLASS(CLASS) : public CLASS

/// <summary>Gets the internal class extension name.</summary>
#define SX_HOOK_DECL(FUNC) SX_HOOK(FUNC)

#define SX_HOOK_STATIC_DECL(CONVENTION, FUNC) CONVENTION SX_HOOK(FUNC)

/// <summary>Gets the internal class extension name.</summary>
#define SX_HOOK_DEF(CLASS, FUNC) SX_CLASS(CLASS)::SX_HOOK(FUNC)

/// <summary>Initialises the hook, needs to be called before hook can be used, preferably before anything else.</summary>
#define SX_HOOK_INIT(CLASS, FUNC) \
	sx_hook_method(&reinterpret_cast<void *&>(CLASS::SX_PTR(FUNC)), sx_void_cast(&SX_CLASS(CLASS)::SX_HOOK(FUNC)));

/* Macros for hooking dynamically imported library functions */

#define SX_HOOK_LIB_CLASS_DECL(NAMESPACE, CLASS) class SX_CLASS(NAMESPACE ## CLASS) : NAMESPACE::CLASS

#define SX_HOOK_LIB_DECL(RETURN_TYPE, CONVENTION, NAMESPACE, CLASS, FUNC, ...) \
	typedef RETURN_TYPE(CONVENTION NAMESPACE::CLASS:: *SX_TYPEDEF(FUNC))(__VA_ARGS__); \
	static SX_TYPEDEF(FUNC) SX_PTR(FUNC); \
	RETURN_TYPE CONVENTION SX_HOOK(FUNC)(__VA_ARGS__)

#define SX_HOOK_LIB_STATIC_DECL(RETURN_TYPE, CONVENTION, NAMESPACE, CLASS, FUNC, ...) \
	typedef RETURN_TYPE(CONVENTION *SX_TYPEDEF(FUNC))(__VA_ARGS__); \
	static SX_TYPEDEF(FUNC) SX_PTR(FUNC); \
	static RETURN_TYPE CONVENTION SX_HOOK(FUNC)(__VA_ARGS__)

#define SX_HOOK_LIB_DEF(RETURN_TYPE, CONVENTION, NAMESPACE, CLASS, FUNC, ...) \
	SX_CLASS(NAMESPACE ## CLASS)::SX_TYPEDEF(FUNC) SX_CLASS(NAMESPACE ## CLASS)::SX_PTR(FUNC) = nullptr; \
	RETURN_TYPE CONVENTION SX_CLASS(NAMESPACE ## CLASS)::SX_HOOK(FUNC)(__VA_ARGS__)

#define SX_HOOK_LIB_INIT(NAMESPACE, CLASS, FUNC) \
	SX_CLASS(NAMESPACE ## CLASS)::SX_PTR(FUNC) = &NAMESPACE::CLASS::FUNC; \
	sx_hook_method(&reinterpret_cast<void *&>(SX_CLASS(NAMESPACE ## CLASS)::SX_PTR(FUNC)), sx_void_cast(&SX_CLASS(NAMESPACE ## CLASS)::SX_HOOK(FUNC)))

#define SX_HOOK_LIB_ADDR_INIT(NAMESPACE, CLASS, FUNC, PTR) \
	SX_CLASS(NAMESPACE ## CLASS)::SX_PTR(FUNC) = sx_member_cast<SX_CLASS(NAMESPACE ## CLASS)::SX_TYPEDEF(FUNC)>(reinterpret_cast<void *>(PTR)); \
	sx_hook_method(&reinterpret_cast<void *&>(SX_CLASS(NAMESPACE ## CLASS)::SX_PTR(FUNC)), sx_void_cast(&SX_CLASS(NAMESPACE ## CLASS)::SX_HOOK(FUNC)))

/* alt */

/// <summary>Calls the original, unhooked, function. Should be used within your own hooks.</summary>
#define SX_ORIG(INST, FUNC) (INST->*SX_PTR(FUNC))

/// <summary>Calls the original, unhooked, function. Should be used within your own hooks.</summary>
#define SX_ORIG_STATIC(FUNC) (*SX_PTR(FUNC))

/// <summary>Calls the original, original, function.</summary>
#define SX_ORIG_OG(INST, FUNC) (INST->*SX_OG_PTR(FUNC))


/* Internal naming macros */

/// <summary>Gets the internal class extension name.</summary>
#define SX_CLASS(FUNC) FUNC ## _SX_CLASS

/// <summary>Gets the internal function hook name.</summary>
#define SX_HOOK(FUNC) FUNC ## _SX_HOOK

/// <summary>Gets the internal function pointer name.</summary>
#define SX_PTR(FUNC) FUNC ## _SX_PTR

/// <summary>Gets the internal non-modified function pointer name.</summary>
#define SX_OG_PTR(FUNC) FUNC ## _SX_OG_PTR

/// <summary>Gets the internal function typedef name.</summary>
#define SX_TYPEDEF(FUNC) FUNC ## _SX_DEF

/* impl */

bool sx_init();
bool sx_hook_method(void **original, void *hook);

/* hacky stuff */

template <typename T>
T sx_this(T ptr, uintptr_t offset)
{
	return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(ptr) - offset);
}

template <typename T>
union vuc
{
	T f;
	void *ptr;
};

template <typename T>
void *sx_void_cast(T _f)
{
	vuc<T> v{ 0 };
	v.f = _f;

	return v.ptr;
}

template <typename T>
T sx_member_cast(void *_ptr)
{
	vuc<T> v{ 0 };
	v.ptr = _ptr;

	return v.f;
}

template<class T>
T get(void *object, uintptr_t offset)
{
	return *reinterpret_cast<T *>(reinterpret_cast<uintptr_t>(object) + offset);
}
