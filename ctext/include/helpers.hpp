#pragma once

#include <MinHook.h>

#include <type_traits>


extern void* baseAddress;


#define ADDR(__arg_offset_)((unsigned int)baseAddress + __arg_offset_)

#define ADDR_AS(__arg_type_, __arg_offset_) reinterpret_cast<__arg_type_>(ADDR(__arg_offset_))

#define ADDR_AS_ACCESSOR(__arg_type_, __arg_name_, __arg_offset_) \
	inline __arg_type_ __arg_name_() { return *ADDR_AS(std::remove_reference_t<__arg_type_>*, __arg_offset_); } \
	inline void __arg_name_(__arg_type_ value) { *ADDR_AS(std::remove_reference_t<__arg_type_>*, __arg_offset_) = value; }

#define ADDR_AS_STATIC_ACCESSOR(__arg_type_, __arg_name_, __arg_offset_) \
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

#define ADDR_AS_FUNC(__arg_return_type_, __arg_callconv_, __arg_name_, __arg_offset_, ...) \
	inline __arg_return_type_ __arg_callconv_ __arg_name_(WEAVE_PARAMS(__VA_ARGS__)) { \
		return ADDR_AS(__arg_return_type_ (__arg_callconv_*)(EXTRACT_EACH_FIRST(__VA_ARGS__)), __arg_offset_)(EXTRACT_EACH_SECOND(__VA_ARGS__));  }

#define HOOK_CLSFN_RET(__arg_name_, __arg_ret_type_, __arg_class_type_, ...) \
	typedef __arg_ret_type_(__thiscall* __arg_name_##_SIG)(__arg_class_type_* _this __VA_OPT__(,) __VA_ARGS__); \
    __arg_name_##_SIG __arg_name_##_ORIG = nullptr; \
	__arg_ret_type_ __fastcall __arg_name_##_HOOK(__arg_class_type_* _this, void* _ __VA_OPT__(,) __VA_ARGS__)

#define HOOK_CLSFN(__arg_name_, __arg_class_type_, ...) \
	HOOK_CLSFN_RET(__arg_name_, void, __arg_class_type_, __VA_ARGS__)

#define HOOK_RET(__arg_name_, __arg_call_sig_, __arg_ret_type_, ...) \
	typedef __arg_ret_type_(__arg_call_sig_* __arg_name_##_SIG)(__VA_ARGS__); \
    __arg_name_##_SIG __arg_name_##_ORIG = nullptr; \
	__arg_ret_type_ __arg_call_sig_ __arg_name_##_HOOK(__VA_ARGS__)

#define CALL_ORIG(__arg_name_, ...) \
	__arg_name_##_ORIG(__VA_ARGS__)

#define ENABLE_HOOK(__arg_name_, __arg_addr_) \
	{ \
		auto _target = ADDR_AS(__arg_name_##_SIG, __arg_addr_); \
		auto _res = MH_CreateHook(_target, __arg_name_##_HOOK, (LPVOID*)&__arg_name_##_ORIG); \
		_res = MH_EnableHook(_target); \
	}

#if defined(ENABLE_LOGGING)
#include <cstdio>
#include <iostream>

#define LOG_DEBUG(__arg_msg_) std::cout << __arg_msg_ << std::endl
#define LOG_ERROR(__arg_msg_) std::cerr << __arg_msg_ << std::endl
#else
#define LOG_DEBUG(__arg_msg_)
#define LOG_ERROR(__arg_msg_)
#endif