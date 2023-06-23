#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define TOTAL 552
#define INF 9999

int MAX = TOTAL;
int **weight; // 인접행렬
int *distance;
int *found;
int *path; //각 노드의 부모경로노드를 저장
int *_path; //path를 거꾸로 저장하는 배열

typedef struct {
    char name[20]; // 역의 노드번호(ex P141)
    char node[20]; // 역의 한글이름(ex 성북(현 광운대))
    int station; // 역의 호선 인덱스 (18개 호선이므로 0 ~ 17)
} Name; // 역정보 구조체

// 역의 호선이름 순서대로 저장(ex 4호선, 공항철도) 구조체
typedef struct {
    char stname[20];
} Station;

typedef struct {
    char tran[20];
} Trans;    //환승 노드번호 저장(ex P141) 구조체

int randInt(int n) {
    srand(time(NULL));
    return rand() % n + 1;  //1이상 n 이하의 랜덤값 생성, 추후 환승 소요 시간에 사용
}

int minPosInDistance() {      //distance 배열에서 가장 작은 값을 찾아 그 위치를 반환합니다.
    int min = INT_MAX;
    int minpos = -1;
    for (int i = 0; i < MAX; i++)
        if ((distance[i] < min) && !found[i])
            min = distance[(minpos = i)];
    return minpos;
}

//choice는 사용자가 입력한 1. 최단경로 | 2. 최소환승 정보이다.
//choice에 따라 가중치에 10을 곱할지 말지가 결정된다.
//최종 경로를 path[]에 업데이트한다.
void shortest_path(int start, Name *names, int choice) {
    int i, u, w;
    for (i = 0; i < MAX; i++) {
        distance[i] = weight[start][i];
        found[i] = FALSE;
        path[i] = start; //path[]의 모든 값을 start로 초기화한다
    }
    found[start] = TRUE;
    distance[start] = 0;
    for (i = 0; i < MAX - 1; i++) {
        u = minPosInDistance();
        found[u] = TRUE;
        for (w = 0; w < MAX; w++) {
            if ((choice == 2) && (strcmp(names[w].node, names[u].node) == 0)) //최소환승인 경우에만 실행
                weight[w][u] = weight[u][w] *= 10;  //간선의 비용을 늘려 환승을 안하는 쪽의 비용이 적도록 함

            if (!found[w])
                if (distance[u] + weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + weight[u][w];
                    path[w] = u; // 새로운 경로로 더 작은 가중치를 찾을 경우
                    //그 경로노드u를 w인덱스의 부모경로노드로 저장한다.
                }
        }
    }
}

//이번 과제의 핵심이 되는 부분
//csv파일로부터 역 이름, 환승정보, 소요시간 등을 불러온다.
//인접행렬을 생성한다.
int makeFile(Name *names, Trans *trans, Station *stations) {

    char str_tmp[1024];
    char *p;
    int f = 0; //파일의 첫 번째 줄을 건너뛰기 위한 변수. f가 0일 때는 첫 번째 줄을 읽지 않고 건너뛴다.
    int d = 0; //문자열을 정수로 변환한 가중치 값을 저장하는 변수
    int s = 0; //현재 탐색중인 열 혹은 현재 역의 호선 번호
    int r = 0; //인접행렬의 행 번호, 현재 역의 인덱스
    int c = 0; //인접행렬의 열 번호, 환승 역의 인덱스

    FILE *pFile[20];

    pFile[0] = fopen("1호선.csv", "r");
    pFile[1] = fopen("1지선.csv", "r");
    pFile[2] = fopen("2호선.csv", "r");
    pFile[3] = fopen("2지선.csv", "r");
    pFile[4] = fopen("3호선.csv", "r");
    pFile[5] = fopen("4호선.csv", "r");
    pFile[6] = fopen("5호선.csv", "r");
    pFile[7] = fopen("5지선.csv", "r");
    pFile[8] = fopen("6호선.csv", "r");
    pFile[9] = fopen("7호선.csv", "r");
    pFile[10] = fopen("8호선.csv", "r");
    pFile[11] = fopen("9호선.csv", "r");
    pFile[12] = fopen("분당선.csv", "r");
    pFile[13] = fopen("인천1선.csv", "r");
    pFile[14] = fopen("중앙선.csv", "r");
    pFile[15] = fopen("경춘선.csv", "r");
    pFile[16] = fopen("경의선.csv", "r");
    pFile[17] = fopen("공항철도.csv", "r");
    pFile[18] = fopen("환승정보.csv", "r");
    pFile[19] = fopen("역이름.csv", "r");

    strcpy(stations[0].stname, "1호선");
    strcpy(stations[1].stname, "1지선");
    strcpy(stations[2].stname, "2호선");
    strcpy(stations[3].stname, "2지선");
    strcpy(stations[4].stname, "3호선");
    strcpy(stations[5].stname, "4호선");
    strcpy(stations[6].stname, "5호선");
    strcpy(stations[7].stname, "5지선");
    strcpy(stations[8].stname, "6호선");
    strcpy(stations[9].stname, "7호선");
    strcpy(stations[10].stname, "8호선");
    strcpy(stations[11].stname, "9호선");
    strcpy(stations[12].stname, "분당선");
    strcpy(stations[13].stname, "인천1선");
    strcpy(stations[14].stname, "중앙선");
    strcpy(stations[15].stname, "경춘선");
    strcpy(stations[16].stname, "경의선");
    strcpy(stations[17].stname, "공항철도");

    for (int i = 0; i < 18; i++) {  //1호선부터 차례대로 총 18개의 파일에 대해 인접행렬을 만든다.
        if (pFile[i] == NULL) {
            perror("파일을 열 수 없습니다.");
            return -1;
        }
        int k = 0; //줄당 글자수
        f = 0;
        while (fgets(str_tmp, sizeof(str_tmp), pFile[i])) { //한 줄씩 읽어오기
            p = strtok(str_tmp, ","); //','를 구분자로 하여 글자 가져오기
            k = 0;
            if (f != 0)//첫번째 줄 제외하고 실행
            {
                while (c < s) {
                    weight[r][c] = INF; //앞부분에 9999를 빈칸에 넣어줌
                    c += 1;
                }
                while (p != NULL) {
                    if (k != 0) {
                        d = atoi(p); //문자열을 정수로 변환
                        weight[r][c] = d; //해당 위치에 가중치 값 저장
                        names[r].station = i; //현재 호선 번호 저장
                        c += 1;
                    }
                    p = strtok(NULL, ",");
                    k += 1;
                }
                while (c < MAX) {
                    weight[r][c] = INF;  // 뒷부분에 9999을 빈칸에 넣어줌
                    c += 1;
                }
                r += 1; //다음 행 이동
            }
            f += 1; //첫 번째 줄 건너뛰기
            c = 0;
            // p가 NULL이면 -> 한줄 다 읽었으면
        }
        s = s + k - 1;  //다음 시작열
        fclose(pFile[i]);
        // 한 파일 끝
    }

    // 역이름을 names구조체의 name배열에 각자 넣어준다.
    f = 0;
    r = 0;
    int i = 0;
    while (fgets(str_tmp, sizeof(str_tmp), pFile[19])) { //역이름.csv에서 한 줄씩 불러오기
        p = strtok(str_tmp, ",");
        if (f != 0) //첫번째 줄 건너뛰기
        {
            i = 0;
            while (p != NULL) {
                if (i == 0) //첫번째 문자열은 노드 번호
                {
                    strcpy(names[r].name, p); //역 이름 복사
                } else if (i == 1) //두번째는 한글 역이름
                {
                    p = strtok(p, "\n"); //개행 문자 제거
                    strcpy(names[r].node, p); //한글 역 이름 복사
                }
                p = strtok(NULL, ","); //다음 글자부터 찾음
                i += 1;
            }
            r += 1; //다음 역 이동
        }
        f += 1; //첫번쨰 줄 건너뛰기
    }
    fclose(pFile[19]);

    //환승 정보 업데이트
    if (pFile[18] == NULL) {
        perror("파일을 열 수 없습니다.");
        return -1;
    }
    int k = 0; //줄당 글자수
    f = 0; //첫번째 줄 건너뛰기 위함
    c = 0; //인접행렬 열 번호
    r = 0; //인접행렬 행 번호
    int R = 0, C = 0; //환승 정보 업데이트를 위한 행/열 번호
    int h = 0; //환승역 구조체 생성 인덱스

    while (fgets(str_tmp, sizeof(str_tmp), pFile[18])) { //환승정보.csv 읽어오기
        p = strtok(str_tmp, ","); //각 줄의 첫번째 글자
        k = 0;
        if (f == 0) //구조체 데이터 첫 번째 줄에 생성
        {
            while (p != NULL) {
                if (k != 0) { //두 번째 글자부터 처리
                    if (h == 149) { p = strtok(p, "\n"); }; //개행 문자 제거
                    strcpy(trans[h].tran, p); //trans 구조체의 tran 멤버에 환승 역 이름 복사
                    h += 1; //다음 환승 역
                }
                p = strtok(NULL, ","); //다음 글자부터 찾음
                k += 1;
            }
            f += 1;
        } else if (f != 0) {
            while (p != NULL) {
                if (k != 0) {
                    d = atoi(p);
                    if (d != INF && d != 0) { //가중치가 9999 또는 0이 아닌 경우에만 실행
                        for (int x = 0; x < MAX; x++) { //names 배열에서 환승역 인덱스 검색
                            if (strcmp(names[x].name, trans[c].tran) == 0) //역 이름이 일치하는 경우
                            {
                                C = x; //환승역 인덱스 저장
                                break;
                            }
                        }
                        for (int y = 0; y < MAX; y++) {
                            if (strcmp(names[y].name, trans[r].tran) == 0) { //역 이름이 일치하는 경우
                                R = y; //환승역 인덱스 저장
                                break;
                            }
                        }
                        weight[C][R] = d; //인접행렬의 해당 위치에서 가중치 값을 저장
                    }
                    c += 1; //다음 역 이동
                }
                p = strtok(NULL, ","); //다음 글자부터 찾음
                k += 1;
            }
            r += 1; //다음 환승 역 이동
            c = 0;
        }
    }
    for(int i = 0; i < sizeof(weight); i++){
        for(int j = 0; j < sizeof(weight[i]); j++){
            printf("%d ", weight[i][j]);
        }
    }
    fclose(pFile[18]); //환승정보 끝

    return 0; //성공 상태 반환
}


int find_index(char *string1, Name *names) //노드 한글 이름에서 인덱스 찾기
{
    for (int x = 0; x < MAX; x++)
        if (strcmp(string1, names[x].node) == 0)
            return x;
    return -1;
}

//path[]에 따라 경로를 출력하고, 소요시간을 계산하여 출력함.
void print_path(int start, int end, Name *names, Trans *trans, Station *stations) {
    int i = 0;
    int count = 0; //거쳐간 정거장 개수
    int sumTime = 0; // 총 시간
    int transTime = 0; // 환승소요시간
    int totalSumTime = 0; // 총 소요시간

    while (end != start) {
        _path[i] = end;
        i++;
        end = path[end];
    }
    _path[i] = start;

    makeFile(names, trans, stations);

    printf("<출발>\n");
    for (int k = i; k >= 0; k--) //뒤에서부터 경로를 출력한다.
    {
        if (strcmp(names[_path[k]].node, names[_path[k - 1]].node) == 0) {
            int random = randInt(weight[_path[k]][_path[k - 1]]);

            printf("-> <환승 : 소요시간 %d 분> ", random);
            printf("%s\n", names[_path[k - 1]].node);
            k -= 1;
            count += 1;
            transTime += random;
        } else {
            printf("-> <%s> %s\n", stations[names[_path[k]].station].stname, names[_path[k]].node);
            count += 1;
            if (k > 0) sumTime += weight[_path[k - 1]][_path[k]];
        }
    }
    totalSumTime = sumTime + transTime;
    printf("<도착>\n");
    printf("소요시간 : %d (%d + 환승 쇼요시간: %d) 분\n", totalSumTime, sumTime, transTime);
    printf("정거장 수 : %d 개\n", count);
}


//입력 예외처리
int input_error(char *started, char *ended, Name *names) {
    int start = 0;
    int end = 0;

    for (int i = 0; i < MAX; i++) {
        if (strcmp(started, names[i].node) == 0) {
            start = 1;
            if (end) break;  // 이미 도착역이 확인되었으면 루프 종료
        }
        if (strcmp(ended, names[i].node) == 0) {
            end = 1;
            if (start) break;  // 이미 출발역이 확인되었으면 루프 종료
        }
    }

    if (start && end) {
        if (strcmp(started, ended) == 0) {
            printf("출발역과 도착역을 다르게 입력하십시오.");
            return -1;
        } else {
            return 0;
        }
    } else {
        printf("잘못되었거나 없는 역입니다.");
        return -1;
    }
}

int main() {
    Name *names; //역한글이름, 역 노드번호, 역 호선 번호
    names = (Name *) malloc(MAX * sizeof(Name));

    Trans *trans; //환승정보 구조체
    trans = (Trans *) malloc(150 * sizeof(Trans));

    Station *stations; //역 호선 정보 구조체
    stations = (Station *) malloc(20 * sizeof(Station));

    char started[100]; //출발 역
    char ended[100]; //도착 역
    int choice; //최소환승 or 최단경로
    int start = 0; //시작 역 인덱스
    int end = 0; //도착 역 인덱스
    weight = (int **) malloc(MAX * sizeof(int *)); //인접행렬 동적할당
    for (int i = 0; i < MAX; ++i) {
        weight[i] = (int *) malloc(MAX * sizeof(int));
    }
    distance = (int *) malloc(MAX * sizeof(int)); //노드별 비용
    found = (int *) malloc(MAX * sizeof(int)); //노드방문 유무
    path = (int *) malloc(MAX * sizeof(int)); //부모노드 저장
    _path = (int *) malloc(MAX * sizeof(int)); //path 역순
    makeFile(names, trans, stations);


    do {
        //출발역 입력
        printf("출발역을 입력해주세요: ");
        scanf("%s", started);
        //도착역 입력
        printf("도착역을 입력해주세요: ");
        scanf("%s", ended);
        printf("\n");
    } while (input_error(started, ended, names) == -1); //예외처리 // 올바른 값 입력할 때까지 반복

    start = find_index(started, names);
    end = find_index(ended, names);

    printf("방식?  1. 최단경로 2. 최소환승\n: ");
    scanf("%d", &choice);
    getchar();
    printf("\n\n");
    (choice > 1) ? printf("최소환승\n") : printf("최단경로\n");
    shortest_path(start, names, choice);

    print_path(start, end, names, trans, stations); // 경로 출력

    for (int i = 0; i < MAX; ++i)  //인접행렬 동적할당 메모리 해제
        free(weight[i]);

    //GC가 없으므로 동적할당 메모리 해제
    free(stations);
    free(weight);
    free(names);
    free(trans);
    free(distance);
    free(found);
    free(path);
    free(_path);

    return 0;
}