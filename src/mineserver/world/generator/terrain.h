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

#include <noise/noise.h>
#include <boost/shared_ptr.hpp>

namespace worldGeneration
{
  class terrainGen
  {

    noise::module::RidgedMulti mountainTerrain;
//     noise::module::ScaleBias mountainScale;
    noise::module::Billow baseFlatTerrain;
    noise::module::ScaleBias flatTerrain;
    noise::module::Perlin terrainType;
    noise::module::Select terrainSelector;
    noise::module::ScaleBias finalTerrain;

// Tims code
    noise::module::Perlin terrainHieght;
    noise::module::Perlin rainfall;
    noise::module::Perlin tempratureBase;
    noise::module::ScaleBias hieghtScale;
    noise::module::Add temprature;

    noise::module::Perlin ocean;
    noise::module::Billow flatLand;
    noise::module::Perlin hill;
    noise::module::Billow highLand;
    noise::module::RidgedMulti mountain;

    noise::module::ScaleBias oceanScale;
    noise::module::ScaleBias flatLandScale;
    noise::module::ScaleBias hillScale;
    noise::module::ScaleBias highLandScale;
    noise::module::ScaleBias mountainScale;

    noise::module::Select oceanFlatSelect;
    noise::module::Select hillSelect;
    noise::module::Select highLandSelect;
    noise::module::Select mountainSelect;

    //noise::module::RidgedMulti river;
    //noise::module::ScaleBias riverScale;
    //noise::module::Const riverConst;
    //noise::module::Blend riverBlend;

   /*noise::module::RidgedMulti mountain;
    noise::module::Perlin mountainType;
    //noise::module::Select mountainSelect;
    noise::module::RidgedMulti moutainVally;
    noise::module::ScaleBias mountainVallyScale;
    noise::module::Const mountainVallyConst;
    noise::module::Blend blendMountainVally;

    //noise::module::Multiply multMoutain;
    //noise::module::Perlin mountainCliff;


    noise::module::Turbulence mountainTurb;
    noise::module::ScaleBias mountainScale;

    noise::module::Billow flatLands;
    noise::module::ScaleBias flatScale;

    noise::module::Perlin ocean;
    noise::module::ScaleBias oceanScale;

    noise::module::Perlin oceanAndFlatType;
    noise::module::Select oceanAndFlatSelector;
    noise::module::Perlin finalType;
    noise::module::Select finalSelector;*/

    long noiseSeed;
    public:

    int32_t (&noiseWrite(int32_t(&heightMap)[16][16], int32_t cX,int32_t cZ))[16][16];//not to sure about this

    bool noiseInit(long seed);
  };
}
