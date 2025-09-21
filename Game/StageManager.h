#pragma once
#include "red.h"
#include "blue.h"
#include "purple.h"
#include "green.h"
#include <random>
#include <vector>

class StageManager : public IGameObject
{
public:
    StageManager();
    ~StageManager();
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

private:
    // 各ブロックをまとめるリスト
    std::vector<red*>    m_redBlocks;
    std::vector<blue*>   m_blueBlocks;
    std::vector<purple*> m_purpleBlocks;
    std::vector<green*>  m_greenBlocks;

    // 配置数（固定）
    static constexpr int numRed = 5;
    static constexpr int numBlue = 15;
    static constexpr int numPurple = 15;
    static constexpr int numGreen = 40;

    // グリッド配置
    static constexpr int numX = 5;   // 横方向
    static constexpr int numZ = 15;  // 奥方向
    static constexpr float blockSizeX = 175.0f;
    static constexpr float blockSizeZ = 175.0f;
    static constexpr float spacingX = blockSizeX + 5.0f;
    static constexpr float spacingZ = blockSizeZ + 5.0f;

    // 基準位置（全体を動かす場合）
    static constexpr float baseX = 0.0f;
    static constexpr float baseZ = -2000.0f;
};

