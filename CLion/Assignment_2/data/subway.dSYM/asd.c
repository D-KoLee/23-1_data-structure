//
// Created by SeungJun Ryu on 2023/06/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define TOTAL 552

int n = TOTAL;
int** weight; // 인접행렬

int *distance;
int *found;
int *path; //각 노드의 부모경로노드를 저장하는 배열.
int *path2; //path[]끝 부분부터의 부모경로노드를 앞에서부터 저장한다.

// 1이상 n 이하의 난수생성 함수(정수형)
int randInt(int n)
{
    srand(time(NULL));
    return rand() % n + 1;
}

// 역정보 구조체
typedef struct Name
{
    char name[20]; // 역의 노드번호(ex P157 -0)
    char node[20]; // 역의 한글이름(ex 소요산)
    int station; // 역의 호선 인덱스 ( 0 ~ 17)
} Name;

// 역의 호선이름 순서대로 저장(ex 4호선, 공항철도) 구조체
typedef struct Station
{
    char stname[20];
} Station;

typedef struct Trans // 환승 노드번호 저장(ex P157 -0) 구조체
{
    char tran[20];
} Trans;

/*
    함수명: choose
    인  자: void
    리턴형: int
    설  명: distance 배열에서 가장 작은 값을 찾아 그 위치를 반환합니다.
*/

int choose()
{
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++)
        if (distance[i]< min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

/*
    함수명: shortest_path
    인  자: int start
    리턴형: void
    설  명: 사용자가 최단시간 선택시 path[]에 경로를 업데이트합니다.
*/

void shortest_path(int start)
{
    int i, u, w;
    for (i = 0; i<n; i++)
    {
        distance[i] = weight[start][i];
        found[i] = FALSE;
        path[i] = start; //path[]의 모든 값을 start로 초기화한다
    }
    found[start] = TRUE;
    distance[start] = 0;
    for (i = 0; i<n-1; i++) {
        u = choose();
        found[u] = TRUE;
        for (w = 0; w<n; w++)
            if (!found[w])
                if (distance[u] + weight[u][w]<distance[w])
                {
                    distance[w] = distance[u] + weight[u][w];
                    path[w] = u; // 새로운 경로로 더 작은 가중치를 찾을 경우
                    //그 경로노드u를 w인덱스의 부모경로노드로 저장한다.

                }
    }
}

/*
    함수명: shortest_path2
    인  자: int start, Name* names
    리턴형: void
    설  명: 사용자가 최소환승 선택시 path[]에 경로를 업데이트합니다.
*/
void shortest_path2(int start, Name* names)
{
    int i, u, w;
    for (i = 0; i<n; i++)
    {
        distance[i] = weight[start][i];
        found[i] = FALSE;
        path[i] = start; //path[]의 모든 값을 start로 초기화한다
    }
    found[start] = TRUE;
    distance[start] = 0;
    for (i = 0; i<n-1; i++) {
        u = choose();
        found[u] = TRUE;
        for (w = 0; w < n; w++)
        {
            if (strcmp(names[w].node, names[u].node) == 0)
            {
                weight[u][w] *= 10; // 비용을 키워서 환승을 최소화한다.
                weight[w][u] *= 10;
            }
            if (!found[w])
            {
                if (distance[u] + weight[u][w]<distance[w])
                {
                    distance[w] = distance[u] + weight[u][w];
                    path[w] = u; // 새로운 경로로 더 작은 가중치를 찾을 경우
                    //그 경로노드u를 w인덱스의 부모경로노드로 저장한다.
                }
            }
        }
    }
}

/*
    함수명: myMalloc
    인  자: void
    리턴형: void
    설  명: 구조체, 배열들의 메모리를 동적으로 할당해줍니다.
*/
void myMalloc(){


    weight = (int**)malloc(n*sizeof(int*)); // 인접행렬

    for(int i = 0; i < n; ++i){
        weight[i] = (int*)malloc(sizeof(int)*n);
    }
    distance = (int*)malloc(sizeof(int)*n); // 노드별 비용
    found = (int*)malloc(sizeof(int)*n); // 노드방문 유무
    path = (int*)malloc(sizeof(int)*n); // 부모노드 저장
    path2 = (int*)malloc(sizeof(int)*n); // 방문경로 역순
}

/*
    함수명: openFile
    인  자: Name* names, Trans* trans, Station* stations
    리턴형: int
    설  명: csv파일을 열어 names, trans, stations구조체의 배열에
            데이터를 저장합니다.
*/

int openFile(Name* names, Trans* trans, Station* stations) {

    char str_tmp[1024];
    char *p;
    int f = 0;
    int d = 0;
    int s = 0;
    int r = 0;
    int c = 0;

    FILE *pFile[20];

    pFile[0] = fopen("1호선.csv", "r" );
    pFile[1] = fopen("1지선.csv", "r" );
    pFile[2] = fopen("2호선.csv", "r" );
    pFile[3] = fopen("2지선.csv", "r" );
    pFile[4] = fopen("3호선.csv", "r" );
    pFile[5] = fopen("4호선.csv", "r" );
    pFile[6] = fopen("5호선.csv", "r" );
    pFile[7] = fopen("5지선.csv", "r" );
    pFile[8] = fopen("6호선.csv", "r" );
    pFile[9] = fopen("7호선.csv", "r" );
    pFile[10] = fopen("8호선.csv", "r" );
    pFile[11] = fopen("9호선.csv", "r" );
    pFile[12] = fopen("분당선.csv", "r" );
    pFile[13] = fopen("인천1선.csv", "r" );
    pFile[14] = fopen("중앙선.csv", "r" );
    pFile[15] = fopen("경춘선.csv", "r" );
    pFile[16] = fopen("경의선.csv", "r" );
    pFile[17] = fopen("공항철도.csv", "r" );
    pFile[18] = fopen("환승정보.csv", "r" );
    pFile[19] = fopen("역이름.csv", "r" );

    strcpy(stations[0].stname,"1호선");
    strcpy(stations[1].stname,"1지선");
    strcpy(stations[2].stname,"2호선");
    strcpy(stations[3].stname,"2지선");
    strcpy(stations[4].stname,"3호선");
    strcpy(stations[5].stname,"4호선");
    strcpy(stations[6].stname,"5호선");
    strcpy(stations[7].stname,"5지선");
    strcpy(stations[8].stname,"6호선");
    strcpy(stations[9].stname,"7호선");
    strcpy(stations[10].stname,"8호선");
    strcpy(stations[11].stname,"9호선");
    strcpy(stations[12].stname,"분당선");
    strcpy(stations[13].stname,"인천1선");
    strcpy(stations[14].stname,"중앙선");
    strcpy(stations[15].stname,"경춘선");
    strcpy(stations[16].stname,"경의선");
    strcpy(stations[17].stname,"공항철도");




    for(int i = 0;i < 18; i++){  // 인접행렬을 만든다.
        if(pFile[i] == NULL)
        {
            perror("파일을 열 수 없습니다.");
            return -1;
        }
        int k = 0; //줄당 글자수
        f = 0;
        while(fgets(str_tmp, sizeof(str_tmp), pFile[i]))
        {
            p = strtok(str_tmp, ","); //각 줄의 첫번째 글자
            k = 0; // 첫번째 글자 뛰어넘기
            if( f != 0)// 첫번째 줄이 아니면
            {
                while(c < s)
                {
                    weight[r][c] = 9999; // 앞부분에 9999를 빈칸에 넣어줌
                    c += 1;
                }
                while(p != NULL){
                    if(k != 0){           // 두번째 글자부터
                        d = atoi(p);
                        weight[r][c] = d;
                        names[r].station = i;
                        c += 1;
                    }
                    p = strtok(NULL, ","); // 다음 글자부터 찾음
                    k += 1;
                }
                while(c < n)
                {
                    weight[r][c] = 9999;  // 뒷부분에 9999을 빈칸에 넣어줌
                    c += 1;
                }
                r += 1;
            }
            f += 1; // if 아닐 경우도 플러스
            c = 0;
            // p가 NULL이면 -> 한줄 다 읽었으면
        }
        s = s + k - 1;  //다음 시작열
        fclose( pFile[i] );
        // 한 파일 끝
    }
    // 역이름을 names구조체의 name배열에 각자 넣어준다.
    f = 0;
    r = 0;
    int i = 0;
    while(fgets(str_tmp, sizeof(str_tmp), pFile[19]))
    {
        p = strtok(str_tmp, ",");
        if( f != 0 ) //첫번째 줄이 아니면
        {
            i = 0;
            while(p != NULL)
            {
                if(i == 0) // 첫번째 문자열은 노드번호
                {
                    strcpy(names[r].name, p);
                }
                else if(i == 1) // 두번째는 한글 역이름
                {
                    p = strtok(p, "\n");
                    strcpy(names[r].node, p);
                }
                p = strtok(NULL, ","); //다음 글자부터 찾음
                i += 1;
            }
            r += 1;
        }
        f += 1;
    }
    fclose( pFile[19] );


    if(pFile[18] == NULL) // 환승 정보파일을 읽어서 인접행렬에 업데이트 하여준다.
    {
        perror("파일을 열 수 없습니다.");
        return -1;
    }
    int k = 0; //줄당 글자수
    f = 0; // 첫번째 줄 거르기 위해 줄 번째 세는거
    c = 0; // 열 -> 오른쪽이동
    r = 0; // 행 -> 아래로이동
    int i_r = 0; // weight에 d 환승시간 업데이트할때
    int i_c = 0; //

    int h = 0; // trans 구조체 생성 인덱스

    while(fgets(str_tmp, sizeof(str_tmp), pFile[18]))
    {
        p = strtok(str_tmp, ","); //각 줄의 첫번째 글자
        k = 0; // 첫번째 글자 뛰어넘기
        if(f == 0) // 첫번째 줄만 trans에 넣기-> 구조체 데이터 먼저 생성
        {
            while(p != NULL){
                if(k != 0)
                {
                    if(h == 149){p = strtok(p, "\n");}; // 마지막 엔터키 제거
                    strcpy(trans[h].tran, p);
                    h += 1;
                }
                p = strtok(NULL, ","); //다음 글자부터 찾음
                k += 1;
            } // p가 NULL이면 -> 한줄 다 읽었으면
            f += 1; // 첫줄 패스
        }
        else if( f != 0 )// 첫번째 줄이 아니면
        {
            while(p != NULL){
                if(k != 0){     //두번째 글자부터
                    d = atoi(p);
                    if(d != 9999 && d != 0)
                    {
                        for(int x = 0; x < n; x++)
                        {
                            if(strcmp(names[x].name, trans[c].tran) == 0) //환승역 배열에 맞는 이름의 위치
                            {
                                i_c = x;
                                break;
                            }
                        }
                        for(int y = 0; y < n; y++)
                        {
                            if(strcmp(names[y].name, trans[r].tran) == 0)
                            {
                                i_r = y;
                                break;
                            }
                        }
                        weight[i_c][i_r] = d; // 두 행과열의 위치를 찾아 환승비용 없데이트
                    }
                    c += 1;
                }
                p = strtok(NULL, ","); //다음 글자부터 찾음
                k += 1; // 두번째 글자로 패스
            } // p가 NULL이면 -> 한줄 다 읽었으면
            r += 1;
            c = 0;
        }
    }
    fclose( pFile[18] ); //환승정보 끝

    return 0;
}

/*
    이름: find-index

    노드 한글 이름에서 인덱스를 찾는 함수입니다.
*/
int find_index(char* string1, Name *names) //노드 한글 이름에서 인덱스 찾기
{
    for(int x = 0; x < n; x++)
    {
        if(strcmp(string1, names[x].node) == 0)
        {
            return x;
        }
    }
    return -1;
}

/*
    함수명: print_path
    인  자: int start, int end, Name* names, Trans* trans, Station* stations
    리턴형: void
    설  명: path[]의 경로에 따라 경로를 출력하고, 각 시간을 계산해 출력합니다.
*/

void print_path(int start, int end, Name* names, Trans* trans, Station* stations)
{
    // Station* stations
    int i = 0;
    int count = 0;
    int time1 = 0; // 총 시간
    int time2 = 0; // 환승소요시간
    int time3 = 0; // 총 소요시간

    while(end != start)
    {
        path2[i] = end; i++;
        end = path[end];
    }
    path2[i] = start;

    openFile(names, trans, stations);

    printf("<출발>\n");
    for(int k = i; k >= 0; k--) //뒤에서부터 경로를 출력한다.
    {
        if(strcmp(names[path2[k]].node, names[path2[k-1]].node) == 0)
        {
            int random = randInt(weight[path2[k]][path2[k-1]]);

            printf("-> <환승 : 소요시간 %d 분> ",random);
            printf("%s\n", names[path2[k-1]].node);
            k -= 1;
            count += 1;
            time2 += random;
        }
        else
        {
            printf("-> <%s> %s\n", stations[names[path2[k]].station].stname, names[path2[k]].node);
            count += 1;
            if (k > 0) time1 += weight[path2[k-1]][path2[k]];
        }
    }
    time3 = time1 + time2;
    printf("<도착>\n");
    printf("소요시간 : %d (%d + 환승 쇼요시간: %d) 분\n", time3, time1, time2);
    printf("정거장 수 : %d 개\n", count);
}

/*
    함수명: print_error
    인  자: char* started, char* ended, Name* names
    리턴형: int
    설  명: 사용자 입력 예외처리 함수입니다.
*/


int print_error(char* started, char* ended, Name* names){
    int s_ok = 0;
    int e_ok = 0;
    for(int i = 0; i < n; i++)
    {
        if (strcmp(started, names[i].node) == 0)  //역이름이 있으면
            s_ok = 1;
    }
    for(int j = 0; j < n; j++)
    {
        if (strcmp(ended, names[j].node) == 0) // 역이름이 있으면
            e_ok = 1;
    }

    if(strcmp(started, ended) == 0) // 같은 역을 입력했으면
    {
        printf("출발역과 도착역을 다르게 입력하세요.");
        return -1;
    }
    else if(s_ok * e_ok == 0) // 곱했을때 0이면 둘중하나라도 없는 역이다.
    {
        printf("없는 역입니다.");
        return -1;
    }
    else
        return 0;
}

/*
    함수명: main
    인  자: void
    리턴형: int
    설  명: 이 프로그램의 메인함수입니다.
*/

int main()
{
    Name *names; // 역정보(역한글이름, 역 노드번호, 역 호선 번호)
    names = (Name*)malloc(sizeof(Name)*n);

    Trans *trans; // 환승정보 구조체
    trans = (Trans*)malloc(sizeof(Trans)*150);

    Station *stations; // 역 호선 정보 구조체
    stations = (Station*)malloc(sizeof(Station)*20);

    char started[100]; // 시작 역 넣는 배열
    char ended[100]; // 도착 역
    int choice; // 방식?
    int start = 0; // 시작 역 인덱스 번호
    int end = 0; // 도착 역 인덱스 번호
    myMalloc();
    openFile(names, trans, stations);

//*************************************************
    printf("출발역을 입력해주세요: ");
    scanf("%s",started);

    printf("도착역을 입력해주세요: ");
    scanf("%s",ended);
    printf("\n\n");

    while (print_error(started, ended, names) == -1) //예외처리 // 올바른 값 입력할 때까지 반복
    {
        printf("\n출발역을 다시 입력해주세요: ");
        scanf("%s",started);
        printf("도착역을 입력해주세요: ");
        scanf("%s",ended);
        printf("\n\n");
    }

    start = find_index(started, names);
    end = find_index(ended, names);

    printf("방식?  1. 최단경로 2. 최소환승\n");
    printf(":");
    scanf("%d",&choice);
    getchar();
    printf("\n\n");

    switch (choice)
    {
        case 1: // 최단경로 선택시
            printf("최단경로\n");
            shortest_path(start);
            break;
        case 2:  // 최소환승 선택시
            printf("최소환승\n");
            shortest_path2(start, names);
            break;
    }
//*************************************************
    print_path(start, end, names, trans, stations); // 경로 출력

    for(int i = 0; i < n; ++i)  // 동적 메모리 해제
    {
        free(weight[i]);
    }
    free(stations);
    free(weight);
    free(names);
    free(trans);
    free(distance);
    free(found);
    free(path);
    free(path2);

    return 0;
}