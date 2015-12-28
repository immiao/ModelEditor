///////////////////////////////////////////////////////////////
//
// FileName : KEPublic.h
// Creator : 李晶晶2
// Date : 2010-08-10 17:07:54
// Comment :该文件中定义公共使用的宏。
//
///////////////////////////////////////////////////////////////

#ifndef _KE_PUBLIC_H__
#define _KE_PUBLIC_H__

#include <assert.h>

#ifndef ASSERT
#define ASSERT assert
#endif

#define KE_BOOL_TO_bool(bValue)		(!!(bValue))
//	进行错误处理的宏定义
#if defined(_MSC_VER)
#define KE_DISABLE_WARNING(warningCode, expression)		\
	__pragma(warning(push))                             \
	__pragma(warning(disable:warningCode))              \
	expression                                          \
	__pragma(warning(pop))
#else
#define KE_DISABLE_WARNING(warningCode, expression)  expression
#endif 
#define KE_WHILE_FALSE_NO_WARNING	KE_DISABLE_WARNING(4127, while (false))
#define KE_USE_ARGUMENT(arg) (arg)

#ifndef PROCESS_ERROR
#ifndef _DEBUG
#define PROCESS_ERROR(Condition)		    \
	do									    \
	{									    \
		if (!(Condition))				    \
		{									\
			goto Exit0;						\
		}									\
	} KE_WHILE_FALSE_NO_WARNING
#else
#define PROCESS_ERROR(Condition)		\
	do									\
	{									\
		if (!(Condition))				\
		{								\
			assert(false);				\
			goto Exit0;					\
		}								\
	} KE_WHILE_FALSE_NO_WARNING
#endif//_DEBUG
#endif//PROCESS_ERROR

#ifndef COM_PROCESS_ERROR
#ifndef _DEBUG
#define COM_PROCESS_ERROR(Condition) \
	do									\
	{									\
		if (FAILED(Condition))			\
		{								\
			goto Exit0;					\
		}								\
	} KE_WHILE_FALSE_NO_WARNING
#else
#define COM_PROCESS_ERROR(Condition) \
	do									\
	{									\
		if (FAILED(Condition))			\
		{								\
			assert(false);				\
			goto Exit0;					\
		}								\
	} while (false)
#endif//_DEBUG
#endif//COM_PROCESS_ERROR

#ifndef GDIP_PROCESS_ERROR
#ifndef _DEBUG
#define GDIP_PROCESS_ERROR(Condition)	\
	do										\
	{										\
	if ((Condition) != 0)					\
		{									\
		goto Exit0;							\
		}									\
	} KE_WHILE_FALSE_NO_WARNING
#else
#define GDIP_PROCESS_ERROR(Condition)	\
	do										\
	{										\
	if ((Condition) != 0)					\
		{									\
		assert(false);						\
		goto Exit0;							\
		}									\
	} KE_WHILE_FALSE_NO_WARNING
#endif//_DEBUG
#endif//GDIP_PROCESS_ERROR

#ifndef PROCESS_ERROR_RET_CODE
#ifndef _DEBUG
#define PROCESS_ERROR_RET_CODE(Condition, Code)		\
	do													\
	{													\
		if (!(Condition))								\
		{												\
			nResult = Code;								\
			goto Exit0;									\
		}												\
	} KE_WHILE_FALSE_NO_WARNING
#else
#define PROCESS_ERROR_RET_CODE(Condition, Code)		\
	do													\
	{													\
		if (!(Condition))								\
		{												\
			nResult = Code;								\
			assert(false);								\
			goto Exit0;									\
		}												\
	} KE_WHILE_FALSE_NO_WARNING
#endif//_DEBUG
#endif//PROCESS_ERROR_RET_CODE

#ifndef PROCESS_ERROR_RET_COM_CODE
#ifndef _DEBUG
#define PROCESS_ERROR_RET_COM_CODE(Condition, Code)	\
	do													\
	{													\
		if (!(Condition))								\
		{												\
			hrResult = Code;							\
			goto Exit0;									\
		}												\
	} KE_WHILE_FALSE_NO_WARNING
#else 
#define PROCESS_ERROR_RET_COM_CODE(Condition, Code)	\
	do													\
	{													\
		if (!(Condition))								\
		{												\
			hrResult = Code;							\
			assert(false);								\
			goto Exit0;									\
		}												\
	} KE_WHILE_FALSE_NO_WARNING
#endif//_DEBUG
#endif//PROCESS_ERROR_RET_COM_CODE

#ifndef COM_PROC_ERR_RET_ERR
#ifndef _DEBUG
#define COM_PROC_ERR_RET_ERR(Condition)  \
	do										\
	{										\
		if (FAILED(Condition))				\
		{									\
			hrResult = Condition;			\
			goto Exit0;						\
		}									\
	} KE_WHILE_FALSE_NO_WARNING
#else
#define COM_PROC_ERR_RET_ERR(Condition)  \
	do										\
	{										\
		if (FAILED(Condition))				\
		{									\
			hrResult = Condition;			\
			assert(false);					\
			goto Exit0;						\
		}									\
	} KE_WHILE_FALSE_NO_WARNING
#endif//_DEBUG
#endif//COM_PROC_ERR_RET_ERR

#ifndef COM_PROC_ERROR_RET_CODE
#ifndef _DEBUG
#define COM_PROC_ERROR_RET_CODE(Condition, Code)     \
	do													\
	{													\
		if (FAILED(Condition))							\
		{												\
			hrResult = Code;							\
			goto Exit0;									\
		}												\
	} KE_WHILE_FALSE_NO_WARNING
#else
#define COM_PROC_ERROR_RET_CODE(Condition, Code)     \
	do													\
	{													\
		if (FAILED(Condition))							\
		{												\
			hrResult = Code;							\
			assert(false);								\
			goto Exit0;									\
		}												\
	} KE_WHILE_FALSE_NO_WARNING
#endif//_DEBUG
#endif//COM_PROC_ERROR_RET_CODE

#ifndef ASSERT_EXIT
#ifndef _DEBUG
#define ASSERT_EXIT(Condition)	\
	do								\
	{								\
		if (!(Condition))			\
		{							\
			goto Exit0;				\
		}							\
	} KE_WHILE_FALSE_NO_WARNING
#else
#define ASSERT_EXIT(Condition)	\
	do								\
	{								\
		if (!(Condition))			\
		{							\
			assert(false);			\
			goto Exit0;				\
		}							\
	} KE_WHILE_FALSE_NO_WARNING
#endif//_DEBUG
#endif//KG_ASSERT_EXIT

#ifndef CHECK_ERROR
#define CHECK_ERROR(Condition)	\
	do								\
	{								\
		if (!(Condition))			\
		{							\
			assert(false);			\
		}							\
	} KE_WHILE_FALSE_NO_WARNING
#endif//CHECK_ERROR

#ifndef COM_CHECK_ERROR
#define COM_CHECK_ERROR(Condition)	\
	do									\
	{									\
		if (FAILED(Condition))			\
		{								\
			assert(false);				\
		}								\
	} KE_WHILE_FALSE_NO_WARNING
#endif

//-----------------------------------------------------------
//	进行正确跳转的宏定义
//-----------------------------------------------------------
#ifndef PROCESS_SUCCESS
#define PROCESS_SUCCESS(Condition)	\
	do									\
	{									\
		if (Condition)					\
		{								\
			goto Exit1;					\
		}								\
	} KE_WHILE_FALSE_NO_WARNING
#endif//PROCESS_SUCCESS

#ifndef COM_PROCESS_SUCCESS
#define COM_PROCESS_SUCCESS(Condition)   \
	do										\
	{										\
		if (SUCCEEDED(Condition))			\
		{									\
			goto Exit1;						\
		}									\
	} KE_WHILE_FALSE_NO_WARNING
#endif//COM_PROCESS_SUCCESS

//-----------------------------------------------------------
//	辅助释放对象/缓冲区宏定义
//-----------------------------------------------------------
#ifndef COM_RELEASE
#define COM_RELEASE(pInterface)		\
	do									\
	{									\
		if (pInterface)                 \
		{                               \
			(pInterface)->Release();    \
			(pInterface) = NULL;        \
		}                               \
	} KE_WHILE_FALSE_NO_WARNING
#endif//COM_RELEASE

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(pArray)     \
	do								\
	{								\
		if (pArray)                 \
		{                           \
			delete [](pArray);      \
			(pArray) = NULL;        \
		}                           \
	} KE_WHILE_FALSE_NO_WARNING
#endif//SAFE_DELETE_ARRAY

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)		\
	do						\
	{						\
		if (p)              \
		{                   \
			delete (p);     \
			(p) = NULL;     \
		}                   \
	} KE_WHILE_FALSE_NO_WARNING
#endif//SAFE_DELETE

#ifndef SAFE_FREE
#define SAFE_FREE(a)					\
	do									\
	{									\
		if (a)							\
		{								\
			free(a);					\
			(a) = NULL;					\
		}								\
	} KE_WHILE_FALSE_NO_WARNING
#endif//SAFE_FREE

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(a)					\
	do									\
	{									\
		if (a)							\
		{								\
			(a)->Release();				\
			(a) = NULL;					\
		}								\
	} KE_WHILE_FALSE_NO_WARNING
#endif//SAFE_RELEASE

#ifndef	countof
#define countof(array)					(sizeof(array)/sizeof(array[0]))
#endif

#ifndef luaAPI
#define luaAPI
#endif

#ifndef KE_PROCESS_ERROR
#ifdef _DEBUG
#define KE_PROCESS_ERROR		PROCESS_ERROR
#else
#define KE_PROCESS_ERROR		PROCESS_ERROR
#endif
#endif

#ifdef _DEBUG
#define KE_PROCESS_SUCCESS		PROCESS_SUCCESS
#else
#define KE_PROCESS_SUCCESS		PROCESS_SUCCESS
#endif

#ifndef KE_CHECK_ERROR
#ifdef _DEBUG
#define KE_CHECK_ERROR			CHECK_ERROR
#else
#define KE_CHECK_ERROR			CHECK_ERROR
#endif
#endif

#ifdef _DEBUG
#define KE_COM_CHECK_ERROR		COM_CHECK_ERROR
#else
#define KE_COM_CHECK_ERROR		COM_CHECK_ERROR
#endif

#ifdef _DEBUG
#define KE_COM_PROCESS_ERROR	COM_PROCESS_ERROR
#else
#define KE_COM_PROCESS_ERROR	COM_PROCESS_ERROR
#endif

#ifndef KE_PROCESS_SUCCESS_TRUE
#define KE_PROCESS_SUCCESS_TRUE		goto Exit1
#endif // !KE_PROCESS_SUCCESS_TRUE

#ifndef SAFE_DELETE
#define SAFE_DELETE				KG_DELETE
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY		KG_DELETE_ARRAY
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE			KG_COM_RELEASE
#endif

#endif // _KE_PUBLIC_H
