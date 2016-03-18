/* 
N2kMessages.cpp

2015-2016 Copyright (c) Kave Oy, www.kave.fi  All right reserved.

Author: Timo Lappalainen

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-
  1301  USA
*/

#include <N2kMessages.h>

//*****************************************************************************
// System time
void SetN2kPGN126992(tN2kMsg &N2kMsg, unsigned char SID, uint16_t SystemDate,
                     double SystemTime, tN2kTimeSource TimeSource) {
    N2kMsg.SetPGN(126992L);
    N2kMsg.Priority=3;
    N2kMsg.AddByte(SID);
    N2kMsg.AddByte(TimeSource);
    N2kMsg.Add2ByteInt(SystemDate);
    N2kMsg.Add4ByteUDouble(SystemTime,0.0001);
}

//*****************************************************************************
bool ParseN2kPGN126992(const tN2kMsg &N2kMsg, unsigned char &SID, uint16_t &SystemDate,
                     double &SystemTime, tN2kTimeSource &TimeSource) {
  if (N2kMsg.PGN!=126992L) return false;

  int Index=0;
  
  SID=N2kMsg.GetByte(Index);
  TimeSource=(tN2kTimeSource)(N2kMsg.GetByte(Index));
  SystemDate=N2kMsg.Get2ByteUInt(Index);
  SystemTime=N2kMsg.Get4ByteDouble(0.0001,Index);
  
  return true;
}

//*****************************************************************************
// Rudder
// Angles should be in radians
void SetN2kPGN127245(tN2kMsg &N2kMsg, double RudderPosition, unsigned char Instance, 
                     tN2kRudderDirectionOrder RudderDirectionOrder, double AngleOrder) {
    N2kMsg.SetPGN(127245L);
    N2kMsg.Priority=2;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(0xf8 | (RudderDirectionOrder&0x07));
    N2kMsg.Add2ByteDouble(AngleOrder,0.0001);
    N2kMsg.Add2ByteDouble(RudderPosition,0.0001);
    N2kMsg.AddByte(0xff); // Reserved
    N2kMsg.AddByte(0xff); // Reserved
}

//*****************************************************************************
// Vessel Heading
// Angles should be in radians
void SetN2kPGN127250(tN2kMsg &N2kMsg, unsigned char SID, double Heading, double Deviation, double Variation, tN2kHeadingReference ref) {
    N2kMsg.SetPGN(127250L);
    N2kMsg.Priority=2;
    N2kMsg.AddByte(SID);
    N2kMsg.Add2ByteUDouble(Heading,0.0001);
    N2kMsg.Add2ByteDouble(Deviation,0.0001);
    N2kMsg.Add2ByteDouble(Variation,0.0001);
    N2kMsg.AddByte(0xfc | ref);
}

bool ParseN2kPGN127250(const tN2kMsg &N2kMsg, unsigned char &SID, double &Heading, double &Deviation, double &Variation, tN2kHeadingReference &ref) {
  if (N2kMsg.PGN!=127250L) return false;

  int Index=0;
  
  SID=N2kMsg.GetByte(Index);
  Heading=N2kMsg.Get2ByteDouble(0.0001,Index);
  Deviation=N2kMsg.Get2ByteUDouble(0.0001,Index);
  Variation=N2kMsg.Get2ByteUDouble(0.0001,Index);
  ref=(tN2kHeadingReference)(N2kMsg.GetByte(Index)&0x03);
  
  return true;
}

//*****************************************************************************
// Rate of turn
// Angles should be in radians
void SetN2kPGN127251(tN2kMsg &N2kMsg, unsigned char SID, double RateOfTurn) {
    N2kMsg.SetPGN(127251L);
    N2kMsg.Priority=2;
    N2kMsg.AddByte(SID);
    N2kMsg.Add4ByteUDouble(RateOfTurn,((1e-3/32.0) * 0.0001));
}

bool ParseN2kPGN127251(const tN2kMsg &N2kMsg, unsigned char &SID, double &RateOfTurn) {
  if (N2kMsg.PGN!=127251L) return false;

  int Index=0;
  
  SID=N2kMsg.GetByte(Index);
  RateOfTurn=N2kMsg.Get4ByteDouble(((1e-3/32.0) * 0.0001),Index);
  
  return true;
}

//*****************************************************************************
// Engine rapid param
void SetN2kPGN127488(tN2kMsg &N2kMsg, unsigned char EngineInstance, double EngineSpeed, 
                     double EngineBoostPressure, int8_t EngineTiltTrim) {
    N2kMsg.SetPGN(127488L);
    N2kMsg.Priority=3;
    N2kMsg.AddByte(EngineInstance);
    N2kMsg.Add2ByteDouble(EngineSpeed,0.25);
    N2kMsg.Add2ByteUDouble(EngineBoostPressure, 100);
    N2kMsg.AddByte(EngineTiltTrim);
    N2kMsg.AddByte(0xff); // Reserved
    N2kMsg.AddByte(0xff); // Reserved
}

bool ParseN2kPGN127488(const tN2kMsg &N2kMsg, unsigned char &EngineInstance, double &EngineSpeed, 
                     double &EngineBoostPressure, int8_t &EngineTiltTrim) {
  if (N2kMsg.PGN!=127488L) return false;

  int Index=0;
  
  EngineInstance=N2kMsg.GetByte(Index);
  EngineSpeed=N2kMsg.Get2ByteDouble(0.25,Index);
  EngineBoostPressure=N2kMsg.Get2ByteUDouble(100,Index);
  EngineTiltTrim=N2kMsg.GetByte(Index);
  
  return true;
}

//*****************************************************************************
void SetN2kPGN127489(tN2kMsg &N2kMsg, unsigned char EngineInstance, double EngineOilPress, double EngineOilTemp, double EngineCoolantTemp, double AltenatorVoltage,
                       double FuelRate, double EngineHours, double EngineCoolantPress, double EngineFuelPress, int8_t EngineLoad, int8_t EngineTorque, 
                       bool flagCheckEngine,
                       bool flagOverTemp, bool flagLowOilPress, bool flagLowOilLevel, bool flagLowFuelPress, bool flagLowSystemVoltage, bool flagLowCoolantLevel,
                       bool flagWaterFlow, bool flagWaterInFuel, bool flagChargeIndicator, bool flagPreheatIndicator, bool flagHighBoostPress, bool flagRevLimitExceeded,
                       bool flagEgrSystem, bool flagTPS, bool flagEmergencyStopMode, bool flagWarning1, bool flagWarning2, bool flagPowerReduction,
                       bool flagMaintenanceNeeded, bool flagEngineCommError, bool flagSubThrottle, bool flagNeutralStartProtect, bool flagEngineShuttingDown) {
    N2kMsg.SetPGN(127489L);
    N2kMsg.Priority=6;
                       
  N2kMsg.AddByte(EngineInstance);
  N2kMsg.Add2ByteUDouble(EngineOilPress, 100);
  N2kMsg.Add2ByteUDouble(EngineOilTemp, 0.1);
  N2kMsg.Add2ByteUDouble(EngineCoolantTemp, 0.01);
  N2kMsg.Add2ByteDouble(AltenatorVoltage, 0.01);
  N2kMsg.Add2ByteDouble(FuelRate, 0.1);
  N2kMsg.Add4ByteUDouble(EngineHours, 1);
  N2kMsg.Add2ByteUDouble(EngineCoolantPress, 100);
  N2kMsg.Add2ByteUDouble(EngineFuelPress, 1000);
  N2kMsg.AddByte(0xff);  // reserved
  N2kMsg.Add2ByteInt(0x0000);  // Discrete Status 1
  N2kMsg.Add2ByteInt(0x0000);  // Discrete Status 2

  int engineStatus1P1 = B00000000;
  int engineStatus1P2 = B00000000;
  int engineStatus2 = B00000000;
  if (flagCheckEngine) engineStatus1P1 |= B00000001;
  if (flagOverTemp) engineStatus1P1 |= B00000010;
  if (flagLowOilPress) engineStatus1P1 |= B00000100;
  if (flagLowOilLevel) engineStatus1P1 |= B00001000;
  if (flagLowFuelPress) engineStatus1P1 |= B00010000;
  if (flagLowSystemVoltage) engineStatus1P1 |= B00100000;
  if (flagLowCoolantLevel) engineStatus1P1 |= B01000000;
  if (flagWaterFlow) engineStatus1P1 |= B10000000;

  if (flagWaterInFuel) engineStatus1P2 |= B00000001;
  if (flagChargeIndicator) engineStatus1P2 |= B00000010;
  if (flagPreheatIndicator) engineStatus1P2 |= B00000100;
  if (flagHighBoostPress) engineStatus1P2 |= B00001000;
  if (flagRevLimitExceeded) engineStatus1P2 |= B00010000;
  if (flagEgrSystem) engineStatus1P2 |= B00100000;
  if (flagTPS) engineStatus1P2 |= B01000000;
  if (flagEmergencyStopMode) engineStatus1P2 |= B10000000;

  if (flagWarning1) engineStatus2 |= B00000001;
  if (flagWarning2) engineStatus2 |= B00000010;
  if (flagPowerReduction) engineStatus2 |= B00000100;
  if (flagMaintenanceNeeded) engineStatus2 |= B00001000;
  if (flagEngineCommError) engineStatus2 |= B00010000;
  if (flagSubThrottle) engineStatus2 |= B00100000;
  if (flagNeutralStartProtect) engineStatus2 |= B01000000;
  if (flagEngineShuttingDown) engineStatus2 |= B10000000;

  N2kMsg.AddByte(EngineLoad);
  N2kMsg.AddByte(EngineTorque);
}
bool ParseN2kPGN127489(const tN2kMsg &N2kMsg, unsigned char &EngineInstance, double &EngineOilPress,
                      double &EngineOilTemp, double &EngineCoolantTemp, double &AltenatorVoltage,
                      double &FuelRate, double &EngineHours, double &EngineCoolantPress, double &EngineFuelPress, 
                      int8_t &EngineLoad, int8_t &EngineTorque) {
  if (N2kMsg.PGN != 127489L) return false;

  int Index = 0;

  EngineInstance = N2kMsg.GetByte(Index);
  EngineOilPress = N2kMsg.Get2ByteUDouble(100, Index);
  EngineOilTemp  = N2kMsg.Get2ByteUDouble(0.1, Index);
  EngineCoolantTemp = N2kMsg.Get2ByteUDouble(0.01, Index);
  AltenatorVoltage = N2kMsg.Get2ByteDouble(0.01, Index);
  FuelRate =  N2kMsg.Get2ByteDouble(0.1, Index);
  EngineHours = N2kMsg.Get4ByteUDouble(1, Index);
  EngineCoolantPress=N2kMsg.Get2ByteUDouble(100, Index);
  EngineFuelPress=N2kMsg.Get2ByteUDouble(1000, Index);
  N2kMsg.GetByte(Index);  // reserved
  N2kMsg.Get2ByteInt(Index);  // Discrete Status 1
  N2kMsg.Get2ByteInt(Index);  // Discrete Status 2
  EngineLoad=N2kMsg.GetByte(Index);
  EngineTorque=N2kMsg.GetByte(Index);
  
  return true;
}


//*****************************************************************************
// Transmission parameters, dynamic
void SetN2kPGN127493(tN2kMsg &N2kMsg, unsigned char EngineInstance, tN2kTransmissionGear TransmissionGear, 
                     double OilPressure, double OilTemperature, unsigned char DiscreteStatus1) {
  N2kMsg.SetPGN(127493L);
  N2kMsg.Priority=6;
  N2kMsg.AddByte(EngineInstance);
  N2kMsg.AddByte((TransmissionGear & 0x03) | 0xfc );
  N2kMsg.Add2ByteUDouble(OilPressure, 100);
  N2kMsg.Add2ByteUDouble(OilTemperature, 0.1);
  N2kMsg.AddByte(DiscreteStatus1);
  N2kMsg.AddByte(0xff);  // Reserved
}

bool ParseN2kPGN127493(const tN2kMsg &N2kMsg, unsigned char &EngineInstance, tN2kTransmissionGear &TransmissionGear, 
                     double &OilPressure, double &OilTemperature, unsigned char &DiscreteStatus1) {
  if (N2kMsg.PGN!=127493L) return false;

  int Index=0;
  
  EngineInstance=N2kMsg.GetByte(Index);
  TransmissionGear=(tN2kTransmissionGear)(N2kMsg.GetByte(Index) & 0x03);
  OilPressure=N2kMsg.Get2ByteUDouble(100,Index);
  OilTemperature=N2kMsg.Get2ByteUDouble(0.1,Index);
  DiscreteStatus1=N2kMsg.GetByte(Index);
  
  return true;
}
                     
//*****************************************************************************
// Fluid level
void SetN2kPGN127505(tN2kMsg &N2kMsg, unsigned char Instance, tN2kFluidType FluidType, double Level, double Capacity) {
    N2kMsg.SetPGN(127505L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance&0x0f) | ((FluidType&0x0f)<<4));
    N2kMsg.Add2ByteDouble(Level,0.004);
    N2kMsg.Add4ByteUDouble(Capacity,0.1);
    N2kMsg.AddByte(0xff); // Reserved
}

//*****************************************************************************
bool ParseN2kPGN127505(const tN2kMsg &N2kMsg, unsigned char &Instance, tN2kFluidType &FluidType, double &Level, double &Capacity) {
  if (N2kMsg.PGN!=127505L) return false;

  int Index=0;
  unsigned char IFt=N2kMsg.GetByte(Index);
  
  Instance=IFt&0x0f;
  FluidType=(tN2kFluidType)((IFt>>4)&0x0f);
  Level=N2kMsg.Get2ByteDouble(0.004,Index);
  Capacity=N2kMsg.Get4ByteUDouble(0.1,Index);
  
  return true;
}

//*****************************************************************************
// DC Detailed Status
//
void SetN2kPGN127506(tN2kMsg &N2kMsg, unsigned char SID, unsigned char DCInstance, tN2kDCType DCType,
                     uint8_t StateOfCharge, uint8_t StateOfHealth, double TimeRemaining, double RippleVoltage) {
    N2kMsg.SetPGN(127506L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(SID);
    N2kMsg.AddByte(DCInstance);
    N2kMsg.AddByte((unsigned char)DCType);
    N2kMsg.AddByte(StateOfCharge);
    N2kMsg.AddByte(StateOfHealth);
    N2kMsg.Add2ByteUDouble(TimeRemaining,1.0);
    N2kMsg.Add2ByteUDouble(RippleVoltage,0.001);
}

//*****************************************************************************
bool ParseN2kPGN127506(const tN2kMsg &N2kMsg, unsigned char &SID, unsigned char &DCInstance, tN2kDCType &DCType,
                     uint8_t &StateOfCharge, uint8_t &StateOfHealth, double &TimeRemaining, double &RippleVoltage){
  if (N2kMsg.PGN!=127506L) return false;
  int Index=0;
  SID=N2kMsg.GetByte(Index);
  DCInstance=N2kMsg.GetByte(Index);
  DCType=(tN2kDCType)(N2kMsg.GetByte(Index));
  StateOfCharge=N2kMsg.GetByte(Index);
  StateOfHealth=N2kMsg.GetByte(Index);
  TimeRemaining=N2kMsg.Get2ByteUDouble(1.0,Index);
  RippleVoltage=N2kMsg.Get2ByteUDouble(0.001,Index);

  return true;
}

//*****************************************************************************
// Battery Status
// Temperatures should be in Kelvins
void SetN2kPGN127508(tN2kMsg &N2kMsg, unsigned char BatteryInstance, double BatteryVoltage, double BatteryCurrent,
                     double BatteryTemperature, unsigned char SID) {
    N2kMsg.SetPGN(127508L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(BatteryInstance);
    N2kMsg.Add2ByteDouble(BatteryVoltage,0.01);
    N2kMsg.Add2ByteDouble(BatteryCurrent,0.1);
    N2kMsg.Add2ByteUDouble(BatteryTemperature,0.01);
    N2kMsg.AddByte(SID);
}

//*****************************************************************************
bool ParseN2kPGN127508(const tN2kMsg &N2kMsg, unsigned char &BatteryInstance, double &BatteryVoltage, double &BatteryCurrent,
                     double &BatteryTemperature, unsigned char &SID) {
  if (N2kMsg.PGN!=127508L) return false;
  int Index=0;
  BatteryInstance=N2kMsg.GetByte(Index);
  BatteryVoltage=N2kMsg.Get2ByteDouble(0.01,Index);
  BatteryCurrent=N2kMsg.Get2ByteDouble(0.01,Index);
  BatteryTemperature=N2kMsg.Get2ByteUDouble(0.01,Index);
  SID=N2kMsg.GetByte(Index);

  return true;
}

//*****************************************************************************
// Battery Configuration Status
void SetN2kPGN127513(tN2kMsg &N2kMsg, unsigned char BatInstance, tN2kBatType BatType, tN2kBatEqSupport SupportsEqual,
                     tN2kBatNomVolt BatNominalVoltage, tN2kBatChem BatChemistry, double BatCapacity, int8_t BatTemperatureCoefficient,
				double PeukertExponent, int8_t ChargeEfficiencyFactor) {
    N2kMsg.SetPGN(127513L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(BatInstance);
    N2kMsg.AddByte(0xc0 | ((SupportsEqual & 0x03) << 4) | (BatType & 0x0f)); // BatType (4 bit), SupportsEqual (2 bit), Reserved (2 bit) 
    N2kMsg.AddByte( ((BatChemistry & 0x0f) << 4) | (BatNominalVoltage & 0x0f) ); // BatNominalVoltage (4 bit), BatChemistry (4 bit)
    N2kMsg.Add2ByteUDouble(BatCapacity,3600);
    N2kMsg.AddByte((int8_t)BatTemperatureCoefficient);
    PeukertExponent-=1; // Is this right or not I am not yet sure!
    if (PeukertExponent<0 || PeukertExponent>0.504) { N2kMsg.AddByte(0xff); } else { N2kMsg.Add1ByteUDouble(PeukertExponent,0.002,-1); }
    N2kMsg.AddByte((int8_t)ChargeEfficiencyFactor);
}

//*****************************************************************************
bool ParseN2kPGN127513(const tN2kMsg &N2kMsg, unsigned char &BatInstance, tN2kBatType &BatType, tN2kBatEqSupport &SupportsEqual,
                     tN2kBatNomVolt &BatNominalVoltage, tN2kBatChem &BatChemistry, double &BatCapacity, int8_t &BatTemperatureCoefficient,
				double &PeukertExponent, int8_t &ChargeEfficiencyFactor) {
  if (N2kMsg.PGN!=127513L) return false;
  int Index=0;
  unsigned char v; 
  BatInstance = N2kMsg.GetByte(Index);
  v = N2kMsg.GetByte(Index); BatType=(tN2kBatType)(v & 0x0f); SupportsEqual=(tN2kBatEqSupport)((v>>4) & 0x03);
  v = N2kMsg.GetByte(Index); BatNominalVoltage=(tN2kBatNomVolt)(v & 0x0f);  BatChemistry=(tN2kBatChem)((v>>4) & 0x0f);
  BatCapacity=N2kMsg.Get2ByteDouble(3600,Index);
  BatTemperatureCoefficient=N2kMsg.GetByte(Index);
  PeukertExponent=N2kMsg.Get1ByteUDouble(0.002,Index); PeukertExponent+=1;
  ChargeEfficiencyFactor=N2kMsg.GetByte(Index);
  
  return true;
}

//*****************************************************************************
// Boat speed
void SetN2kPGN128259(tN2kMsg &N2kMsg, unsigned char SID, double WaterRefereced, double GroundReferenced, tN2kSpeedWaterReferenceType SWRT) {
    N2kMsg.SetPGN(128259L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(SID);
    N2kMsg.Add2ByteUDouble(WaterRefereced,0.01);
    N2kMsg.Add2ByteUDouble(GroundReferenced,0.01);
    N2kMsg.AddByte(SWRT);
    N2kMsg.AddByte(0xff); // Reserved
}

bool ParseN2kPGN128259(const tN2kMsg &N2kMsg, unsigned char &SID, double &WaterRefereced, double &GroundReferenced, tN2kSpeedWaterReferenceType &SWRT) {
  if (N2kMsg.PGN!=128259L) return false;

  int Index=0;

  SID=N2kMsg.GetByte(Index);
  WaterRefereced=N2kMsg.Get2ByteUDouble(0.01,Index);
  GroundReferenced=N2kMsg.Get2ByteDouble(0.01,Index);
  SWRT=(tN2kSpeedWaterReferenceType)(N2kMsg.GetByte(Index)&0x0F);

  return true;
}

//*****************************************************************************
// Water depth
void SetN2kPGN128267(tN2kMsg &N2kMsg, unsigned char SID, double DepthBelowTransducer, double Offset) {
    N2kMsg.SetPGN(128267L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(SID);
    N2kMsg.Add4ByteUDouble(DepthBelowTransducer,0.01);
    N2kMsg.Add2ByteDouble(Offset,0.001);
    N2kMsg.AddByte(0xff); // Reserved
}

bool ParseN2kPGN128267(const tN2kMsg &N2kMsg, unsigned char &SID, double &DepthBelowTransducer, double &Offset) {
  if (N2kMsg.PGN!=128267L) return false;

  int Index=0;
  SID=N2kMsg.GetByte(Index);
  DepthBelowTransducer=N2kMsg.Get4ByteUDouble(0.01,Index);
  Offset=N2kMsg.Get2ByteDouble(0.001,Index);
  
  return true;
}

//*****************************************************************************
// Distance log
void SetN2kPGN128275(tN2kMsg &N2kMsg, uint16_t DaysSince1970, double SecondsSinceMidnight, uint32_t Log, uint32_t TripLog) {
    N2kMsg.SetPGN(128275L);
    N2kMsg.Priority=6;
    N2kMsg.Add2ByteInt(DaysSince1970);
    N2kMsg.Add4ByteUDouble(SecondsSinceMidnight,0.0001);
    N2kMsg.Add4ByteUInt(Log);
    N2kMsg.Add4ByteUInt(TripLog);
}

bool ParseN2kPGN128275(const tN2kMsg &N2kMsg, uint16_t &DaysSince1970, double &SecondsSinceMidnight, uint32_t &Log, uint32_t &TripLog) {
    if (N2kMsg.PGN!=128275L) return false;

    int Index=0;

    DaysSince1970=N2kMsg.Get2ByteUInt(Index);
    SecondsSinceMidnight=N2kMsg.Get4ByteDouble(0.0001,Index);
    Log=N2kMsg.Get4ByteUDouble(1,Index);
    TripLog=N2kMsg.Get4ByteUDouble(1,Index);

    return true;
}

//*****************************************************************************
// Lat long rapid
void SetN2kPGN129025(tN2kMsg &N2kMsg, double Latitude, double Longitude) {
    N2kMsg.SetPGN(129025L);
    N2kMsg.Priority=3;
    N2kMsg.Add4ByteDouble(Latitude,1e-7);
    N2kMsg.Add4ByteDouble(Longitude,1e-7);
}

//*****************************************************************************
// COG SOG rapid
// COG should be in radians
// SOG should be in m/s
void SetN2kPGN129026(tN2kMsg &N2kMsg, unsigned char SID, tN2kHeadingReference ref, double COG, double SOG) {
    N2kMsg.SetPGN(129026L);
    N2kMsg.Priority=3;
    N2kMsg.AddByte(SID);
    N2kMsg.AddByte( (((unsigned char)(ref)) & 0x03) | 0xfc );
    N2kMsg.Add2ByteUDouble(COG,0.0001); //0.0057295779513082332);
    N2kMsg.Add2ByteUDouble(SOG,0.01);
    N2kMsg.AddByte(0xff); // Reserved
    N2kMsg.AddByte(0xff); // Reserved
}

bool ParseN2kPGN129026(const tN2kMsg &N2kMsg, unsigned char &SID, tN2kHeadingReference &ref, double &COG, double &SOG) {
  if (N2kMsg.PGN!=129026L) return false;
  int Index=0;
  unsigned char b;
  
  SID=N2kMsg.GetByte(Index);
  b=N2kMsg.GetByte(Index); ref=(tN2kHeadingReference)( b & 0x03 );
  COG=N2kMsg.Get2ByteDouble(0.0001,Index);
  SOG=N2kMsg.Get2ByteDouble(0.01,Index);

  return true;
}

//*****************************************************************************
// GNSS Position Data
void SetN2kPGN129029(tN2kMsg &N2kMsg, unsigned char SID, uint16_t DaysSince1970, double SecondsSinceMidnight, 
                     double Latitude, double Longitude, double Altitude, 
                     tN2kGNSStype GNSStype, tN2kGNSSmethod GNSSmethod,
                     unsigned char nSatellites, double HDOP, double PDOP, double GeoidalSeparation,
                     unsigned char nReferenceStations, tN2kGNSStype ReferenceStationType, uint16_t ReferenceSationID,
                     double AgeOfCorrection
                     ) {

                     
    N2kMsg.SetPGN(129029L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(SID);
    N2kMsg.Add2ByteInt(DaysSince1970);
    N2kMsg.Add4ByteUDouble(SecondsSinceMidnight,0.0001);
    N2kMsg.Add8ByteDouble(Latitude,1e-16);
    N2kMsg.Add8ByteDouble(Longitude,1e-16);
    N2kMsg.Add8ByteDouble(Altitude,1e-6);
    N2kMsg.AddByte( (((unsigned char) GNSStype) & 0x0f) | (((unsigned char) GNSSmethod) & 0x0f)<<4 );
    N2kMsg.AddByte(1);  // Integrity 2 bit, reserved 6 bits
    N2kMsg.AddByte(nSatellites);
    N2kMsg.Add2ByteDouble(HDOP,0.01);
    N2kMsg.Add2ByteDouble(PDOP,0.01);
    N2kMsg.Add4ByteDouble(GeoidalSeparation,0.01);
    if (nReferenceStations!=0xff && nReferenceStations>0) {
      N2kMsg.AddByte(1); // Note that we have values for only one reference station, so pass only one values.
      N2kMsg.Add2ByteInt( (((int)ReferenceStationType) & 0x0f) | ReferenceSationID<<4 );
      N2kMsg.Add2ByteUDouble(AgeOfCorrection,0.01);
    } else N2kMsg.AddByte(nReferenceStations);
}

bool ParseN2kPGN129029(const tN2kMsg &N2kMsg, unsigned char &SID, uint16_t &DaysSince1970, double &SecondsSinceMidnight, 
                     double &Latitude, double &Longitude, double &Altitude, 
                     tN2kGNSStype &GNSStype, tN2kGNSSmethod &GNSSmethod,
                     uint8_t &nSatellites, double &HDOP, double &PDOP, double &GeoidalSeparation,
                     uint8_t &nReferenceStations, tN2kGNSStype &ReferenceStationType, uint16_t &ReferenceSationID,
                     double &AgeOfCorrection
                     ) {
  if (N2kMsg.PGN!=129029L) return false;
  int Index=0;
  unsigned char vb;
  int16_t vi;
  
  SID=N2kMsg.GetByte(Index);
  DaysSince1970=N2kMsg.Get2ByteUInt(Index);
  SecondsSinceMidnight=N2kMsg.Get4ByteDouble(0.0001,Index);
  Latitude=N2kMsg.Get8ByteDouble(1e-16,Index);
  Longitude=N2kMsg.Get8ByteDouble(1e-16,Index);
  Altitude=N2kMsg.Get8ByteDouble(1e-6,Index);
  vb=N2kMsg.GetByte(Index); GNSStype=(tN2kGNSStype)(vb & 0x0f); GNSSmethod=(tN2kGNSSmethod)((vb>>4) & 0x0f);
  vb=N2kMsg.GetByte(Index);  // Integrity 2 bit, reserved 6 bits
  nSatellites=N2kMsg.GetByte(Index);
  HDOP=N2kMsg.Get2ByteDouble(0.01,Index);
  PDOP=N2kMsg.Get2ByteDouble(0.01,Index);
  GeoidalSeparation=N2kMsg.Get4ByteDouble(0.01,Index);
  nReferenceStations=N2kMsg.GetByte(Index);
  if (nReferenceStations!=N2kUInt8NA && nReferenceStations>0) {
    // Note that we return real number of stations, but we only have variabes for one.
    vi=N2kMsg.Get2ByteUInt(Index); ReferenceStationType=(tN2kGNSStype)(vi & 0x0f); ReferenceSationID=(vi>>4);
    AgeOfCorrection=N2kMsg.Get2ByteUDouble(0.01,Index);
  } 
  
  return true;
}
                     
//*****************************************************************************
// Cross Track Error
void SetN2kPGN129283(tN2kMsg &N2kMsg, unsigned char SID, tN2kXTEMode XTEMode, bool NavigationTerminated, double XTE) {
    N2kMsg.SetPGN(129283L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(SID);
    N2kMsg.AddByte((char)XTEMode | (NavigationTerminated?0x40:0));
    N2kMsg.Add4ByteDouble(XTE,0.01);
    N2kMsg.AddByte(0xff); // Reserved
    N2kMsg.AddByte(0xff); // Reserved
}

//*****************************************************************************
// Navigation info
void SetN2kPGN129284(tN2kMsg &N2kMsg, unsigned char SID, double DistanceToWaypoint, tN2kHeadingReference BearingReference,
                      bool PerpendicularCrossed, bool ArrivalCircleEntered, tN2kDistanceCalculationType CalculationType,
                      double ETATime, int16_t ETADate, double BearingOriginToDestinationWaypoint, double BearingPositionToDestinationWaypoint,
                      uint8_t OriginWaypointNumber, uint8_t DestinationWaypointNumber, 
                      double DestinationLatitude, double DestinationLongitude, double WaypointClosingVelocity) {
    N2kMsg.SetPGN(129284L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(SID);
    N2kMsg.Add4ByteUDouble(DistanceToWaypoint,0.01);
    N2kMsg.AddByte((char)BearingReference | (PerpendicularCrossed?0x04:0) | (ArrivalCircleEntered?0x10:0)  | (CalculationType==N2kdct_RhumbLine?0x40:0));
    N2kMsg.Add4ByteUDouble(ETATime,0.0001);
    N2kMsg.Add2ByteUInt(ETADate);
    N2kMsg.Add2ByteUDouble(BearingOriginToDestinationWaypoint,0.0001);
    N2kMsg.Add2ByteUDouble(BearingPositionToDestinationWaypoint,0.0001);
    N2kMsg.Add4ByteUInt(OriginWaypointNumber);
    N2kMsg.Add4ByteUInt(DestinationWaypointNumber);
    N2kMsg.Add4ByteDouble(DestinationLatitude,1e-07);
    N2kMsg.Add4ByteDouble(DestinationLongitude,1e-07);
    N2kMsg.Add2ByteDouble(WaypointClosingVelocity,0.01);
}

//*****************************************************************************
// Wind Speed
void SetN2kPGN130306(tN2kMsg &N2kMsg, unsigned char SID, double WindSpeed, double WindAngle, tN2kWindReference WindReference) {
    N2kMsg.SetPGN(130306L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(SID);
    N2kMsg.Add2ByteUDouble(WindSpeed,0.01);
    N2kMsg.Add2ByteUDouble(WindAngle,0.0001);
    N2kMsg.AddByte((unsigned char)WindReference);
    //N2kMsg.AddByte(0xff); // Reserved
    //N2kMsg.AddByte(0xff); // Reserved
}

bool ParseN2kPGN130306(const tN2kMsg &N2kMsg, unsigned char &SID, double &WindSpeed, double &WindAngle, tN2kWindReference &WindReference) {
  if (N2kMsg.PGN!=130306L) return false;
  int Index=0;
  SID=N2kMsg.GetByte(Index);
  WindSpeed=N2kMsg.Get2ByteUDouble(0.01,Index);
  WindAngle=N2kMsg.Get2ByteUDouble(0.0001,Index);
  WindReference=(tN2kWindReference)(N2kMsg.GetByte(Index)&0x07);

  return true;
}

//*****************************************************************************
// Outside Environmental parameters
void SetN2kPGN130310(tN2kMsg &N2kMsg, unsigned char SID, double WaterTemperature,
                     double OutsideAmbientAirTemperature, double AtmosphericPressure) {
    N2kMsg.SetPGN(130310L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(SID);
    N2kMsg.Add2ByteUDouble(WaterTemperature,0.01);
    N2kMsg.Add2ByteUDouble(OutsideAmbientAirTemperature,0.01);
    N2kMsg.Add2ByteUDouble(AtmosphericPressure,1);
    N2kMsg.AddByte(0xff);  // reserved
}
                     
bool ParseN2kPGN130310(const tN2kMsg &N2kMsg, unsigned char &SID, double &WaterTemperature,
                     double &OutsideAmbientAirTemperature, double &AtmosphericPressure) {
  if (N2kMsg.PGN!=130310L) return false;
  int Index=0;
  SID=N2kMsg.GetByte(Index);
  WaterTemperature=N2kMsg.Get2ByteUDouble(0.01,Index);
  OutsideAmbientAirTemperature=N2kMsg.Get2ByteUDouble(0.01,Index);
  AtmosphericPressure=N2kMsg.Get2ByteUDouble(1,Index);
  
  return true;
}                     

                     
//*****************************************************************************
// Environmental parameters
void SetN2kPGN130311(tN2kMsg &N2kMsg, unsigned char SID, tN2kTempSource TempInstance, double Temperature,
                     tN2kHumiditySource HumidityInstance, double Humidity, double AtmosphericPressure) {
    N2kMsg.SetPGN(130311L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(SID);
    N2kMsg.AddByte(((HumidityInstance) & 0x03)<<6 | (TempInstance & 0x3f));
    N2kMsg.Add2ByteUDouble(Temperature,0.01);
    N2kMsg.Add2ByteDouble(Humidity,0.004);
    N2kMsg.Add2ByteUDouble(AtmosphericPressure,1);
}

//*****************************************************************************
// Temperature
// Temperatures should be in Kelvins
void SetN2kPGN130312(tN2kMsg &N2kMsg, unsigned char SID, unsigned char TempInstance, tN2kTempSource TempSource,
                     double ActualTemperature, double SetTemperature) {
    N2kMsg.SetPGN(130312L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(SID);
    N2kMsg.AddByte((unsigned char)TempInstance);
    N2kMsg.AddByte((unsigned char)TempSource);
    N2kMsg.Add2ByteUDouble(ActualTemperature,0.01);
    N2kMsg.Add2ByteUDouble(SetTemperature,0.01);
    N2kMsg.AddByte(0xff); // Reserved
}

bool ParseN2kPGN130312(const tN2kMsg &N2kMsg, unsigned char &SID, unsigned char &TempInstance, tN2kTempSource &TempSource,
                     double &ActualTemperature, double &SetTemperature) {
  if (N2kMsg.PGN!=130312L) return false;
  int Index=0;
  SID=N2kMsg.GetByte(Index);
  TempInstance=N2kMsg.GetByte(Index);
  TempSource=(tN2kTempSource)(N2kMsg.GetByte(Index));
  ActualTemperature=N2kMsg.Get2ByteUDouble(0.01,Index);
  SetTemperature=N2kMsg.Get2ByteUDouble(0.01,Index);
  
  return true;
}

//*****************************************************************************
// Temperature extended range
// Temperatures should be in Kelvins
void SetN2kPGN130316(tN2kMsg &N2kMsg, unsigned char SID, unsigned char TempInstance, tN2kTempSource TempSource,
                     double ActualTemperature, double SetTemperature) {
    N2kMsg.SetPGN(130316L);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(SID);
    N2kMsg.AddByte((unsigned char)TempInstance);
    N2kMsg.AddByte((unsigned char)TempSource);
    N2kMsg.Add3ByteDouble(ActualTemperature,0.001);
    N2kMsg.Add2ByteDouble(SetTemperature,0.1);
}

bool ParseN2kPGN130316(const tN2kMsg &N2kMsg, unsigned char &SID, unsigned char &TempInstance, tN2kTempSource &TempSource,
                     double &ActualTemperature, double &SetTemperature) {
  if (N2kMsg.PGN!=130316L) return false;
  int Index=0;
  SID=N2kMsg.GetByte(Index);
  TempInstance=N2kMsg.GetByte(Index);
  TempSource=(tN2kTempSource)(N2kMsg.GetByte(Index));
  ActualTemperature=N2kMsg.Get3ByteDouble(0.001,Index);
  SetTemperature=N2kMsg.Get2ByteDouble(0.1,Index);
  
  return true;
}


