#include <ctime>
#include <sys/time.h>
#include "workWithTime.h"
int getSec (time_t* difference) {
    std::time_t t = std::time(difference);
    std::tm* cur = std::localtime(&t);
    return (cur -> tm_sec);
}
int getMin (time_t* difference) {
    std::time_t t = std::time(difference);
    std::tm* cur = std::localtime(&t);
    return (cur -> tm_min);
}
int getHour (time_t* difference) {
    std::time_t t = std::time(difference);
    std::tm* cur = std::localtime(&t);
    return (cur -> tm_hour);
}
int getMs (time_t* difference) {
    struct timeval cur;
    gettimeofday( &cur, difference );
    return (cur.tv_usec);
}
int getYDay (time_t* difference) {
    std::time_t t = std::time(difference);
    std::tm* cur = std::localtime(&t);
    return (cur -> tm_yday);
}
int getWDay (time_t* difference) {
    std::time_t t = std::time(difference);
    std::tm* cur = std::localtime(&t);
    return (cur -> tm_wday);
}
int getMonth (time_t* difference) {
    std::time_t t = std::time(difference);
    std::tm* cur = std::localtime(&t);
    return (cur -> tm_mon);
}
int getYear (time_t* difference) {
    std::time_t t = std::time(difference);
    std::tm* cur = std::localtime(&t);
    return (cur -> tm_year + 1900);
}
