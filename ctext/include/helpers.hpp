#pragma once

#include <MinHook.h>

#include <cstdint>
#include <type_traits>


extern void* baseAddress;


#define ADDR(__arg_offset_)((uintptr_t)baseAddress + __arg_offset_)

#define ADDR_AS(__arg_type_, __arg_offset_) reinterpret_cast<__arg_type_>(ADDR(__arg_offset_))

#define ACSR(__arg_type_, __arg_name_, __arg_offset_) \
	static inline __arg_type_ __arg_name_() { return *ADDR_AS(std::remove_reference_t<__arg_type_>*, __arg_offset_); } \
	static inline void __arg_name_(__arg_type_ value) { *ADDR_AS(std::remove_reference_t<__arg_type_>*, __arg_offset_) = value; }

#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(__arg_macro_, ...) __VA_OPT__(EXPAND(FOR_EACH_HELPER(__arg_macro_, __VA_ARGS__)))
#define FOR_EACH_HELPER(__arg_macro_, a1, a2, ...) __arg_macro_(a1, a2) __VA_OPT__(, FOR_EACH_AGAIN PARENS (__arg_macro_, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define EXTRACT_SECOND(x, y) y
#define EXTRACT_EACH_SECOND(...) FOR_EACH(EXTRACT_SECOND, __VA_ARGS__)
#define EXTRACT_FIRST(x, y) x
#define EXTRACT_EACH_FIRST(...) FOR_EACH(EXTRACT_FIRST, __VA_ARGS__)
#define WEAVE_PARAM(x, y) x y
#define WEAVE_PARAMS(...) FOR_EACH(WEAVE_PARAM, __VA_ARGS__)


#define FN_CC(__arg_conv_, __arg_ret_, __arg_name_, __arg_addr_, ...) \
	static const uintptr_t __arg_name_##_ADDR = __arg_addr_; \
	static inline __arg_ret_ __arg_name_(WEAVE_PARAMS(__VA_ARGS__)) { \
		return ADDR_AS( \
			__arg_ret_ (__arg_conv_ *)(EXTRACT_EACH_FIRST(__VA_ARGS__)), \
			__arg_addr_ \
		)(EXTRACT_EACH_SECOND(__VA_ARGS__)); \
	}

#define FN(__arg_ret_, __arg_name_, __arg_addr_, ...) \
	FN_CC(__cdecl, __arg_ret_, __arg_name_, __arg_addr_ __VA_OPT__(,) __VA_ARGS__)

#define C_FN(__arg_ret_, __arg_name_, __arg_addr_, ...) \
	static const uintptr_t __arg_name_##_ADDR = __arg_addr_; \
	inline __arg_ret_ __arg_name_(WEAVE_PARAMS(__VA_ARGS__)) { \
		return ADDR_AS( \
			__arg_ret_ (* __thiscall)(decltype(this) __VA_OPT__(,) EXTRACT_EACH_FIRST(__VA_ARGS__)), \
			__arg_addr_ \
		)(this __VA_OPT__(,) EXTRACT_EACH_SECOND(__VA_ARGS__)); \
	}


#define C_FN_HOOK_A(__arg_ret_, __arg_class_, __arg_name_, __arg_addr_, ...) \
	struct __arg_class_##__##__arg_name_ : public __arg_class_ { \
		static __arg_ret_ (__thiscall * ORIG)(__arg_class_* __VA_OPT__(,) EXTRACT_EACH_FIRST(__VA_ARGS__)); \
		__arg_ret_ __arg_name_##_HOOK(EXTRACT_EACH_FIRST(__VA_ARGS__)); \
	}; \
	__arg_ret_ (__thiscall * __arg_class_##__##__arg_name_::ORIG)(\
		__arg_class_* __VA_OPT__(,) EXTRACT_EACH_FIRST(__VA_ARGS__)\
	) = (decltype(__arg_class_##__##__arg_name_::ORIG))__arg_addr_; \
	__arg_ret_ __fastcall __arg_class_##__##__arg_name_##_HOOK( \
		__arg_class_* _this, void* _ __VA_OPT__(,) WEAVE_PARAMS(__VA_ARGS__) \
	) { \
		return reinterpret_cast<__arg_class_##__##__arg_name_*>(_this)->__arg_name_##_HOOK( \
			EXTRACT_EACH_SECOND(__VA_ARGS__) \
		); \
	} \
	void Enable##__arg_class_##__##__arg_name_##Hook() { \
		auto _target = ADDR_AS(decltype(__arg_class_##__##__arg_name_::ORIG), __arg_addr_); \
		auto _res = MH_CreateHook( \
			_target, \
			__arg_class_##__##__arg_name_##_HOOK, \
			(LPVOID*)&__arg_class_##__##__arg_name_::ORIG \
		); \
		_res = MH_EnableHook(_target); \
		LOG_DEBUG("Enabled " #__arg_class_ "::" #__arg_name_ " hook"); \
	} \
	__arg_ret_ __arg_class_##__##__arg_name_::__arg_name_##_HOOK(WEAVE_PARAMS(__VA_ARGS__))

#define C_FN_HOOK(__arg_ret_, __arg_class_, __arg_name_, ...) \
	C_FN_HOOK_A(__arg_ret_, __arg_class_, __arg_name_, __arg_class_::__arg_name_##_ADDR __VA_OPT__(,) __VA_ARGS__)

#define FN_HOOK_A(__arg_conv_, __arg_ret_, __arg_name_, __arg_addr_, ...) \
	__arg_ret_ (__arg_conv_ * __arg_name_##_ORIG)(EXTRACT_EACH_FIRST(__VA_ARGS__)) = \
		(decltype(__arg_name_##_ORIG))__arg_addr_; \
    __arg_ret_ __arg_conv_ __arg_name_##_HOOK(WEAVE_PARAMS(__VA_ARGS__)); \
	void Enable##__arg_name_##Hook() { \
		auto _target = ADDR_AS(decltype(__arg_name_##_HOOK)*, __arg_addr_); \
		auto _res = MH_CreateHook(_target, __arg_name_##_HOOK, (LPVOID*)&__arg_name_##_ORIG); \
		_res = MH_EnableHook(_target); \
		LOG_DEBUG("Enabled " #__arg_name_ " hook"); \
	} \
    __arg_ret_ __arg_conv_ __arg_name_##_HOOK(WEAVE_PARAMS(__VA_ARGS__))

#define FN_HOOK(__arg_conv, __arg_ret_, __arg_name_, ...) \
	FN_HOOK_A(__arg_conv_, __arg_ret_, __arg_name_, __arg_name_##_ADDR __VA_OPT__(,) __VA_ARGS__)

#define CALL_ORIG(__arg_name_, ...) \
	__arg_name_##_ORIG(__VA_ARGS__)

#define C_CALL_ORIG(...) \
	ORIG(this __VA_OPT__(,) __VA_ARGS__)

#define ENABLE_FN_HOOK(__arg_name_) \
	Enable##__arg_name_##Hook()

#define ENABLE_C_FN_HOOK(__arg_class_, __arg_name_) \
	Enable##__arg_class_##__##__arg_name_##Hook()

#if defined(ENABLE_LOGGING)
#include <iostream>

#define LOG_DEBUG(__arg_msg_) std::cout << __arg_msg_ << std::endl
#define LOG_ERROR(__arg_msg_) std::cerr << __arg_msg_ << std::endl
#else
#define LOG_DEBUG(__arg_msg_)
#define LOG_ERROR(__arg_msg_)
#endif