/**
 * @file BaseApplication.hpp
 * @brief 
 * @author 邹浩 (zouhaodata@gmail.com)
 * @version 1.0.0
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021  UpPower Studio
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version   <th>Author   <th>Description
 * <tr><td>2021-06-18 <td>1.0.0     <td>邹浩     <td>内容
 * </table>
 */
#pragma once
#include "Core/GraphicConfig.hpp"

namespace UpPower
{
    class BaseApplication
    {
    public:
        BaseApplication(GraphicConfig& cfg);
        /// @brief 引擎初始化
        /// @return 返回0正确初始化，返回其他值初始化错误
        virtual int DoInit();
        virtual void DoTick();
        virtual void DoFinalize();
        virtual bool IsQuit();

        inline GraphicConfig& GetConfig() { return m_iConfig; };

    protected:
        virtual void OnDraw() {};

    protected:
        static bool m_bQuit;
        GraphicConfig m_iConfig;

    private:
        BaseApplication(){};
    };
}