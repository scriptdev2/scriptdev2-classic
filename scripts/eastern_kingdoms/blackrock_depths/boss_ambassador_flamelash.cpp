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
SDName: Boss_Ambassador_Flamelash
SD%Complete: 100
SDComment: -
SDCategory: Blackrock Depths
EndScriptData */

#include "precompiled.h"
#include "blackrock_depths.h"

enum
{
    SPELL_FIRE_BLAST            = 15573,
    SPELL_BURNING_SPIRIT_ADD    = 13489,
    SPELL_BURNING_SPIRIT_BOSS   = 14744,

    BURNING_SPIRIT_DISTANCE     = 1,
};

struct boss_ambassador_flamelashAI : public ScriptedAI
{
    boss_ambassador_flamelashAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    GameObject* pGObject;
    uint32 m_uiSpiritTimer[MAX_RUNES];

    void Reset() override
    {
        DoCastSpellIfCan(m_creature, SPELL_FIRE_BLAST, CAST_TRIGGERED | CAST_AURA_NOT_PRESENT);

        for (int i = 0; i < MAX_RUNES; i++)
            m_uiSpiritTimer[i] = urand(0 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
    }

    void Aggro(Unit* /*pWho*/) override
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_FLAMELASH, IN_PROGRESS);

        DoCastSpellIfCan(m_creature, SPELL_FIRE_BLAST, CAST_TRIGGERED | CAST_AURA_NOT_PRESENT);
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_FLAMELASH, DONE);
    }

    void EnterEvadeMode() override
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_FLAMELASH, FAIL);

        ScriptedAI::EnterEvadeMode();
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // m_uiSpiritTimer
        for (int i = 0; i < MAX_RUNES; i++)
        {
            if (m_uiSpiritTimer[i] < uiDiff)
            {
                pGObject = m_pInstance->GetSingleGameObjectFromStorage(GO_DWARFRUNE_A01 + i);
                m_creature->SummonCreature(NPC_BURNING_SPIRIT, pGObject->GetPositionX(), pGObject->GetPositionY(), pGObject->GetPositionZ(), pGObject->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0, true);
                m_uiSpiritTimer[i] = urand(15 * IN_MILLISECONDS, 30 * IN_MILLISECONDS);
            }
            else
                m_uiSpiritTimer[i] -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

bool EffectDummyCreature_spell_boss_ambassador_flamelash(Unit* /*pCaster*/, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* pCreatureTarget, ObjectGuid /*originalCasterGuid*/)
{
    if (uiSpellId == SPELL_BURNING_SPIRIT_ADD && uiEffIndex == EFFECT_INDEX_1)
    {
        pCreatureTarget->CastSpell(pCreatureTarget, SPELL_BURNING_SPIRIT_BOSS, true);
        return true;
    }

    return false;
}

struct npc_burning_spiritAI : public ScriptedAI
{
    npc_burning_spiritAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    Creature* pCreature;

    void Reset() override
    {

    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            pCreature = m_pInstance->GetSingleCreatureFromStorage(NPC_FLAMELASH);

            if (m_creature->IsWithinDist2d(pCreature->GetPositionX(), pCreature->GetPositionY(), BURNING_SPIRIT_DISTANCE))
                DoCastSpellIfCan(pCreature, SPELL_BURNING_SPIRIT_ADD, CAST_TRIGGERED);
            else
                m_creature->GetMotionMaster()->MovePoint(1, pCreature->GetPositionX(), pCreature->GetPositionY(), pCreature->GetPositionZ(), true);
            return;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_ambassador_flamelash(Creature* pCreature)
{
    return new boss_ambassador_flamelashAI(pCreature);
}

CreatureAI* GetAI_npc_burning_spirit(Creature* pCreature)
{
    return new npc_burning_spiritAI(pCreature);
}

void AddSC_boss_ambassador_flamelash()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_ambassador_flamelash";
    pNewScript->GetAI = &GetAI_boss_ambassador_flamelash;
    pNewScript->pEffectDummyNPC = &EffectDummyCreature_spell_boss_ambassador_flamelash;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_burning_spirit";
    pNewScript->GetAI = &GetAI_npc_burning_spirit;
    pNewScript->RegisterSelf();
}
