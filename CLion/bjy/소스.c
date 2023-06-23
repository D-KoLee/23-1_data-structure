#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <locale.h>

#define TRUE 1
#define FALSE 0
#define MAX_ROWS 151
#define MAX_COLS 151
#define HOSUN_ROWS 18
#define HOSUN_COLS 63
#define MAX_LINE_LENGTH 1000
#define MAX_STATIONS 553
#define MAX_NAME_LENGTH 35
#define INF 9999 /* 무한대 (연결이 없는 경우) */

int distance[MAX_STATIONS]; /* 시작정점으로부터의 최단경로 거리 */
int found[MAX_STATIONS];
int path[MAX_STATIONS][MAX_STATIONS] = { 0, };

char stations[MAX_STATIONS][2][30] = {
        {"100", "소요산"},
        {"101", "동두천"},
        {"102", "보산"},
        {"103", "동두천중앙"},
        {"104", "지행"},
        {"105", "덕정"},
        {"106", "덕계"},
        {"107", "양주"},
        {"108", "녹양"},
        {"109", "가능"},
        {"110", "의정부"},
        {"111", "회룡"},
        {"112", "망월사"},
        {"113", "도봉산"},
        {"114", "도봉"},
        {"115", "방학"},
        {"116", "창동"},
        {"117", "녹천"},
        {"118", "월계"},
        {"119", "성북"},
        {"120", "석계"},
        {"121", "신이문"},
        {"122", "외대앞"},
        {"123", "회기"},
        {"124", "청량리"},
        {"125", "제기동"},
        {"126", "신설동"},
        {"127", "동묘앞"},
        {"128", "동대문"},
        {"129", "종로5가"},
        {"130", "종로3가"},
        {"131", "종각"},
        {"132", "시청"},
        {"133", "서울역"},
        {"134", "남영"},
        {"135", "용산"},
        {"136", "노량진"},
        {"137", "대방"},
        {"138", "신길"},
        {"139", "영등포"},
        {"140", "신도림"},
        {"141", "구로"},
        {"142", "구일"},
        {"143", "개봉"},
        {"144", "오류동"},
        {"145", "온수"},
        {"146", "역곡"},
        {"147", "소사"},
        {"148", "부천"},
        {"149", "중동"},
        {"150", "송내"},
        {"151", "부개"},
        {"152", "부평"},
        {"153", "백운"},
        {"154", "동암"},
        {"155", "간석"},
        {"156", "주안"},
        {"157", "도화"},
        {"158", "제물포"},
        {"159", "도원"},
        {"160", "동인천"},
        {"161", "인천"},
        {"P141", "구로"},
        {"P142", "가산디지털단지"},
        {"P143", "독산"},
        {"P144", "금천구청"},
        {"P145", "석수"},
        {"P146", "관악"},
        {"P147", "안양"},
        {"P148", "명학"},
        {"P149", "금정"},
        {"P150", "군포"},
        {"P151", "당정"},
        {"P152", "의왕"},
        {"P153", "성균관대"},
        {"P154", "화서"},
        {"P155", "수원"},
        {"P156", "세류"},
        {"P157", "병점"},
        {"P158", "세마"},
        {"P159", "오산대"},
        {"P160", "오산"},
        {"P161", "진위"},
        {"P162", "송탄"},
        {"P163", "서정리"},
        {"P164", "지제"},
        {"P165", "평택"},
        {"P166", "성환"},
        {"P167", "직산"},
        {"P168", "두정"},
        {"P169", "천안"},
        {"P170", "봉명"},
        {"P171", "쌍용"},
        {"P172", "아산"},
        {"P174", "배방"},
        {"P176", "온양온천"},
        {"P177", "신창"},
        {"P144-0", "금천구청"},
        {"K410", "광명"},
        {"P157-0", "병점"},
        {"P157-1", "서동탄"},
        {"202", "을지로입구"},
        {"203", "을지로3가"},
        {"204", "을지로4가"},
        {"205", "동대문역사문화공원"},
        {"206", "신당"},
        {"207", "상왕십리"},
        {"208", "왕십리"},
        {"209", "한양대"},
        {"210", "뚝섬"},
        {"211", "성수"},
        {"212", "건대입구"},
        {"213", "구의"},
        {"214", "강변"},
        {"215", "잠실나루"},
        {"216", "잠실"},
        {"217", "신천"},
        {"218", "종합운동장"},
        {"219", "삼성"},
        {"220", "선릉"},
        {"221", "역삼"},
        {"222", "강남"},
        {"223", "교대"},
        {"224", "서초"},
        {"225", "방배"},
        {"226", "사당"},
        {"227", "낙성대"},
        {"228", "서울대입구"},
        {"229", "봉천"},
        {"230", "신림"},
        {"231", "신대방"},
        {"232", "구로디지털단지"},
        {"233", "대림"},
        {"234", "신도림"},
        {"235", "문래"},
        {"236", "영등포구청"},
        {"237", "당산"},
        {"238", "합정"},
        {"239", "홍대입구"},
        {"240", "신촌"},
        {"241", "이대"},
        {"242", "아현"},
        {"243", "충정로"},
        {"201", "시청"},
        {"211-0", "성수"},
        {"211-1", "용답"},
        {"211-2", "신답"},
        {"211-3", "용두"},
        {"211-4", "신설동"},
        {"234-0", "신도림"},
        {"234-1", "도림천"},
        {"234-2", "양천구청"},
        {"234-3", "신정네거리"},
        {"234-4", "까치산"},
        {"310", "대화"},
        {"311", "주엽"},
        {"312", "정발산"},
        {"313", "마두"},
        {"314", "백석"},
        {"315", "대곡"},
        {"316", "화정"},
        {"317", "원당"},
        {"318", "삼송"},
        {"319", "지축"},
        {"320", "구파발"},
        {"321", "연신내"},
        {"322", "불광"},
        {"323", "녹번"},
        {"324", "홍제"},
        {"325", "무악재"},
        {"326", "독립문"},
        {"327", "경복궁"},
        {"328", "안국"},
        {"329", "종로3가"},
        {"330", "을지로3가"},
        {"331", "충무로"},
        {"332", "동대입구"},
        {"333", "약수"},
        {"334", "금호"},
        {"335", "옥수"},
        {"336", "압구정"},
        {"337", "신사"},
        {"338", "잠원"},
        {"339", "고속터미널"},
        {"340", "교대"},
        {"341", "남부터미널"},
        {"342", "양재"},
        {"343", "매봉"},
        {"344", "도곡"},
        {"345", "대치"},
        {"346", "학여울"},
        {"347", "대청"},
        {"348", "일원"},
        {"349", "수서"},
        {"350", "가락시장"},
        {"351", "경찰병원"},
        {"352", "오금"},
        {"409", "당고개"},
        {"410", "상계"},
        {"411", "노원"},
        {"412", "창동"},
        {"413", "쌍문"},
        {"414", "수유"},
        {"415", "미아"},
        {"416", "미아삼거리"},
        {"417", "길음"},
        {"418", "성신여대입구"},
        {"419", "한성대입구"},
        {"420", "혜화"},
        {"421", "동대문"},
        {"422", "동대문역사문화공원"},
        {"423", "충무로"},
        {"424", "명동"},
        {"425", "회현"},
        {"426", "서울역"},
        {"427", "숙대입구"},
        {"428", "삼각지"},
        {"429", "신용산"},
        {"430", "이촌"},
        {"431", "동작"},
        {"432", "이수"},
        {"433", "사당"},
        {"434", "남태령"},
        {"435", "선바위"},
        {"436", "경마공원"},
        {"437", "대공원"},
        {"438", "과천"},
        {"439", "정부과천청사"},
        {"440", "인덕원"},
        {"441", "평촌"},
        {"442", "범계"},
        {"443", "금정"},
        {"444", "산본"},
        {"445", "수리산"},
        {"446", "대야미"},
        {"447", "반월"},
        {"448", "상록수"},
        {"449", "한대앞"},
        {"450", "중앙"},
        {"451", "고잔"},
        {"452", "공단"},
        {"453", "안산"},
        {"454", "신길온천"},
        {"455", "정왕"},
        {"456", "오이도"},
        {"510", "방화"},
        {"511", "개화산"},
        {"512", "김포공항"},
        {"513", "송정"},
        {"514", "마곡"},
        {"515", "발산"},
        {"516", "우장산"},
        {"517", "화곡"},
        {"518", "까치산"},
        {"519", "신정"},
        {"520", "목동"},
        {"521", "오목교"},
        {"522", "양평"},
        {"523", "영등포구청"},
        {"524", "영등포시장"},
        {"525", "신길"},
        {"526", "여의도"},
        {"527", "여의나루"},
        {"528", "마포"},
        {"529", "공덕"},
        {"530", "애오개"},
        {"531", "충정로"},
        {"532", "서대문"},
        {"533", "광화문"},
        {"534", "종로3가"},
        {"535", "을지로4가"},
        {"536", "동대문역사문화공원"},
        {"537", "청구"},
        {"538", "신금호"},
        {"539", "행당"},
        {"540", "왕십리"},
        {"541", "마장"},
        {"542", "답십리"},
        {"543", "장한평"},
        {"544", "군자"},
        {"545", "아차산"},
        {"546", "광나루"},
        {"547", "천호"},
        {"548", "강동"},
        {"549", "길동"},
        {"550", "굽은다리"},
        {"551", "명일"},
        {"552", "고덕"},
        {"553", "상일동"},
        {"P548", "강동"},
        {"P549", "둔촌동"},
        {"P550", "올림픽공원"},
        {"P551", "방이"},
        {"P552", "오금"},
        {"P553", "개롱"},
        {"P554", "거여"},
        {"P555", "마천"},
        {"610", "역촌"},
        {"611", "불광"},
        {"612", "독바위"},
        {"613", "연신내"},
        {"614", "구산"},
        {"615", "응암"},
        {"616", "새절"},
        {"617", "증산"},
        {"618", "디지털미디어시티"},
        {"619", "월드컵경기장"},
        {"620", "마포구청"},
        {"621", "망원"},
        {"622", "합정"},
        {"623", "상수"},
        {"624", "광흥창"},
        {"625", "대흥"},
        {"626", "공덕"},
        {"627", "효창공원앞"},
        {"628", "삼각지"},
        {"629", "녹사평"},
        {"630", "이태원"},
        {"631", "한강진"},
        {"632", "버티고개"},
        {"633", "약수"},
        {"634", "청구"},
        {"635", "신당"},
        {"636", "동묘앞"},
        {"637", "창신"},
        {"638", "보문"},
        {"639", "안암"},
        {"640", "고려대"},
        {"641", "월곡"},
        {"642", "상월곡"},
        {"643", "돌곶이"},
        {"644", "석계"},
        {"645", "태릉입구"},
        {"646", "화랑대"},
        {"647", "봉화산"},
        {"709", "장암"},
        {"710", "도봉산"},
        {"711", "수락산"},
        {"712", "마들"},
        {"713", "노원"},
        {"714", "중계"},
        {"715", "하계"},
        {"716", "공릉"},
        {"717", "태릉입구"},
        {"718", "먹골"},
        {"719", "중화"},
        {"720", "상봉"},
        {"721", "면목"},
        {"722", "사가정"},
        {"723", "용마산"},
        {"724", "중곡"},
        {"725", "군자"},
        {"726", "어린이대공원"},
        {"727", "건대입구"},
        {"728", "뚝섬유원지"},
        {"729", "청담"},
        {"730", "강남구청"},
        {"731", "학동"},
        {"732", "논현"},
        {"733", "반포"},
        {"734", "고속터미널"},
        {"735", "내방"},
        {"736", "이수"},
        {"737", "남성"},
        {"738", "숭실대입구"},
        {"739", "상도"},
        {"740", "장승배기"},
        {"741", "신대방삼거리"},
        {"742", "보라매"},
        {"743", "신풍"},
        {"744", "대림"},
        {"745", "남구로"},
        {"746", "가산디지털단지"},
        {"747", "철산"},
        {"748", "광명사거리"},
        {"749", "천왕"},
        {"750", "온수"},
        {"810", "암사"},
        {"811", "천호"},
        {"812", "강동구청"},
        {"813", "몽촌토성"},
        {"814", "잠실"},
        {"815", "석촌"},
        {"816", "송파"},
        {"817", "가락시장"},
        {"818", "문정"},
        {"819", "장지"},
        {"820", "복정"},
        {"821", "산성"},
        {"822", "남한산성입구"},
        {"823", "단대오거리"},
        {"824", "신흥"},
        {"825", "수진"},
        {"826", "모란"},
        {"901", "개화"},
        {"902", "김포공항"},
        {"903", "공항시장"},
        {"904", "신방화"},
        {"905", "마곡나루"},
        {"906", "양천향교"},
        {"907", "가양"},
        {"908", "증미"},
        {"909", "등촌"},
        {"910", "염창"},
        {"911", "신목동"},
        {"912", "선유도"},
        {"913", "당산"},
        {"914", "국회의사당"},
        {"915", "여의도"},
        {"916", "샛강"},
        {"917", "노량진"},
        {"918", "노들"},
        {"919", "흑석"},
        {"920", "동작"},
        {"921", "구반포"},
        {"922", "신반포"},
        {"923", "고속터미널"},
        {"924", "사평"},
        {"925", "신논현"},
        {"K210", "왕십리"},
        {"K211", "서울숲"},
        {"K212", "신청담"},
        {"K213", "강남구청"},
        {"K214", "삼릉"},
        {"K215", "선릉"},
        {"K216", "한티"},
        {"K217", "도곡"},
        {"K218", "구룡"},
        {"K219", "개포동"},
        {"K220", "대모산입구"},
        {"K221", "수서"},
        {"K222", "복정"},
        {"K223", "경원대"},
        {"K224", "태평"},
        {"K225", "모란"},
        {"K226", "야탑"},
        {"K227", "이매"},
        {"K228", "서현"},
        {"K229", "수내"},
        {"K230", "정자"},
        {"K231", "미금"},
        {"K232", "오리"},
        {"K233", "죽전"},
        {"K234", "보정"},
        {"I110", "계양"},
        {"I111", "귤현"},
        {"I112", "박촌"},
        {"I113", "임학"},
        {"I114", "계산"},
        {"I115", "경인교대"},
        {"I116", "작전"},
        {"I117", "갈산"},
        {"I118", "부평구청"},
        {"I119", "부평시장"},
        {"I120", "부평"},
        {"I121", "동수"},
        {"I122", "부평삼거리"},
        {"I123", "간석오거리"},
        {"I124", "인천시청"},
        {"I125", "예술회관"},
        {"I126", "인천터미널"},
        {"I127", "문학경기장"},
        {"I128", "선학"},
        {"I129", "신연수"},
        {"I130", "원인재"},
        {"I131", "동춘"},
        {"I132", "동막"},
        {"I133", "캠퍼스타운"},
        {"I134", "테크노파크"},
        {"I135", "지식정보단지"},
        {"I136", "인천대입구"},
        {"I137", "센트럴파크"},
        {"I138", "국제업무지구"},
        {"K110", "용산"},
        {"K111", "이촌"},
        {"K112", "서빙고"},
        {"K113", "한남"},
        {"K114", "옥수"},
        {"K115", "응봉"},
        {"K116", "왕십리"},
        {"K117", "청량리"},
        {"K118", "회기"},
        {"K119", "중랑"},
        {"K120", "상봉"},
        {"K121", "망우"},
        {"K122", "양원"},
        {"K123", "구리"},
        {"K124", "도농"},
        {"K125", "양정"},
        {"K126", "덕소"},
        {"K127", "도심"},
        {"K128", "팔당"},
        {"K129", "운길산"},
        {"K130", "양수"},
        {"K131", "신원"},
        {"K132", "국수"},
        {"K133", "아신"},
        {"K134", "오빈"},
        {"K135", "양평"},
        {"K136", "원덕"},
        {"K137", "용문"},
        {"P120", "상봉"},
        {"P121", "망우"},
        {"P122", "신내"},
        {"P123", "갈매"},
        {"P124", "별내"},
        {"P125", "퇴계원"},
        {"P126", "사릉"},
        {"P127", "금곡"},
        {"P128", "평내호평"},
        {"P129", "묵현"},
        {"P130", "마석"},
        {"P131", "대성리"},
        {"P132", "청평"},
        {"P133", "상천"},
        {"P134", "가평"},
        {"P135", "굴봉산"},
        {"P136", "백양리"},
        {"P137", "강촌"},
        {"P138", "김유정"},
        {"P139", "남춘천"},
        {"P140", "춘천"},
        {"P313", "서울역"},
        {"P314", "신촌"},
        {"K315", "가좌"},
        {"K316", "디지털미디어시티"},
        {"K317", "수색"},
        {"K318", "화전"},
        {"K320", "행신"},
        {"K321", "능곡"},
        {"K322", "대곡"},
        {"K323", "곡산"},
        {"K324", "백마"},
        {"K325", "풍산"},
        {"K326", "일산"},
        {"K327", "탄현"},
        {"K329", "운정"},
        {"K330", "금릉"},
        {"K331", "금촌"},
        {"K333", "월롱"},
        {"K334", "파주"},
        {"K335", "문산"},
        {"A01", "서울역"},
        {"A02", "공덕"},
        {"A03", "홍대입구"},
        {"A04", "디지털미디어시티"},
        {"A05", "김포공항"},
        {"A06", "계양"},
        {"A07", "검암"},
        {"A08", "운서"},
        {"A09", "공항화물청사"},
        {"A10", "인천국제공항"}
};

char* hosun[HOSUN_ROWS][HOSUN_COLS] = { 0 };

typedef struct {
    int n;  // 노드 개수
    char*** weight;  // 인접행렬 (엣지의 가중치)
    int* visited;  // 방문 여부
    char** path;  // 최소환승 경로 정보
} GraphType;

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++)
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

void print_status(GraphType* g) {
    static int step = 1; // static ?
    printf("STEP %d: ", step++);
    printf("distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF)
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }
    printf("\n\n");
}

void input_path(int w, int u) {
    int i = 0;
    while (path[w][i] != 0)
        i++;

    path[w][i] = w;
    int j = 0;
    while (path[u][j] != 0) {
        path[w][i + j + 1] = path[u][j];
        j++;
        if (j > 553)
            break;
    }
}

void init_path() {
    for (int i = 0; i < MAX_STATIONS; i++)
        for (int j = 0; j < MAX_STATIONS; j++)
            path[i][j] = 0;
}

//최소환승 찾는 함수
void minimum_transfer(GraphType* g, int start, char* start_num) {
    int i, u, w;
    init_path();
    for (i = 1; i < g->n; i++) { // 초기화
        distance[i] = atoi(g->weight[start][i]);
        if (atoi(g->weight[start][i]) != INF) {
            path[i][0] = i;
            if (i != start)
                path[i][1] = start;
        }
        found[i] = FALSE;
    }
    distance[0] = 9999;
    found[start] = TRUE; /* 시작 정점 방문 표시 */
    found[0] = TRUE;
    for (i = 0; i < g->n - 1; i++) {
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        for (w = 1; w < g->n; w++) {
            if (!found[w] && w >= 0 && w < g->n)
                if (distance[u] + atoi(g->weight[u][w]) < distance[w]) {
                    distance[w] = distance[u] + atoi(g->weight[u][w]);
                    input_path(w, u);
                }
        }
    }
}

//최단경로 찾는 함수
void shortest_path(GraphType* g, int start, char* start_num) {
    int i, u, w;
    for (i = 1; i < g->n; i++) { // 초기화
        distance[i] = atoi(g->weight[start][i]);
        if (atoi(g->weight[start][i]) != INF) {
            path[i][0] = i;
            if (i != start)
                path[i][1] = start;
        }
        found[i] = FALSE;
    }
    distance[0] = 9999;
    found[start] = TRUE; /* 시작 정점 방문 표시 */
    found[0] = TRUE;
    for (i = 0; i < g->n - 1; i++) {
        if (i > 551)
            print_status(g);
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        for (w = 1; w < g->n; w++) {
            if (!found[w] && w >= 0 && w < g->n)
                if (distance[u] + atoi(g->weight[u][w]) < distance[w]) {
                    distance[w] = distance[u] + atoi(g->weight[u][w]);
                    input_path(w, u);
                }
        }
    }
}

int is_transfer(GraphType* g, char* change_info[MAX_ROWS][MAX_COLS], int row, int col) {
    //행에 대한 역번호
    char* row_num = g->weight[row][0];
    //열에 대한 역번호
    char* col_num = g->weight[0][col];

    int temp1 = 0;
    int temp2 = 0;

    for (int i = 0; i < MAX_ROWS; i++) {
        if (strcmp(change_info[i][0], row_num) == 0) {
            temp1 = i;
        }
        if (strcmp(change_info[0][i], col_num) == 0) {
            temp2 = i;
        }
    }
    if (strcmp(change_info[temp1][temp2], g->weight[row][col]) == 0)
        return 1;
    else {
        return 0;
    }
}

char* find_station_hosun(char* station_name) {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 63; j++) {
            if (hosun[i][j] == NULL)
                break;
            if (strcmp(hosun[i][j], station_name) == 0) {
                switch (i) {
                    case 0:
                        return "1호선";
                    case 1:
                        return "1지선";
                    case 2:
                        return "2호선";
                    case 3:
                        return "2지선";
                    case 4:
                        return "3호선";
                    case 5:
                        return "4호선";
                    case 6:
                        return "5호선";
                    case 7:
                        return "5지선";
                    case 8:
                        return "6호선";
                    case 9:
                        return "7호선";
                    case 10:
                        return "8호선";
                    case 11:
                        return "9호선";
                    case 12:
                        return "분당선";
                    case 13:
                        return "인천1선";
                    case 14:
                        return "중앙선";
                    case 15:
                        return "경춘선";
                    case 16:
                        return "경의선";
                    case 17:
                        return "공항철도";
                }
            }
        }
    }
    return -1; // not found
}

void print_path(GraphType* g, char* name[MAX_STATIONS][2], int start, int end) {
    char* before = { 0 };
    int num = 0;
    int len = 0;
    int trans_cnt = 0;
    int total_trans_time = 0;

    for (int i = 0; i < MAX_STATIONS; i++) {
        if (path[end][i] == 0)
            break;
        else
            len++;
    }

    for (int j = len - 1; j >= 0; j--) {
        if (j != 0) {
            before = name[path[end][j - 1]][1];
            num = j - 1;
        }
        if (strcmp(name[path[end][j]][1], before) == 0 && j != 0) {
            printf("<환승 : 소요시간 %s분> %s\n", g->weight[path[end][j]][path[end][num]], name[path[end][j]][1]);
            total_trans_time += atoi(g->weight[path[end][j]][path[end][num]]);
            trans_cnt++;
        }
        else {
            //<호선> 역이름 출력
            printf("<%s> %s\n", find_station_hosun(g->weight[0][path[end][j]]), name[path[end][j]][1]);
            //다음꺼 저장8+7+8
        }
    }
    printf("소요시간 %d(%d + 환승 소요시간 : %d) 분\n", distance[end], distance[end] - total_trans_time, total_trans_time);
    printf("정거장수 : %d 개\n", len - trans_cnt);
}
void print_minimum_trans_path_reverse(GraphType* g, char* name[MAX_STATIONS][2], int start, int end, char*** origin) {
    char* before = { 0 };
    int num = 0;
    int len = 0;
    int trans_cnt = 0;
    int total_trans_time = 0;
    int time = 0;
    for (int i = 0; i < MAX_STATIONS; i++) {
        if (path[end][i] == 0)
            break;
        else
            len++;
    }

    for (int j = 0; j < len; j++) {
        if (j < len) {
            before = name[path[end][j + 1]][1];
            num = j + 1;
            if (path[end][num] != 0)
                time += atoi(origin[path[end][j]][path[end][num]]);
            printf("소요시간 %d(%d + 환승 소요시간 : %d) 분\n", time, time - total_trans_time, total_trans_time);
        }
        if (strcmp(name[path[end][j]][1], before) == 0 && j != len) {
            printf("<환승 : 소요시간 %s분> %s\n", origin[path[end][j]][path[end][num]], name[path[end][j]][1]);
            total_trans_time += atoi(origin[path[end][j]][path[end][num]]);
            trans_cnt++;
        }
        else {
            //<호선> 역이름 출력
            printf("<%s> %s\n", find_station_hosun(g->weight[0][path[end][j]]), name[path[end][j]][1]);
            //다음꺼 저장8+7+8
        }
    }
    printf("소요시간 %d(%d + 환승 소요시간 : %d) 분\n", time, time - total_trans_time, total_trans_time);
    printf("정거장수 : %d 개\n", len - trans_cnt);
}

void print_minimum_trans_path(GraphType* g, char* name[MAX_STATIONS][2], int start, int end, char*** origin) {
    char* before = { 0 };
    int num = 0;
    int len = 0;
    int trans_cnt = 0;
    int total_trans_time = 0;
    int time = 0;
    for (int i = 0; i < MAX_STATIONS; i++) {
        if (path[end][i] == 0)
            break;
        else
            len++;
    }

    for (int j = len - 1; j >= 0; j--) {
        if (j != 0) {
            before = name[path[end][j - 1]][1];
            num = j - 1;
            time += atoi(origin[path[end][j]][path[end][num]]);
        }
        if (strcmp(name[path[end][j]][1], before) == 0 && j != 0) {
            printf("<환승 : 소요시간 %s분> %s\n", origin[path[end][j]][path[end][num]], name[path[end][j]][1]);
            total_trans_time += atoi(origin[path[end][j]][path[end][num]]);
            trans_cnt++;
        }
        else {
            //<호선> 역이름 출력
            printf("<%s> %s\n", find_station_hosun(g->weight[0][path[end][j]]), name[path[end][j]][1]);
        }
    }
    printf("소요시간 %d(%d + 환승 소요시간 : %d) 분\n", time, time - total_trans_time, total_trans_time);
    printf("정거장수 : %d 개\n", len - trans_cnt);
}

// csv 파일을 읽는 함수 행 열의 길이를 넘겨줌
void read_csv(char* filename, char* data[MAX_ROWS][MAX_COLS], int* num_rows, int* num_cols) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file: %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    *num_rows = 0;
    *num_cols = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char* token;
        int col = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            // LF 문자 제거
            if (token[strlen(token) - 1] == '\n') {
                token[strlen(token) - 1] = '\0';
            }

            data[*num_rows][col++] = strdup(token);
            token = strtok(NULL, ",");
        }

        if (*num_cols == 0) {
            *num_cols = col;
        }
        (*num_rows)++;
    }

    fclose(file);
}
// 역 이름.csv파일 읽기위한 함수
void name_read_csv(char* filename, char* name[MAX_STATIONS][2]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file: %s\n", filename);
        return;
    }

    int i = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, 500, file) != NULL) {
        char* token;
        int col = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            // LF 문자 제거
            if (token[strlen(token) - 1] == '\n') {
                token[strlen(token) - 1] = '\0';
            }

            name[i][col++] = strdup(token);
            token = strtok(NULL, ",");
        }
        i++;
    }

    fclose(file);
}
// 역 번호가 몇 호선인지 저장하는 함수
void hosun_read_csv(char* filename, char* data[18][63], int row) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file: %s\n", filename);
        return;
    }
    static int num_rows = 0;
    char line[MAX_LINE_LENGTH];
    //첫줄 날리기
    fgets(line, MAX_LINE_LENGTH, file);

    int col = 0;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char* token;
        token = strtok(line, ",");
        // LF 문자 제거
        if (token[strlen(token) - 1] == '\n') {
            token[strlen(token) - 1] = '\0';
        }

        data[row][col++] = strdup(token);
    }
    num_rows++;
    fclose(file);
}

// 총 역수에 맞는 인접배열에 역 정보를 저장할 때 쓸 함수
void save_first_adj_line(char* data[MAX_ROWS][MAX_COLS], char*** adj_line, int num_rows, int num_cols) {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            strcpy(adj_line[row][col], data[row][col]);
        }
    }
    strcpy(adj_line[0][0], "역정보");
}

// 총 역수에 맞는 인접배열에 역 정보를 저장할 때 쓸 함수
void save_adj_line(char* data[MAX_ROWS][MAX_COLS], char*** adj_line, int num_rows, int num_cols, int total_rows, int total_cols) {
    for (int i = 1; i < num_rows; i++)
        strcpy(adj_line[0][i + total_cols - 1], data[0][i]);
    for (int j = 1; j < num_cols; j++)
        strcpy(adj_line[j + total_rows - 1][0], data[j][0]);

    for (int row = 1; row < num_rows; row++) {
        for (int col = 1; col < num_cols; col++) {
            strcpy(adj_line[row + total_rows - 1][col + total_cols - 1], data[row][col]);
        }
    }
}

// csv 파일을 읽을 때 쓴 배열 free
void free_csv_data(char* data[MAX_ROWS][MAX_COLS], int num_rows, int num_cols) {
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            free(data[row][col]);
        }
    }
}

// 총 역수에 맞는 인접배열을 위한 2차원 char*배열 동적할당 하는 함수
char*** create_adj_line() {
    char*** adj_line = (char***)malloc(MAX_STATIONS * sizeof(char**));
    if (adj_line == NULL) {
        printf("Failed to allocate memory for adj_line\n");
        return NULL;  // 메모리 할당 실패 시 NULL 반환
    }

    for (int i = 0; i < MAX_STATIONS; i++) {
        adj_line[i] = (char**)malloc(MAX_STATIONS * sizeof(char*));
        if (adj_line[i] == NULL) {
            printf("Failed to allocate memory for adj_line[%d]\n", i);

            // 메모리 해제
            for (int j = 0; j < i; j++) {
                free(adj_line[j]);
            }
            free(adj_line);

            return NULL;  // 메모리 할당 실패 시 NULL 반환
        }

        for (int j = 0; j < MAX_STATIONS; j++) {
            adj_line[i][j] = (char*)malloc(MAX_NAME_LENGTH * sizeof(char));
            if (adj_line[i][j] == NULL) {
                printf("Failed to allocate memory for adj_line[%d][%d]\n", i, j);

                // 메모리 해제
                for (int k = 0; k < j; k++) {
                    free(adj_line[i][k]);
                }
                free(adj_line[i]);
                for (int k = 0; k < i; k++) {
                    free(adj_line[k]);
                }
                free(adj_line);

                return NULL;  // 메모리 할당 실패 시 NULL 반환
            }

            strcpy(adj_line[i][j], "9999");  // 값을 "9999"로 설정
        }
    }

    return adj_line;
}

//인접행렬에서 찾는 함수
void find_in_adj_line(char*** adj_line, int total_rows, int total_cols, char* target_row, char* target_col, char* target) {
    int where_row = 0;
    int where_col = 0;
    // 첫 번째 행 검사
    for (int col = 0; col < total_cols; col++) {
        if (strcmp(adj_line[0][col], target_row) == 0) {
            where_col = col;
        }
    }

    // 첫 번째 열 검사
    for (int row = 1; row < total_rows; row++) {
        if (strcmp(adj_line[row][0], target_col) == 0) {
            where_row = row;
        }
    }

    strcpy(adj_line[where_row][where_col], target);
}

int find_station_index(char*** adj_line, int total_rows, int total_cols, char* station_name) {
    for (int i = 1; i < total_rows; i++) {
        if (strcmp(adj_line[i][0], station_name) == 0) {
            return i;
        }
    }
    return -1; // not found
}


void input_stations(char* start_station, char* end_station, char* start, char* end, char*** adj_line, int* start_index, int* end_index, int total_rows, int total_cols, char name[MAX_STATIONS][2][30]) {
    int i;
    while (1) {
        printf("출발역을 입력해주세요 : ");
        strcpy(start_station, "인천대입구");
        printf("도착역을 입력해주세요 : ");
        strcpy(end_station, "과천");

        for (i = 0; i < MAX_STATIONS; i++) {
            if (strcmp(name[i][1], start_station) == 0)
                strcpy(start, name[i][0]);
        }
        for (i = 0; i < MAX_STATIONS; i++) {
            if (strcmp(name[i][1], end_station) == 0)
                strcpy(end, name[i][0]);
        }

        *start_index = find_station_index(adj_line, total_rows, total_cols, start);
        *end_index = find_station_index(adj_line, total_rows, total_cols, end);
        if (*start_index == -1 || *end_index == -1) { // 시작역 도착역 정보가 없을 때
            printf("역 정보가 없습니다.\n");
            printf("다시 입력해주세요.\n");
        }
        else if (strcmp(start_station, end_station) == 0) {
            printf("출발역과 도착역이 같습니다.\n");
            printf("다시 입력해주세요.\n");
        }
        else
            return;
    }
}


int main() {
    setlocale(LC_ALL, ""); // 현재 환경의 로케일을 사용

    char* line[MAX_ROWS][MAX_COLS];
    char* name[MAX_STATIONS][2];


    int num_rows, num_cols;
    int total_rows = 0;
    int total_cols = 0;
    int i, j;

    GraphType g;
    //csv 파일명 저장
    char* filename_line[18] = { "1호선.csv", "1지선.csv", "2호선.csv", "2지선.csv", "3호선.csv",
                                "4호선.csv", "5호선.csv", "5지선.csv" ,"6호선.csv", "7호선.csv",
                                "8호선.csv", "9호선.csv", "분당선.csv", "인천1선.csv", "중앙선.csv",
                                "경춘선.csv", "경의선.csv", "공항철도.csv" };
    char* filename_change = "환승정보.csv";

    //인접배열 동적할당
    char*** adj_line = create_adj_line();
    if (adj_line == NULL) {
        printf("Failed to create adj_line\n");
        return 1;  // adj_line 생성 실패 시 적절한 처리
    }
    //ex
    char*** example = create_adj_line();
    if (adj_line == NULL) {
        printf("Failed to create adj_line\n");
        return 1;  // adj_line 생성 실패 시 적절한 처리
    }

    // CSV 파일 읽기
    read_csv(filename_line[0], line, &num_rows, &num_cols);
    save_first_adj_line(line, adj_line, num_rows, num_cols);
    total_rows += num_rows;
    total_cols += num_cols;
    //1호선 정보
    hosun_read_csv(filename_line[0], hosun, 0);
    free_csv_data(line, num_rows, num_cols);
    num_rows = num_cols = 0;

    // CSV 파일 읽기
    for (i = 1; i < 18; i++) {
        read_csv(filename_line[i], line, &num_rows, &num_cols);

        // adj_line에 내용 저장
        save_adj_line(line, adj_line, num_rows, num_cols, total_rows, total_cols);
        total_rows += num_rows - 1;
        total_cols += num_cols - 1;

        hosun_read_csv(filename_line[i], hosun, i);

        // line 메모리 해제
        free_csv_data(line, num_rows, num_cols);
        num_rows = num_cols = 0;
    }

    char change_row_info[MAX_NAME_LENGTH];
    char change_col_info[MAX_NAME_LENGTH];
    // 환승정보.CSV 파일 읽기
    read_csv(filename_change, line, &num_rows, &num_cols);
    // 환승정보를 인접배열에 갱신
    for (i = 1; i < num_rows; i++) {
        for (j = 1; j < num_cols; j++) {
            if (strcmp(line[i][j], "0") != 0 && strcmp(line[i][j], "9999") != 0) {
                strcpy(change_row_info, line[0][j]);
                strcpy(change_col_info, line[i][0]);
                find_in_adj_line(adj_line, total_rows, total_cols, change_row_info, change_col_info, line[i][j]);
            }
        }
    }

    int a = 0;
    char b[10];

    for (i = 0; i < MAX_STATIONS; i++) {
        for (j = 0; j < MAX_STATIONS; j++) {
            strcpy(example[i][j], adj_line[i][j]);
        }
    }
    for (i = 1; i < MAX_STATIONS; i++) {
        for (j = 1; j < MAX_STATIONS; j++) {
            if (strcmp(example[i][j], "9999") != 0)
                strcpy(example[i][j], "0");
        }
    }
    for (i = 1; i < num_rows; i++) {
        for (j = 1; j < num_cols; j++) {
            if (strcmp(line[i][j], "0") != 0 && strcmp(line[i][j], "9999") != 0) {
                a = 1;
                strcpy(change_row_info, line[0][j]);
                strcpy(change_col_info, line[i][0]);
                sprintf(b, "%d", a);
                find_in_adj_line(example, total_rows, total_cols, change_row_info, change_col_info, b);
            }
        }
    }

    // 출발역, 도착역 입력
    char start_station[MAX_NAME_LENGTH];
    char end_station[MAX_NAME_LENGTH];
    // 출발역, 도착역의 역 번호
    char start[MAX_NAME_LENGTH] = "";
    char end[MAX_NAME_LENGTH] = "";
    int* start_index = (int*)malloc(sizeof(int));
    int* end_index = (int*)malloc(sizeof(int));

    //역이름.csv 읽어오기
    name_read_csv("역이름.csv", name);

    input_stations(start_station, end_station, start, end, adj_line, start_index, end_index, total_rows, total_cols, stations);


    g.weight = adj_line;
    g.n = MAX_STATIONS;

    shortest_path(&g, *start_index, start);
    print_path(&g, name, *start_index, *end_index);
    printf("최단거리 찾기 끝\n\n\n");


    g.weight = example;
    if (*start_index < *end_index) {
        minimum_transfer(&g, *start_index, start);
        print_minimum_trans_path(&g, name, *start_index, *end_index, adj_line);
    }
    else {
        minimum_transfer(&g, *end_index, end);
        print_minimum_trans_path_reverse(&g, name, *end_index, *start_index, adj_line);
    }

    // 메모리 해제
    for (i = 0; i < MAX_STATIONS; i++) {
        for (j = 0; j < MAX_STATIONS; j++) {
            free(adj_line[i][j]);
        }
        free(adj_line[i]);
    }
    free(adj_line);

    return 0;
}