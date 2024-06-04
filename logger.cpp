#include "logger.h"

bool LOG_WRITE_DATE = false;
bool LOG_SILENT = false;
int LOG_LEVEL = 1;

bool isNumber(const char* stringArray){
    for (int i =0; stringArray[i]!='\000';i++){
        if(isdigit(stringArray[i])==0)
            return false;
    }
    return true;
}


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
static const char *level_colors[] = {
        "",
        "",
        "",
        "",
        ""
};
#elif __linux__
static const char *level_colors[] = {
        "\x1b[34m", //DEBUG - BLUE
        "\x1b[32m", //INFO - GREEN
        "\x1b[33m", //WARNING - YELLOW
        "\x1b[31m", // ERROR - RED
        "\x1b[37m" //RESET - WHITE
};
#endif


static const char *level_strings[] = {
        "[D]",
        "[ ]",
        "[W]",
        "[!]"
};

int getTimeZoneOffset(){

    time_t now = time(NULL);
    struct tm timeinfo;
    timeinfo = *gmtime(&now);
    timeinfo.tm_isdst = -1;
    time_t timeinfot = mktime(&timeinfo);
    int diff = (now - timeinfot)/3600;

    return diff;
};

struct tm* get_time(){
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    return timeinfo;
};


void print_DBG(int level, char* filename, int line, struct tm * curTime, int timeZoneOffset){
    if(!LOG_WRITE_DATE) {

        fprintf(stdout, "%s%02d:%02d:%02d %s%-3d%s%-5s%s%-5s%s%-5d:%s%-1s",
                level_colors[4], curTime->tm_hour, curTime->tm_min, curTime->tm_sec, "UTC",
                timeZoneOffset,//print time
                level_colors[level], level_strings[level],//print level
                level_colors[4], filename, ":", line, level_colors[level],
                "");
    }
    else {
        fprintf(stdout, "%s%d-%02d-%02d %02d:%02d:%02d %s%-3d%s%-5s%s%-5s%s%-5d:%s%-1s",
                level_colors[4],curTime->tm_year+1900, curTime->tm_mon+1, curTime->tm_mday,
                curTime->tm_hour, curTime->tm_min, curTime->tm_sec, "UTC", timeZoneOffset,//print time
                level_colors[level], level_strings[level],//print level
                level_colors[4], filename,":", line, level_colors[level],
                "");//print file, code line + custom message
    }
}

void print_(int level, struct tm * curTime, int timeZoneOffset){
    if(!LOG_WRITE_DATE) {
        fprintf(stdout, "%s%02d:%02d:%02d %s%-3d%s%-5s%s",
                level_colors[4], curTime->tm_hour, curTime->tm_min, curTime->tm_sec, "UTC", timeZoneOffset,//print time
                level_colors[level], level_strings[level],//print level
                level_colors[level]);//print file, code line + custom message
    }
    else{
        fprintf(stdout, "%s%d-%02d-%02d %02d:%02d:%02d %s%-3d%s%-5s%s",
                level_colors[4],curTime->tm_year+1900, curTime->tm_mon+1, curTime->tm_mday,
                curTime->tm_hour, curTime->tm_min, curTime->tm_sec, "UTC", timeZoneOffset,//print time
                level_colors[level], level_strings[level],//print level
                level_colors[level]);//print file, code line + custom message
    }

}

void print_ER(struct tm * curTime, int timeZoneOffset){
    char *errorBuf = strerror(errno);
    if(!LOG_WRITE_DATE) {
        fprintf(stdout, "\n");
        fprintf(stderr, "%s%02d:%02d:%02d %s%-3d%s%-5s%s",
                level_colors[4], curTime->tm_hour, curTime->tm_min, curTime->tm_sec, "UTC", timeZoneOffset,
                level_colors[3], "[E]", errorBuf);
    }
    else {
        fprintf(stdout, "\n");
        fprintf(stderr, "%s%d-%02d-%02d %02d:%02d:%02d %s%-3d%s%-5s%s",
                level_colors[4], curTime->tm_year + 1900, curTime->tm_mon + 1, curTime->tm_mday,
                curTime->tm_hour, curTime->tm_min, curTime->tm_sec, "UTC", timeZoneOffset,
                level_colors[3], "[E]", errorBuf);
    }
    reset_color();
}


void lprint(int level,char* filename, int line, const char *msg, ...){

    int timeZoneOffset = getTimeZoneOffset();
    struct tm *curTime = get_time();
    va_list ap;
    va_start(ap, msg);
    if (!LOG_SILENT){
        if (level >= LOG_LEVEL){
                    if(LOG_LEVEL == LOG_DEBUG){
                        print_DBG(level, filename, line, curTime, timeZoneOffset);
                    }
                    else {
                        print_(level, curTime, timeZoneOffset);
                    }
                    vprintf(msg, ap);
                    va_end(ap);
                    if (errno !=0 || level == LOG_FATAL){
                        print_ER( curTime, timeZoneOffset);
                    }
                    reset_color();
        }
    }
};

void setDateLog(bool date){
    LOG_WRITE_DATE = date;
}

void setLogLevel(int level){
    LOG_LEVEL = level;
};
void setLogSilent(bool silent){
    if(silent){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        freopen("nul", "w+", stdout);
        freopen("nul", "w+", stderr);
    #elif __linux__
        fclose(stdout);
        fclose(stderr);
    #endif
    }
    LOG_SILENT = silent;
};
