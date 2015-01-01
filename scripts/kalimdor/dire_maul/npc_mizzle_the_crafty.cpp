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
SDName: npc_mizzle_the_crafty
SD%Complete: 100
SDComment: -
SDCategory: Dire Maul
EndScriptData */

#include "precompiled.h"
#include "escort_ai.h"
#include "dire_maul.h"

enum
{
    SAY_KING_DEAD_1          = -1999925,
    SAY_KING_DEAD_2          = -1999926,
	
    GOSSIP_GORDOK_BUFF       = -3509002,
    GOSSIP_GORDOK_BUFF_SUB   = -3509003,
    GOSSIP_TRIBUTE_CHEST     = -3509004,
    GOSSIP_TRIBUTE_CHEST_SUB = -3509005,
};

struct npc_mizzle_the_craftyAI : public npc_escortAI
{
    npc_mizzle_the_craftyAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset() override
    {
        Start(true, NULL, NULL, false, false);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
    }

    void WaypointStart(uint32 uiPointId)
    {
        switch (uiPointId)
        {
            case 0:
                DoScriptText(SAY_KING_DEAD_1, m_creature);
                break;
        }
    }

    void WaypointReached(uint32 uiPoint) override
    {
        switch (uiPoint)
        {
            case 2:
                SetEscortPaused(true);
                DoScriptText(SAY_KING_DEAD_2, m_creature);
                m_creature->SetFacingTo(3.159046f);
                m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                break;
        }
    }
};

CreatureAI* GetAI_npc_mizzle_the_crafty(Creature* pCreature)
{
    return new npc_mizzle_the_craftyAI(pCreature);
}

bool GossipHello_npc_mizzle_the_crafty(Player* pPlayer, Creature* pCreature)
{
    if (!pPlayer->HasAura(SPELL_KING_GORDOK))
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_GORDOK_BUFF, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0);
    else if (pPlayer->HasAura(SPELL_KING_GORDOK))
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_TRIBUTE_CHEST, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_npc_mizzle_the_crafty(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 0:
            if (!pPlayer->HasAura(SPELL_KING_GORDOK))
                pCreature->CastSpell(pPlayer, SPELL_KING_GORDOK, false);
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_GORDOK_BUFF_SUB, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_TRIBUTE_CHEST_SUB, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            ScriptedInstance* m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

            if (m_pInstance->GetData(TYPE_TRIBUTE) == NOT_STARTED)
            {
                m_pInstance->DoRespawnGameObject(GO_GORDOK_TRIBUTE, 2 * HOUR);
                m_pInstance->SetData(TYPE_TRIBUTE, DONE);
            }

            pPlayer->CLOSE_GOSSIP_MENU();
            break;
    }

    return true;
}

void AddSC_npc_mizzle_the_crafty()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_mizzle_the_crafty";
    pNewScript->pGossipHello = &GossipHello_npc_mizzle_the_crafty;
    pNewScript->pGossipSelect = &GossipSelect_npc_mizzle_the_crafty;
    pNewScript->GetAI = &GetAI_npc_mizzle_the_crafty;
    pNewScript->RegisterSelf();
}
