#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winSock2.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include<iostream>

#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")

// 닉네임을 사용자에 맞게 변경해 주세요.
#define NICKNAME "A0021_1149469"

// 일타싸피 프로그램을 로컬에서 실행할 경우 변경하지 않습니다.
#define HOST "127.0.0.1"

// 일타싸피 프로그램과 통신할 때 사용하는 코드값으로 변경하지 않습니다.
#define PORT 1447
#define CODE_SEND 9901
#define CODE_REQUEST 9902
#define SIGNAL_ORDER 9908
#define SIGNAL_CLOSE 9909

void ErrorHandling(const char* message);

int main()
{
	// 게임 환경에 대한 상수입니다.
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
	int flag = 0;
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
		// 이 위는 일타싸피와 통신하여 데이터를 주고 받기 위해 작성된 부분이므로 수정하면 안됩니다.
		//
		// 모든 수신값은 변수, 배열에서 확인할 수 있습니다.
		//   - order: 1인 경우 선공, 2인 경우 후공을 의미
		//   - balls[][]: 일타싸피 정보를 수신해서 각 공의 좌표를 배열로 저장
		//     예) balls[0][0]: 흰 공의 X좌표
		//         balls[0][1]: 흰 공의 Y좌표
		//         balls[1][0]: 1번 공의 X좌표
		//         balls[4][0]: 4번 공의 X좌표
		//         balls[5][0]: 마지막 번호(8번) 공의 X좌표

		// 여기서부터 코드를 작성하세요.
		// 아래에 있는 것은 샘플로 작성된 코드이므로 자유롭게 변경할 수 있습니다.






		// whiteBall_x, whiteBall_y: 흰 공의 X, Y좌표를 나타내기 위해 사용한 변수
		float whiteBall_x = balls[0][0];
		float whiteBall_y = balls[0][1];

		float hole_position_x[6] = { 0,0,127,127,254,254 };
		float hole_position_y[6] = { 0, 127,0,127,0,127 };

		float ball_R = 5.73;

		// targetBall_x, targetBall_y: 목적구의 X, Y좌표를 나타내기 위해 사용한 변수

		float targetBall_x = 0.0f;
		float targetBall_y = 0.0f;
		int cnt = 0;

		for (int i = 1; i < 6; i++) {
			if (balls[i][0] != -1.0f && balls[i][1] != -1.0f) {
				cnt++;
			}
		}

		if (cnt == 3) {
			flag = 1;
		}

		if (cnt >= 4) {
			flag = 2;
		}


		for (int i = 1; i < 6; i++) {
			if (balls[i][0] != -1.0f && balls[i][1] != -1.0f) {
				targetBall_x = balls[i][0];
				targetBall_y = balls[i][1];
				break;
			}
		}
		float width = fabsf(targetBall_x - whiteBall_x);
		float height = fabsf(targetBall_y - whiteBall_y);
		double distance = (double)sqrt((width * width) + (height * height));
		float available_radian = asin((2 * ball_R) / distance);
		float available_angle = (float)((180 / M_PI) * available_radian);
		int angle_diff = 100000;

		// width, height: 목적구와 흰 공의 X좌표 간의 거리, Y좌표 간의 거리
		

		// radian: width와 height를 두 변으로 하는 직각삼각형의 각도를 구한 결과
		//   - 1radian = 180 / PI (도)
		//   - 1도 = PI / 180 (radian)
		// angle : 아크탄젠트로 얻은 각도 radian을 degree로 환산한 결과
		double radian = height > 0 ? atan(width / height) : 0;
		angle = (float)((180 / M_PI) * radian);
		// 목적구가 상하좌우로 일직선상에 위치했을 때 각도 입력
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

		// 목적구가 흰공을 중심으로 2사분면에 위치해ㅔㅆ을때 각도를 재계산
		if (whiteBall_x > targetBall_x && whiteBall_y < targetBall_y)
		{
			radian = atan(width / height);
			angle = (float)(360 - ((180 / M_PI) * radian));
		}
		// 목적구가 흰 공을 중심으로 3사분면에 위치했을 때 각도를 재계산
		if (whiteBall_x > targetBall_x && whiteBall_y > targetBall_y)
		{
			radian = atan(width / height);
			angle = (float)(((180 / M_PI) * radian) + 180);
		}
		// 목적구가 흰 공을 중심으로 4사분면에 위치했을 때 각도를 재계산
		else if (whiteBall_x < targetBall_x && whiteBall_y > targetBall_y)
		{
			radian = atan(height / width);
			angle = (float)(((180 / M_PI) * radian) + 90);
		}
		int check = 0;
		//홀과 공이 일직선상에 존재하는지 확인


		for (int i = 0; i < 6; i++) {
			float hole_width = fabsf(targetBall_x - hole_position_x[i]);
			float hole_height = fabsf(targetBall_y - hole_position_y[i]);
			double hole_radian = hole_height > 0 ? atan(hole_width / hole_height) : 0;
			float hole_angle = (float)((180 / M_PI) * hole_radian);
			// 목적구가 상하좌우로 일직선상에 위치했을 때 각도 입력
			if (targetBall_x == hole_position_x[i])
			{
				if (whiteBall_y < hole_position_y[i])
				{
					hole_angle = 0;
				}
				else
				{
					hole_angle = 180;
				}
			}
			else if (targetBall_y == hole_position_y[i])
			{
				if (targetBall_x < hole_position_x[i])
				{
					hole_angle = 90;
				}
				else
				{
					hole_angle = 270;
				}
			}
			// 목적구가 흰공을 중심으로 2사분면에 위치해ㅔㅆ을때 각도를 재계산
			if (targetBall_x > hole_position_x[i] && targetBall_y < hole_position_y[i])
			{
				hole_radian = atan(hole_width / hole_height);
				hole_angle = (float)(360 - ((180 / M_PI) * hole_radian));
			}
			// 목적구가 흰 공을 중심으로 3사분면에 위치했을 때 각도를 재계산
			if (targetBall_x > hole_position_x[i] && targetBall_y > hole_position_y[i])
			{
				hole_radian = atan(hole_width / hole_height);
				hole_angle = (float)(((180 / M_PI) * hole_radian) + 180);
			}
			// 목적구가 흰 공을 중심으로 4사분면에 위치했을 때 각도를 재계산
			else if (targetBall_x < hole_position_x[i] && targetBall_y > hole_position_y[i])
			{
				hole_radian = atan(hole_height / hole_width);
				hole_angle = (float)(((180 / M_PI) * hole_radian) + 90);
			}
			if (angle - available_angle < (180-hole_angle) && (180-hole_angle) < angle + available_angle) {
				//angle = (180-hole_angle);
			}
		}

		std::cout << check << std::endl;



		// distance: 두 점(좌표) 사이의 거리를 계산


		// power: 거리 distance에 따른 힘의 세기를 계산
		power = (float)distance * 0.5f;
		
		
		if( flag == 1) {
			power = 90;
		}
		if (flag == 2) {
			power = 99;
		}


		

		// 주어진 데이터(공의 좌표)를 활용하여 두 개의 값을 최종 결정하고 나면,
		// 나머지 코드에서 일타싸피로 값을 보내 자동으로 플레이를 진행하게 합니다.
		//   - angle: 흰 공을 때려서 보낼 방향(각도)
		//   - power: 흰 공을 때릴 힘의 세기
		// 
		// 이 때 주의할 점은 power는 100을 초과할 수 없으며,
		// power = 0인 경우 힘이 제로(0)이므로 아무런 반응이 나타나지 않습니다.
		//
		// 아래는 일타싸피와 통신하는 나머지 부분이므로 수정하면 안됩니다.
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