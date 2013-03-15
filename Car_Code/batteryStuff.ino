const int referenceVolts = 5; // the default reference on a 5-volt board
//const float referenceVolts = 3.3; // use this for a 3.3-volt board

const int R1 = 2200; // value for a maximum voltage of 20 volts
const int R2 = 2700;
// determine by voltage divider resistors, see text
const int resistorFactor = 511 / (R2/(R1 + R2)); 
int smoothedData[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0};            // last 10 voltages recorded, will be averaged to smooth input
int prevIndex = 0;
int initPercentRemaining;
boolean initPercent = false;
int timeRemaining = 0;
int distanceRemaining = 0;
int skipCounter;
int timeCounter = 0;
int batteryPin = 1; // +V from battery is connected to analog pin 1

int currentBDIndex = 1;
const int dataLen = 336;
const int batteryData[336] = {-4895,
-4890,
-4885,
-4865,
-4765,
-4685,
-4670,
-4645,
-4635,
-4630,
-4625,
-4620,
-4605,
-4600,
-4600,
-4595,
-4585,
-4580,
-4580,
-4570,
-4565,
-4560,
-4560,
-4555,
-4550,
-4545,
-4540,
-4540,
-4535,
-4530,
-4525,
-4525,
-4520,
-4520,
-4510,
-4510,
-4505,
-4500,
-4500,
-4500,
-4500,
-4495,
-4495,
-4490,
-4490,
-4490,
-4490,
-4485,
-4480,
-4480,
-4480,
-4475,
-4475,
-4470,
-4470,
-4465,
-4460,
-4455,
-4455,
-4450,
-4450,
-4450,
-4445,
-4445,
-4445,
-4440,
-4440,
-4440,
-4440,
-4435,
-4435,
-4435,
-4435,
-4430,
-4430,
-4425,
-4425,
-4425,
-4425,
-4425,
-4425,
-4425,
-4425,
-4425,
-4420,
-4420,
-4420,
-4420,
-4420,
-4415,
-4415,
-4415,
-4415,
-4415,
-4410,
-4410,
-4410,
-4410,
-4410,
-4410,
-4405,
-4405,
-4405,
-4405,
-4405,
-4400,
-4400,
-4400,
-4400,
-4395,
-4395,
-4395,
-4395,
-4395,
-4390,
-4390,
-4390,
-4385,
-4385,
-4375,
-4375,
-4375,
-4375,
-4370,
-4370,
-4370,
-4370,
-4370,
-4365,
-4365,
-4365,
-4360,
-4360,
-4360,
-4355,
-4355,
-4355,
-4355,
-4350,
-4350,
-4350,
-4350,
-4350,
-4350,
-4345,
-4345,
-4345,
-4345,
-4345,
-4340,
-4340,
-4340,
-4340,
-4340,
-4340,
-4340,
-4335,
-4335,
-4335,
-4335,
-4330,
-4330,
-4325,
-4325,
-4325,
-4320,
-4320,
-4320,
-4320,
-4315,
-4315,
-4315,
-4315,
-4310,
-4310,
-4310,
-4305,
-4305,
-4300,
-4300,
-4300,
-4300,
-4295,
-4295,
-4295,
-4295,
-4290,
-4290,
-4285,
-4280,
-4280,
-4275,
-4265,
-4255,
-4255,
-4255,
-4255,
-4250,
-4250,
-4250,
-4250,
-4245,
-4240,
-4240,
-4240,
-4235,
-4235,
-4235,
-4235,
-4230,
-4230,
-4225,
-4225,
-4225,
-4220,
-4220,
-4220,
-4215,
-4215,
-4210,
-4210,
-4210,
-4205,
-4205,
-4205,
-4205,
-4200,
-4200,
-4200,
-4195,
-4195,
-4195,
-4195,
-4190,
-4190,
-4190,
-4185,
-4185,
-4185,
-4180,
-4180,
-4180,
-4180,
-4175,
-4170,
-4170,
-4170,
-4170,
-4170,
-4170,
-4165,
-4165,
-4165,
-4160,
-4160,
-4160,
-4160,
-4155,
-4155,
-4150,
-4150,
-4145,
-4145,
-4145,
-4145,
-4145,
-4145,
-4140,
-4140,
-4135,
-4135,
-4130,
-4130,
-4130,
-4125,
-4125,
-4125,
-4125,
-4125,
-4120,
-4120,
-4120,
-4110,
-4105,
-4105,
-4095,
-4095,
-4090,
-4090,
-4085,
-4080,
-4080,
-4075,
-4070,
-4065,
-4065,
-4060,
-4055,
-4050,
-4040,
-4035,
-4020,
-4020,
-4010,
-3990,
-3985,
-3975,
-3970,
-3955,
-3940,
-3925,
-3895,
-3880,
-3855,
-3825,
-3795,
-3750,
-3730,
-3650,
-3605,
-3545,
-3120,
-3055,
-2875,
-2820,
-2725,
-2560,
-2145,
-2090,
-1990,
-1965,
-1915,
-1885,
-1820,
-1765,
-1520
};


void getVoltage()
{
  digitalWrite(digitalBatteryPin, HIGH);
  delay(1);
  int val = analogRead(batteryPin); // read the value from the sensor
  float volts = (val / resistorFactor) * referenceVolts ; // calculate the ratio
  digitalWrite(digitalBatteryPin, LOW);
  Serial.println(volts);
  for(int shift = 9; shift >= 1; shift--)
  {
    smoothedData[shift] = smoothedData[shift-1];
  }
  smoothedData[0] = volts; 
}


void calculateTime()
{
  
  int voltageSum = 0;
  int dataPoints = 0;
  for(int recentVoltages = 0; recentVoltages < 10; recentVoltages++)
  {
    if(smoothedData[recentVoltages] != 0)
    {
      voltageSum = voltageSum + smoothedData[recentVoltages];
      dataPoints++;
    }
  }

  if(dataPoints != 0)
  {  
    voltageSum = voltageSum/dataPoints;
    getIndex(voltageSum);
    if(currentBDIndex > prevIndex)
    {
      int IncreaseIndex = currentBDIndex - prevIndex;
      if((dataPoints == 6) && ( initPercentRemaining == false))
      {
        initPercentRemaining = 100 * ((dataLen-currentBDIndex)/dataLen);
        initPercent = true;
      }
      timeRemaining = (((dataLen - currentBDIndex)/IncreaseIndex)*skipCounter); // give time remaining in minutes
      int percentUsed = initPercentRemaining - (100 * ((dataLen - currentBDIndex)/dataLen));
      distanceRemaining = (totalDistance/percentUsed) * (initPercentRemaining - percentUsed);  //calculate distance, return both
      prevIndex = currentBDIndex;
      skipCounter = 0;
    }
    else
    {
      skipCounter++;
    }
  }
  
  sendBatteryInfo(timeRemaining, distanceRemaining);  
}


void sendBatteryInfo(int timeRemaining, int distanceRemaining)
{
  String tval = (String) timeRemaining;
  while(tval.length() < 11)
  {
    tval = "0" + tval;
  }
  String dval = (String) distanceRemaining;
  while(dval.length() < 11)
  {
    dval = "0" + dval;
  }
  String batteryOut = "**b0" + tval;
  String batteryOut2 = "**b1" + dval;
  if(batteryOut.length() == 15)
  {
    delay(1);
    Serial.println(batteryOut);
  }
  if((batteryOut2.length() == 15) && (initPercentRemaining == true))
  {
    delay(1);
    Serial.println(batteryOut2);
  }  
}


void getIndex(int voltageSum)
{
  while(voltageSum < batteryData[currentBDIndex])  
  {
    currentBDIndex++;
  }
}


void tenSeconds()
{
  getVoltage();
  if((timeCounter % 3) == 0)
  {
    calculateTime();
  }
  timeCounter++;
}

