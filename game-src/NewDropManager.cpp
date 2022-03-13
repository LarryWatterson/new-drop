/**************************
* * Author: Larry Watterson *
* ? Date: x ?
* ! Version: x !
***************************/
#include "stdafx.h"
#ifdef NEW_DROP_MANAGER
#include "NewDropManager.h"
#include "char.h"
#include "db.h"

#define LOGS
const std::string qf_ = "kill_drop.";

auto CNewDropManager::Initialize() -> void {
    const std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT * FROM newdrop_info"));
    if (pMsg->Get()->uiNumRows==0) {
        sys_err("NewDrop tablosu bos!");
        return;
    }
    MYSQL_ROW row;
    tDropInfo   info;
    d_vec.reserve(pMsg->Get()->uiNumRows);
    while (nullptr != (row = mysql_fetch_row(pMsg->Get()->pSQLResult))) {
        WORD col = 0;
        info.qfName = qf_ + row[col++];
        str_to_number(info.dwMobVnum, row[col++]);
        str_to_number(info.bMobCount, row[col++]);
        str_to_number(info.dwItemVnum, row[col++]);
        str_to_number(info.bItemCount, row[col++]);
        d_vec.emplace_back(info);
    }

#ifdef LOGS
    for (const auto& it : d_vec) {
        sys_err("%s - %d - %d - %d - %d", it.qfName.c_str(), it.dwMobVnum, it.bMobCount, it.dwItemVnum, it.bItemCount);
    }
#endif
}

auto CNewDropManager::NewDropKillAction(LPCHARACTER killer, const DWORD dwMobVnum) -> void {
    if (const auto& it = std::find_if(d_vec.cbegin, d_vec.cend(),
						[&dwMobVnum] (const auto &p) { return p.dwMobVnum == dwMobVnum; }); it != d_vec.cend()) {
        const auto killedCount = killer->GetQuestFlag(it->qfName) + 1;
        killer->SetQuestFlag(it->qfName, killedCount);
        if (killedCount >= it->bMobCount) {
            killer->SetQuestFlag(it->qfName, 0);
            killer->AutoGiveItem(it->dwItemVnum, it->bItemCount);
        }
        else {
            killer->SetQuestFlag(it->qfName, killedCount);
            killer->ChatPacket(1, "You must kill %d more for reward.", it->bMobCount - killedCount);
        }
    }
}
#endif