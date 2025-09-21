#include "stdafx.h"
#include "StageManager.h"

StageManager::StageManager()
{ 

}

StageManager::~StageManager()
{
    // 生成したブロックを全削除
    for (auto obj : m_redBlocks) { DeleteGO(obj); }
    for (auto obj : m_blueBlocks) { DeleteGO(obj); }
    for (auto obj : m_purpleBlocks) { DeleteGO(obj); }
    for (auto obj : m_greenBlocks) { DeleteGO(obj); }
}

bool StageManager::Start()
{
    // --- ブロック種類をリストに追加（合計75個） ---
    std::vector<std::string> blockTypes;
    blockTypes.insert(blockTypes.end(), numRed, "red");
    blockTypes.insert(blockTypes.end(), numBlue, "blue");
    blockTypes.insert(blockTypes.end(), numPurple, "purple");
    blockTypes.insert(blockTypes.end(), numGreen, "green");

    // --- ランダムシャッフル ---
    std::random_device rd;
    std::mt19937 mt(rd());
    std::shuffle(blockTypes.begin(), blockTypes.end(), mt);

    // --- 中心揃え用オフセット ---
    float offsetX = -(numX - 1) * spacingX * 0.5f;
    float offsetZ = -(numZ - 1) * spacingZ * 0.5f;

    // --- グリッド配置 ---
    int idx = 0;
    for (int z = 0; z < numZ; z++)
    {
        for (int x = 0; x < numX; x++)
        {
            if (idx >= (int)blockTypes.size()) break;

            float posX = baseX + offsetX + x * spacingX;
            float posZ = baseZ + offsetZ + z * spacingZ;
            Vector3 pos = { posX, 0.0f, posZ };

            if (blockTypes[idx] == "red")
            {
                auto obj = NewGO<red>(0, "red");
                obj->SetPosition(pos);
                m_redBlocks.push_back(obj);
            }
            else if (blockTypes[idx] == "blue")
            {
                auto obj = NewGO<blue>(0, "blue");
                obj->SetPosition(pos);
                m_blueBlocks.push_back(obj);
            }
            else if (blockTypes[idx] == "purple")
            {
                auto obj = NewGO<purple>(0, "purple");
                obj->SetPosition(pos);
                m_purpleBlocks.push_back(obj);
            }
            else if (blockTypes[idx] == "green")
            {
                auto obj = NewGO<green>(0, "green");
                obj->SetPosition(pos);
                m_greenBlocks.push_back(obj);
            }

            idx++;
        }
    }

    return true;
}

void StageManager::Update()
{

}

void StageManager::Render(RenderContext& rc)
{

}

