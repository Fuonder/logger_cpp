#ifndef LOG_LIB_H
#define LOG_LIB_H

/**
\file logger.h 
**/

#include <ctime>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdbool>
#include <cstring>
#include <cerrno>
#include <string>

/**\brief Enum log possible levels.

 * **/
enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_FATAL,
};

#define reset_color(){ \
        fprintf(stdout, "\n%s", level_colors[4]);         \
};

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define __FILENAME__ (char*)(strrchr( __FILE__, '\\') ? (char*)strrchr( __FILE__, '\\') + 1 : __FILE__)
#elif __linux__
#define __FILENAME__ (char*)(strrchr( __FILE__, '/') ? (char*)strrchr( __FILE__, '/') + 1 : __FILE__)
#endif

/**\brief Wrapper function over fprintf.
 * 
 * 
 * Function prints message on certain log-level with certain color and certain structute.
 * 
 * 
 * \param [in] level Current log level.
 * \param [in] filename Caller filename.
 * \param [in] line Caller line number.
 * \param [in] msg Message to print.
 * \param [in] ... other arguments.
 * 
 * 
 * \returns Function does **not return any** values.
 * 
 * 
 * **/

void lprint(int level, char* filename, int line, const char *msg, ...);

/**\brief Function set global log-level.
 * 
 * 
 * \param [in] level Log level.

 * 
 * 
 * \returns Function does **not return any** values.
 * 
 * 
 * **/

void setLogLevel(int level);

/**\brief Function set log-silent.
 * 
 * 
 * \param [in] silent True/False
 * 
 * \returns Function does **not return any** values.
 * 
 * 
 * **/

void setLogSilent(bool silent);

/**\brief Function set log-format "with date".
 * 
 * 
 * \param [in] date True/False.
 * 
 * \returns Function does **not return any** values.
 * 
 * 
 * **/

void setDateLog(bool date);

/**\brief Defenition of wrapper function over #lprint.
 * 
 * lprint_debug prints debug-level messages.
 * 
 * **/

#define lprint_debug(...) lprint(LOG_DEBUG,__FILENAME__, __LINE__, __VA_ARGS__)

/**\brief Defenition of wrapper function over #lprint.
 * 
 * lprint_info prints info-level messages.
 * 
 * **/
#define lprint_info(...) lprint(LOG_INFO,__FILENAME__, __LINE__, __VA_ARGS__)

/**\brief Defenition of wrapper function over #lprint.
 * 
 * lprint_warning prints warning-level messages.
 * 
 * **/

#define lprint_warning(...) lprint(LOG_WARNING,__FILENAME__, __LINE__, __VA_ARGS__)

/**\brief Defenition of wrapper function over #lprint.
 * 
 * lprint_fatal prints fatal-level messages.
 * 
 * **/

#define lprint_fatal(...) lprint(LOG_FATAL,__FILENAME__, __LINE__, __VA_ARGS__)

/**\brief Function check if input string is a number.
 * 
 * 
 * \param [in] stringArray String.
 * 
 * \returns 
 * <table>
 * <tr><th>Value       <th>Description
 * <tr><td>True     <td>Is number
 * <tr><td>False   <td>Not number
 * 
 * 
 * **/

bool isNumber(const char* stringArray);

/**\brief Function calculate time zone offset.
 * 
 * \returns 
 * <table>
 * <tr><th>Value       <th>Description
 * <tr><td>int     <td>Current offset
 * 
 * **/

int getTimeZoneOffset();

/**\brief Function calculate current local date and time.
 * 
 * \returns 
 * <table>
 * <tr><th>Value       <th>Description
 * <tr><td>struct *tm     <td>Current local date and time
 * 
 * **/

struct tm* get_time();

/**\brief Wrapper function over fprintf.
 * 
 * 
 * Function prints message on log-debug level with certain color and certain structute.
 * 
 * 
 * \param [in] level Current log level.
 * \param [in] filename Caller filename.
 * \param [in] line Caller line number.
 * \param [in] curTime Current local date and time.
 * \param [in] timeZoneOffset Current time zone offset.
 * 
 * \returns Function does **not return any** values.
 * 
 * 
 * **/

void print_DBG(int level, char* filename, int line, struct tm * curTime, int timeZoneOffset);

/**\brief Wrapper function over fprintf.
 * 
 * 
 * Function prints message on log-info and higher levels with certain color and certain structute.
 * 
 * 
 * \param [in] level Current log level.
 * \param [in] curTime Current local date and time.
 * \param [in] timeZoneOffset Current time zone offset.
 * 
 * 
 * \returns Function does **not return any** values.
 * 
 * 
 * **/

void print_(int level, struct tm * curTime, int timeZoneOffset);

/**\brief Wrapper function over fprintf.
 * 
 * 
 * Function prints error log-message with certain color and certain structute.
 * 
 * 
 * \param [in] curTime Current local date and time.
 * \param [in] timeZoneOffset Current time zone offset.
 * 
 * 
 * \returns Function does **not return any** values.
 * 
 * 
 * **/

void print_ER(struct tm * curTime, int timeZoneOffset);

#endif //LOG_LIB_H
 

