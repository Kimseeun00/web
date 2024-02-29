#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winSock2.h>
#define _USE_MATH_DEFINES
#include <math.h>

#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")

// �г����� ����ڿ� �°� ������ �ּ���.
#define NICKNAME "GUMI03_C"

// ��Ÿ���� ���α׷��� ���ÿ��� ������ ��� �������� �ʽ��ϴ�.
#define HOST "127.0.0.1"

// ��Ÿ���� ���α׷��� ����� �� ����ϴ� �ڵ尪���� �������� �ʽ��ϴ�.
#define PORT 1447
#define CODE_SEND 9901
#define CODE_REQUEST 9902
#define SIGNAL_ORDER 9908
#define SIGNAL_CLOSE 9909

void ErrorHandling(const char* message);

int main()
{
    // ���� ȯ�濡 ���� ����Դϴ�.
    int TABLE_WIDTH = 254;
    int TABLE_HEIGHT = 127;
    int NUMBER_OF_BALLS = 6;
    int HOLES[6][2] = { {0, 0}, {127, 0}, {254, 0}, {0, 127}, {127, 127}, {254, 127} };

    float balls[6][2] = {
        0.0f,
    };
    int order = 0;

    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN sockAddr;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup failure.");

    hSocket = socket(PF_INET, SOCK_STREAM, 0);

    if (hSocket == INVALID_SOCKET)
        ErrorHandling("Socket Creating Failure.");

    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr(HOST);
    sockAddr.sin_port = htons(PORT);

    printf("Trying Connect: %s:%d\n", HOST, PORT);
    if (connect(hSocket, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
        ErrorHandling("Connection Failure.");
    else
        printf("Connected: %s:%d\n", HOST, PORT);

    char sendData[1024];

    sprintf(sendData, "%d/%s/", CODE_SEND, NICKNAME);
    send(hSocket, (char*)&sendData, sizeof(sendData), 0);
    printf("Ready to play!\n--------------------");

    while (1)
    {
        // Receive Data
        char message[1024];
        int strLen;
        int recvCount = 0;
        strLen = recv(hSocket, message, sizeof(message) - 1, 0);
        // printf("Data Received: %s\n", message);

        // Read Game Data
        char* recvData;
        recvData = strtok(message, "/");
        float pos = atof(recvData);

        recvCount++;

        for (int i = 0; i < NUMBER_OF_BALLS; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                balls[i][j] = pos;
                recvData = strtok(NULL, "/");

                if (recvData != NULL)
                {
                    pos = atof(recvData);

                    recvCount++;
                }
            }
        }

        // Check Signal for Player Order or Close Connection
        if (balls[0][0] == SIGNAL_ORDER)
        {
            order = (int)balls[0][1];
            printf("\n\n* You will be the %s player. *\n\n", order == 1 ? "first" : "second");
            continue;
        }
        else if (balls[0][0] == SIGNAL_CLOSE)
        {
            break;
        }

        // Show Balls' Position
        for (int i = 0; i < NUMBER_OF_BALLS; i++)
        {
            printf("ball %d: %f, %f\n", i, balls[i][0], balls[i][1]);
        }

        float angle = 0.0f;
        float power = 0.0f;

        //////////////////////////////
        // �� ���� ��Ÿ���ǿ� ����Ͽ� �����͸� �ְ� �ޱ� ���� �ۼ��� �κ��̹Ƿ� �����ϸ� �ȵ˴ϴ�.
        //
        // ��� ���Ű��� ����, �迭���� Ȯ���� �� �ֽ��ϴ�.
        //   - order: 1�� ��� ����, 2�� ��� �İ��� �ǹ�
        //   - balls[][]: ��Ÿ���� ������ �����ؼ� �� ���� ��ǥ�� �迭�� ����
        //     ��) balls[0][0]: �� ���� X��ǥ
        //         balls[0][1]: �� ���� Y��ǥ
        //         balls[1][0]: 1�� ���� X��ǥ
        //         balls[4][0]: 4�� ���� X��ǥ
        //         balls[5][0]: ������ ��ȣ(8��) ���� X��ǥ

        // ���⼭���� �ڵ带 �ۼ��ϼ���.
        // �Ʒ��� �ִ� ���� ���÷� �ۼ��� �ڵ��̹Ƿ� �����Ӱ� ������ �� �ֽ��ϴ�.






        // whiteBall_x, whiteBall_y: �� ���� X, Y��ǥ�� ��Ÿ���� ���� ����� ����
        float whiteBall_x = balls[0][0];
        float whiteBall_y = balls[0][1];

        // targetBall_x, targetBall_y: �������� X, Y��ǥ�� ��Ÿ���� ���� ����� ����

        float targetBall_x = balls[1][0];
        float targetBall_y = balls[1][1];
        if (order == 1) {
            if (balls[1][0] == -1 && balls[1][1] == -1) {
                targetBall_x = balls[3][0];
                targetBall_y = balls[3][1];
                if (balls[3][0] == 10) {
                    targetBall_x = balls[3][0] + 4;
                    targetBall_y = balls[3][1] - 3;
                }

            }
            if (balls[3][0] == -1 && balls[3][1] == -1) {
                targetBall_x = balls[5][0];
                targetBall_y = balls[5][1];
            }
        }
        else
        {
            if (balls[2][0] == -1 && balls[2][1] == -1) {
                targetBall_x = balls[4][0];
                targetBall_y = balls[4][1];
                if (balls[4][0] == 10) {
                    targetBall_x = balls[4][0] + 4;
                    targetBall_y = balls[4][1] - 3;
                }

            }
            if (balls[4][0] == -1 && balls[4][1] == -1) {
                targetBall_x = balls[5][0];
                targetBall_y = balls[5][1];
            }
        }


        // width, height: �������� �� ���� X��ǥ ���� �Ÿ�, Y��ǥ ���� �Ÿ�
        float width = fabsf(targetBall_x - whiteBall_x);
        float height = fabsf(targetBall_y - whiteBall_y);

        // radian: width�� height�� �� ������ �ϴ� �����ﰢ���� ������ ���� ���
        //   - 1radian = 180 / PI (��)
        //   - 1�� = PI / 180 (radian)
        // angle : ��ũź��Ʈ�� ���� ���� radian�� degree�� ȯ���� ���
        double radian = height > 0 ? atan(width / height) : 0;
        angle = (float)((180 / M_PI) * radian);

        // �������� �����¿�� �������� ��ġ���� �� ���� �Է�
        if (whiteBall_x == targetBall_x)
        {
            if (whiteBall_y < targetBall_y)
            {
                angle = 0;
            }
            else
            {
                angle = 180;
            }
        }
        else if (whiteBall_y == targetBall_y)
        {
            if (whiteBall_x < targetBall_x)
            {
                angle = 90;
            }
            else
            {
                angle = 270;
            }
        }



        // �������� �� ���� �߽����� 3��и鿡 ��ġ���� �� ������ ����
        if (whiteBall_x > targetBall_x && whiteBall_y > targetBall_y)
        {
            radian = atan(width / height);

            //angle = (float)(((180 / M_PI) * radian) + 213);
            //if (balls[1][0] > 0)
            angle = (float)(((180 / M_PI) * radian) + 180);
        }
        // �������� �� ���� �߽����� 4��и鿡 ��ġ���� �� ������ ����
        else if (whiteBall_x < targetBall_x && whiteBall_y > targetBall_y)
        {
            radian = atan(height / width);
            angle = (float)(((180 / M_PI) * radian) + 90);
        }
        //�������� �� ���� �߽����� 2��и鿡 ��ġ���� �� ������ ����
        else if (whiteBall_x > targetBall_x && whiteBall_y < targetBall_y)
        {
            radian = atan(height / width);
            angle = 90 - (float)(((180 / M_PI) * radian));
        }
        // �������� �� ���� �߽����� 1��и鿡 ��ġ���� �� ������ ����
        else if (whiteBall_x < targetBall_x && whiteBall_y < targetBall_y)
        {
            radian = atan(height / width);
            angle = 90 - (float)(((180 / M_PI) * radian));
        }


        // distance: �� ��(��ǥ) ������ �Ÿ��� ���
        double distance = (double)sqrt((width * width) + (height * height));

        // power: �Ÿ� distance�� ���� ���� ���⸦ ���
        power = (float)distance * 0.5f;
        power = 80;

        printf("%f", angle);


        // �־��� ������(���� ��ǥ)�� Ȱ���Ͽ� �� ���� ���� ���� �����ϰ� ����,
        // ������ �ڵ忡�� ��Ÿ���Ƿ� ���� ���� �ڵ����� �÷��̸� �����ϰ� �մϴ�.
        //   - angle: �� ���� ������ ���� ����(����)
        //   - power: �� ���� ���� ���� ����
        // 
        // �� �� ������ ���� power�� 100�� �ʰ��� �� ������,
        // power = 0�� ��� ���� ����(0)�̹Ƿ� �ƹ��� ������ ��Ÿ���� �ʽ��ϴ�.
        //
        // �Ʒ��� ��Ÿ���ǿ� ����ϴ� ������ �κ��̹Ƿ� �����ϸ� �ȵ˴ϴ�.
        //////////////////////////////

        char mergedData[1024];
        sprintf(mergedData, "%f/%f/", angle, power);
        send(hSocket, (char*)&mergedData, sizeof(mergedData), 0);
        printf("Data Sent: %s\n", mergedData);
    }

    closesocket(hSocket);
    WSACleanup();

    return 0;
}

void ErrorHandling(const char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}