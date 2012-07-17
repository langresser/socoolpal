//
//  CQCrashReport.mm
//  CQ2Client
//
//  Created by 程序三部 on 11-2-25.
//  Copyright 2011 网龙公司. All rights reserved.
//
#include <string>
#import "CQCrashReport.h"

#include <signal.h>
#include <execinfo.h>

#ifdef DEBUG
#define LogMsg printf
#else
#define LogMsg //
#endif

namespace {
static int s_fatal_signals[] = {
    SIGABRT,
    SIGBUS,
    SIGFPE,
    SIGILL,
    SIGSEGV,
    SIGTRAP,
	SIGTERM,
	SIGKILL,
};

static const char* s_fatal_signal_names[] = {
	"SIGABRT",
	"SIGBUS",
	"SIGFPE",
	"SIGILL",
	"SIGSEGV",
	"SIGTRAP",
	"SIGTERM",
	"SIGKILL",
};

static int s_fatal_signal_num = sizeof(s_fatal_signals) / sizeof(s_fatal_signals[0]);
}

// =====================================================================================================================
// =======================================================================================================================
const char* GetSingalName(int nSignal)
{

	for (int i = 0; i < s_fatal_signal_num; ++i) {
		if (s_fatal_signals[i] == nSignal) {
			return s_fatal_signal_names[i];
		}
	}
	
	return NULL;
}

// =====================================================================================================================
//  将指定数据发给web服务器
// =======================================================================================================================
void SendErrorLogToHttp(const char* pszLog)
{
#if 0
	if (!pszLog || pszLog[0] == 0) {
		return;
	}

    NSString* str = @"http://haha.91.com/izferrormsg/msg.php";
    NSURL* url = [[NSURL alloc]initWithString: str];

    if (!url) {
        LogMsg("SendLog Error Url");
    }

    NSMutableURLRequest* request = [[NSMutableURLRequest alloc]initWithURL : url];
    if (!request) {
        LogMsg("SendLog Error Request");
    }

	NSStringEncoding enc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingGB_18030_2000);
	NSString* strLog = [[NSString alloc]initWithCString:pszLog encoding:enc];
	NSString* strServer = [[NSString alloc]initWithCString:"" encoding:enc];
    NSString* strContent = [[NSString alloc]initWithFormat:@"client=ipadpal%@&msg=%@", strServer, strLog];
    [request setHTTPMethod : @"POST"];
    [request setValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
    [request setHTTPBody: [strContent dataUsingEncoding:enc]];
    
    NSURLResponse* respone;
    NSError* error;
    [NSURLConnection sendSynchronousRequest:request returningResponse:&respone error:&error];
#endif
}

// =====================================================================================================================
//  记录错误日志，并将结果发送到指定服务器
// =======================================================================================================================
void LogMsgError(const char* pszErrorType, const char* pszCallStacks, const char* pszExtractInfo)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::string strLogBuf;
	char szTempInfo[256] = { 0 };
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (!pszErrorType) {
		strncpy(szTempInfo, "Error: Unknown\n", 255);
	} else {
		snprintf(szTempInfo, 255, "Error: %s\n", pszErrorType);
	}
	strLogBuf += szTempInfo;

	NSError * err = nil;
	NSDictionary* fileAttr = [[NSFileManager defaultManager] attributesOfItemAtPath: [[NSBundle mainBundle] executablePath] error : &err];
	if (fileAttr != nil) {
		snprintf(szTempInfo, 255, "ExeInfo: %d  %s\n", [[fileAttr objectForKey : NSFileSize] unsignedIntValue], [[[fileAttr objectForKey : NSFileModificationDate] description] UTF8String]);
		strLogBuf += szTempInfo;
	}

	extern char * GAME_CLIENT_VERSION;
	snprintf(szTempInfo, 255, "Ver: %s    OS: %s\n", "98", [[[UIDevice currentDevice]systemVersion]UTF8String]);
	strLogBuf += szTempInfo;
	
	if (pszExtractInfo && pszExtractInfo[0] != 0) {
		snprintf(szTempInfo, 255, "Other: %s\n", pszExtractInfo);
		strLogBuf += szTempInfo;
	}

	if (pszCallStacks) {
		strLogBuf += pszCallStacks;
	}

	SendErrorLogToHttp(strLogBuf.c_str());
	LogMsg(strLogBuf.c_str());
}

// =====================================================================================================================
//  对使用空指针、错误的内存读写等错误的处理
// =======================================================================================================================
void SignalHandler(int signal)
{
	switch (signal) {
		case SIGTERM:		// 程序被任务管理起咔掉
			break;
		default:
		{
			void* callstack[128];
			int numFrames = backtrace(callstack, 128);
			char **symbols = backtrace_symbols(callstack, numFrames);

			if (numFrames > 10) {
				numFrames = 10;
			}

			std::string strCallStack;
			for (int i = 0; i < numFrames; ++i) 
			{
				strCallStack += symbols[i];
				strCallStack += "\n";
			}

			free(symbols);
			LogMsgError(GetSingalName(signal), strCallStack.c_str(), NULL);
			exit(0);
		}
			break;
	}
}

// =====================================================================================================================
//  未捕获异常的处理
// =======================================================================================================================
void UncaughtExceptionHandler(NSException *exception)
{
	void* callstack[128];
	int numFrames = backtrace(callstack, 128);
	char **symbols = backtrace_symbols(callstack, numFrames);

	if (numFrames > 10) {
		numFrames = 10;
	}

	std::string strCallStack;
	for (int i = 0; i < numFrames; ++i) 
	{
		strCallStack += symbols[i];
		strCallStack += "\n";
	}

	free(symbols);
	LogMsgError([[exception name]UTF8String], strCallStack.c_str(), [[exception reason]UTF8String]);
	exit(0);
}

// =====================================================================================================================
//  客户端在程序开始的时候调用
// =======================================================================================================================
extern "C" void InitCrashReport()
{
	for (int i = 0; i < s_fatal_signal_num; ++i) {
		signal(s_fatal_signals[i], SignalHandler);
	}

	NSSetUncaughtExceptionHandler(&UncaughtExceptionHandler);
}

// =====================================================================================================================
//  客户端在程序结束的时候调用
// =======================================================================================================================
void ReleaseCrashReport()
{
	for (int i = 0; i < s_fatal_signal_num; ++i) {
		signal(s_fatal_signals[i], SIG_DFL);
	}

	NSSetUncaughtExceptionHandler(NULL);
}

// =====================================================================================================================
//  供pm命令和测试调用，崩溃
// =======================================================================================================================
void TestCrash(int nCrashType)
{
	switch (nCrashType) {
		case CRASH_SIGBUS:
		{
		  void (*func)() = 0;
			func();
		}
			break;
		case CRASH_SIGABRT:
			abort();
			break;
		case CRASH_SIGFPE:
		{
			int zero = 0;
			int i = 10/zero;
			++i;
		}
			break;
		case CRASH_SIGILL:
		{
		  typedef void(*FUNC)(void);
		  const static unsigned char insn[4] = { 0xff, 0xff, 0xff, 0xff };
		  void (*func)() = (FUNC)insn;
		  func();
		}
			break;
		case CRASH_EXCEPTION:
		{
			NSException *e = [NSException exceptionWithName:@"TestException" reason:@"Testing" userInfo:nil];
			@throw e;
		}
		default:
		{
			int* p = 0;
			(*p) = 0x123;
		}
			break;
	}
}
