#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int get_day_of_week(const char *date) {
    // 요일을 숫자로 반환하는 함수
    if (strcmp(date, "MON") == 0) return 1;
    if (strcmp(date, "TUE") == 0) return 2;
    if (strcmp(date, "WED") == 0) return 3;
    if (strcmp(date, "THU") == 0) return 4;
    if (strcmp(date, "FRI") == 0) return 5;
    if (strcmp(date, "SAT") == 0) return 6;
    if (strcmp(date, "SUN") == 0) return 7;
    return 0;
}

bool is_login_date(const char *date, const char **login_dates, size_t login_dates_len) {
    // 특정 날짜에 접속했는지 확인하는 함수
    for (int i = 0; i < login_dates_len; i++) {
        if (strcmp(date, login_dates[i]) == 0) {
            return true;
        }
    }
    return false;
}

int solution(const char *start_date, const char *end_date, const char *login_dates[], size_t login_dates_len) {
    int answer = 0, current_streak = 0;
    int start_month, start_day, end_month, end_day;
    char day_of_week[4];

    sscanf(start_date, "%02d/%02d %s", &start_month, &start_day, day_of_week);
    sscanf(end_date, "%02d/%02d", &end_month, &end_day);

    int current_day_of_week = get_day_of_week(day_of_week);

    for (int month = start_month; month <= end_month; month++) {
        int last_day = (month == end_month) ? end_day : (month == 2) ? 28 : (month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31;

        for (int day = (month == start_month) ? start_day : 1; day <= last_day; day++) {
            char current_date[6];
            sprintf(current_date, "%02d/%02d", month, day);

            if (is_login_date(current_date, login_dates, login_dates_len)) {
                if (current_day_of_week >= 1 && current_day_of_week <= 5) {
                    current_streak++;
                }
            } else {
                if (current_day_of_week >= 1 && current_day_of_week <= 5) {
                    if (current_streak > answer) {
                        answer = current_streak;
                    }
                    current_streak = 0;
                }
            }

            current_day_of_week = (current_day_of_week % 7) + 1;
        }
    }

    if (current_streak > answer) {
        answer = current_streak;
    }

    return answer;
}

int main() {
    //const char* start_date = "05/04 MON";
    //const char* end_date = "05/30";
    //const char* login_dates[] = {"05/26", "05/25", "05/27", "05/10", "05/11", "05/23", "05/22", "05/21", "05/06", "05/09", "05/07", "05/08"};

    const char* start_date = "05/27 SUN";
    const char* end_date = "06/16";
    const char* login_dates[] = {
        "05/31", "05/30", "06/01", "06/04", "06/07", "06/06", "06/09", "06/08", "06/13", "06/14", "06/10"
    };


    size_t login_dates_len = sizeof(login_dates) / sizeof(login_dates[0]);

    int result = solution(start_date, end_date, login_dates, login_dates_len);
    printf("Result: %d\n", result);

    return 0;
}