/* This file is part of the ScriptDev2 Project. See AUTHORS file for Copyright information
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Undercity
SD%Complete: 95
SDComment: Quest support: 9180(post-event).
SDCategory: Undercity
EndScriptData */

/* ContentData
npc_lady_sylvanas_windrunner
EndContentData */

#include "precompiled.h"

/*######
## npc_lady_sylvanas_windrunner
######*/

struct MANGOS_DLL_DECL npc_lady_sylvanas_windrunnerAI : public ScriptedAI
{
    npc_lady_sylvanas_windrunnerAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }

    void Reset() override
    {
    }
};

CreatureAI* GetAI_npc_lady_sylvanas_windrunner(Creature* pCreature)
{
    return new npc_lady_sylvanas_windrunnerAI(pCreature);
}

void AddSC_undercity()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_lady_sylvanas_windrunner";
    pNewScript->GetAI = &GetAI_npc_lady_sylvanas_windrunner;
    pNewScript->RegisterSelf();
}
