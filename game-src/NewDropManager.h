#pragma once
class CNewDropManager : public singleton<CNewDropManager>
{
    using tDropInfo = struct sDropInfo {
        std::string     qfName;
        DWORD           dwMobVnum;
        BYTE            bMobCount;
        DWORD           dwItemVnum;
        BYTE            bItemCount;
    };
    using DROP_VEC = std::vector<tDropInfo>;
public:
    auto    Initialize() -> void;
    auto    NewDropKillAction(LPCHARACTER killer, DWORD dwMobVnum) -> void;

private:
    DROP_VEC        d_vec;
};