#pragma config(Sensor, S4,     lightSensor,    sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

TFileHandle fileHandler;
TFileIOResult nIOResult;
string fileName = "data.txt";
int nFileSize = 32000;
string data;
byte CR = 13;
byte LF = 10;

float crane_length = 12.85;
float crane_y = 0.0;
float picture_length = 14.0;//14.0
float pause_length = 3.0;//0.0
float picture_length2 = 10.0;//14.0
float wheel_radius = 2.8;
float wheel_length = 2.0 * wheel_radius * PI;


void write (float x, float y)
{
		data = "";
		StringFormat(data, "%f %f", x, y);
		WriteString(fileHandler, nIOResult, data);
		WriteByte(fileHandler, nIOResult, CR);
		WriteByte(fileHandler, nIOResult, LF);
}

void moveCrane (bool direction)
{
		if (direction)
		while (nMotorEncoder[motorA] > -45)
		{
				motor[motorA] = -15;
				wait1Msec (20);
				motor[motorA] = 0;
				int angle = 90 + nMotorEncoder[motorA];
				if (SensorValue (lightSensor) < 50)
					write (crane_length * cosDegrees (angle), crane_y + crane_length * sinDegrees (angle));
		}
		else
		while (nMotorEncoder[motorA] < 45)
		{
				motor[motorA] = 15;
				wait1Msec (20);
				motor[motorA] = 0;
				int angle = 90 + nMotorEncoder[motorA];
				if (SensorValue (lightSensor) < 50)
					write (crane_length * cosDegrees (angle), crane_y + crane_length * sinDegrees (angle));
		}	
}

void moveRobot ()
{
		motor[motorB] = 30;
		wait1Msec (50);
		motor[motorB] = 0;
		crane_y = nMotorEncoder[motorB] / 360.0 * wheel_length;
}

void move (int distance)
{
		int cnt = nMotorEncoder[motorB];
		while ((nMotorEncoder[motorB] - cnt) / 360.0 * wheel_length < distance) motor[motorB] = 10;
		motor[motorB] = 0;
}

task main()
{
		Delete(fileName,nIOResult);
		OpenWrite(fileHandler, nIOResult, fileName, nFileSize);
		
		nMotorEncoder[motorA] = 0;
		nMotorEncoder[motorB] = 0;
		
		while (nMotorEncoder[motorA] < 45) motor[motorA] = 10;
		motor[motorA] = 0;
		
		for (int i = 0; nMotorEncoder[motorB] / 360.0 * wheel_length < picture_length; ++i)
		{		
				moveCrane ((i % 2 == 0));
				moveRobot ();
		}
		
		Close(fileHandler, nIOResult);
		
		fileName = "data2.txt";
		Delete(fileName,nIOResult);
		OpenWrite(fileHandler, nIOResult, fileName, nFileSize);
		
		move (pause_length);
		
		while (nMotorEncoder[motorA] < 45) motor[motorA] = 10;
		motor[motorA] = 0;
		
		picture_length += picture_length2 + pause_length;
		
		for (int i = 0; nMotorEncoder[motorB] / 360.0 * wheel_length < picture_length; ++i)
		{		
				moveCrane ((i % 2 == 0));
				moveRobot ();
		}
		
		Close(fileHandler, nIOResult);
}