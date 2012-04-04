/*
 * Copyright (c) 2011-2012, The Mineserver Project
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 * Neither the name of the The Mineserver Project nor the
 *  names of its contributors may be used to endorse or promote products
 *  derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*This will generate all the terrain for
the map. This includes mountains and flats
ect. I am going to use libnoise for now.*/

#include <mineserver/world/generator/terrain.h>

bool worldGeneration::terrainGen::noiseInit(long seed)//libnoise uses int while seed is long not to sure what i should do here
{
  using namespace noise;

  //noise::module::DEFAULT_BIAS = 64;
  //noise::module::DEFAULT_SCALE = 64;

  terrainHieght.SetFrequency(0.0025);
  terrainHieght.SetSeed(seed+1);
  terrainHieght.SetOctaveCount(3);

  tempratureBase.SetFrequency(0.0025);
  tempratureBase.SetSeed(seed+2);
  tempratureBase.SetOctaveCount(3);

  rainfall.SetFrequency(0.0025);
  rainfall.SetSeed(seed+3);
  rainfall.SetOctaveCount(3);

  hieghtScale.SetSourceModule(0,terrainHieght);
  hieghtScale.SetBias(0.0);
  hieghtScale.SetScale(0.5);

  temprature.SetSourceModule(0,hieghtScale);
  temprature.SetSourceModule(1,tempratureBase);


  ocean.SetFrequency(0.01);
  ocean.SetOctaveCount(6);
  ocean.SetSeed(seed+123);

  flatLand.SetFrequency(0.01);
  flatLand.SetOctaveCount(4);
  flatLand.SetSeed(seed+4);

  hill.SetFrequency(0.01);
  hill.SetOctaveCount(5);
  hill.SetSeed(seed+94);

  highLand.SetFrequency(0.01);
  highLand.SetOctaveCount(4);
  highLand.SetSeed(seed+41);

  mountain.SetFrequency(0.01);
  mountain.SetOctaveCount(5);
  mountain.SetSeed(seed+1312);



  oceanScale.SetSourceModule(0,ocean);
  oceanScale.SetBias(30);
  oceanScale.SetScale(10);

  flatLandScale.SetSourceModule(0,flatLand);
  flatLandScale.SetBias(44);
  flatLandScale.SetScale(7);

  hillScale.SetSourceModule(0,hill);
  hillScale.SetBias(60);
  hillScale.SetScale(15);

  highLandScale.SetSourceModule(0,highLand);
  highLandScale.SetBias(90);
  highLandScale.SetScale(7);

  mountainScale.SetSourceModule(0,mountain);
  mountainScale.SetBias(84);
  mountainScale.SetScale(36);

  oceanFlatSelect.SetSourceModule(0, oceanScale);
  oceanFlatSelect.SetSourceModule(1, flatLandScale);
  oceanFlatSelect.SetControlModule(terrainHieght);
  oceanFlatSelect.SetBounds(-0.45,0.0);
  oceanFlatSelect.SetEdgeFalloff(0.25);

  hillSelect.SetSourceModule(0, oceanFlatSelect);
  hillSelect.SetSourceModule(1, hillScale);
  hillSelect.SetControlModule(terrainHieght);
  hillSelect.SetBounds(0.0,0.35);
  hillSelect.SetEdgeFalloff(0.5);

  highLandSelect.SetSourceModule(0, hillSelect);
  highLandSelect.SetSourceModule(1, highLandScale);
  highLandSelect.SetControlModule(terrainHieght);
  highLandSelect.SetBounds(0.35,0.55);
  highLandSelect.SetEdgeFalloff(0.5);

  mountainSelect.SetSourceModule(0, highLandSelect);
  mountainSelect.SetSourceModule(1, mountainScale);
  mountainSelect.SetControlModule(terrainHieght);
  mountainSelect.SetBounds(0.55,1000.0);
  mountainSelect.SetEdgeFalloff(0.25);

  //river.SetFrequency(0.010);
  //river.SetOctaveCount (1);
  //river.SetLacunarity(2.123);

  //riverScale.SetSourceModule (0, river);
  //riverScale.SetScale (-0.2);
  //riverScale.SetBias (0.2);

  //riverConst.SetConstValue (0.0);

  //riverBlend.SetSourceModule (0, riverConst);
  //riverBlend.SetSourceModule (1, mountainSelect);
  //riverBlend.SetControlModule (riverScale);


  /*mountainSteep.SetFrequency(0.014);
  mountainSteep.SetOctaveCount(5);
  mountainSteep.SetSeed(seed+94);

  mountain.SetFrequency(0.004);
  mountain.SetOctaveCount(5);
  mountain.SetSeed(seed+1);

  mountainType.SetFrequency (0.002);
  mountainType.SetPersistence (0.25);
  mountainType.SetSeed(seed+2);

  mountainSelect.SetSourceModule(0,mountainSteep);
  mountainSelect.SetSourceModule(1,mountain);
  mountainSelect.SetControlModule (mountainType);
  mountainSelect.SetBounds (0.0, 1000.0);
  mountainSelect.SetEdgeFalloff (0.5);

  moutainVally.SetFrequency(0.016);
  moutainVally.SetOctaveCount (1);

  mountainVallyScale.SetSourceModule (0, moutainVally);
  mountainVallyScale.SetScale (-2.0);
  mountainVallyScale.SetBias (-0.5);

  mountainVallyConst.SetConstValue (-1.0);

  blendMountainVally.SetSourceModule (0, mountainVallyConst);
  blendMountainVally.SetSourceModule (1, mountainSelect);
  blendMountainVally.SetControlModule (mountainVallyScale);

  //mountainCliff.SetFrequency(0.04);
  //mountainCliff.SetOctaveCount(2);
  //mountainCliff.SetPersistence(0.75);

  mountainTurb.SetSourceModule(0,blendMountainVally);
  mountainTurb.SetFrequency (4.0);
  mountainTurb.SetPower (0.125);
  mountainTurb.SetSeed(seed+3);

  mountainScale.SetSourceModule(0, mountainTurb);
  mountainScale.SetScale(40);
  mountainScale.SetBias(70);


  flatLands.SetFrequency(0.01);
  flatLands.SetOctaveCount(4);
  flatLands.SetSeed(seed+4);

  flatScale.SetSourceModule(0,flatLands);
  flatScale.SetScale(7);
  flatScale.SetBias(44);



  ocean.SetFrequency(0.01);
  ocean.SetOctaveCount(6);
  ocean.SetSeed(seed+5);

  oceanScale.SetSourceModule(0,ocean);
  oceanScale.SetScale(10);
  oceanScale.SetBias(30);



  oceanAndFlatType.SetFrequency(0.002);
  oceanAndFlatType.SetPersistence (0.25);
  oceanAndFlatType.SetSeed(seed+6);

  oceanAndFlatSelector.SetSourceModule(0,oceanScale);
  oceanAndFlatSelector.SetSourceModule(1,flatScale);
  oceanAndFlatSelector.SetControlModule (oceanAndFlatType);
  oceanAndFlatSelector.SetBounds (0.0, 1000.0);
  oceanAndFlatSelector.SetEdgeFalloff(0.25);

  finalType.SetFrequency(0.002);
  finalType.SetPersistence (0.25);
  finalType.SetSeed(seed+7);

  finalSelector.SetSourceModule(0,oceanAndFlatSelector);
  finalSelector.SetSourceModule(1,mountainScale);
  finalSelector.SetControlModule (finalType);
  finalSelector.SetBounds (0.4, 1000.0);
  finalSelector.SetEdgeFalloff(0.125);  */

  return true;
}

int32_t (&worldGeneration::terrainGen::noiseWrite( int32_t(&heightMap)[16][16], int32_t cX,int32_t cZ))[16][16]
{

  int32_t xBlockpos = cX << 4;
  int32_t zBlockpos = cZ << 4;

  for(int32_t x=0;x<16;x++)
  {
    for(int32_t z=0;z<16;z++)
    {
      heightMap[x][z] = (int32_t)(mountainSelect.GetValue(xBlockpos +x, 0, zBlockpos + z));
    }
  }
  return heightMap;
}
