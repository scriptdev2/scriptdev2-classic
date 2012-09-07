/* Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
* This program is free software licensed under GPL version 2
* Please see the included DOCS/LICENSE.TXT for more information */

#ifndef SC_PRECOMPILED_H
#define SC_PRECOMPILED_H

#include "../ScriptMgr.h"
#include "Object.h"
#include "Unit.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "GameObject.h"
#include "sc_creature.h"
#include "sc_gossip.h"
#include "sc_grid_searchers.h"
#include "sc_instance.h"
#include "SpellAuras.h"

#ifdef WIN32
#  include <windows.h>
    BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
    {
        return true;
    }
#endif

// Backport helpers
typedef std::list<ObjectGuid> GuidList;
typedef std::vector<ObjectGuid> GuidVector;
typedef std::set<ObjectGuid> GuidSet;

#define SetLevitateTRUE         AddSplineFlag(SPLINEFLAG_FLYING)
#define SetLevitateFALSE        RemoveSplineFlag(SPLINEFLAG_FLYING)
#define SetWalkTRUE             AddSplineFlag(SPLINEFLAG_WALKMODE)
#define SetWalkFALSE            RemoveSplineFlag(SPLINEFLAG_WALKMODE)

#define IsFlying()              HasSplineFlag(SPLINEFLAG_FLYING)
#define IsLevitating()          HasSplineFlag(SPLINEFLAG_FLYING)

#define UNIT_BYTE1_FLAG_UNK_2   0
#define AREA_FLAG_LOWLEVEL      0

// only used with remove mode, hence ok this way
#define AURA_STATE_HEALTHLESS_35_PERCENT  AURA_STATE_HEALTHLESS_20_PERCENT

#define SelectAttackingTarget(a, b, c, d)       SelectAttackingTarget(a, b)
#define MoveRandomAroundPoint(x, y, z, range)   MoveIdle()
#define PlayDirectSoundToMap(a, b)              PlayDirectSoundToMap(a)

// sc_gossip.h:             ADD_GOSSIP_ITEM_EXTENDED outcommented box-money (Required until professions are fixed)
// item_scripts.cpp:        Remove scripts with SendCastResult
// sc_creature.cpp:         Used in ScriptedAI::SelectSpell, outcommented SchoolMask
// sc_grid_searchers.cpp:   NearestCreatureEntryWithLiveStateInObjectRangeCheck - outcommented bOnlyDead (REQUIRED core backport)
//                          Replace AllCreaturesOfEntryInRangeCheck with MaNGOS::AllCreaturesOfEntryInRangeCheck after 11962
// escort_ai.cpp:           Replaced SetWalk(!m_bIsRunning) (2 times)

#endif
