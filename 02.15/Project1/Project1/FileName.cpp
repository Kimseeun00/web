#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winSock2.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include<iostream>

#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")

// �г����� ����ڿ� �°� ������ �ּ���.
#define NICKNAME "A0021_1149469"

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

		float hole_position_x[6] = { 0,0,127,127,254,254 };
		float hole_position_y[6] = { 0, 127,0,127,0,127 };

		float ball_R = 5.73;

		// targetBall_x, targetBall_y: �������� X, Y��ǥ�� ��Ÿ���� ���� ����� ����

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

		// width, height: �������� �� ���� X��ǥ ���� �Ÿ�, Y��ǥ ���� �Ÿ�
		

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

		// �������� ����� �߽����� 2��и鿡 ��ġ�ؤĤ����� ������ ����
		if (whiteBall_x > targetBall_x && whiteBall_y < targetBall_y)
		{
			radian = atan(width / height);
			angle = (float)(360 - ((180 / M_PI) * radian));
		}
		// �������� �� ���� �߽����� 3��и鿡 ��ġ���� �� ������ ����
		if (whiteBall_x > targetBall_x && whiteBall_y > targetBall_y)
		{
			radian = atan(width / height);
			angle = (float)(((180 / M_PI) * radian) + 180);
		}
		// �������� �� ���� �߽����� 4��и鿡 ��ġ���� �� ������ ����
		else if (whiteBall_x < targetBall_x && whiteBall_y > targetBall_y)
		{
			radian = atan(height / width);
			angle = (float)(((180 / M_PI) * radian) + 90);
		}
		int check = 0;
		//Ȧ�� ���� �������� �����ϴ��� Ȯ��


		for (int i = 0; i < 6; i++) {
			float hole_width = fabsf(targetBall_x - hole_position_x[i]);
			float hole_height = fabsf(targetBall_y - hole_position_y[i]);
			double hole_radian = hole_height > 0 ? atan(hole_width / hole_height) : 0;
			float hole_angle = (float)((180 / M_PI) * hole_radian);
			// �������� �����¿�� �������� ��ġ���� �� ���� �Է�
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
			// �������� ����� �߽����� 2��и鿡 ��ġ�ؤĤ����� ������ ����
			if (targetBall_x > hole_position_x[i] && targetBall_y < hole_position_y[i])
			{
				hole_radian = atan(hole_width / hole_height);
				hole_angle = (float)(360 - ((180 / M_PI) * hole_radian));
			}
			// �������� �� ���� �߽����� 3��и鿡 ��ġ���� �� ������ ����
			if (targetBall_x > hole_position_x[i] && targetBall_y > hole_position_y[i])
			{
				hole_radian = atan(hole_width / hole_height);
				hole_angle = (float)(((180 / M_PI) * hole_radian) + 180);
			}
			// �������� �� ���� �߽����� 4��и鿡 ��ġ���� �� ������ ����
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



		// distance: �� ��(��ǥ) ������ �Ÿ��� ���


		// power: �Ÿ� distance�� ���� ���� ���⸦ ���
		power = (float)distance * 0.5f;
		
		
		if( flag == 1) {
			power = 90;
		}
		if (flag == 2) {
			power = 99;
		}


		

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